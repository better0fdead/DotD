add_library(AssetManager STATIC src/AssetManager.cpp)

target_include_directories(AssetManager PUBLIC include)
target_link_libraries(AssetManager PUBLIC StateManager GameState)