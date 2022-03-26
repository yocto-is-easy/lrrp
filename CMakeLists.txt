project(lrrp)

cmake_minimum_required(VERSION 3.8)

add_subdirectory(lib/googletest)
find_package(Boost 1.78 REQUIRED system regex thread)
add_subdirectory(lib/json)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(GTEST_DIR lib/googletest)
set(JSON_DIR lib/json)

include_directories(
    ${GTEST_DIR}/googletest/include
    ${Boost_INCLUDE_DIR}
    ${JSON_DIR}/include
    include/
)

add_library(lrrp
    src/request_builder.cpp
    src/request.cpp
    src/response_builder.cpp
    src/response.cpp
    src/client.cpp
    src/server.cpp
)

target_link_libraries(lrrp
    Threads::Threads
)

set(LRRP_TEST ${CMAKE_PROJECT_NAME}-test)
add_executable(${LRRP_TEST}
    test/test_happy.cpp
    test/test_integration_asio.cpp
    test/test_integration_json.cpp
    test/test_request.cpp
    test/test_response.cpp
)

target_link_libraries(${LRRP_TEST}
    gtest_main
    ${Boost_LIBRARIES}
    nlohmann_json::nlohmann_json
    lrrp
)
