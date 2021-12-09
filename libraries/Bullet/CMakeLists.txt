add_library(Bullet STATIC src/Bullet.cpp)

target_include_directories(Bullet PUBLIC include)
target_link_libraries(Bullet PUBLIC Entity GameContext)
