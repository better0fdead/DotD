add_library(State STATIC src/State.cpp)

target_include_directories(State PUBLIC include)
target_link_libraries(State PUBLIC sfml-graphics sfml-window sfml-system)
