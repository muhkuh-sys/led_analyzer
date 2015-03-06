#                                               -*- cmake -*-
#
#  LibFTDI1Config.cmake(.in)
#
#  Copyright (C) 2013 Intra2net AG and the libftdi developers
#
#  This file is part of LibFTDI.
#
#  LibFTDI is free software; you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License
#  version 2.1 as published by the Free Software Foundation;
#

# Use the following variables to compile and link against LibFTDI:
#  LIBFTDI_FOUND              - True if LibFTDI was found on your system
#  LIBFTDI_USE_FILE           - The file making LibFTDI usable
#  LIBFTDI_DEFINITIONS        - Definitions needed to build with LibFTDI
#  LIBFTDI_INCLUDE_DIRS       - Directory where ftdi.h can be found
#  LIBFTDI_INCLUDE_DIRS       - List of directories of LibFTDI and it's dependencies
#  LIBFTDI_LIBRARY            - LibFTDI library location
#  LIBFTDI_LIBRARIES          - List of libraries to link against LibFTDI library
#  LIBFTDIPP_LIBRARY          - LibFTDI C++ wrapper library location
#  LIBFTDIPP_LIBRARIES        - List of libraries to link against LibFTDI C++ wrapper
#  LIBFTDI_LIBRARY_DIRS       - List of directories containing LibFTDI' libraries
#  LIBFTDI_ROOT_DIR           - The base directory of LibFTDI
#  LIBFTDI_VERSION_STRING     - A human-readable string containing the version
#  LIBFTDI_VERSION_MAJOR      - The major version of LibFTDI
#  LIBFTDI_VERSION_MINOR      - The minor version of LibFTDI
#  LIBFTDI_VERSION_PATCH      - The patch version of LibFTDI
#  LIBFTDI_PYTHON_MODULE_PATH - Path to the python module

set ( LIBFTDI_FOUND 1 )
set ( LIBFTDI_USE_FILE     "C:/Program Files (x86)/libftdi1/lib/cmake/libftdi1/UseLibFTDI1.cmake" )

set ( LIBFTDI_DEFINITIONS  "" )
set ( LIBFTDI_INCLUDE_DIR  "C:/Program Files (x86)/libftdi1/include/libftdi1" )
set ( LIBFTDI_INCLUDE_DIRS "C:/Program Files (x86)/libftdi1/include/libftdi1" )
set ( LIBFTDI_LIBRARY      "ftdi1" )
set ( LIBFTDI_LIBRARIES    "ftdi1;C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/../libusb/libusb-1.0.19/install/lib/libusb.a" )
set ( LIBFTDI_STATIC_LIBRARY      "ftdi1.a" )
set ( LIBFTDI_STATIC_LIBRARIES    "ftdi1.a;C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/../libusb/libusb-1.0.19/install/lib/libusb.a" )
set ( LIBFTDIPP_LIBRARY    "" )
set ( LIBFTDIPP_LIBRARIES  "" )
set ( LIBFTDI_LIBRARY_DIRS "C:/Program Files (x86)/libftdi1/bin" )
set ( LIBFTDI_ROOT_DIR     "C:/Program Files (x86)/libftdi1" )

set ( LIBFTDI_VERSION_STRING "1.2" )
set ( LIBFTDI_VERSION_MAJOR  "1" )
set ( LIBFTDI_VERSION_MINOR  "2" )
set ( LIBFTDI_VERSION_PATCH  "" )

set ( LIBFTDI_PYTHON_MODULE_PATH "" )

