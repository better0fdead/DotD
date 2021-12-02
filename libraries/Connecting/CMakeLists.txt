add_library(Connecting STATIC src/Connecting.cpp)

target_include_directories(Connecting PUBLIC include)

target_link_libraries(Connecting socket_lib)
