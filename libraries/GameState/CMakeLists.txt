add_library(GameState STATIC src/GameState.cpp)

target_include_directories(GameState PUBLIC include)
target_link_libraries(GameState PUBLIC State StateManager Collider LostState GameContext  Client PauseState Guardian Tyan Button Bullet Stone utils)
