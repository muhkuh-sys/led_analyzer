cmake_minimum_required(VERSION 2.8)

PROJECT("cmakeTests")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(mytestexe main.c )

