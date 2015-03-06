cmake_minimum_required(VERSION 2.8)
#libftdi as external project

#----------------------------------------------------------------------------
#
# This script provides the libusb parts to the build process.
#
# 1) It depacks the archiv.
# 2) Eventually compile the sources.
# 3) It provides all necessary variables to link the library.
#
# The provided variables are:
#
#  LIBFTDI_LIBRARIES : The libusb library with the complete path and all
#                     required system libraries. The list must be separated
#                     with whitespace.
#
#  LIBFTDI_DEFINES : All defines for the libusb library. This should be a
#                   list of entries starting with "-D".
#
#  LIBFTDI_INCLUDE_DIRECTORIES : The include folders for the library headers.
#                               The list must be separated with whitespace.
#

PROJECT("libftdi")

INCLUDE(ExternalProject)


#----------------------------------------------------------------------------
#
# Build the project.
#




#SET(LIBUSB_CMAKE_ARGS "")
#list baut eine ganze zeile aus den sachen die mit append hinzugefügt wurden 
LIST(APPEND LIBFTDI_CMAKE_ARGS "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
LIST(APPEND LIBFTDI_CMAKE_ARGS "-DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
LIST(APPEND LIBFTDI_CMAKE_ARGS "-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}")
LIST(APPEND LIBFTDI_CMAKE_ARGS "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")
IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	LIST(APPEND LIBUSB_CMAKE_ARGS "-DCMAKE_RC_COMPILER=${CMAKE_RC_COMPILER}")
ENDIF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

#SET(LIBUSB_INCLUDE_DIR C:/Users/subhan/Desktop/led_analyzer/testbin/external/libusb/libusb-1.0.19/install/include/libusb-1.0)
#SET(LIBUSB_LIBRARIES C:/Users/subhan/Desktop/led_analyzer/testbin/external/libusb/libusb-1.0.19/install/lib/libusb.a) 

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../libusb/libusb-1.0.19/install/include/libusb-1.0)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../libusb/libusb-1.0.19/install/lib)

SET(LIBUSB_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../libusb/libusb-1.0.19/install/include/libusb-1.0)
SET(LIBUSB_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/../libusb/libusb-1.0.19/install/lib/libusb.a)

LIST(APPEND LIBUSB_PATHS "${LIBUSB_INCLUDE_DIR}")
LIST(APPEND LIBUSB_PATHS "${LIBUSB_LIBRARIES}")


ExternalProject_Add(TARGET_libftdi
					DEPENDS TARGET_libusb
					#download
					PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libftdi1-1.2
                    URL ${CMAKE_CURRENT_SOURCE_DIR}/libftdi1-1.2.tar.bz2
                    #configure 
					PATCH_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/templates ${CMAKE_CURRENT_BINARY_DIR}/libftdi1-1.2/src/TARGET_libftdi
                    CMAKE_ARGS ${LIBFTDI_CMAKE_ARGS} -DLIBUSB_INCLUDE_DIR=${CMAKE_CURRENT_BINARY_DIR}/../libusb/libusb-1.0.19/install/include/libusb-1.0 -DLIBUSB_LIBRARIES=${CMAKE_CURRENT_BINARY_DIR}/../libusb/libusb-1.0.19/install/lib/libusb.a
                    INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install DESTDIR=${CMAKE_CURRENT_BINARY_DIR}/libftdi1-1.2
)

# LIBUSB_INCLUDE_DIR needs the path to the libusb header file
# DLIBUSB_LIBRARIES needs the path AND the static library of libusb
#SET(LIBUSB_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../libusb/lib/libusb-1.0.19/src/TARGET_libusb/libusb)
#SET(LIBUSB_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/../libusb/lib/libusb-1.0.19/src/TARGET_libusb-build/libusb.a)




# 3) Provide all variables for the build.
 SET(LIBRARY ${CMAKE_CURRENT_BINARY_DIR}/libftdi/install/lib/libftdi1.a)
 #SET(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/libusb-1.0.19/install/include/libusb-1.0)


 IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"  AND  "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	# SET(LDFLAGS "-pthread -lrt -ludev")
 ENDIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"  AND  "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

 SET(DEFINES -DROMLOADER_USB_LIBFTDI_VERSION=1)
 
 #SET(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/libftdi1-1.2/install/include/libftdi-1.0)
 #SET(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR}/libusb-1.0.19/install/include/libusb-1.0)


# ----------------------------------------------------------------------------

 # Store all information about the library in the cache.

 #SET(LIBFTDI_LIBRARY              ${LIBRARY}              CACHE INTERNAL "The libftdi library with the complete path.")
 SET(LIBFTDI_LDFLAGS              ${LDFLAGS}              CACHE INTERNAL "All linker flags required to link the library. The list must be separated with whitespace.")
 SET(LIBFTDI_DEFINES              ${DEFINES}              CACHE INTERNAL "All defines for the libftdi library. This should be a list of entries starting with -D.")
 SET(LIBFTDI_INCLUDE_DIRECTORIES  ${INCLUDE_DIRECTORIES}  CACHE INTERNAL "The include folders for the library headers. The list must be separated with whitespace.")
