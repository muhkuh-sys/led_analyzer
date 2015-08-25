cmake_minimum_required(VERSION 2.8)

PROJECT("led_analyzer")

INCLUDE(ExternalProject)


GET_FILENAME_COMPONENT(COCO_WIN32_INSTALL "../../build_windows32" ABSOLUTE)
GET_FILENAME_COMPONENT(COCO_WIN64_INSTALL "../../build_windows64" ABSOLUTE)
GET_FILENAME_COMPONENT(LED_ANALYZER_LUA "../../modules/led_analyzer" ABSOLUTE)
GET_FILENAME_COMPONENT(COCO_ICONS       "../../ColorControl/pic" ABSOLUTE)

# set installation directories 
SET(INSTALL_DIR_LUA_MODULES lua_plugins)
SET(INSTALL_DIR_LUA_SCRIPTS lua)


#include the cmake files 
#version 
INCLUDE(../../cmake/versions.cmake)
INCLUDE(../../cmake/version.cmake)


# Led_Analyzer Version number
SET(CPACK_PACKAGE_VERSION_MAJOR ${COCO_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${COCO_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${COCO_VERSION_PATH})
SET(VERSION_FULL ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})


SET(PACKAGE_CMAKE_ARGS "")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCOCO_WIN32_INSTALL=${COCO_WIN32_INSTALL}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCOCO_WIN64_INSTALL=${COCO_WIN64_INSTALL}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCOCO_WIN64_INSTALL=${COCO_WIN64_INSTALL}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DLED_ANALYZER_LUA=${LED_ANALYZER_LUA}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCOCO_ICONS=${COCO_ICONS}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DINSTALL_DIR_LUA_MODULES=${INSTALL_DIR_LUA_MODULES}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DINSTALL_DIR_LUA_SCRIPTS=${INSTALL_DIR_LUA_SCRIPTS}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCPACK_PACKAGE_VERSION_MAJOR=${CPACK_PACKAGE_VERSION_MAJOR}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCPACK_PACKAGE_VERSION_MINOR=${CPACK_PACKAGE_VERSION_MINOR}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DCPACK_PACKAGE_VERSION_PATCH=${CPACK_PACKAGE_VERSION_PATCH}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DVERSION_FULL=${VERSION_FULL}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DPROJECT_VERSION_VCS=${PROJECT_VERSION_VCS}")
LIST(APPEND PACKAGE_CMAKE_ARGS "-DARTIFACT_LISTS_OUTPUT=${CMAKE_CURRENT_BINARY_DIR}/artifacts")

ExternalProject_Add(TARGET_led_analyzer
                    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/led_analyzer
                    CMAKE_ARGS ${PACKAGE_CMAKE_ARGS}
                    INSTALL_COMMAND make package
)


#----------------------------------------------------------------------------
#
# Copy the artifacts to a filename without the version number.
# This is needed for the part in the travis.ci script where
# the deploy to "GitHub releases" is configured. It is only
# possible to use fixed filenames there.
#
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/TARGET_led_analyzer-prefix/src/TARGET_led_analyzer-build/led_analyzer-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.zip
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
	RENAME led_analyzer.zip
)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/TARGET_led_analyzer-prefix/src/TARGET_led_analyzer-build/ivy-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.xml
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
	RENAME ivy.xml
)



#----------------------------------------------------------------------------
#
# Copy the artifacts to a local repository. This is needed for the coco_gui
# installer.
#
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/TARGET_led_analyzer-prefix/src/TARGET_led_analyzer-build/led_analyzer-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.zip
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/repository/org/muhkuh/tools/led_analyzer/${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}/
)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/TARGET_led_analyzer-prefix/src/TARGET_led_analyzer-build/ivy-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}.xml
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/repository/org/muhkuh/tools/led_analyzer/${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}/
)



#----------------------------------------------------------------------------
#
# Construct the installer for the GUI application.
# This will be placed in the folder "coco_gui". Execute "ant bootstrap" and
# "ant" there to build the package.
#
CONFIGURE_FILE(coco_gui/artifacts_coco_gui.xml  ${CMAKE_CURRENT_BINARY_DIR}/artifacts/artifacts_coco_gui.xml  @ONLY)
CONFIGURE_FILE(coco_gui/build.xml               ${CMAKE_CURRENT_BINARY_DIR}/coco_gui/build.xml                @ONLY)
CONFIGURE_FILE(coco_gui/ivy.xml                 ${CMAKE_CURRENT_BINARY_DIR}/coco_gui/ivy.xml                  @ONLY)
CONFIGURE_FILE(coco_gui/ivysettings.xml         ${CMAKE_CURRENT_BINARY_DIR}/coco_gui/ivysettings.xml          @ONLY)

