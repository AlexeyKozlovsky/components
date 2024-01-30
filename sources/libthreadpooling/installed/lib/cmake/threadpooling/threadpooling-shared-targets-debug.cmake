#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "threadpooling::threadpooling" for configuration "Debug"
set_property(TARGET threadpooling::threadpooling APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(threadpooling::threadpooling PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/threadpooling.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/threadpooling.dll"
  )

list(APPEND _cmake_import_check_targets threadpooling::threadpooling )
list(APPEND _cmake_import_check_files_for_threadpooling::threadpooling "${_IMPORT_PREFIX}/lib/threadpooling.lib" "${_IMPORT_PREFIX}/bin/threadpooling.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
