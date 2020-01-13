#!/usr/bin/env python

import optparse
parser = optparse.OptionParser()
parser.add_option('-s', '--submission-dir', dest='submission_dir', action='store', type = 'string', 
                  default='submitDir',
                  help='Submission directory for EventLoop')

parser.add_option("--inputFilePath", action="store", type="string", dest="inputFilePath", 
                  default="/data/maxi22/atljphys/stsuno/analysis/pixelOffline.10.08.2018/data/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.recon.DAOD_PIXELVALID.e3601_e5984_s3126_r10957/", 
                  help="Input directory")

parser.add_option("--filename", action="store", type="string", dest="filename", 
                  default="DAOD_PIXELVALID.15861948._00000*", 
                  help="File name")

parser.add_option("--GRLFile", action="store", type="string", dest="GRLFile", 
                  default="../lumifiles/data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns_PIXELVALID.xml", 
                  help="GRL file")

parser.add_option("--PileupWeightFile", action="store", type="string", dest="PileupWeightFile", 
                  default="../lumifiles/mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.deriv.NTUP_PILEUP.e3601_e5984_s3126_r10957_p3384_prw.root",
                  help="Pileup weight file")

parser.add_option("--LumiCalcFiles", action="store", type="string", dest="LumiCalcFiles", 
                  default="../lumifiles/ilumicalc_histograms_None_278880-279345_OflLumi-13TeV-010.root",
                  help="LumiCalc file")

parser.add_option("--ReadIDTRKVALID", action="store", type="int", dest="ReadIDTRKVALID", 
                  default=0, help="ReadIDTRKVALID")

(options,args)=parser.parse_args()

import ROOT
ROOT.xAOD.Init().ignore()

import os
sh = ROOT.SH.SampleHandler()
sh.setMetaString( 'nc_tree', 'CollectionTree' )

ROOT.SH.ScanDir().filePattern(options.filename).scan(sh,options.inputFilePath)

sh.printContent()

job = ROOT.EL.Job()
job.sampleHandler(sh)
job.outputAdd(ROOT.EL.OutputStream ('ANALYSIS'))
job.options().setDouble(ROOT.EL.Job.optMaxEvents, -1)

from AnaAlgorithm.AnaAlgorithmConfig import AnaAlgorithmConfig
config = AnaAlgorithmConfig( 'ZmumuAnalysis/AnalysisAlg' )

config.ReadIDTRKVALID   = options.ReadIDTRKVALID
config.GRLFile          = options.GRLFile
config.PileupWeightFile = options.PileupWeightFile
config.LumiCalcFiles    = options.LumiCalcFiles

job.algsAdd(config)
driver = ROOT.EL.DirectDriver()
driver.submit(job,options.submission_dir)

