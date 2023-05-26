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


set(MODBUS_LIB_DIR /home/alexeykozlovsky/Documents/Career/Dialtek/components/releases/linux/libmodbus)
set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib:${MODBUS_LIB_DIR}")

include_directories(${CMAKE_SOURCE_DIR} ${MODBUS_LIB_DIR}/include)

find_library(LIBMODBUS_CMAKE
        NAMES libmodbus
        PATHS ${MODBUS_LIB_DIR})

message(${LIBMODBUS_CMAKE})

target_link_libraries(libdevice PUBLIC ${LIBMODBUS_CMAKE})
target_compile_features(libdevice PRIVATE cxx_std_17)
