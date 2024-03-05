cmake_minimum_required(VERSION 3.14)
project(callbacks-add LANGUAGES CXX)
include(env.cmake)


set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(utils REQUIRED)
find_package(modbus REQUIRED)
find_package(modbuswrappers REQUIRED)
find_package(threadpooling REQUIRED)
find_package(widgets REQUIRED)
find_package(callbacks REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        utils::utils
        modbus::modbus
        threadpooling::threadpooling
        modbuswrappers::modbuswrappers
        widgets::widgets
        callbacks::callbacks
        )
