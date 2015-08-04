cmake_minimum_required(VERSION 2.8)


PROJECT("led_analyzer")


# Swig is required to generate the bindings.
FIND_PACKAGE(SWIG REQUIRED)


# Find the Doxygen package
find_package(Doxygen)


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



SET(USE_SYSTEM_LUA FALSE)


#----------------------------------------------------------------------------
#
# Include the projects in the subdirectories.

add_subdirectory(external)
add_subdirectory(modules)
#add_subdirectory(ColorControl)


#----------------------------------------------------------------------------
#
# Create a doxygen documentation 

if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc ALL
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)
