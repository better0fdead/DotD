cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libraries/Server)
add_subdirectory(libraries/ConnectingPeople)
add_subdirectory(libraries/ConnectingState)

enable_testing()
add_executable(tests tests/tests.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(tests ${GTEST_LIBRARIES} Server ConnectingState ConnectingPeople)

add_executable(test test.cpp)
target_link_libraries(test PUBLIC Game State Entity)