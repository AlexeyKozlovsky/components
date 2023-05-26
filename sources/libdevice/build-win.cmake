include_directories("boost")
set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_Fortran_COMPILER ${TOOLCHAIN_PREFIX}-gfortran)
set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32 /)
set(CMAKE_EXE_LINKER_FLAGS -static-libstdc++ -static-libgcc
        -Wl,-Bstatic,--whole-archive -lpthread -Wl,--no-whole-archive
        -L/mingw32/lib -Wl,-Bstatic -lboost_system-mt -lws2_32 -lwsock32)

add_compile_definitions(FOR_WIN)


# FOR WINDOWS CROSS COMPILE END

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

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
        SUFFIX ".dll"
        PUBLIC_HEADER api/libdevice.h)
configure_file(libdevice.pc.in libdevice.pc @ONLY)
target_include_directories(libdevice PRIVATE .)
install(TARGETS libdevice
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/libdevice.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# ДЛЯ ТЕСТОВОГО МОДБАС ДЕВАЙСА

#file(GLOB TEST_SRC "test/*.cpp")
#
set(MODBUS_LIB_DIR /home/alexeykozlovsky/Documents/Career/Dialtek/components/releases/windows/libmodbus)
#set(CMAKE_EXE_LINKER_FLAGS
#        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib:${MODBUS_LIB_DIR}")
#
include_directories(${CMAKE_SOURCE_DIR} ${MODBUS_LIB_DIR}/include)

find_library(LIBMODBUS_CMAKE
        NAMES libmodbus
        PATHS ${MODBUS_LIB_DIR})

#message(${LIBMODBUS_CMAKE})

# ЛИНКОВКА НАПРЯМУЮ!!! Find_library не ищет dll

target_link_libraries(libdevice PRIVATE /home/alexeykozlovsky/Documents/Career/Dialtek/cross-compile/openssl/libssl.a /home/alexeykozlovsky/Documents/Career/Dialtek/cross-compile/openssl/libcrypto.a crypt32 ws2_32)
target_link_libraries(libdevice PUBLIC /home/alexeykozlovsky/Documents/Career/Dialtek/components/releases/windows/libmodbus/liblibmodbus.dll)
target_compile_features(libdevice PRIVATE cxx_std_17)
