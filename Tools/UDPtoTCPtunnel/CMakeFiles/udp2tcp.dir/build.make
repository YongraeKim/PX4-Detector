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
include CMakeFiles/udp2tcp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/udp2tcp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/udp2tcp.dir/flags.make

CMakeFiles/udp2tcp.dir/src/main.cpp.o: CMakeFiles/udp2tcp.dir/flags.make
CMakeFiles/udp2tcp.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/udp2tcp.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/udp2tcp.dir/src/main.cpp.o -c /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/main.cpp

CMakeFiles/udp2tcp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/udp2tcp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/main.cpp > CMakeFiles/udp2tcp.dir/src/main.cpp.i

CMakeFiles/udp2tcp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/udp2tcp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/main.cpp -o CMakeFiles/udp2tcp.dir/src/main.cpp.s

CMakeFiles/udp2tcp.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/udp2tcp.dir/src/main.cpp.o.requires

CMakeFiles/udp2tcp.dir/src/main.cpp.o.provides: CMakeFiles/udp2tcp.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/udp2tcp.dir/build.make CMakeFiles/udp2tcp.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/udp2tcp.dir/src/main.cpp.o.provides

CMakeFiles/udp2tcp.dir/src/main.cpp.o.provides.build: CMakeFiles/udp2tcp.dir/src/main.cpp.o


CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o: CMakeFiles/udp2tcp.dir/flags.make
CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o: src/UDP_SOCKET.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o -c /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/UDP_SOCKET.cpp

CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/UDP_SOCKET.cpp > CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.i

CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/src/UDP_SOCKET.cpp -o CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.s

CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.requires:

.PHONY : CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.requires

CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.provides: CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.requires
	$(MAKE) -f CMakeFiles/udp2tcp.dir/build.make CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.provides.build
.PHONY : CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.provides

CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.provides.build: CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o


# Object files for target udp2tcp
udp2tcp_OBJECTS = \
"CMakeFiles/udp2tcp.dir/src/main.cpp.o" \
"CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o"

# External object files for target udp2tcp
udp2tcp_EXTERNAL_OBJECTS =

udp2tcp: CMakeFiles/udp2tcp.dir/src/main.cpp.o
udp2tcp: CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o
udp2tcp: CMakeFiles/udp2tcp.dir/build.make
udp2tcp: /usr/lib/x86_64-linux-gnu/libboost_system.so
udp2tcp: /usr/lib/x86_64-linux-gnu/libboost_thread.so
udp2tcp: CMakeFiles/udp2tcp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable udp2tcp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/udp2tcp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/udp2tcp.dir/build: udp2tcp

.PHONY : CMakeFiles/udp2tcp.dir/build

CMakeFiles/udp2tcp.dir/requires: CMakeFiles/udp2tcp.dir/src/main.cpp.o.requires
CMakeFiles/udp2tcp.dir/requires: CMakeFiles/udp2tcp.dir/src/UDP_SOCKET.cpp.o.requires

.PHONY : CMakeFiles/udp2tcp.dir/requires

CMakeFiles/udp2tcp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/udp2tcp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/udp2tcp.dir/clean

CMakeFiles/udp2tcp.dir/depend:
	cd /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel /home/yrkim/PX4-Swon/Tools/UDPtoTCPtunnel/CMakeFiles/udp2tcp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/udp2tcp.dir/depend
