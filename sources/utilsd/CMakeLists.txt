cmake_minimum_required(VERSION 3.14)
message(${TARGET_SYSTEM})
if(${TARGET_SYSTEM} STREQUAL linux)
    message("F")
    include(env-linux.cmake)
elseif(${TARGET_SYSTEM} STREQUAL win)
    include(env.cmake)
endif()

project(utils
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# LIB_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(LIB_BUILD_TESTS "Build utils tests" OFF)
option(LIB_BUILD_EXAMPLES "Build utils examples" OFF)
option(UTILS_BUILD_DOCS "Build utils documentation" OFF)
option(LIB_INSTALL "Generate target for installing utils" ${is_top_level})
set_if_undefined(LIB_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/utils" CACHE STRING
    "Install path for utils package-related CMake files")

if(DEFINED LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${LIB_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(utils) # initialized below
add_library(utils::utils ALIAS utils)

#----------------------------------------------------------------------------------------------------------------------
# utils dependencies
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


#----------------------------------------------------------------------------------------------------------------------
# utils sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(utils EXPORT_FILE_NAME include/utils/${export_file_name})

file(GLOB sources
        include/utils/*.h
        include/utils/storages/*.h
        include/utils/services/*.h
        include/utils/services/domain/*.h
        include/utils/services/domain/impls/*.h
        include/utils/services/uidgeneratorimpls/*.h
        include/utils/services/uidgeneratorimpls/boost/*.h

        src/utils/*.cpp
        src/utils/storages/*.cpp
        src/utils/services/*.cpp
        src/utils/services/domain/*.cpp
        src/utils/services/domain/impls/*.cpp
        src/utils/services/uidgeneratorimpls/*.cpp
        src/utils/services/uidgeneratorimpls/boost/*.cpp

        )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# utils target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(utils PRIVATE ${sources})
target_compile_definitions(utils PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:UTILS_STATIC_DEFINE>")

target_include_directories(utils
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(utils PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/utils-config.cmake.in utils-config.cmake
        INSTALL_DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(utils-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS utils EXPORT utils_export
        RUNTIME COMPONENT utils
        LIBRARY COMPONENT utils NAMELINK_COMPONENT utils-dev
        ARCHIVE COMPONENT utils-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT utils-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/utils/${export_file_name}"
        COMPONENT utils-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utils")

    set(targets_file "utils-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "utils-static-targets.cmake")
    endif()

    install(EXPORT utils_export
        COMPONENT utils-dev
        FILE "${targets_file}"
        DESTINATION "${LIB_INSTALL_CMAKEDIR}"
        NAMESPACE utils::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/utils-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/utils-config-version.cmake"
        COMPONENT utils-dev
        DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:utils>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:utils>/$<TARGET_FILE_PREFIX:utils>$<TARGET_FILE_BASE_NAME:utils>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT utils-dev
            CONFIGURATIONS ${CMAKE_BUILD_TYPE}
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(LIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(LIB_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(UTILS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
