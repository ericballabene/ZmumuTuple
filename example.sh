#####################
# Z->tautau (SiHit) #
#####################
./ZmumuAnalysis.py --submission-dir=submitDir \
           --inputFilePath="./data" \
           --filename="DAOD_TIDE.5_3.1_1.3_0.8_300_300_300_300.pool.root" \
           --ReadIDTRKVALID=0 \
           --GRLFile="DUMMY" \
           --PileupWeightFile="DUMMY" \
           --LumiCalcFiles="DUMMY"
#mv submitDir/data-ANALYSIS/data.root /data/mc2017rad_sihit_13TeV.361108.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Ztautau.EVENT_NT._0001.pool.root
#mv data/output/data.root /data/NTUPLE_RADDAM.5_3.1_1.3_0.8_300_300_300_300.pool.root


###########
# Z->mumu #
###########
#rm -r submitDir/
#./ZmumuAnalysis.py --submission-dir=submitDir \
#           --inputFilePath="/data/" \
#           --filename="DAOD_PIXELVALID.16463100._0000[0-4]*" \
#           --ReadIDTRKVALID=0 \
#           --GRLFile="../lumifiles/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml" \
#           --PileupWeightFile="../lumifiles/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.deriv.NTUP_PILEUP.e3601_s3126_r11117_p3604_prw.root" \
#           --LumiCalcFiles="../lumifiles/ilumicalc_histograms_None_349451-362776_OflLumi-13TeV-001.root"
#mv submitDir/data-ANALYSIS/data.root /data/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.recon.EVENT_NT.e3601_e5984_s3126_r11117._0001.pool.root
#
###############
# DATA 362776 #
###############
#rm -r submitDir/
#./ZmumuAnalysis.py --submission-dir=submitDir \
#           --inputFilePath="/data/DAOD_PIXELVALID/data18_13TeV.00362776.physics_Main.merge.DAOD_PIXELVALID.f993_m1831_r11581_p3909/" \
#           --filename="DAOD_PIXELVALID.18905750._000001.pool.root.1" \
#           --ReadIDTRKVALID=0 \
#           --GRLFile="../lumifiles/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml" \
#           --PileupWeightFile="../lumifiles/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.deriv.NTUP_PILEUP.e3601_s3126_r10948_p3384_prw.root" \
#           --LumiCalcFiles="../lumifiles/ilumicalc_histograms_None_326439-339957_OflLumi-13TeV-010.root"
#mv submitDir/data-ANALYSIS/data18_13TeV.00362776.physics_Main.merge.DAOD_PIXELVALID.f993_m1831_r11581_p3909.root /data/data18_13TeV.00362776.physics_Main.merge.EVENT_NT.f993_m1831_r11581_p3909._0001.pool.root

