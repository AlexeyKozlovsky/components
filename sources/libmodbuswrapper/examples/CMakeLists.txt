project(modbuswrappers_example
        VERSION 1.0.0
        DESCRIPTION "Template for C++ library built with CMake"
        LANGUAGES CXX)

include(env.cmake)

#find_package(modbuswrappers REQUIRED)

find_package(threadpooling REQUIRED)
find_package(utils REQUIRED)
find_package(modbus REQUIRED)

file(GLOB sources
        ../include/modbuswrappers/*.h
        ../include/modbuswrappers/mocks/*.h
        ../include/modbuswrappers/modbusasyncclientwrapper/*.h
        ../include/modbuswrappers/modbusclientwrapper/*.h
        ../include/modbuswrappers/modbuswrappermodbusiddecorator/*.h
        ../include/modbuswrappers/modbuspostponedwritewrapper/*.h
        ../include/modbuswrappers/storages/*.h
        ../src/modbuswrappers/*.cpp
        ../src/modbuswrappers/mocks/*.cpp
        ../src/modbuswrappers/modbusasyncclientwrapper/*.cpp
        ../src/modbuswrappers/modbusclientwrapper/*.cpp
        ../src/modbuswrappers/modbuswrappermodbusiddecorator/*.cpp
        ../src/modbuswrappers/modbuspostponedwritewrapper/*.cpp
        ../src/modbuswrappers/storages/*.cpp
        )

include_directories(../include)
add_executable(${PROJECT_NAME} ${sources} main.cpp)
target_link_libraries(${PROJECT_NAME}
        threadpooling::threadpooling
        utils::utils
        modbus::modbus)
#target_link_libraries(${PROJECT_NAME} modbuswrappers::modbuswrappers)
