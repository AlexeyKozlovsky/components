cmake_minimum_required(VERSION 3.4.0) #VERSION 3.24
project(modbustcpd)
#include(GenerateExportHeader)

set(LIB_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/libmodbustcpd)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_HEADERS_DIR "C:/Users/User/Documents/Soft/boost_include")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${BOOST_HEADERS_DIR})

set(UTILS_LIB_DIR "c:/Users/User/Documents/Career/Dialtek/components/releases/windows/libutilsd")
include_directories(${UTILS_LIB_DIR}/include)

file(GLOB SRC
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/services/*.cpp"
        "${PROJECT_SOURCE_DIR}/services/responses/*.cpp"
        "${PROJECT_SOURCE_DIR}/services/requests/*.cpp"
        "${PROJECT_SOURCE_DIR}/managers/*.cpp"
        "${PROJECT_SOURCE_DIR}/creators/*.cpp"
        "${PROJECT_SOURCE_DIR}/utils/*.cpp"
        )

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

#set(EXAMPLE_EXEC_NAME example)
#add_executable(${EXAMPLE_EXEC_NAME} ${PROJECT_SOURCE_DIR}/example/main.cpp)
#target_link_libraries(${EXAMPLE_EXEC_NAME} ${PROJECT_NAME})
#if(WIN32)
#    target_link_libraries(${EXAMPLE_EXEC_NAME} wsock32 ws2_32)
#endif()

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

set(EXAMPLE_EXEC_NAME example)
file(GLOB EXAMPLE_SRC
        ${PROJECT_SOURCE_DIR}/example/*.cpp)

add_executable(${EXAMPLE_EXEC_NAME} ${SRC} ${EXAMPLE_SRC})
#target_link_libraries(${EXAMPLE_EXEC_NAME} ${PROJECT_NAME})
if(WIN32)
    target_link_libraries(${EXAMPLE_EXEC_NAME} wsock32 ws2_32)
endif()
