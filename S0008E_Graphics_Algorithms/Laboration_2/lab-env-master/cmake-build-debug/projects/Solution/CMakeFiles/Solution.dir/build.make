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
CMAKE_SOURCE_DIR = /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug

# Include any dependencies generated for this target.
include projects/Solution/CMakeFiles/Solution.dir/depend.make

# Include the progress variables for this target.
include projects/Solution/CMakeFiles/Solution.dir/progress.make

# Include the compile flags for this target's objects.
include projects/Solution/CMakeFiles/Solution.dir/flags.make

projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o: projects/Solution/CMakeFiles/Solution.dir/flags.make
projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o: ../projects/Solution/code/exampleapp.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Solution.dir/code/exampleapp.cc.o -c /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/exampleapp.cc

projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solution.dir/code/exampleapp.cc.i"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/exampleapp.cc > CMakeFiles/Solution.dir/code/exampleapp.cc.i

projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solution.dir/code/exampleapp.cc.s"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/exampleapp.cc -o CMakeFiles/Solution.dir/code/exampleapp.cc.s

projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.requires:

.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.requires

projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.provides: projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.requires
	$(MAKE) -f projects/Solution/CMakeFiles/Solution.dir/build.make projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.provides.build
.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.provides

projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.provides.build: projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o


projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o: projects/Solution/CMakeFiles/Solution.dir/flags.make
projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o: ../projects/Solution/code/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Solution.dir/code/main.cc.o -c /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/main.cc

projects/Solution/CMakeFiles/Solution.dir/code/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solution.dir/code/main.cc.i"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/main.cc > CMakeFiles/Solution.dir/code/main.cc.i

projects/Solution/CMakeFiles/Solution.dir/code/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solution.dir/code/main.cc.s"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/main.cc -o CMakeFiles/Solution.dir/code/main.cc.s

projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.requires:

.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.requires

projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.provides: projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.requires
	$(MAKE) -f projects/Solution/CMakeFiles/Solution.dir/build.make projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.provides.build
.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.provides

projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.provides.build: projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o


projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o: projects/Solution/CMakeFiles/Solution.dir/flags.make
projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o: ../projects/Solution/code/Skeleton.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Solution.dir/code/Skeleton.cpp.o -c /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/Skeleton.cpp

projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solution.dir/code/Skeleton.cpp.i"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/Skeleton.cpp > CMakeFiles/Solution.dir/code/Skeleton.cpp.i

projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solution.dir/code/Skeleton.cpp.s"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/Skeleton.cpp -o CMakeFiles/Solution.dir/code/Skeleton.cpp.s

projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.requires:

.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.requires

projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.provides: projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.requires
	$(MAKE) -f projects/Solution/CMakeFiles/Solution.dir/build.make projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.provides.build
.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.provides

projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.provides.build: projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o


projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o: projects/Solution/CMakeFiles/Solution.dir/flags.make
projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o: ../projects/Solution/code/Animation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Solution.dir/code/Animation.cpp.o -c /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/Animation.cpp

projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solution.dir/code/Animation.cpp.i"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/Animation.cpp > CMakeFiles/Solution.dir/code/Animation.cpp.i

projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solution.dir/code/Animation.cpp.s"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution/code/Animation.cpp -o CMakeFiles/Solution.dir/code/Animation.cpp.s

projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.requires:

.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.requires

projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.provides: projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.requires
	$(MAKE) -f projects/Solution/CMakeFiles/Solution.dir/build.make projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.provides.build
.PHONY : projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.provides

projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.provides.build: projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o


# Object files for target Solution
Solution_OBJECTS = \
"CMakeFiles/Solution.dir/code/exampleapp.cc.o" \
"CMakeFiles/Solution.dir/code/main.cc.o" \
"CMakeFiles/Solution.dir/code/Skeleton.cpp.o" \
"CMakeFiles/Solution.dir/code/Animation.cpp.o"

# External object files for target Solution
Solution_EXTERNAL_OBJECTS =

projects/Solution/Solution: projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o
projects/Solution/Solution: projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o
projects/Solution/Solution: projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o
projects/Solution/Solution: projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o
projects/Solution/Solution: projects/Solution/CMakeFiles/Solution.dir/build.make
projects/Solution/Solution: engine/core/libcore.a
projects/Solution/Solution: engine/render/librender.a
projects/Solution/Solution: exts/glew/libglew.a
projects/Solution/Solution: exts/glfw-3.1.1/src/libglfw3.a
projects/Solution/Solution: projects/Solution/CMakeFiles/Solution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Solution"
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Solution.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
projects/Solution/CMakeFiles/Solution.dir/build: projects/Solution/Solution

.PHONY : projects/Solution/CMakeFiles/Solution.dir/build

projects/Solution/CMakeFiles/Solution.dir/requires: projects/Solution/CMakeFiles/Solution.dir/code/exampleapp.cc.o.requires
projects/Solution/CMakeFiles/Solution.dir/requires: projects/Solution/CMakeFiles/Solution.dir/code/main.cc.o.requires
projects/Solution/CMakeFiles/Solution.dir/requires: projects/Solution/CMakeFiles/Solution.dir/code/Skeleton.cpp.o.requires
projects/Solution/CMakeFiles/Solution.dir/requires: projects/Solution/CMakeFiles/Solution.dir/code/Animation.cpp.o.requires

.PHONY : projects/Solution/CMakeFiles/Solution.dir/requires

projects/Solution/CMakeFiles/Solution.dir/clean:
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution && $(CMAKE_COMMAND) -P CMakeFiles/Solution.dir/cmake_clean.cmake
.PHONY : projects/Solution/CMakeFiles/Solution.dir/clean

projects/Solution/CMakeFiles/Solution.dir/depend:
	cd /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/projects/Solution /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution /home/ponste-5/Documents/GIT/ponste-5/S0008E/Laboration_2/lab-env-master/cmake-build-debug/projects/Solution/CMakeFiles/Solution.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : projects/Solution/CMakeFiles/Solution.dir/depend

