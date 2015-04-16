#! /bin/bash


## -----------------------------------------
#  Build the 32 Bit Version

rm -rf build_windows32
mkdir build_windows32
cd build_windows32

cmake -DUSE_SYSTEM_LUA=FALSE -DCMAKE_C_FLAGS=-m32 -DCMAKE_SHARED_LINKER_FLAGS=-m32 -DCMAKE_EXE_LINKER_FLAGS=-m32 -DCMAKE_MODULE_LINKER_FLAGS=-m32 -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=/usr/bin/i686-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=/usr/bin/i686-w64-mingw32-g++ ..

STATUS=$?
if [ $STATUS -ne 0 ]; then
	exit 1
fi

make
STATUS=$?
if [ $STATUS -ne 0 ]; then
	exit 1
fi

cd ..

## -----------------------------------------
#  Build the 64 Bit Version

rm -rf build_windows64
mkdir build_windows64
cd build_windows64

cmake -DUSE_SYSTEM_LUA=FALSE -DCMAKE_C_FLAGS=-m64 -DCMAKE_SHARED_LINKER_FLAGS=-m64 -DCMAKE_EXE_LINKER_FLAGS=-m64 -DCMAKE_MODULE_LINKER_FLAGS=-m64 -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=/usr/bin/x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=/usr/bin/x86_64-w64-mingw32-g++ ..

STATUS=$?
if [ $STATUS -ne 0 ]; then
	exit 1
fi

make
STATUS=$?
if [ $STATUS -ne 0 ]; then
	exit 1
fi

cd .. 



## ----------------------------------------
#  Assemble the artifacts

rm -rf build
mkdir build
cd build
cmake ../installer/ivy

STATUS=$?
if [ $STATUS -ne 0 ]; then
	exit 1
fi

make
STATUS=$?
if [ $STATUS -ne 0 ]; then
	exit 1
fi


cd ..




