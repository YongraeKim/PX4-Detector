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
CMAKE_SOURCE_DIR = /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel

# Include any dependencies generated for this target.
include CMakeFiles/upd2tcp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/upd2tcp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/upd2tcp.dir/flags.make

CMakeFiles/upd2tcp.dir/src/main.cpp.o: CMakeFiles/upd2tcp.dir/flags.make
CMakeFiles/upd2tcp.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/upd2tcp.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/upd2tcp.dir/src/main.cpp.o -c /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/main.cpp

CMakeFiles/upd2tcp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/upd2tcp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/main.cpp > CMakeFiles/upd2tcp.dir/src/main.cpp.i

CMakeFiles/upd2tcp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/upd2tcp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/main.cpp -o CMakeFiles/upd2tcp.dir/src/main.cpp.s

CMakeFiles/upd2tcp.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/upd2tcp.dir/src/main.cpp.o.requires

CMakeFiles/upd2tcp.dir/src/main.cpp.o.provides: CMakeFiles/upd2tcp.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/upd2tcp.dir/build.make CMakeFiles/upd2tcp.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/upd2tcp.dir/src/main.cpp.o.provides

CMakeFiles/upd2tcp.dir/src/main.cpp.o.provides.build: CMakeFiles/upd2tcp.dir/src/main.cpp.o


# Object files for target upd2tcp
upd2tcp_OBJECTS = \
"CMakeFiles/upd2tcp.dir/src/main.cpp.o"

# External object files for target upd2tcp
upd2tcp_EXTERNAL_OBJECTS =

upd2tcp: CMakeFiles/upd2tcp.dir/src/main.cpp.o
upd2tcp: CMakeFiles/upd2tcp.dir/build.make
upd2tcp: CMakeFiles/upd2tcp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable upd2tcp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/upd2tcp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/upd2tcp.dir/build: upd2tcp

.PHONY : CMakeFiles/upd2tcp.dir/build

CMakeFiles/upd2tcp.dir/requires: CMakeFiles/upd2tcp.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/upd2tcp.dir/requires

CMakeFiles/upd2tcp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/upd2tcp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/upd2tcp.dir/clean

CMakeFiles/upd2tcp.dir/depend:
	cd /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles/upd2tcp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/upd2tcp.dir/depend

