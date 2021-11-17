add_library(Game STATIC src/Game.cpp)

target_include_directories(Game PUBLIC include)
target_link_libraries(Game PUBLIC State sfml-graphics sfml-window sfml-system)
