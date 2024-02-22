cmake_minimum_required(VERSION 3.14)
include(env.cmake)
project(widgets
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
option(LIB_BUILD_TESTS "Build widgets tests" OFF)
option(LIB_BUILD_EXAMPLES "Build widgets examples" OFF)
option(WIDGETS_BUILD_DOCS "Build widgets documentation" OFF)
option(LIB_INSTALL "Generate target for installing widgets" ${is_top_level})
set_if_undefined(LIB_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/widgets" CACHE STRING
    "Install path for widgets package-related CMake files")

if(DEFINED LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${LIB_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(widgets) # initialized below
add_library(widgets::widgets ALIAS widgets)

#----------------------------------------------------------------------------------------------------------------------
# widgets dependencies
#----------------------------------------------------------------------------------------------------------------------


find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)

if(WIN32)
    find_library(WSOCK32_LIBRARY wsock32)
    find_library(WS2_32_LIBRARY ws2_32)
    target_link_libraries(${PROJECT_NAME}  wsock32 ws2_32)

endif()

#----------------------------------------------------------------------------------------------------------------------
# widgets sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(widgets EXPORT_FILE_NAME include/widgets/${export_file_name})

file(GLOB sources
        include/widgets/*.h
        include/widgets/stylesheets/*.h
        include/widgets/common/*.h
        include/widgets/common/basic/*.h
        include/widgets/common/composed/*.h

        src/widgets/*.cpp
        src/widgets/common/*.cpp
        src/widgets/common/basic/*.cpp
        src/widgets/common/composed/*.cpp
        )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# widgets target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(widgets PRIVATE ${sources})
target_compile_definitions(widgets PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:WIDGETS_STATIC_DEFINE>")

target_include_directories(widgets
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(widgets PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/widgets-config.cmake.in widgets-config.cmake
        INSTALL_DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(widgets-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS widgets EXPORT widgets_export
        RUNTIME COMPONENT widgets
        LIBRARY COMPONENT widgets NAMELINK_COMPONENT widgets-dev
        ARCHIVE COMPONENT widgets-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT widgets-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/widgets/${export_file_name}"
        COMPONENT widgets-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/widgets")

    set(targets_file "widgets-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "widgets-static-targets.cmake")
    endif()

    install(EXPORT widgets_export
        COMPONENT widgets-dev
        FILE "${targets_file}"
        DESTINATION "${LIB_INSTALL_CMAKEDIR}"
        NAMESPACE widgets::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/widgets-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/widgets-config-version.cmake"
        COMPONENT widgets-dev
        DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:widgets>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:widgets>/$<TARGET_FILE_PREFIX:widgets>$<TARGET_FILE_BASE_NAME:widgets>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT widgets-dev
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

if(WIDGETS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
