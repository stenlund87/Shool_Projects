# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/ponste-5/Documents/clion-2017.2.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/ponste-5/Documents/clion-2017.2.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug

# Include any dependencies generated for this target.
include projects/example/CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include projects/example/CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include projects/example/CMakeFiles/example.dir/flags.make

projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o: projects/example/CMakeFiles/example.dir/flags.make
projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o: ../projects/example/code/exampleapp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/code/exampleapp.cc.o -c /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example/code/exampleapp.cc

projects/example/CMakeFiles/example.dir/code/exampleapp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/code/exampleapp.cc.i"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example/code/exampleapp.cc > CMakeFiles/example.dir/code/exampleapp.cc.i

projects/example/CMakeFiles/example.dir/code/exampleapp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/code/exampleapp.cc.s"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example/code/exampleapp.cc -o CMakeFiles/example.dir/code/exampleapp.cc.s

projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.requires:

.PHONY : projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.requires

projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.provides: projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.requires
	$(MAKE) -f projects/example/CMakeFiles/example.dir/build.make projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.provides.build
.PHONY : projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.provides

projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.provides.build: projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o


projects/example/CMakeFiles/example.dir/code/main.cc.o: projects/example/CMakeFiles/example.dir/flags.make
projects/example/CMakeFiles/example.dir/code/main.cc.o: ../projects/example/code/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object projects/example/CMakeFiles/example.dir/code/main.cc.o"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/code/main.cc.o -c /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example/code/main.cc

projects/example/CMakeFiles/example.dir/code/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/code/main.cc.i"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example/code/main.cc > CMakeFiles/example.dir/code/main.cc.i

projects/example/CMakeFiles/example.dir/code/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/code/main.cc.s"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example/code/main.cc -o CMakeFiles/example.dir/code/main.cc.s

projects/example/CMakeFiles/example.dir/code/main.cc.o.requires:

.PHONY : projects/example/CMakeFiles/example.dir/code/main.cc.o.requires

projects/example/CMakeFiles/example.dir/code/main.cc.o.provides: projects/example/CMakeFiles/example.dir/code/main.cc.o.requires
	$(MAKE) -f projects/example/CMakeFiles/example.dir/build.make projects/example/CMakeFiles/example.dir/code/main.cc.o.provides.build
.PHONY : projects/example/CMakeFiles/example.dir/code/main.cc.o.provides

projects/example/CMakeFiles/example.dir/code/main.cc.o.provides.build: projects/example/CMakeFiles/example.dir/code/main.cc.o


# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/code/exampleapp.cc.o" \
"CMakeFiles/example.dir/code/main.cc.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

projects/example/example: projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o
projects/example/example: projects/example/CMakeFiles/example.dir/code/main.cc.o
projects/example/example: projects/example/CMakeFiles/example.dir/build.make
projects/example/example: engine/core/libcore.a
projects/example/example: engine/render/librender.a
projects/example/example: exts/glew/libglew.a
projects/example/example: exts/glfw-3.1.1/src/libglfw3.a
projects/example/example: projects/example/CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable example"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/example/CMakeFiles/example.dir/build: projects/example/example

.PHONY : projects/example/CMakeFiles/example.dir/build

projects/example/CMakeFiles/example.dir/requires: projects/example/CMakeFiles/example.dir/code/exampleapp.cc.o.requires
projects/example/CMakeFiles/example.dir/requires: projects/example/CMakeFiles/example.dir/code/main.cc.o.requires

.PHONY : projects/example/CMakeFiles/example.dir/requires

projects/example/CMakeFiles/example.dir/clean:
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example && $(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : projects/example/CMakeFiles/example.dir/clean

projects/example/CMakeFiles/example.dir/depend:
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/projects/example /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_1/lab-env-master/cmake-build-debug/projects/example/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : projects/example/CMakeFiles/example.dir/depend

