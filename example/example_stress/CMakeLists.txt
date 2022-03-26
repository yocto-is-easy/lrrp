project(lrrp-example)

cmake_minimum_required(VERSION 3.8)

include_directories(../../include/)

add_executable(client-stress
    src/client.cpp
)

add_executable(server-stress
    src/server.cpp
)

target_link_libraries(client-stress lrrp)
target_link_libraries(server-stress lrrp)
