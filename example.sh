#####################
# Z->tautau (SiHit) #
#####################
temp = "mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.recon.DAOD_PIXELVALID.e3601_e5984_s3126_r11117_tid16746672_00"

rm -r submitDir/
./ZmumuAnalysis.py --submission-dir=submitDir \
           --inputFilePath="./data/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.recon.DAOD_PIXELVALID.e3601_e5984_s3126_r11117_tid16746672_00"\
           --filename="DAOD_PIXELVALID.16746672._000012.pool.root.1" \
           --ReadIDTRKVALID=0 \
           --GRLFile="DUMMY" \
           --PileupWeightFile="DUMMY" \
           --LumiCalcFiles="DUMMY"
mv submitDir/data-ANALYSIS/${temp} output_mc2016.EVENT_NT._0001.pool.root
