# The name of the package:
atlas_subdir (HistManager)

# Add the shared library:
atlas_add_library (HistManagerLib
  HistManager/*.h Root/*.cxx
  PUBLIC_HEADERS HistManager
  LINK_LIBRARIES EventLoop AnaAlgorithmLib xAODEventInfo xAODTracking xAODTruth )

# Add the dictionary:
atlas_add_dictionary (HistManagerDict
  HistManager/HistManagerDict.h
  HistManager/selection.xml
  LINK_LIBRARIES HistManagerLib)

#if (NOT XAOD_STANDALONE)
#  # Add a component library for AthAnalysis only:
#  atlas_add_component (MyAnalysis
#    src/components/*.cxx
#    LINK_LIBRARIES MyAnalysisLib)
#endif ()

# Install files from the package:
atlas_install_joboptions( share/*.py )

