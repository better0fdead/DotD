add_library(TyanState STATIC src/TyanState.cpp)

target_include_directories(TyanState PUBLIC include)
target_link_libraries(TyanState PUBLIC State StateManager GameContext AssetManager Button Client)
