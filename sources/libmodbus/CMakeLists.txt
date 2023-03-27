cmake_minimum_required(VERSION 3.2) #VERSION 3.24
project(libmodbus VERSION 1.0.1 DESCRIPTION "libmodbus description")
include(GNUInstallDirs)

message(${BUILD_SYSTEM})
if (${BUILD_SYSTEM} STREQUAL "linux")
    include(build-linux.cmake)
elseif(${BUILD_SYSTEM} STREQUAL "win")
    include(build-win.cmake)
else()
    message(SEND_ERROR "Build system may be: linux or win")
endif()