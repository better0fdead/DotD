add_library(MenuState STATIC src/MenuState.cpp)

target_include_directories(MenuState PUBLIC include)
target_link_libraries(MenuState PUBLIC State StateManager GameContext)
