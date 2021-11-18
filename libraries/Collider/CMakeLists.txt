add_library(Collider STATIC src/Collider.cpp)

target_include_directories(Collider PUBLIC include)
target_link_libraries(Collider PUBLIC sfml-graphics sfml-window sfml-system)
