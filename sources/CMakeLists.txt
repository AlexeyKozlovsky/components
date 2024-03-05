cmake_minimum_required(VERSION 3.14)
project(dt-components
        VERSION 1.0.0
        DESCRIPTION "Template for C++ library built with CMake"
        LANGUAGES CXX)

include(env.cmake)

add_subdirectory(utilsd)
add_subdirectory(libmodbus)
#add_subdirectory(libthreadpooling)
#add_subdirectory(libmodbuswrapper)
#add_subdirectory(libcallbacks)
#add_subdirectory(libwidgets)
#add_subdirectory(libplugin)