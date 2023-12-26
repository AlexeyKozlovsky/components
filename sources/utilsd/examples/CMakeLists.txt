cmake_minimum_required(VERSION 3.14)
project(utils-example LANGUAGES CXX)

include(env.cmake)


# BOOST DEP PART
include_directories(${BOOST_HEADERS_DIR})



find_package(utils REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} utils::utils)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()