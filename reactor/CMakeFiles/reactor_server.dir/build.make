# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luna/reactor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luna/reactor

# Include any dependencies generated for this target.
include CMakeFiles/reactor_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/reactor_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/reactor_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/reactor_server.dir/flags.make

CMakeFiles/reactor_server.dir/Main.cpp.o: CMakeFiles/reactor_server.dir/flags.make
CMakeFiles/reactor_server.dir/Main.cpp.o: Main.cpp
CMakeFiles/reactor_server.dir/Main.cpp.o: CMakeFiles/reactor_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/reactor/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/reactor_server.dir/Main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/reactor_server.dir/Main.cpp.o -MF CMakeFiles/reactor_server.dir/Main.cpp.o.d -o CMakeFiles/reactor_server.dir/Main.cpp.o -c /home/luna/reactor/Main.cpp

CMakeFiles/reactor_server.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/reactor_server.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/reactor/Main.cpp > CMakeFiles/reactor_server.dir/Main.cpp.i

CMakeFiles/reactor_server.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/reactor_server.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/reactor/Main.cpp -o CMakeFiles/reactor_server.dir/Main.cpp.s

# Object files for target reactor_server
reactor_server_OBJECTS = \
"CMakeFiles/reactor_server.dir/Main.cpp.o"

# External object files for target reactor_server
reactor_server_EXTERNAL_OBJECTS =

reactor_server: CMakeFiles/reactor_server.dir/Main.cpp.o
reactor_server: CMakeFiles/reactor_server.dir/build.make
reactor_server: CMakeFiles/reactor_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/luna/reactor/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable reactor_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reactor_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/reactor_server.dir/build: reactor_server
.PHONY : CMakeFiles/reactor_server.dir/build

CMakeFiles/reactor_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/reactor_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/reactor_server.dir/clean

CMakeFiles/reactor_server.dir/depend:
	cd /home/luna/reactor && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luna/reactor /home/luna/reactor /home/luna/reactor /home/luna/reactor /home/luna/reactor/CMakeFiles/reactor_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/reactor_server.dir/depend

