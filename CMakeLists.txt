cmake_minimum_required(VERSION 2.8)


PROJECT("led_analyzer")


# Swig is required to generate the bindings.
FIND_PACKAGE(SWIG REQUIRED)



# Select the LUA version.
INCLUDE(cmake/muhkuh_lua.cmake)


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


#

SET(SWIG_EXECUTABLE C:/Users/subhan/Desktop/swigwin-3.0.2/swig.exe)
SET(USE_SYSTEM_LUA FALSE)


#----------------------------------------------------------------------------
#
# Include the projects in the subdirectories.

add_subdirectory(external)
#add_subdirectory(lua)
#add_subdirectory(modules)


#----------------------------------------------------------------------------

