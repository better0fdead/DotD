cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libraries/Game)
add_subdirectory(libraries/State)
add_subdirectory(libraries/GameState)
add_subdirectory(libraries/LostState)
add_subdirectory(libraries/Entity)
add_subdirectory(libraries/Character)
add_subdirectory(libraries/Collider)
add_subdirectory(libraries/Tyan)
add_subdirectory(libraries/Guardian)
add_subdirectory(libraries/Bullet)

add_executable(test test.cpp)
target_link_libraries(test PUBLIC Game State Bullet)
