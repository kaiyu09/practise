# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nio/kkrepo/cmake_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nio/kkrepo/cmake_project/build

# Include any dependencies generated for this target.
include src_bb/CMakeFiles/bb_static.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src_bb/CMakeFiles/bb_static.dir/compiler_depend.make

# Include the progress variables for this target.
include src_bb/CMakeFiles/bb_static.dir/progress.make

# Include the compile flags for this target's objects.
include src_bb/CMakeFiles/bb_static.dir/flags.make

src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.o: src_bb/CMakeFiles/bb_static.dir/flags.make
src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.o: ../src_bb/bb_test.cpp
src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.o: src_bb/CMakeFiles/bb_static.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nio/kkrepo/cmake_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.o"
	cd /home/nio/kkrepo/cmake_project/build/src_bb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.o -MF CMakeFiles/bb_static.dir/bb_test.cpp.o.d -o CMakeFiles/bb_static.dir/bb_test.cpp.o -c /home/nio/kkrepo/cmake_project/src_bb/bb_test.cpp

src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bb_static.dir/bb_test.cpp.i"
	cd /home/nio/kkrepo/cmake_project/build/src_bb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nio/kkrepo/cmake_project/src_bb/bb_test.cpp > CMakeFiles/bb_static.dir/bb_test.cpp.i

src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bb_static.dir/bb_test.cpp.s"
	cd /home/nio/kkrepo/cmake_project/build/src_bb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nio/kkrepo/cmake_project/src_bb/bb_test.cpp -o CMakeFiles/bb_static.dir/bb_test.cpp.s

# Object files for target bb_static
bb_static_OBJECTS = \
"CMakeFiles/bb_static.dir/bb_test.cpp.o"

# External object files for target bb_static
bb_static_EXTERNAL_OBJECTS =

src_bb/libbb_static.a: src_bb/CMakeFiles/bb_static.dir/bb_test.cpp.o
src_bb/libbb_static.a: src_bb/CMakeFiles/bb_static.dir/build.make
src_bb/libbb_static.a: src_bb/CMakeFiles/bb_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nio/kkrepo/cmake_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libbb_static.a"
	cd /home/nio/kkrepo/cmake_project/build/src_bb && $(CMAKE_COMMAND) -P CMakeFiles/bb_static.dir/cmake_clean_target.cmake
	cd /home/nio/kkrepo/cmake_project/build/src_bb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bb_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src_bb/CMakeFiles/bb_static.dir/build: src_bb/libbb_static.a
.PHONY : src_bb/CMakeFiles/bb_static.dir/build

src_bb/CMakeFiles/bb_static.dir/clean:
	cd /home/nio/kkrepo/cmake_project/build/src_bb && $(CMAKE_COMMAND) -P CMakeFiles/bb_static.dir/cmake_clean.cmake
.PHONY : src_bb/CMakeFiles/bb_static.dir/clean

src_bb/CMakeFiles/bb_static.dir/depend:
	cd /home/nio/kkrepo/cmake_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nio/kkrepo/cmake_project /home/nio/kkrepo/cmake_project/src_bb /home/nio/kkrepo/cmake_project/build /home/nio/kkrepo/cmake_project/build/src_bb /home/nio/kkrepo/cmake_project/build/src_bb/CMakeFiles/bb_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src_bb/CMakeFiles/bb_static.dir/depend

