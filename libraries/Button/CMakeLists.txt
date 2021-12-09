add_library(Button STATIC src/Button.cpp)

target_include_directories(Button PUBLIC include)
target_link_libraries(Button PUBLIC Entity sfml-graphics sfml-window sfml-system GameContext MenuState)
