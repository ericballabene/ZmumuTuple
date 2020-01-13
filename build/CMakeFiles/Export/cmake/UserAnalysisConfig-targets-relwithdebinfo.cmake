#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "UserAnalysis::HistManagerLib" for configuration "RelWithDebInfo"
set_property(TARGET UserAnalysis::HistManagerLib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(UserAnalysis::HistManagerLib PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libHistManagerLib.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libHistManagerLib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS UserAnalysis::HistManagerLib )
list(APPEND _IMPORT_CHECK_FILES_FOR_UserAnalysis::HistManagerLib "${_IMPORT_PREFIX}/lib/libHistManagerLib.so" )

# Import target "UserAnalysis::ParticleAnalysisLib" for configuration "RelWithDebInfo"
set_property(TARGET UserAnalysis::ParticleAnalysisLib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(UserAnalysis::ParticleAnalysisLib PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libParticleAnalysisLib.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libParticleAnalysisLib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS UserAnalysis::ParticleAnalysisLib )
list(APPEND _IMPORT_CHECK_FILES_FOR_UserAnalysis::ParticleAnalysisLib "${_IMPORT_PREFIX}/lib/libParticleAnalysisLib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
