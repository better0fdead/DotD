add_library(utils STATIC src/utils.cpp)

target_include_directories(utils PUBLIC include)
target_link_libraries(utils PUBLIC GameContext)
