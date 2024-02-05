cmake_minimum_required(VERSION 3.14)
include(env.cmake)

project(modbuswrappers
    VERSION 1.0.0
    DESCRIPTION "Template for C++ library built with CMake"
    LANGUAGES CXX)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# MODBUSWRAPPERS_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(MODBUSWRAPPERS_BUILD_TESTS "Build modbuswrappers tests" OFF)
option(MODBUSWRAPPERS_BUILD_EXAMPLES "Build modbuswrappers examples" OFF)
option(MODBUSWRAPPERS_BUILD_DOCS "Build modbuswrappers documentation" OFF)
option(MODBUSWRAPPERS_INSTALL "Generate target for installing modbuswrappers" ${is_top_level})
set_if_undefined(MODBUSWRAPPERS_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/modbuswrappers" CACHE STRING
    "Install path for modbuswrappers package-related CMake files")

if(DEFINED MODBUSWRAPPERS_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${MODBUSWRAPPERS_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(modbuswrappers) # initialized below
add_library(modbuswrappers::modbuswrappers ALIAS modbuswrappers)

#----------------------------------------------------------------------------------------------------------------------
# modbuswrappers dependencies
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

find_package(modbus REQUIRED)
target_link_libraries(${PROJECT_NAME}  modbus::modbus)

find_package(threadpooling REQUIRED)
target_link_libraries(${PROJECT_NAME}  threadpooling::threadpooling)


#----------------------------------------------------------------------------------------------------------------------
# modbuswrappers sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(modbuswrappers EXPORT_FILE_NAME include/modbuswrappers/${export_file_name})

file(GLOB sources
    include/modbuswrappers/*.h
    include/modbuswrappers/mocks/*.h
    include/modbuswrappers/modbusasyncclientwrapper/*.h
    include/modbuswrappers/modbusclientwrapper/*.h
    include/modbuswrappers/modbuswrappermodbusiddecorator/*.h
        include/modbuswrappers/modbuspostponedwritewrapper/*.h
    include/modbuswrappers/storages/*.h
    src/modbuswrappers/*.cpp
    src/modbuswrappers/mocks/*.cpp
    src/modbuswrappers/modbusasyncclientwrapper/*.cpp
    src/modbuswrappers/modbusclientwrapper/*.cpp
    src/modbuswrappers/modbuswrappermodbusiddecorator/*.cpp
    src/modbuswrappers/modbuspostponedwritewrapper/*.cpp
    src/modbuswrappers/storages/*.cpp
    )
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# modbuswrappers target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(modbuswrappers PRIVATE ${sources})
target_compile_definitions(modbuswrappers PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:MODBUSWRAPPERS_STATIC_DEFINE>")

target_include_directories(modbuswrappers
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(modbuswrappers PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(MODBUSWRAPPERS_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/modbuswrappers-config.cmake.in modbuswrappers-config.cmake
        INSTALL_DESTINATION "${MODBUSWRAPPERS_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(modbuswrappers-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS modbuswrappers EXPORT modbuswrappers_export
        RUNTIME COMPONENT modbuswrappers
        LIBRARY COMPONENT modbuswrappers NAMELINK_COMPONENT modbuswrappers-dev
        ARCHIVE COMPONENT modbuswrappers-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT modbuswrappers-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/modbuswrappers/${export_file_name}"
        COMPONENT modbuswrappers-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/modbuswrappers")

    set(targets_file "modbuswrappers-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "modbuswrappers-static-targets.cmake")
    endif()

    install(EXPORT modbuswrappers_export
        COMPONENT modbuswrappers-dev
        FILE "${targets_file}"
        DESTINATION "${MODBUSWRAPPERS_INSTALL_CMAKEDIR}"
        NAMESPACE modbuswrappers::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/modbuswrappers-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/modbuswrappers-config-version.cmake"
        COMPONENT modbuswrappers-dev
        DESTINATION "${MODBUSWRAPPERS_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:modbuswrappers>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:modbuswrappers>/$<TARGET_FILE_PREFIX:modbuswrappers>$<TARGET_FILE_BASE_NAME:modbuswrappers>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT modbuswrappers-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(MODBUSWRAPPERS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(MODBUSWRAPPERS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(MODBUSWRAPPERS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()
