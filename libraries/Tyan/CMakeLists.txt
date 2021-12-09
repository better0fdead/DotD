add_library(Tyan STATIC src/Tyan.cpp)

target_include_directories(Tyan PUBLIC include)
target_link_libraries(Tyan PUBLIC Character)
