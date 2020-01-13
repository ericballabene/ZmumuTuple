## Setup ATLAS
   on lxplus: setupATLAS 
   on a different machine: 
   export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
   source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh  

## Setup
   lsetup -a testing asetup
   asetup 21.2,AnalysisBase,latest

   mkdir build; cd build/
   cmake ../source/
   make
   source ./x86_64-centos7-gcc8-opt/setup.sh
   mkdir ../submitDir
   
**Run the code, **
   source example.sh
   

**Please,**
keep attention that if the input xAOD is IDTRACKVALID, then, please set 
   —ReadIDTRKVALID=1    
   