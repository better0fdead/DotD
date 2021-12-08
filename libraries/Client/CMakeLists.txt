cmake_minimum_required(VERSION 3.17)
project(client)

set(CMAKE_CXX_STANDARD 14)
SET(MYCOMPILE_FLAGS "-pthread -lboost_thread")
add_definitions(${MYCOMPILE_FLAGS})
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(client src/client.cpp)
target_link_libraries(client  ${Boost_LIBRARIES})

target_include_directories(client PUBLIC include)
