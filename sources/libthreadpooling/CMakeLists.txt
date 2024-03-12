cmake_minimum_required(VERSION 3.14)

if(${TARGET_SYSTEM} STREQUAL linux)
    message("F")
    include(env-linux.cmake)
elseif(${TARGET_SYSTEM} STREQUAL win)
    include(env.cmake)
endif()

project(threadpooling
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
option(LIB_BUILD_TESTS "Build threadpooling tests" OFF)
option(LIB_BUILD_EXAMPLES "Build threadpooling examples" OFF)
option(THREADPOOLING_BUILD_DOCS "Build threadpooling documentation" OFF)
option(LIB_INSTALL "Generate target for installing threadpooling" ${is_top_level})
set_if_undefined(LIB_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/threadpooling" CACHE STRING
    "Install path for threadpooling package-related CMake files")

if(DEFINED LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${LIB_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(threadpooling) # initialized below
add_library(threadpooling::threadpooling ALIAS threadpooling)

#----------------------------------------------------------------------------------------------------------------------
# threadpooling dependencies
#----------------------------------------------------------------------------------------------------------------------

find_package(utils REQUIRED)
target_link_libraries(${PROJECT_NAME}  utils::utils)

#----------------------------------------------------------------------------------------------------------------------
# threadpooling sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(threadpooling EXPORT_FILE_NAME include/threadpooling/${export_file_name})

file(GLOB sources
    include/threadpooling/*.h
    include/threadpooling/impls/.h
    src/threadpooling/*.cpp
    src/threadpooling/impls/*.cpp
    src/threadpooling/impls/periodic/*.cpp
        )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# threadpooling target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(threadpooling PRIVATE ${sources})
target_compile_definitions(threadpooling PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:THREADPOOLING_STATIC_DEFINE>")

target_include_directories(threadpooling
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(threadpooling PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/threadpooling-config.cmake.in threadpooling-config.cmake
        INSTALL_DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(threadpooling-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS threadpooling EXPORT threadpooling_export
        RUNTIME COMPONENT threadpooling
        LIBRARY COMPONENT threadpooling NAMELINK_COMPONENT threadpooling-dev
        ARCHIVE COMPONENT threadpooling-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT threadpooling-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/threadpooling/${export_file_name}"
        COMPONENT threadpooling-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/threadpooling")

    set(targets_file "threadpooling-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "threadpooling-static-targets.cmake")
    endif()

    install(EXPORT threadpooling_export
        COMPONENT threadpooling-dev
        FILE "${targets_file}"
        DESTINATION "${LIB_INSTALL_CMAKEDIR}"
        NAMESPACE threadpooling::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/threadpooling-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/threadpooling-config-version.cmake"
        COMPONENT threadpooling-dev
        DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:threadpooling>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:threadpooling>/$<TARGET_FILE_PREFIX:threadpooling>$<TARGET_FILE_BASE_NAME:threadpooling>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT threadpooling-dev
            CONFIGURATIONS Debug RelWithDebInfo
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

if(THREADPOOLING_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
