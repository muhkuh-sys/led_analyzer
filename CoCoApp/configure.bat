mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m64 -DCMAKE_CXX_FLAGS=-m64 -DCMAKE_SHARED_LINKER_FLAGS=-m64 -DCMAKE_EXE_LINKER_FLAGS=-m64 -DCMAKE_C_COMPILER=C:/TDM-GCC-64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/TDM-GCC-64/bin/g++.exe -DwxWidgets_ROOT_DIR=C:/Users/subhan/Desktop/wxWidgets-3.0.2/build_win64/install/usr/local -DwxWidgets_LIB_DIR=C:/Users/subhan/Desktop/wxWidgets-3.0.2/build_win64/install/usr/local/lib/gcc_lib -DwxWidgets_CONFIGURATION=mswu -DwxWidgets_EXCLUDE_COMMON_LIBRARIES=FALSE ..
if %ERRORLEVEL% GEQ 1 EXIT /B 1

PAUSE


c:\TDM-GCC-64\bin\mingw32-make.exe


rem wxWidgets_LIB_DIR       - Path to wxWidgets libraries
rem (e.g., C:/wxWidgets-2.6.3/lib/vc_lib).
