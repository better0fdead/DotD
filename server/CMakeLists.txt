cmake_minimum_required(VERSION 3.14)
project(sever)

set(CMAKE_CXX_STANDARD 14)

set(SOCKET_LIB common/socket.cpp)
add_library(socket_lib STATIC ${SOCKET_LIB})
add_executable(server src/server.cpp)
target_link_libraries(server socket_lib)

target_include_directories(server PUBLIC include)
