#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "widgets::widgets" for configuration "Debug"
set_property(TARGET widgets::widgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(widgets::widgets PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/widgets.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt5::Widgets"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/widgets.dll"
  )

list(APPEND _cmake_import_check_targets widgets::widgets )
list(APPEND _cmake_import_check_files_for_widgets::widgets "${_IMPORT_PREFIX}/lib/widgets.lib" "${_IMPORT_PREFIX}/bin/widgets.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
