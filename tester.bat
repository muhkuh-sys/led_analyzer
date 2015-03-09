
mkdir testfolder
cd testfolder
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m64 -DCMAKE_CXX_FLAGS=-m64 -DCMAKE_C_COMPILER=C:/TDM-GCC-64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/TDM-GCC-64/bin/g++.exe .. 



choice /c:12 /n /m "Waehle 1 to quit, 2 to make"

if %errorlevel%==1 exit

c:\TDM-GCC-64\bin\mingw32-make.exe


PAUSE