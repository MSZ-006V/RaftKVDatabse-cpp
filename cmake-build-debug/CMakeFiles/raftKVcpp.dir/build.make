# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\OpenProject\RaftKVDatabase

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\OpenProject\RaftKVDatabase\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/raftKVcpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raftKVcpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raftKVcpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raftKVcpp.dir/flags.make

CMakeFiles/raftKVcpp.dir/codegen:
.PHONY : CMakeFiles/raftKVcpp.dir/codegen

CMakeFiles/raftKVcpp.dir/main.cpp.obj: CMakeFiles/raftKVcpp.dir/flags.make
CMakeFiles/raftKVcpp.dir/main.cpp.obj: CMakeFiles/raftKVcpp.dir/includes_CXX.rsp
CMakeFiles/raftKVcpp.dir/main.cpp.obj: D:/OpenProject/RaftKVDatabase/main.cpp
CMakeFiles/raftKVcpp.dir/main.cpp.obj: CMakeFiles/raftKVcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\OpenProject\RaftKVDatabase\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raftKVcpp.dir/main.cpp.obj"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raftKVcpp.dir/main.cpp.obj -MF CMakeFiles\raftKVcpp.dir\main.cpp.obj.d -o CMakeFiles\raftKVcpp.dir\main.cpp.obj -c D:\OpenProject\RaftKVDatabase\main.cpp

CMakeFiles/raftKVcpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raftKVcpp.dir/main.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\OpenProject\RaftKVDatabase\main.cpp > CMakeFiles\raftKVcpp.dir\main.cpp.i

CMakeFiles/raftKVcpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raftKVcpp.dir/main.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\OpenProject\RaftKVDatabase\main.cpp -o CMakeFiles\raftKVcpp.dir\main.cpp.s

CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj: CMakeFiles/raftKVcpp.dir/flags.make
CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj: CMakeFiles/raftKVcpp.dir/includes_CXX.rsp
CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj: D:/OpenProject/RaftKVDatabase/src/Persister.cpp
CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj: CMakeFiles/raftKVcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\OpenProject\RaftKVDatabase\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj -MF CMakeFiles\raftKVcpp.dir\src\Persister.cpp.obj.d -o CMakeFiles\raftKVcpp.dir\src\Persister.cpp.obj -c D:\OpenProject\RaftKVDatabase\src\Persister.cpp

CMakeFiles/raftKVcpp.dir/src/Persister.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raftKVcpp.dir/src/Persister.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\OpenProject\RaftKVDatabase\src\Persister.cpp > CMakeFiles\raftKVcpp.dir\src\Persister.cpp.i

CMakeFiles/raftKVcpp.dir/src/Persister.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raftKVcpp.dir/src/Persister.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\OpenProject\RaftKVDatabase\src\Persister.cpp -o CMakeFiles\raftKVcpp.dir\src\Persister.cpp.s

CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj: CMakeFiles/raftKVcpp.dir/flags.make
CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj: CMakeFiles/raftKVcpp.dir/includes_CXX.rsp
CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj: D:/OpenProject/RaftKVDatabase/src/skiplist.cpp
CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj: CMakeFiles/raftKVcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\OpenProject\RaftKVDatabase\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj -MF CMakeFiles\raftKVcpp.dir\src\skiplist.cpp.obj.d -o CMakeFiles\raftKVcpp.dir\src\skiplist.cpp.obj -c D:\OpenProject\RaftKVDatabase\src\skiplist.cpp

CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\OpenProject\RaftKVDatabase\src\skiplist.cpp > CMakeFiles\raftKVcpp.dir\src\skiplist.cpp.i

CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\OpenProject\RaftKVDatabase\src\skiplist.cpp -o CMakeFiles\raftKVcpp.dir\src\skiplist.cpp.s

CMakeFiles/raftKVcpp.dir/src/util.cpp.obj: CMakeFiles/raftKVcpp.dir/flags.make
CMakeFiles/raftKVcpp.dir/src/util.cpp.obj: CMakeFiles/raftKVcpp.dir/includes_CXX.rsp
CMakeFiles/raftKVcpp.dir/src/util.cpp.obj: D:/OpenProject/RaftKVDatabase/src/util.cpp
CMakeFiles/raftKVcpp.dir/src/util.cpp.obj: CMakeFiles/raftKVcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\OpenProject\RaftKVDatabase\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/raftKVcpp.dir/src/util.cpp.obj"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/raftKVcpp.dir/src/util.cpp.obj -MF CMakeFiles\raftKVcpp.dir\src\util.cpp.obj.d -o CMakeFiles\raftKVcpp.dir\src\util.cpp.obj -c D:\OpenProject\RaftKVDatabase\src\util.cpp

CMakeFiles/raftKVcpp.dir/src/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/raftKVcpp.dir/src/util.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\OpenProject\RaftKVDatabase\src\util.cpp > CMakeFiles\raftKVcpp.dir\src\util.cpp.i

CMakeFiles/raftKVcpp.dir/src/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/raftKVcpp.dir/src/util.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\OpenProject\RaftKVDatabase\src\util.cpp -o CMakeFiles\raftKVcpp.dir\src\util.cpp.s

# Object files for target raftKVcpp
raftKVcpp_OBJECTS = \
"CMakeFiles/raftKVcpp.dir/main.cpp.obj" \
"CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj" \
"CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj" \
"CMakeFiles/raftKVcpp.dir/src/util.cpp.obj"

# External object files for target raftKVcpp
raftKVcpp_EXTERNAL_OBJECTS =

raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/main.cpp.obj
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/src/Persister.cpp.obj
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/src/skiplist.cpp.obj
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/src/util.cpp.obj
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/build.make
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/linkLibs.rsp
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/objects1.rsp
raftKVcpp.exe: CMakeFiles/raftKVcpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\OpenProject\RaftKVDatabase\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable raftKVcpp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\raftKVcpp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raftKVcpp.dir/build: raftKVcpp.exe
.PHONY : CMakeFiles/raftKVcpp.dir/build

CMakeFiles/raftKVcpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\raftKVcpp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/raftKVcpp.dir/clean

CMakeFiles/raftKVcpp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\OpenProject\RaftKVDatabase D:\OpenProject\RaftKVDatabase D:\OpenProject\RaftKVDatabase\cmake-build-debug D:\OpenProject\RaftKVDatabase\cmake-build-debug D:\OpenProject\RaftKVDatabase\cmake-build-debug\CMakeFiles\raftKVcpp.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/raftKVcpp.dir/depend

