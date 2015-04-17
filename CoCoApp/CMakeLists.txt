PROJECT(CoCoApp)

cmake_minimum_required(VERSION 3.0)


find_package(wxWidgets REQUIRED net gl core base)
include(${wxWidgets_USE_FILE})



SET(SRC_LIST minimal.cpp)


add_executable(coco ${SRC_LIST})
target_link_libraries(coco ${wxWidgets_LIBRARIES})


