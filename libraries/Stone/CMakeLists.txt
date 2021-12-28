add_library(Stone STATIC src/Stone.cpp)

target_include_directories(Stone PUBLIC include)
target_link_libraries(Stone PUBLIC Entity utils)
