cmake_minimum_required(VERSION 3.2) # VERSION 3.24cd
project(libdevice VERSION 1.0.1 DESCRIPTION "libdevice description")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)  # Странно, что 17 не берет

message(${BUILD_SYSTEM})
if (${BUILD_SYSTEM} STREQUAL "linux")
    include(build-linux.cmake)
elseif(${BUILD_SYSTEM} STREQUAL "win")
    include(build-win.cmake)
else()
    message(SEND_ERROR "Build system may be: linux or win")
endif()
