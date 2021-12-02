add_library(LoadState STATIC src/LoadState.cpp)

target_include_directories(LoadState PUBLIC include)
target_link_libraries(LoadState PUBLIC State StateManager GameContext Button sfml-audio Connecting)
