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
CMAKE_SOURCE_DIR = /home/luna/Epoll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luna/Epoll

# Include any dependencies generated for this target.
include CMakeFiles/Client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/Client.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Client.cpp.o: Client.cpp
CMakeFiles/Client.dir/Client.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luna/Epoll/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/Client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/Client.cpp.o -MF CMakeFiles/Client.dir/Client.cpp.o.d -o CMakeFiles/Client.dir/Client.cpp.o -c /home/luna/Epoll/Client.cpp

CMakeFiles/Client.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Client.dir/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luna/Epoll/Client.cpp > CMakeFiles/Client.dir/Client.cpp.i

CMakeFiles/Client.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luna/Epoll/Client.cpp -o CMakeFiles/Client.dir/Client.cpp.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/Client.cpp.o"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client: CMakeFiles/Client.dir/Client.cpp.o
Client: CMakeFiles/Client.dir/build.make
Client: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/luna/Epoll/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: Client
.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	cd /home/luna/Epoll && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luna/Epoll /home/luna/Epoll /home/luna/Epoll /home/luna/Epoll /home/luna/Epoll/CMakeFiles/Client.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Client.dir/depend

