#! /bin/bash



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





