# The name of the package:
atlas_subdir (ParticleAnalysis)

# Add the shared library:
atlas_add_library (ParticleAnalysisLib
  ParticleAnalysis/*.h Root/*.cxx
  PUBLIC_HEADERS ParticleAnalysis
  LINK_LIBRARIES AnaAlgorithmLib xAODEventInfo HistManagerLib GoodRunsListsLib PileupReweightingLib TrigDecisionToolLib TrigConfInterfaces xAODTracking xAODTruth xAODMuon MuonAnalysisInterfacesLib xAODJet JetInterface JetJvtEfficiencyLib xAODTau xAODMissingET )

# Add the dictionary:
atlas_add_dictionary (ParticleAnalysisDict
  ParticleAnalysis/ParticleAnalysisDict.h
  ParticleAnalysis/selection.xml
  JetAnalysisInterfacesDict
  LINK_LIBRARIES ParticleAnalysisLib)

#if (NOT XAOD_STANDALONE)
#  # Add a component library for AthAnalysis only:
#  atlas_add_component (MyAnalysis
#    src/components/*.cxx
#    LINK_LIBRARIES MyAnalysisLib)
#endif ()

# Install files from the package:
atlas_install_joboptions( share/*.py )

