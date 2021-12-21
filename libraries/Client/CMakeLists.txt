cmake_minimum_required(VERSION 3.14)
project(client)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES src/client.cpp)

add_library(utils STATIC ${SOURCES})
target_include_directories(utils PUBLIC include)


add_executable(main src/main.cpp)
target_link_libraries(main utils ${Boost_LIBRARIES})