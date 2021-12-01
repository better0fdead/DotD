add_library(PauseState STATIC src/PauseState.cpp)

target_include_directories(PauseState PUBLIC include)
target_link_libraries(PauseState PUBLIC State StateManager GameContext)
