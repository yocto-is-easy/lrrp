project(lrrp)

cmake_minimum_required(VERSION 3.8)

add_subdirectory(lib/googletest)

set(GTEST_DIR lib/googletest)

include_directories(
    ${GTEST_DIR}/googletest/include
)

set(LRRP_TEST ${CMAKE_PROJECT_NAME}-test)
add_executable(${LRRP_TEST}
    test/test_happy.cpp
)

target_link_libraries(${LRRP_TEST}
    gtest_main
)

