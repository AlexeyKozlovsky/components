#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "modbus::modbus" for configuration "Debug"
set_property(TARGET modbus::modbus APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(modbus::modbus PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/modbus.lib"
  )

list(APPEND _cmake_import_check_targets modbus::modbus )
list(APPEND _cmake_import_check_files_for_modbus::modbus "${_IMPORT_PREFIX}/lib/modbus.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)