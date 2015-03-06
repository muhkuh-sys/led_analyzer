# Install script for directory: C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/libftdi1")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES
    "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/libftdi1.pc"
    "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/libftdipp1.pc"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/libftdi1-config")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libftdi1" TYPE FILE FILES
    "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/LibFTDI1Config.cmake"
    "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/LibFTDI1ConfigVersion.cmake"
    "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi/cmake/UseLibFTDI1.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/src/cmake_install.cmake")
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/ftdipp/cmake_install.cmake")
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/python/cmake_install.cmake")
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/ftdi_eeprom/cmake_install.cmake")
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/examples/cmake_install.cmake")
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/packages/cmake_install.cmake")
  include("C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi-build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
