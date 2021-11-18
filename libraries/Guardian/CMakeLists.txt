add_library(Guardian STATIC src/Guardian.cpp)

target_include_directories(Guardian PUBLIC include)
target_link_libraries(Guardian PUBLIC Character)
