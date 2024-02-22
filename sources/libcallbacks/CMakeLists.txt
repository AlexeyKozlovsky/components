cmake_minimum_required(VERSION 3.14)
project(callbacks
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

include(env.cmake)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# LIB_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(LIB_BUILD_TESTS "Build callbacks tests" OFF)
option(LIB_BUILD_EXAMPLES "Build callbacks examples" OFF)
option(CALLBACKS_BUILD_DOCS "Build callbacks documentation" OFF)
option(LIB_INSTALL "Generate target for installing callbacks" ${is_top_level})
set_if_undefined(LIB_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/callbacks" CACHE STRING
    "Install path for callbacks package-related CMake files")

if(DEFINED LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${LIB_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(callbacks) # initialized below
add_library(callbacks::callbacks ALIAS callbacks)

#----------------------------------------------------------------------------------------------------------------------
# callbacks dependencies
#----------------------------------------------------------------------------------------------------------------------

find_package (Boost REQUIRED)

# Если библиотека найдена, то
if (Boost_FOUND)
    include_directories (${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
    target_link_libraries (${PROJECT_NAME}  ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)


find_package(utils REQUIRED)
find_package(modbus REQUIRED)
find_package(threadpooling REQUIRED)
find_package(modbuswrappers REQUIRED)

target_link_libraries(${PROJECT_NAME}  utils::utils)
target_link_libraries(${PROJECT_NAME}  modbus::modbus)
target_link_libraries(${PROJECT_NAME}  threadpooling::threadpooling)
target_link_libraries(${PROJECT_NAME}  modbuswrappers::modbuswrappers)


#----------------------------------------------------------------------------------------------------------------------
# callbacks sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(callbacks EXPORT_FILE_NAME include/callbacks/${export_file_name})

file(GLOB sources
        include/callbacks/*.h
        include/callbacks/models/*.h
        include/callbacks/models/impls/*.h
        include/callbacks/models/impls/standaloneimpl/*.h
        include/callbacks/models/impls/standaloneimpl/background/*.h
        include/callbacks/models/impls/standaloneimpl/background/impl3/*.h

    src/models/*.cpp
    src/models/impls/*.cpp
    src/models/impls/standaloneimpl/*.cpp
    src/models/impls/standaloneimpl/background/*.cpp
    src/models/impls/standaloneimpl/background/impl3/*.cpp

        )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# callbacks target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(callbacks PRIVATE ${sources})
target_compile_definitions(callbacks PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:LIB_STATIC_DEFINE>")

target_include_directories(callbacks
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(callbacks PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/callbacks-config.cmake.in callbacks-config.cmake
        INSTALL_DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(callbacks-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS callbacks EXPORT callbacks_export
        RUNTIME COMPONENT callbacks
        LIBRARY COMPONENT callbacks NAMELINK_COMPONENT callbacks-dev
        ARCHIVE COMPONENT callbacks-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT callbacks-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/callbacks/${export_file_name}"
        COMPONENT callbacks-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/callbacks")

    set(targets_file "callbacks-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "callbacks-static-targets.cmake")
    endif()

    install(EXPORT callbacks_export
        COMPONENT callbacks-dev
        FILE "${targets_file}"
        DESTINATION "${LIB_INSTALL_CMAKEDIR}"
        NAMESPACE callbacks::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/callbacks-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/callbacks-config-version.cmake"
        COMPONENT callbacks-dev
        DESTINATION "${LIB_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:callbacks>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:callbacks>/$<TARGET_FILE_PREFIX:callbacks>$<TARGET_FILE_BASE_NAME:callbacks>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT callbacks-dev
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

if(CALLBACKS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
