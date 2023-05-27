cmake_minimum_required(VERSION 3.2) #VERSION 3.24
project(libmodbus VERSION 1.0.1 DESCRIPTION "libmodbus description")

set(BOOST_HEADERS_DIR "C:/Users/User/Documents/Soft/boost_include")

include_directories(${BOOST_HEADERS_DIR})
file(GLOB SRC "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SRC})
if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()