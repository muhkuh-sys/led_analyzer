# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build

# Include any dependencies generated for this target.
include examples/CMakeFiles/bitbang.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/bitbang.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/bitbang.dir/flags.make

examples/CMakeFiles/bitbang.dir/bitbang.c.obj: examples/CMakeFiles/bitbang.dir/flags.make
examples/CMakeFiles/bitbang.dir/bitbang.c.obj: examples/CMakeFiles/bitbang.dir/includes_C.rsp
examples/CMakeFiles/bitbang.dir/bitbang.c.obj: C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi/examples/bitbang.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/bitbang.dir/bitbang.c.obj"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\bitbang.dir\bitbang.c.obj   -c C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples\bitbang.c

examples/CMakeFiles/bitbang.dir/bitbang.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bitbang.dir/bitbang.c.i"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples\bitbang.c > CMakeFiles\bitbang.dir\bitbang.c.i

examples/CMakeFiles/bitbang.dir/bitbang.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bitbang.dir/bitbang.c.s"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples\bitbang.c -o CMakeFiles\bitbang.dir\bitbang.c.s

examples/CMakeFiles/bitbang.dir/bitbang.c.obj.requires:
.PHONY : examples/CMakeFiles/bitbang.dir/bitbang.c.obj.requires

examples/CMakeFiles/bitbang.dir/bitbang.c.obj.provides: examples/CMakeFiles/bitbang.dir/bitbang.c.obj.requires
	$(MAKE) -f examples\CMakeFiles\bitbang.dir\build.make examples/CMakeFiles/bitbang.dir/bitbang.c.obj.provides.build
.PHONY : examples/CMakeFiles/bitbang.dir/bitbang.c.obj.provides

examples/CMakeFiles/bitbang.dir/bitbang.c.obj.provides.build: examples/CMakeFiles/bitbang.dir/bitbang.c.obj

# Object files for target bitbang
bitbang_OBJECTS = \
"CMakeFiles/bitbang.dir/bitbang.c.obj"

# External object files for target bitbang
bitbang_EXTERNAL_OBJECTS =

examples/bitbang.exe: examples/CMakeFiles/bitbang.dir/bitbang.c.obj
examples/bitbang.exe: examples/CMakeFiles/bitbang.dir/build.make
examples/bitbang.exe: src/libftdi1.dll.a
examples/bitbang.exe: C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/../libusb/libusb-1.0.19/install/lib/libusb.a
examples/bitbang.exe: examples/CMakeFiles/bitbang.dir/objects1.rsp
examples/bitbang.exe: examples/CMakeFiles/bitbang.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable bitbang.exe"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bitbang.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/bitbang.dir/build: examples/bitbang.exe
.PHONY : examples/CMakeFiles/bitbang.dir/build

examples/CMakeFiles/bitbang.dir/requires: examples/CMakeFiles/bitbang.dir/bitbang.c.obj.requires
.PHONY : examples/CMakeFiles/bitbang.dir/requires

examples/CMakeFiles/bitbang.dir/clean:
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && $(CMAKE_COMMAND) -P CMakeFiles\bitbang.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/bitbang.dir/clean

examples/CMakeFiles/bitbang.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples\CMakeFiles\bitbang.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/bitbang.dir/depend

