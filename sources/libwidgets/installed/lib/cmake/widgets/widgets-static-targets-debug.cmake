#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "widgets::widgets" for configuration "Debug"
set_property(TARGET widgets::widgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(widgets::widgets PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/widgets.lib"
  )

list(APPEND _cmake_import_check_targets widgets::widgets )
list(APPEND _cmake_import_check_files_for_widgets::widgets "${_IMPORT_PREFIX}/lib/widgets.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
