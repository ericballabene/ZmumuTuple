# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.14.3/Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.14.3/Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /afs/cern.ch/user/e/eballabe/public/ntuple/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/cern.ch/user/e/eballabe/public/ntuple/build

# Utility rule file for UserAnalysisRootMapMerge.

# Include the progress variables for this target.
include CMakeFiles/UserAnalysisRootMapMerge.dir/progress.make

CMakeFiles/UserAnalysisRootMapMerge: HistManager/CMakeFiles/HistManagerDict.dsomap
CMakeFiles/UserAnalysisRootMapMerge: ParticleAnalysis/CMakeFiles/ParticleAnalysisDict.dsomap
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/afs/cern.ch/user/e/eballabe/public/ntuple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Built UserAnalysisRootMapMerge"
	/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.14.3/Linux-x86_64/bin/cmake -E make_directory /afs/cern.ch/user/e/eballabe/public/ntuple/build/x86_64-centos7-gcc8-opt/lib
	/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2020-01-10T0347/AnalysisBase/21.2.105/InstallArea/x86_64-centos7-gcc8-opt/cmake/modules/scripts/mergeFiles.sh /afs/cern.ch/user/e/eballabe/public/ntuple/build/x86_64-centos7-gcc8-opt/lib/UserAnalysis.rootmap /afs/cern.ch/user/e/eballabe/public/ntuple/build/CMakeFiles/UserAnalysisRootMapMergeFiles.txt

UserAnalysisRootMapMerge: CMakeFiles/UserAnalysisRootMapMerge
UserAnalysisRootMapMerge: CMakeFiles/UserAnalysisRootMapMerge.dir/build.make

.PHONY : UserAnalysisRootMapMerge

# Rule to build all files generated by this target.
CMakeFiles/UserAnalysisRootMapMerge.dir/build: UserAnalysisRootMapMerge

.PHONY : CMakeFiles/UserAnalysisRootMapMerge.dir/build

CMakeFiles/UserAnalysisRootMapMerge.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UserAnalysisRootMapMerge.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UserAnalysisRootMapMerge.dir/clean

CMakeFiles/UserAnalysisRootMapMerge.dir/depend:
	cd /afs/cern.ch/user/e/eballabe/public/ntuple/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/cern.ch/user/e/eballabe/public/ntuple/source /afs/cern.ch/user/e/eballabe/public/ntuple/source /afs/cern.ch/user/e/eballabe/public/ntuple/build /afs/cern.ch/user/e/eballabe/public/ntuple/build /afs/cern.ch/user/e/eballabe/public/ntuple/build/CMakeFiles/UserAnalysisRootMapMerge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UserAnalysisRootMapMerge.dir/depend

