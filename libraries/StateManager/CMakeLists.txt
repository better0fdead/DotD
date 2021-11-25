add_library(StateManager STATIC src/StateManager.cpp)

target_include_directories(StateManager PUBLIC include)
target_link_libraries(StateManager PUBLIC State MenuState)
