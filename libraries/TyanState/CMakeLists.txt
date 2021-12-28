add_library(TyanState STATIC src/TyanState.cpp)

target_include_directories(TyanState PUBLIC include)
target_link_libraries(TyanState PUBLIC Tasks State StateManager GameContext AssetManager LostState Button Client Tyan Guardian)
