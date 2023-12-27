cmake_minimum_required(VERSION 3.14)
include(env.cmake)

project(modbus
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# MODBUS_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(MODBUS_BUILD_TESTS "Build modbus tests" OFF)
option(MODBUS_BUILD_EXAMPLES "Build modbus examples" OFF)
option(MODBUS_BUILD_DOCS "Build modbus documentation" OFF)
option(MODBUS_INSTALL "Generate target for installing modbus" ${is_top_level})
set_if_undefined(MODBUS_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/modbus" CACHE STRING
    "Install path for modbus package-related CMake files")

if(DEFINED MODBUS_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${MODBUS_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(modbus) # initialized below
add_library(modbus::modbus ALIAS modbus)

#----------------------------------------------------------------------------------------------------------------------
# modbus dependencies
#----------------------------------------------------------------------------------------------------------------------

set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

# Подключаем необходимые модули. Для примера подключим program_options
find_package (Boost REQUIRED)

# Если библиотека найдена, то
if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    target_link_libraries (${PROJECT_NAME}  ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()


find_package(utils REQUIRED)
target_link_libraries(${PROJECT_NAME}  utils::utils)

#----------------------------------------------------------------------------------------------------------------------
# modbus sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(modbus EXPORT_FILE_NAME include/modbus/${export_file_name})

file(GLOB sources
    include/modbus/*.h
    src/modbus/*.cpp
        )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# modbus target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(modbus PRIVATE ${sources})
target_compile_definitions(modbus PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:MODBUS_STATIC_DEFINE>")

target_include_directories(modbus
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(modbus PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(MODBUS_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/modbus-config.cmake.in modbus-config.cmake
        INSTALL_DESTINATION "${MODBUS_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(modbus-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS modbus EXPORT modbus_export
        RUNTIME COMPONENT modbus
        LIBRARY COMPONENT modbus NAMELINK_COMPONENT modbus-dev
        ARCHIVE COMPONENT modbus-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT modbus-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/modbus/${export_file_name}"
        COMPONENT modbus-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/modbus")

    set(targets_file "modbus-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "modbus-static-targets.cmake")
    endif()

    install(EXPORT modbus_export
        COMPONENT modbus-dev
        FILE "${targets_file}"
        DESTINATION "${MODBUS_INSTALL_CMAKEDIR}"
        NAMESPACE modbus::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/modbus-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/modbus-config-version.cmake"
        COMPONENT modbus-dev
        DESTINATION "${MODBUS_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:modbus>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:modbus>/$<TARGET_FILE_PREFIX:modbus>$<TARGET_FILE_BASE_NAME:modbus>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT modbus-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(MODBUS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MODBUS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(MODBUS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
