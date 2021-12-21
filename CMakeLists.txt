cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lboost_thread --coverage")
set(CMAKE_CXX_STANDARD 14)

add_compile_options("--coverage")


add_subdirectory(libraries/Client)



#enable_testing()
#find_package(GTest REQUIRED)
#add_executable(tests tests/tests.cpp)
#include_directories(${GTEST_INCLUDE_DIRS})
#target_link_libraries(tests ${GTEST_LIBRARIES} Game State Entity GameState LostState
#                        Character Collider Stone Tyan Guardian Bullet Button gcov)
