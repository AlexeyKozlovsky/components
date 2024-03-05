project(plugin-example-1)

find_package(utils REQUIRED)
find_package(modbus REQUIRED)
find_package(modbuswrappers REQUIRED)
find_package(threadpooling REQUIRED)
find_package(plugin REQUIRED)
find_package(widgets REQUIRED)
find_package(callbacks REQUIRED)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package (Boost REQUIRED)

file(GLOB SRC )

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

#set(type "shared")