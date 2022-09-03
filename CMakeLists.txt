project(lrrp)

cmake_minimum_required(VERSION 3.8)

find_package(Boost 1.72 REQUIRED system regex thread)

include_directories(
    ${Boost_INCLUDE_DIR}
    include/
)

install(DIRECTORY include DESTINATION /usr)
