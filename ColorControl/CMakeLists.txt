PROJECT(ColorControlApp)

cmake_minimum_required(VERSION 3.0)


find_package(wxWidgets REQUIRED adv propgrid net gl core base)
include(${wxWidgets_USE_FILE})


# Windows builds use the Muhkuh LUA package. Linux builds use the system LUA package.
IF((${CMAKE_SYSTEM_NAME} STREQUAL "Windows"))
	FIND_PACKAGE(org.muhkuh.lua-lua51 REQUIRED)
ELSE((${CMAKE_SYSTEM_NAME} STREQUAL "Windows"))
	FIND_PACKAGE(Lua51 REQUIRED)
	INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
ENDIF((${CMAKE_SYSTEM_NAME} STREQUAL "Windows"))

# Color Control headers 
include_directories(include/)

SET(SRC_LIST src/ColorControlMain.cpp src/ColorControlApp.cpp src/CDevice.cpp src/CLua.cpp src/CSensorData.cpp src/CTestGeneration.cpp
			 src/GUIFrame.cpp src/PanelTestrow.cpp src/PanelSensor.cpp)

SET(HDR_LIST include/ColorControlMain.h include/ColorControlApp.h include/CDevice.h include/CLua.h include/CSensorData.h
			 include/CTestGeneration include/GUIFrame.h include/PanelTestrow.h include/PanelSensor.h)
			 
			 
set(SRCS ${SRC_LIST} ${HDR_LIST})
			 
add_executable(ColorControl ${SRCS})
target_link_libraries(ColorControl org.muhkuh.lua-lua51::TARGET_lualib ${wxWidgets_LIBRARIES})

