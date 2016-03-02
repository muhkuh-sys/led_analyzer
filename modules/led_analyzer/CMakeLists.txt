cmake_minimum_required(VERSION 2.8)

PROJECT("Led_Analyzer")

SET(Led_Analyzer_VERSION 0.0.1)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${LIBFTDI_INCLUDE_DIRECTORIES})
include_directories(${LIBUSB_INCLUDE_DIRECTORIES})

SET_SOURCE_FILES_PROPERTIES(led_analyzer.i PROPERTIES CPLUSPLUS OFF)
SET_SOURCE_FILES_PROPERTIES(led_analyzer.i PROPERTIES SWIG_FLAGS "")

SWIG_ADD_MODULE(TARGET_led_analyzer lua led_analyzer.i led_analyzer.c i2c_routines.c io_operations.c tcs3472.c)
SWIG_LINK_LIBRARIES(TARGET_led_analyzer ${LUA_LIBRARIES} ${LIBFTDI_LIBRARY} ${LIBUSB_LIBRARY} ${LIBUSB_LDFLAGS})

# Set the name of the output file to "led_analyzer".
SET_TARGET_PROPERTIES(TARGET_led_analyzer PROPERTIES PREFIX "" OUTPUT_NAME "led_analyzer")


# On mingw link all compiler libraries static.
IF((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") AND (${CMAKE_COMPILER_IS_GNUCC}))
	set_property(TARGET TARGET_led_analyzer PROPERTY LINK_FLAGS "-static-libgcc")
ENDIF((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") AND (${CMAKE_COMPILER_IS_GNUCC}))


# Add tests for this module.
IF((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") AND (${CMAKE_COMPILER_IS_GNUCC}))
	# Here are the MinGW specific tests.
	ADD_TEST(NAME romloader_usb_MinGW_DLL_dependencies
	         COMMAND "${PYTHON_EXECUTABLE}" ${CMAKE_HOME_DIRECTORY}/cmake/tests/mingw_dll_dependencies.py -u lua5.1 $<TARGET_FILE:TARGET_led_analyzer>)
ENDIF((${CMAKE_SYSTEM_NAME} STREQUAL "Windows") AND (${CMAKE_COMPILER_IS_GNUCC}))
