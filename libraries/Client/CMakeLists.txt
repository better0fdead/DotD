add_library(Client STATIC src/client.cpp)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(Client PUBLIC include)
target_link_libraries(Client PUBLIC Bullet Stone ${Boost_LIBRARIES})
