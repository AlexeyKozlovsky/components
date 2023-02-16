cmake_minimum_required(VERSION 3.24)
project(libdevice VERSION 1.0.1 DESCRIPTION "libdevice description")
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/include/")

file(GLOB SRC
        "${PROJECT_SOURCE_DIR}/services/*.cpp"
        "${PROJECT_SOURCE_DIR}/devices/*.cpp"
        "${PROJECT_SOURCE_DIR}/managers/*.cpp"
        "${PROJECT_SOURCE_DIR}/devices/modbus/*.cpp")

add_library(libdevice SHARED ${SRC})
set_target_properties(libdevice PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER api/libdevice.h)
configure_file(libdevice.pc.in libdevice.pc @ONLY)
target_include_directories(libdevice PRIVATE .)
install(TARGETS libdevice
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/libdevice.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# ДЛЯ ТЕСТОВОГО МОДБАС ДЕВАЙСА

file(GLOB TEST_SRC "test/*.cpp")

set(MODBUS_LIB_DIR /home/alexeykozlovsky/Documents/Career/Dialtek/components/releases/linux/libmodbus)
set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib:${MODBUS_LIB_DIR}")

include_directories(${CMAKE_SOURCE_DIR} ${MODBUS_LIB_DIR}/include)

find_library(LIBMODBUS_CMAKE
        NAMES libmodbus
        PATHS ${MODBUS_LIB_DIR})

set(TEST_EXEC_NAME test_libdevice)
add_executable(${TEST_EXEC_NAME} ${TEST_SRC} main.cpp)

target_link_libraries(${TEST_EXEC_NAME} libdevice ${LIBMODBUS_CMAKE})

# For examples

set(EXAMPLE_EXEC_EPSS example-exec-epss)
set(EXAMPLE_EXEC_EPSS_DIR ${CMAKE_SOURCE_DIR}/examples/epss-device)

file(GLOB EXAMPLE_EXEC_EPSS_SRC "${EXAMPLE_EXEC_EPSS_DIR}/src/*.cpp")

add_executable(${EXAMPLE_EXEC_EPSS} ${EXAMPLE_EXEC_EPSS_SRC} ${EXAMPLE_EXEC_EPSS_DIR}/main.cpp)

target_link_libraries(${EXAMPLE_EXEC_EPSS} libdevice ${LIBMODBUS_CMAKE})

#add_executable(libdevice ${SRC} main.cpp)
