
FILE (GLOB SRC "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(libmodbus SHARED ${SRC})
set_target_properties(libmodbus PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER api/libmodbus.h)
configure_file(libmodbus.pc.in libmodbus.pc @ONLY)
target_include_directories(libmodbus PRIVATE .)
install(TARGETS libmodbus
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/libmodbus.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


add_subdirectory(tests)

set(EXAMPLE_NAME example)
include_directories(${CMAKE_SOURCE_DIR})
add_executable(${EXAMPLE_NAME} ${CMAKE_SOURCE_DIR}/example/main.cpp)
add_compile_options("-fno-stack-protector")
target_link_libraries(${EXAMPLE_NAME} libmodbus)