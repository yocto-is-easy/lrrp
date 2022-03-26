project(lrrp-example)

cmake_minimum_required(VERSION 3.8)

include_directories(../../include/)

add_executable(client
    src/client.cpp
)

add_executable(server
    src/server.cpp
)

target_link_libraries(client lrrp)
target_link_libraries(server lrrp)
