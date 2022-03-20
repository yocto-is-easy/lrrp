project(lrrp)

cmake_minimum_required(VERSION 3.8)

add_subdirectory(lib/googletest)
find_package(Boost 1.78 REQUIRED system regex)

set(GTEST_DIR lib/googletest)

include_directories(
    ${GTEST_DIR}/googletest/include
    ${Boost_INCLUDE_DIR}
)

set(LRRP_TEST ${CMAKE_PROJECT_NAME}-test)
add_executable(${LRRP_TEST}
    test/test_happy.cpp
    test/test_integration_asio.cpp
)

target_link_libraries(${LRRP_TEST}
    gtest_main
    ${Boost_LIBRARIES}
)
