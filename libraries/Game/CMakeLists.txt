add_library(Game STATIC src/Game.cpp)

target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC AssetManager StateManager MenuState GameContext LostState Button sfml-graphics sfml-window sfml-system)
