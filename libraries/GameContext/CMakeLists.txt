add_library(GameContext STATIC src/GameContext.cpp)

target_include_directories(GameContext PUBLIC include)
target_link_libraries(GameContext PUBLIC AssetManager StateManager)
