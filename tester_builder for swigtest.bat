mkdir testfolder
cd testfolder 
cmake -G "MinGW Makefiles" -DSWIG_EXECUTABLE=C:/Users/subhan/Desktop/swigwin-3.0.2/swig.exe -DUSE_SYSTEM_LUA=FALSE -DCMAKE_C_FLAGS=-m64 -DCMAKE_CXX_FLAGS=-m64 -DCMAKE_C_COMPILER=C:/TDM-GCC-64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/TDM-GCC-64/bin/g++.exe ..

PAUSE	


cd testfolder 
c:\TDM-GCC-64\bin\mingw32-make.exe

PAUSE
