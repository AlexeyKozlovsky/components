cmake_minimum_required(VERSION 3.14)
include(env.cmake)
project(plugin
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# PLUGIN_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(PLUGIN_BUILD_TESTS "Build plugin tests" OFF)
option(PLUGIN_BUILD_EXAMPLES "Build plugin examples" OFF)
option(PLUGIN_BUILD_DOCS "Build plugin documentation" OFF)
option(PLUGIN_INSTALL "Generate target for installing plugin" ${is_top_level})
set_if_undefined(PLUGIN_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/plugin" CACHE STRING
    "Install path for plugin package-related CMake files")

if(DEFINED PLUGIN_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${PLUGIN_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(plugin) # initialized below
add_library(plugin::plugin ALIAS plugin)

#----------------------------------------------------------------------------------------------------------------------
# plugin dependencies
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
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()

find_package(utils REQUIRED)
find_package(modbus REQUIRED)
find_package(threadpooling REQUIRED)
find_package(modbuswrappers REQUIRED)

target_link_libraries(${PROJECT_NAME}  utils::utils)
target_link_libraries(${PROJECT_NAME}  modbus::modbus)
target_link_libraries(${PROJECT_NAME}  threadpooling::threadpooling)
target_link_libraries(${PROJECT_NAME}  modbuswrappers::modbuswrappers)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)

if(WIN32)
    find_library(WSOCK32_LIBRARY wsock32)
    find_library(WS2_32_LIBRARY ws2_32)
    target_link_libraries(${PROJECT_NAME}  wsock32 ws2_32)

endif()

#----------------------------------------------------------------------------------------------------------------------
# plugin sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(plugin EXPORT_FILE_NAME include/plugin/${export_file_name})

file(GLOB sources
    include/plugin/*.h
    include/plugin/deviceplugins/*.h
    include/plugin/deviceplugins/commandproviders/*.h
    include/plugin/deviceplugins/abstracts/*.h
    include/plugin/deviceplugins/abstracts/creationpart/*.h
    include/plugin/deviceplugins/abstracts/managementpart/*.h
    include/plugin/storages/*.h
    include/plugin/storages/impls/*.h
    include/plugin/storages/impls/impl1/*.h

       src/plugin/*.cpp
       src/plugin/deviceplugins/*.cpp
       src/plugin/deviceplugins/commandproviders/*.cpp
       src/plugin/deviceplugins/abstracts/*.cpp
       src/plugin/deviceplugins/abstracts/creationpart/*.cpp
       src/plugin/deviceplugins/abstracts/managementpart/*.cpp
       src/plugin/storages/*.cpp
       src/plugin/storages/impls/*.cpp
       src/plugin/storages/impls/impl1/*.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# plugin target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(plugin PRIVATE ${sources})
target_compile_definitions(plugin PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:PLUGIN_STATIC_DEFINE>")

target_include_directories(plugin
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(plugin PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(PLUGIN_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/plugin-config.cmake.in plugin-config.cmake
        INSTALL_DESTINATION "${PLUGIN_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(plugin-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS plugin EXPORT plugin_export
        RUNTIME COMPONENT plugin
        LIBRARY COMPONENT plugin NAMELINK_COMPONENT plugin-dev
        ARCHIVE COMPONENT plugin-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT plugin-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/plugin/${export_file_name}"
        COMPONENT plugin-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/plugin")

    set(targets_file "plugin-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "plugin-static-targets.cmake")
    endif()

    install(EXPORT plugin_export
        COMPONENT plugin-dev
        FILE "${targets_file}"
        DESTINATION "${PLUGIN_INSTALL_CMAKEDIR}"
        NAMESPACE plugin::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/plugin-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/plugin-config-version.cmake"
        COMPONENT plugin-dev
        DESTINATION "${PLUGIN_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:plugin>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:plugin>/$<TARGET_FILE_PREFIX:plugin>$<TARGET_FILE_BASE_NAME:plugin>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT plugin-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(PLUGIN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(PLUGIN_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(PLUGIN_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
