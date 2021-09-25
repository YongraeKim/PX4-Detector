cmake_minimum_required(VERSION 3.5)
project(udp2tcp
VERSION 1.0.0)
## System dependencies are found with CMake's conventions
find_package(Boost 1.58 REQUIRED COMPONENTS system thread filesystem)

include_directories(include
${Boost_INCLUDE_DIR})

link_libraries(
  ${Boost_SYSTEM_LIBRARY_RELEASE}
  ${Boost_THREAD_LIBRARY_RELEASE}
  ${Boost_TIMER_LIBRARY_RELEASE}
)

add_executable(udp2tcp src/main.cpp src/UDP_SOCKET.cpp src/TCP_SOCKET.cpp)
target_link_libraries (udp2tcp ${CMAKE_THREAD_LIBS_INIT})