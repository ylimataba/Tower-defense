# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.7.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.7.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build

# Include any dependencies generated for this target.
include CMakeFiles/QuadTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/QuadTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QuadTree.dir/flags.make

CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o: CMakeFiles/QuadTree.dir/flags.make
CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o: ../examples/MapWithQuadTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o -c /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/examples/MapWithQuadTree.cpp

CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/examples/MapWithQuadTree.cpp > CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.i

CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/examples/MapWithQuadTree.cpp -o CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.s

CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.requires:

.PHONY : CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.requires

CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.provides: CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.requires
	$(MAKE) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.provides.build
.PHONY : CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.provides

CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.provides.build: CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o


# Object files for target QuadTree
QuadTree_OBJECTS = \
"CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o"

# External object files for target QuadTree
QuadTree_EXTERNAL_OBJECTS =

QuadTree: CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o
QuadTree: CMakeFiles/QuadTree.dir/build.make
QuadTree: libtmx-loader.dylib
QuadTree: libpugi.dylib
QuadTree: /usr/local/lib/libsfml-graphics.dylib
QuadTree: /usr/local/lib/libsfml-window.dylib
QuadTree: /usr/local/lib/libsfml-system.dylib
QuadTree: /usr/lib/libz.dylib
QuadTree: CMakeFiles/QuadTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable QuadTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QuadTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QuadTree.dir/build: QuadTree

.PHONY : CMakeFiles/QuadTree.dir/build

CMakeFiles/QuadTree.dir/requires: CMakeFiles/QuadTree.dir/examples/MapWithQuadTree.cpp.o.requires

.PHONY : CMakeFiles/QuadTree.dir/requires

CMakeFiles/QuadTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QuadTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QuadTree.dir/clean

CMakeFiles/QuadTree.dir/depend:
	cd /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build/CMakeFiles/QuadTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QuadTree.dir/depend
