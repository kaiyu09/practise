# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nio/kkrepo/code_c++/basecode/i2c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nio/kkrepo/code_c++/basecode/i2c/build

# Include any dependencies generated for this target.
include CMakeFiles/i2ctest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/i2ctest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/i2ctest.dir/flags.make

CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o: CMakeFiles/i2ctest.dir/flags.make
CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o: ../flash_isx031_intf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nio/kkrepo/code_c++/basecode/i2c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o -c /home/nio/kkrepo/code_c++/basecode/i2c/flash_isx031_intf.cpp

CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nio/kkrepo/code_c++/basecode/i2c/flash_isx031_intf.cpp > CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.i

CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nio/kkrepo/code_c++/basecode/i2c/flash_isx031_intf.cpp -o CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.s

CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.requires:

.PHONY : CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.requires

CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.provides: CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.requires
	$(MAKE) -f CMakeFiles/i2ctest.dir/build.make CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.provides.build
.PHONY : CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.provides

CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.provides.build: CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o


# Object files for target i2ctest
i2ctest_OBJECTS = \
"CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o"

# External object files for target i2ctest
i2ctest_EXTERNAL_OBJECTS =

i2ctest: CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o
i2ctest: CMakeFiles/i2ctest.dir/build.make
i2ctest: CMakeFiles/i2ctest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nio/kkrepo/code_c++/basecode/i2c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable i2ctest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/i2ctest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/i2ctest.dir/build: i2ctest

.PHONY : CMakeFiles/i2ctest.dir/build

CMakeFiles/i2ctest.dir/requires: CMakeFiles/i2ctest.dir/flash_isx031_intf.cpp.o.requires

.PHONY : CMakeFiles/i2ctest.dir/requires

CMakeFiles/i2ctest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/i2ctest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/i2ctest.dir/clean

CMakeFiles/i2ctest.dir/depend:
	cd /home/nio/kkrepo/code_c++/basecode/i2c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nio/kkrepo/code_c++/basecode/i2c /home/nio/kkrepo/code_c++/basecode/i2c /home/nio/kkrepo/code_c++/basecode/i2c/build /home/nio/kkrepo/code_c++/basecode/i2c/build /home/nio/kkrepo/code_c++/basecode/i2c/build/CMakeFiles/i2ctest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/i2ctest.dir/depend

