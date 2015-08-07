PROJECT(ColorControlApp)

cmake_minimum_required(VERSION 3.0)

OPTION(BUILD_COCO_GUI "Build the CoCo GUI." ON)
IF( BUILD_COCO_GUI )
	# The GUI needs wxWidgets.
	FIND_PACKAGE(wxWidgets REQUIRED adv propgrid net gl core base)
	INCLUDE(${wxWidgets_USE_FILE})

	# This is the list of source files. They will be compiled.
	SET(SRC_LIST
		src/ColorControlMain.cpp
		src/ColorControlApp.cpp
		src/CDevice.cpp
		src/CLua.cpp
		src/CSensorData.cpp
		src/CTestGeneration.cpp
		src/GUIFrame.cpp
		src/PanelTestrow.cpp
		src/PanelSensor.cpp)

	# This is the list of headers.
	SET(HDR_LIST
		include/ColorControlMain.h
		include/ColorControlApp.h
		include/CDevice.h
		include/CLua.h
		include/CSensorData.h
		include/CTestGeneration
		include/GUIFrame.h
		include/PanelTestrow.h
		include/PanelSensor.h)

	ADD_EXECUTABLE(ColorControl ${SRC_LIST})
	TARGET_LINK_LIBRARIES(ColorControl ${LUA_LIBRARIES} ${wxWidgets_LIBRARIES})
	TARGET_INCLUDE_DIRECTORIES(ColorControl PRIVATE include ${LUA_INCLUDE_DIR})
ELSE( BUILD_COCO_GUI )
	MESSAGE(STATUS "Building the CoCo GUI was disabled.")
ENDIF( BUILD_COCO_GUI )
