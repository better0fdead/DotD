cmake_minimum_required(VERSION 3.14)
project(Connect)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -Wall -ggdb3 -pthread")
set(SOCKET_LIB common/socket.cpp)


add_library(socket_lib STATIC ${SOCKET_LIB})
add_executable(Connecting src/Connecting.cpp)
target_link_libraries(Connecting socket_lib)
target_include_directories(Connecting PUBLIC include)
