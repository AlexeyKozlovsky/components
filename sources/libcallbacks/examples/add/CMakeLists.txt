cmake_minimum_required(VERSION 3.14)
project(callbacks-add LANGUAGES CXX)
include(env.cmake)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(utils REQUIRED)
find_package(modbus REQUIRED)
find_package(modbuswrappers REQUIRED)
find_package(threadpooling REQUIRED)
find_package(plugin REQUIRED)
find_package(widgets REQUIRED)
find_package(callbacks REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
        Qt5::Widgets
        utils::utils
        modbus::modbus
        threadpooling::threadpooling
        modbuswrappers::modbuswrappers
        plugin::plugin
        widgets::widgets
        callbacks::callbacks
        )
