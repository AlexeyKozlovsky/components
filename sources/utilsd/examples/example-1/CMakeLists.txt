cmake_minimum_required(VERSION 3.14)
project(utils-example-1 LANGUAGES CXX)

include(env.cmake)

find_package (Boost REQUIRED)
find_package(utils REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} utils::utils)

if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    target_link_libraries (${PROJECT_NAME}  ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()