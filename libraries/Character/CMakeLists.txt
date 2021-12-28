add_library(Character STATIC src/Character.cpp)

target_include_directories(Character PUBLIC include)
target_link_libraries(Character PUBLIC Entity)
