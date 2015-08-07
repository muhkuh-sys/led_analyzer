cmake_minimum_required(VERSION 2.8)


PROJECT("led_analyzer")


# Swig is required to generate the bindings.
FIND_PACKAGE(SWIG REQUIRED)

# Find the Doxygen package
FIND_PACKAGE(Doxygen)


#----------------------------------------------------------------------------
#
# Set custom definitions for several compiler.
#

# Microsoft: Do not show msvs security warnings about unsafe functions.
if(${CMAKE_BUILD_TOOL} MATCHES "(msdev|VCExpress|devenv|nmake)")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF(${CMAKE_BUILD_TOOL} MATCHES "(msdev|VCExpress|devenv|nmake)")


# Microsoft: Set warning level to 2.
if(${CMAKE_BUILD_TOOL} MATCHES "(msdev|VCExpress|devenv)")
	add_definitions(/W2)
ENDIF(${CMAKE_BUILD_TOOL} MATCHES "(msdev|VCExpress|devenv)")


#----------------------------------------------------------------------------
#
# Include CMake scripts.

# Include the location of the dependencies.
INCLUDE(ivy/dependencies/ant_paths.cmake)

# Select the LUA version.
INCLUDE(cmake/muhkuh_lua.cmake)


#----------------------------------------------------------------------------
#
# Include the projects in the subdirectories.

add_subdirectory(external)
add_subdirectory(modules)
add_subdirectory(ColorControl)


#----------------------------------------------------------------------------
#
# Create a doxygen documentation 

IF(DOXYGEN_FOUND)
	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	ADD_CUSTOM_TARGET(doc ALL
	                  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	                  COMMENT "Generating API documentation with Doxygen" VERBATIM)
ENDIF(DOXYGEN_FOUND)
