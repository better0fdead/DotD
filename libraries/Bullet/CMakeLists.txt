add_library(Bullet STATIC src/Stone.cpp)

target_include_directories(Bullet PUBLIC include)
target_link_libraries(Bullet PUBLIC Entity)
