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
include CMakeFiles/BenchMark.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BenchMark.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BenchMark.dir/flags.make

CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o: CMakeFiles/BenchMark.dir/flags.make
CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o: ../examples/Benchmark.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o -c /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/examples/Benchmark.cpp

CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/examples/Benchmark.cpp > CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.i

CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/examples/Benchmark.cpp -o CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.s

CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.requires:

.PHONY : CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.requires

CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.provides: CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.requires
	$(MAKE) -f CMakeFiles/BenchMark.dir/build.make CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.provides.build
.PHONY : CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.provides

CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.provides.build: CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o


# Object files for target BenchMark
BenchMark_OBJECTS = \
"CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o"

# External object files for target BenchMark
BenchMark_EXTERNAL_OBJECTS =

BenchMark: CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o
BenchMark: CMakeFiles/BenchMark.dir/build.make
BenchMark: libtmx-loader.dylib
BenchMark: libpugi.dylib
BenchMark: /usr/local/lib/libsfml-graphics.dylib
BenchMark: /usr/local/lib/libsfml-window.dylib
BenchMark: /usr/local/lib/libsfml-system.dylib
BenchMark: /usr/lib/libz.dylib
BenchMark: CMakeFiles/BenchMark.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BenchMark"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BenchMark.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BenchMark.dir/build: BenchMark

.PHONY : CMakeFiles/BenchMark.dir/build

CMakeFiles/BenchMark.dir/requires: CMakeFiles/BenchMark.dir/examples/Benchmark.cpp.o.requires

.PHONY : CMakeFiles/BenchMark.dir/requires

CMakeFiles/BenchMark.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BenchMark.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BenchMark.dir/clean

CMakeFiles/BenchMark.dir/depend:
	cd /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build /Users/mataba/Documents/Codes/Cpp/project/sfml-tmxloader-master/build/CMakeFiles/BenchMark.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BenchMark.dir/depend

