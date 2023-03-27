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
set(CMAKE_EXE_LINKER_FLAGS -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lpthread -Wl,--no-whole-archive -L/mingw32/lib -Wl,-Bstatic -lboost_system-mt -lws2_32 -lwsock32)

add_compile_definitions(FOR_WIN)


# FOR WINDOWS CROSS COMPILE END

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


FILE (GLOB SRC "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(libmodbus SHARED ${SRC})
set_target_properties(libmodbus PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        SUFFIX ".dll"
        PUBLIC_HEADER api/libmodbus.h)
configure_file(libmodbus.pc.in libmodbus.pc @ONLY)
target_include_directories(libmodbus PRIVATE .)
install(TARGETS libmodbus
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/libmodbus.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

target_link_libraries(libmodbus PRIVATE /home/alexeykozlovsky/Documents/Career/Dialtek/cross-compile/openssl/libssl.a /home/alexeykozlovsky/Documents/Career/Dialtek/cross-compile/openssl/libcrypto.a crypt32 ws2_32)

