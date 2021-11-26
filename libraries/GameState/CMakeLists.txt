add_library(GameState STATIC src/GameState.cpp)

target_include_directories(GameState PUBLIC include)
target_link_libraries(GameState PUBLIC State StateManager GameContext Guardian Tyan Button Bullet Stone)
