add_library(LostState STATIC src/LostState.cpp)

target_include_directories(LostState PUBLIC include)
target_link_libraries(LostState PUBLIC State Button)
