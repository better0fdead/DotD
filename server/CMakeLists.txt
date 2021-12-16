cmake_minimum_required(VERSION 3.14)
project(server)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(server src/server.cpp)
target_link_libraries(server  ${Boost_LIBRARIES})

target_include_directories(server PUBLIC include)
