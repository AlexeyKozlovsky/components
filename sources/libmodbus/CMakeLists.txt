cmake_minimum_required(VERSION 3.4.0) #VERSION 3.24
project(modbusd)
#include(GenerateExportHeader)

set(LIB_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/libmodbusd)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_HEADERS_DIR "C:/Users/User/Documents/Soft/boost_include")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${BOOST_HEADERS_DIR})
file(GLOB SRC "${PROJECT_SOURCE_DIR}/*.cpp")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
add_library(${PROJECT_NAME} SHARED ${SRC})
if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()
#
#GENERATE_EXPORT_HEADER( ${PROJECT_NAME}
#        BASE_NAME ${PROJECT_NAME}
#        EXPORT_MACRO_NAME ${PROJECT_NAME}_EXPORT
#        EXPORT_FILE_NAME ${PROJECT_NAME}_Export.h
#        )

set(EXAMPLE_EXEC_NAME example)
add_executable(${EXAMPLE_EXEC_NAME} ${PROJECT_SOURCE_DIR}/example/main.cpp)
target_link_libraries(${EXAMPLE_EXEC_NAME} ${PROJECT_NAME})
if(WIN32)
    target_link_libraries(${EXAMPLE_EXEC_NAME} wsock32 ws2_32)
endif()

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/*.h")

set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        VERSION 1.0.0
        SOVERSION 1
        )


install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${LIB_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${LIB_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${LIB_INSTALL_PREFIX}/lib
        )

install(TARGETS ${PROJECT_NAME} DESTINATION ${LIB_INSTALL_PREFIX}/bin)
install(FILES ${HEADERS} DESTINATION ${LIB_INSTALL_PREFIX}/include)