add_library(ConnectingState STATIC src/ConnectingState.cpp)

target_include_directories(ConnectingState PUBLIC include)
target_link_libraries(ConnectingState PUBLIC State Button)