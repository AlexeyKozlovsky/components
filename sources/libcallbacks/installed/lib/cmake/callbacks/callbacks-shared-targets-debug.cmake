#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "callbacks::callbacks" for configuration "Debug"
set_property(TARGET callbacks::callbacks APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(callbacks::callbacks PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/callbacks.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/callbacks.dll"
  )

list(APPEND _cmake_import_check_targets callbacks::callbacks )
list(APPEND _cmake_import_check_files_for_callbacks::callbacks "${_IMPORT_PREFIX}/lib/callbacks.lib" "${_IMPORT_PREFIX}/bin/callbacks.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
