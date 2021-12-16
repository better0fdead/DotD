add_library(GameState STATIC src/GameState.cpp)

target_include_directories(GameState PUBLIC include ../../assets/textures)
target_link_libraries(GameState PUBLIC State StateManager Collider LostState GameContext PauseState Guardian Tyan Button Bullet Stone utils)
