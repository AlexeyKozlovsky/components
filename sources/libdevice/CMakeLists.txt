cmake_minimum_required(VERSION 3.2) # VERSION 3.24cd
project(deviced VERSION 1.0.1 DESCRIPTION "libdevice description")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_PREFIX "C:/Users/User/Documents/Career/Dialtek/components/sources/libdevice/libdeviced/")

set(BOOST_HEADERS_DIR "C:/Users/User/Documents/Soft/boost_include/")
set(MODBUS_LIB_DIR "c:/Users/User/Documents/Career/Dialtek/components/releases/windows/libmodbus/")


include_directories(${BOOST_HEADERS_DIR})
include_directories("${MODBUS_LIB_DIR}/include/")
include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SRC
        "${PROJECT_SOURCE_DIR}/services/*.cpp"
        "${PROJECT_SOURCE_DIR}/devices/*.cpp"
        "${PROJECT_SOURCE_DIR}/managers/*.cpp"
        "${PROJECT_SOURCE_DIR}/devices/modbus/*.cpp")

find_library(LIBMODUS_CMAKE NAMES modbusd
        PATHS ${MODBUS_LIB_DIR}
        NO_DEFAULT_PATH)

message("${LIBMODBUS_CMAKE}")

add_library(${PROJECT_NAME} SHARED ${SRC})
#link_directories(${MODBUS_LIB_DIR})
target_link_libraries(${PROJECT_NAME} "c:/Users/User/Documents/Career/Dialtek/components/releases/windows/libmodbus/libmodbusd.dll")
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        VERSION 1.0.0
        SOVERSION 1
        )
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )



if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/devices/*.h"
        "${PROJECT_SOURCE_DIR}/modbus/*.h"
        "${PROJECT_SOURCE_DIR}/managers/*.h"
        "${PROJECT_SOURCE_DIR}/services/*.h"
        )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${HEADERS} DESTINATION include/device)

#set(EXAMPLE_EXEC_NAME example)
#add_executable(${EXAMPLE_EXEC_NAME} ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/test/TestDevice.cpp)
#target_link_libraries(${EXAMPLE_EXEC_MAME} ${PROJECT_NAME})