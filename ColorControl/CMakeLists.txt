PROJECT(ColorControlApp)

cmake_minimum_required(VERSION 3.0)


find_package(wxWidgets REQUIRED adv propgrid net gl core base)
include(${wxWidgets_USE_FILE})


# Color Control headers 
include_directories(include/)

SET(SRC_LIST src/ColorControlMain.cpp src/ColorControlApp.cpp src/CDevice.cpp src/CLua.cpp src/CSensorData.cpp src/CTestGeneration.cpp
             src/GUIFrame.cpp src/PanelTestrow.cpp src/PanelSensor.cpp)

SET(HDR_LIST include/ColorControlMain.h include/ColorControlApp.h include/CDevice.h include/CLua.h include/CSensorData.h
             include/CTestGeneration include/GUIFrame.h include/PanelTestrow.h include/PanelSensor.h)


#set(SRCS ${SRC_LIST} ${HDR_LIST})

add_executable(ColorControl ${SRC_LIST})
target_link_libraries(ColorControl ${LUA_LIBRARIES} ${wxWidgets_LIBRARIES})
TARGET_INCLUDE_DIRECTORIES(ColorControl PRIVATE ${LUA_INCLUDE_DIR})
