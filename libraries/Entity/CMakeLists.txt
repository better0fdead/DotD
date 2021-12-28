add_library(Entity STATIC src/Entity.cpp)

target_include_directories(Entity PUBLIC include)
target_link_libraries(Entity PUBLIC Collider)
