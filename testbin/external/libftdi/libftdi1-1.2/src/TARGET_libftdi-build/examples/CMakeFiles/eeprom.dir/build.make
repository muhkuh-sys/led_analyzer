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
include examples/CMakeFiles/eeprom.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/eeprom.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/eeprom.dir/flags.make

examples/CMakeFiles/eeprom.dir/eeprom.c.obj: examples/CMakeFiles/eeprom.dir/flags.make
examples/CMakeFiles/eeprom.dir/eeprom.c.obj: examples/CMakeFiles/eeprom.dir/includes_C.rsp
examples/CMakeFiles/eeprom.dir/eeprom.c.obj: C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/libftdi1-1.2/src/TARGET_libftdi/examples/eeprom.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/eeprom.dir/eeprom.c.obj"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles\eeprom.dir\eeprom.c.obj   -c C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples\eeprom.c

examples/CMakeFiles/eeprom.dir/eeprom.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eeprom.dir/eeprom.c.i"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -E C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples\eeprom.c > CMakeFiles\eeprom.dir\eeprom.c.i

examples/CMakeFiles/eeprom.dir/eeprom.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eeprom.dir/eeprom.c.s"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && C:\TDM-GCC-64\bin\gcc.exe  $(C_DEFINES) $(C_FLAGS) -S C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples\eeprom.c -o CMakeFiles\eeprom.dir\eeprom.c.s

examples/CMakeFiles/eeprom.dir/eeprom.c.obj.requires:
.PHONY : examples/CMakeFiles/eeprom.dir/eeprom.c.obj.requires

examples/CMakeFiles/eeprom.dir/eeprom.c.obj.provides: examples/CMakeFiles/eeprom.dir/eeprom.c.obj.requires
	$(MAKE) -f examples\CMakeFiles\eeprom.dir\build.make examples/CMakeFiles/eeprom.dir/eeprom.c.obj.provides.build
.PHONY : examples/CMakeFiles/eeprom.dir/eeprom.c.obj.provides

examples/CMakeFiles/eeprom.dir/eeprom.c.obj.provides.build: examples/CMakeFiles/eeprom.dir/eeprom.c.obj

# Object files for target eeprom
eeprom_OBJECTS = \
"CMakeFiles/eeprom.dir/eeprom.c.obj"

# External object files for target eeprom
eeprom_EXTERNAL_OBJECTS =

examples/eeprom.exe: examples/CMakeFiles/eeprom.dir/eeprom.c.obj
examples/eeprom.exe: examples/CMakeFiles/eeprom.dir/build.make
examples/eeprom.exe: src/libftdi1.dll.a
examples/eeprom.exe: C:/Users/subhan/Desktop/led_analyzer/testbin/external/libftdi/../libusb/libusb-1.0.19/install/lib/libusb.a
examples/eeprom.exe: examples/CMakeFiles/eeprom.dir/objects1.rsp
examples/eeprom.exe: examples/CMakeFiles/eeprom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable eeprom.exe"
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\eeprom.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/eeprom.dir/build: examples/eeprom.exe
.PHONY : examples/CMakeFiles/eeprom.dir/build

examples/CMakeFiles/eeprom.dir/requires: examples/CMakeFiles/eeprom.dir/eeprom.c.obj.requires
.PHONY : examples/CMakeFiles/eeprom.dir/requires

examples/CMakeFiles/eeprom.dir/clean:
	cd /d C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples && $(CMAKE_COMMAND) -P CMakeFiles\eeprom.dir\cmake_clean.cmake
.PHONY : examples/CMakeFiles/eeprom.dir/clean

examples/CMakeFiles/eeprom.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi\examples C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples C:\Users\subhan\Desktop\led_analyzer\testbin\external\libftdi\libftdi1-1.2\src\TARGET_libftdi-build\examples\CMakeFiles\eeprom.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/eeprom.dir/depend

