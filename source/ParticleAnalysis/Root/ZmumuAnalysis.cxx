#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>

#include <AsgTools/MessageCheck.h>
#include <ParticleAnalysis/ZmumuAnalysis.h>
#include <HistManager/TrackHelper.h>

#include <PATInterfaces/CorrectionCode.h>
#include <xAODCore/ShallowAuxContainer.h>
#include <xAODCore/ShallowCopy.h>

#include <TSystem.h>
#include <TFile.h>

#include <xAODEventInfo/EventInfo.h>
#include <xAODTracking/TrackParticle.h>
#include <xAODTracking/TrackParticleContainer.h>
#include <xAODTracking/TrackParticleAuxContainer.h>
#include <xAODTracking/TrackStateValidationContainer.h>
#include <xAODTracking/TrackMeasurementValidationContainer.h>
#include <xAODMuon/MuonContainer.h>

#include <xAODTruth/TruthParticleAuxContainer.h>
#include <xAODTruth/TruthVertex.h>
#include <xAODTracking/VertexContainer.h>

#include <xAODJet/Jet.h>
#include <xAODJet/JetContainer.h>

#include <xAODTau/TauJet.h>
#include <xAODTau/TauJetContainer.h>
#include <xAODTau/TauJetAuxContainer.h>

#include <xAODMissingET/MissingET.h>
#include <xAODMissingET/MissingETContainer.h>

ZmumuAnalysis::ZmumuAnalysis(const std::string& name, ISvcLocator *pSvcLocator):EL::AnaAlgorithm(name, pSvcLocator),
  m_flagTRKSTREAM(false),
  m_GRLFile("DUMMY"),
  m_pileupWeightFile("DUMMY"),
  m_lumiCalcFile("DUMMY"),
  m_grl("GoodRunsListSelectionTool/grl",this),
  m_pileuptool("CP::PileupReweightingTool/prw",this),
  m_trigConfigTool("TrigConf::xAODConfigTool/xAODConfigTool"),
  m_trigDecisionTool("Trig::TrigDecisionTool/TrigDecisionTool"),
  m_muonSelection("CP::MuonSelectionTool",this),
  m_muonCalibrationAndSmearingTool("CP::MuonCalibrationAndSmearingTool/MuonCorrectionTool",this),
  m_jetCleaning("JetCleaningTool/JetCleaning",this),
  m_jetsf("CP::JetJvtEfficiency/jetsf",this),
  m_fjetsf("CP::JetJvtEfficiency/fjetsf",this)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0. Note that things like resetting
  // statistics variables should rather go into the initialize() function.
  declareProperty("ReadIDTRKVALID", m_flagTRKSTREAM);
  declareProperty("GRLFile", m_GRLFile, "File name of the good run list");
  declareProperty("PileupWeightFile", m_pileupWeightFile, "File name of the pileup weight");
  declareProperty("LumiCalcFiles", m_lumiCalcFile, "File name of the pileup weight");
}

ZmumuAnalysis::~ZmumuAnalysis() {
  delete m_trackPt;
  delete m_trackPhi;
  delete m_trackEta;
  delete m_trackTheta;
  delete m_trackCharge;
  delete m_trackqOverP;
  delete m_trackD0;
  delete m_trackZ0;
  delete m_trackD0Err;
  delete m_trackZ0Err;
  delete m_trackqOverPErr;
  delete m_trackDeltaZSinTheta;
  delete m_trackMindR;
  delete m_trackClass;
  delete m_trackPassCut;
  delete m_trackOutliers;
  delete m_trackChiSqPerDof;
  delete m_trackStdDevChi2OS;
  delete m_nPixelHits;
  delete m_nPixelHoles;
  delete m_nPixelLayers;
  delete m_nPixelOutliers;
  delete m_nPixelGanged;
  delete m_nPixelShared;
  delete m_nPixelSplit;
  delete m_nPixelDeadSensors;
  delete m_nIBLUsedHits;
  delete m_nBLUsedHits;
  delete m_nSCTHits;
  delete m_nSCTHoles;
  delete m_nSCTOutliers;
  delete m_nSCTDeadSensors;
  delete m_nTRTHits;
  delete m_nTRTOutliers;
  delete m_nTRTHoles;
  delete m_nTRTHTHits;
  delete m_nIBLSplitHits;
  delete m_nBLSplitHits;
  delete m_nIBLSharedHits;
  delete m_nBLSharedHits;
  delete m_nIBLHits;
  delete m_nBLHits;
  delete m_nL1Hits;
  delete m_nL2Hits;
  delete m_nECHits;
  delete m_nIBLExpectedHits;
  delete m_nBLExpectedHits;
  delete m_nSCTSharedHits;
  delete m_extrapolatedIBLX;
  delete m_extrapolatedIBLY;
  delete m_extrapolatedIBLZ;
  delete m_extrapolatedBLX;
  delete m_extrapolatedBLY;
  delete m_extrapolatedBLZ;
  delete m_extrapolatedL1X;
  delete m_extrapolatedL1Y;
  delete m_extrapolatedL1Z;
  delete m_extrapolatedL2X;
  delete m_extrapolatedL2Y;
  delete m_extrapolatedL2Z;
  delete m_TruncateddEdx;
  delete m_nTruncateddEdx;

  delete m_truePt;
  delete m_truePhi;
  delete m_trueEta;
  delete m_trueE;
  delete m_trued0;
  delete m_truez0;
  delete m_truephi;
  delete m_truetheta;
  delete m_trueqoverp;
  delete m_truepdgid;
  delete m_truebarcode;
  delete m_truthmatchprob;
  delete m_trueMindR;
  delete m_genVtxR;
  delete m_genVtxZ;
  delete m_parentFlav;

  delete m_hitIsEndCap;
  delete m_hitIsHole;
  delete m_hitIsOutlier;
  delete m_hitLayer;
  delete m_hitEtaModule;
  delete m_hitPhiModule;
  delete m_hitCharge;
  delete m_hitToT;
  delete m_hitLVL1A;
  delete m_hitNPixel;
  delete m_hitNPixelX;
  delete m_hitNPixelY;
  delete m_hitBSerr;
  delete m_hitDCSstate;
  delete m_hitVBias;
  delete m_hitTemp;
  delete m_hitLorentzShift;
  delete m_hitIsSplit;
  delete m_hitIsEdge;
  delete m_hitIsOverflow;
  delete m_hitIsolation10x2;
  delete m_hitIsolation20x4;
  delete m_hitGlobalX;
  delete m_hitGlobalY;
  delete m_hitGlobalZ;
  delete m_hitLocalX;
  delete m_hitLocalY;
  delete m_trkLocalX;
  delete m_trkLocalY;
  delete m_unbiasedResidualX;
  delete m_unbiasedResidualY;
  delete m_unbiasedPullX;
  delete m_unbiasedPullY;
  delete m_trkPhiOnSurface;
  delete m_trkThetaOnSurface;
  delete m_numTotalClustersPerModule;
  delete m_numTotalPixelsPerModule;
  delete m_RdoToT;
  delete m_RdoCharge;
  delete m_RdoPhi;
  delete m_RdoEta;
  delete m_hitTruthPdgId;
  delete m_siHitPdgId;
  delete m_siHitBarcode;
  delete m_siHitStartPosX;
  delete m_siHitStartPosY;
  delete m_siHitEndPosX;
  delete m_siHitEndPosY;
  delete m_siHitEnergyDeposit;

  delete m_truthEta;
  delete m_truthPhi;
  delete m_truthPt;
  delete m_truthE;
  delete m_truthCharge;
  delete m_truthPdgId;
  delete m_truthBarcode;
  delete m_truthStatus;

  delete m_muonEta;
  delete m_muonPhi;
  delete m_muonPt;
  delete m_muonE;

  delete m_jetEta;
  delete m_jetPhi;
  delete m_jetPt;
  delete m_jetE;
  delete m_jetPassJVT;

  delete m_tauEta;
  delete m_tauPhi;
  delete m_tauPt;
  delete m_tauM;
  delete m_tauCharge;
  delete m_tau_nTracksCharged;
  delete m_tau_nTracksIsolation;
  delete m_tau_nAllTracks;
  delete m_tau_trackFilterProngs;
  delete m_tau_trackFilterQuality;
  delete m_tau_nClusters;
  delete m_tau_nPi0s;
  delete m_tau_numCells;
  delete m_tau_isTauFlags;
  delete m_tau_BDTJetScore;
  delete m_tau_BDTEleScore;
  delete m_tau_EleMatchLikelihoodScore;
  delete m_tau_BDTJetScoreSigTrans;
  delete m_tau_RNNJetScore;
  delete m_tau_RNNJetScoreSigTrans;
  delete m_tau_ipZ0SinThetaSigLeadTrk;
  delete m_tau_etOverPtLeadTrk;
  delete m_tau_leadTrkPt;
  delete m_tau_ipSigLeadTrk;
  delete m_tau_massTrkSys;
  delete m_tau_trkWidth2;
  delete m_tau_trFlightPathSig;
  delete m_tau_EMRadius;
  delete m_tau_hadRadius;
  delete m_tau_etEMAtEMScale;
  delete m_tau_etHadAtEMScale;
  delete m_tau_isolFrac;
  delete m_tau_centFrac;
  delete m_tau_stripWidth2;
  delete m_tau_nStrip;
  delete m_tau_trkAvgDist;
  delete m_tau_dRmax;

}

StatusCode ZmumuAnalysis::initialize() {
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.
  ANA_MSG_INFO("Initialize");
	m_eventCounter=0;
  std::cout << "Set counter to 0 " << m_eventCounter << std::endl;

  // GRL
  if (m_GRLFile=="DUMMY") {
    std::cout << "Nothing to do with GoodRunsListSelectionTool" << std::endl;
  }
  else {
    std::vector<std::string> vecStringGRL;
    vecStringGRL.push_back(m_GRLFile);
    ANA_CHECK(m_grl.setProperty("GoodRunsListVec", vecStringGRL));
    ANA_CHECK(m_grl.setProperty("PassThrough", false)); // if true (default) will ignore result of GRL and will just pass all events
    ANA_CHECK(m_grl.initialize());
  }

  // pileup re-weighting tool
  if (m_pileupWeightFile=="DUMMY") {
    std::cout << "Nothing to do with PileupReweightingTool" << std::endl;
  }
  else {
    std::vector<std::string> confFiles;
    std::vector<std::string> lcalcFiles;
    confFiles.push_back(m_pileupWeightFile);
    lcalcFiles.push_back(m_lumiCalcFile);
    ANA_CHECK(m_pileuptool.setProperty("ConfigFiles",confFiles));
    ANA_CHECK(m_pileuptool.setProperty("LumiCalcFiles",lcalcFiles));
    ANA_CHECK(m_pileuptool.initialize());
  }

/*
  // Initialize and configure trigger tools
  ANA_CHECK (m_trigConfigTool.initialize());
  ANA_CHECK (m_trigDecisionTool.setProperty("ConfigTool",m_trigConfigTool.getHandle()));
  ANA_CHECK (m_trigDecisionTool.setProperty("TrigDecisionKey","xTrigDecision"));
  ANA_CHECK (m_trigDecisionTool.initialize());
*/

  // set up and initialize the muon selection tool in initialize()
  ANA_CHECK(m_muonSelection.setProperty("MaxEta", 2.5)); 
  ANA_CHECK(m_muonSelection.setProperty("MuQuality", 1));
  ANA_CHECK(m_muonSelection.initialize());

  ANA_CHECK (m_muonCalibrationAndSmearingTool.initialize());

  // initialize and configure the jet cleaning tool
  ANA_CHECK(m_jetCleaning.setProperty( "CutLevel", "LooseBad"));
  ANA_CHECK(m_jetCleaning.setProperty("DoUgly", false));
  ANA_CHECK(m_jetCleaning.initialize());

  ANA_CHECK(m_jetsf.setProperty("SFFile","JetJvtEfficiency/Moriond2018/JvtSFFile_LC.root"));
  ANA_CHECK(m_jetsf.initialize());

  ANA_CHECK(m_fjetsf.setProperty("SFFile","JetJvtEfficiency/Moriond2018/fJvtSFFile.root"));
  ANA_CHECK(m_fjetsf.setProperty("ScaleFactorDecorationName","fJVTSF"));
  ANA_CHECK(m_fjetsf.initialize());

  // Root Tree
  ANA_CHECK(book(TTree("eventtree", "Zmumu ntuple")));
  TTree* mytree = tree ("eventtree");
  mytree->Branch("runNumber",   &m_runNumber);
  mytree->Branch("eventNumber", &m_eventNumber);
  mytree->Branch("pileupWeight",&m_pileupWeight);
  mytree->Branch("mcWeight",    &m_mcWeight);

  mytree->Branch("lumiBlock",&m_lumiB);
  mytree->Branch("averagePU",&m_averagePU);
  mytree->Branch("eventPU",  &m_eventPU);
  mytree->Branch("mcFlag",   &m_mcFlag); 

  mytree->Branch("numVtx",&m_numVtx);
  mytree->Branch("pVtxX",&m_pVtxX);
  mytree->Branch("pVtxY",&m_pVtxY);
  mytree->Branch("pVtxZ",&m_pVtxZ);

  mytree->Branch("pVtxXErr",&m_pVtxXErr);
  mytree->Branch("pVtxYErr",&m_pVtxYErr);
  mytree->Branch("pVtxZErr",&m_pVtxZErr);

  mytree->Branch("truthPVtxX",&m_truthPVtxX);
  mytree->Branch("truthPVtxY",&m_truthPVtxY);
  mytree->Branch("truthPVtxZ",&m_truthPVtxZ);

  m_trackPt             = new std::vector<float>(); mytree->Branch("trackPt",            &m_trackPt);
  m_trackPhi            = new std::vector<float>(); mytree->Branch("trackPhi",           &m_trackPhi);
  m_trackEta            = new std::vector<float>(); mytree->Branch("trackEta",           &m_trackEta);
  m_trackTheta          = new std::vector<float>(); mytree->Branch("trackTheta",         &m_trackTheta);
  m_trackCharge         = new std::vector<float>(); mytree->Branch("trackCharge",        &m_trackCharge);
  m_trackqOverP         = new std::vector<float>(); mytree->Branch("trackqOverP",        &m_trackqOverP);
  m_trackD0             = new std::vector<float>(); mytree->Branch("trackD0",            &m_trackD0);
  m_trackZ0             = new std::vector<float>(); mytree->Branch("trackZ0",            &m_trackZ0);
  m_trackD0Err          = new std::vector<float>(); mytree->Branch("trackD0Err",         &m_trackD0Err);
  m_trackZ0Err          = new std::vector<float>(); mytree->Branch("trackZ0Err",         &m_trackZ0Err);
  m_trackqOverPErr      = new std::vector<float>(); mytree->Branch("trackqOverPErr",     &m_trackqOverPErr);
  m_trackDeltaZSinTheta = new std::vector<float>(); mytree->Branch("trackDeltaZSinTheta",&m_trackDeltaZSinTheta);
  m_trackMindR          = new std::vector<float>(); mytree->Branch("trackMindR",         &m_trackMindR);
  m_trackClass          = new std::vector<int>();   mytree->Branch("trackClass",         &m_trackClass);
  m_trackPassCut        = new std::vector<int>();   mytree->Branch("trackPassCut",       &m_trackPassCut);
  m_trackOutliers       = new std::vector<int>();   mytree->Branch("trackOutliers",      &m_trackOutliers);
  m_trackChiSqPerDof    = new std::vector<float>(); mytree->Branch("trackChiSqPerDof",   &m_trackChiSqPerDof);
  m_trackStdDevChi2OS   = new std::vector<float>(); mytree->Branch("trackStdDevChi2OS",  &m_trackStdDevChi2OS);
  m_nPixelHits       = new std::vector<int>(); mytree->Branch("trackNPixelHits",      &m_nPixelHits);
  m_nPixelHoles      = new std::vector<int>(); mytree->Branch("trackNPixelHoles",     &m_nPixelHoles);
  m_nPixelLayers     = new std::vector<int>(); mytree->Branch("trackNPixelLayers",    &m_nPixelLayers);
  m_nPixelOutliers   = new std::vector<int>(); mytree->Branch("trackNPixelOutliers",  &m_nPixelOutliers);
  m_nPixelGanged        = new std::vector<int>();   mytree->Branch("nPixelGanged",       &m_nPixelGanged);
  m_nPixelShared        = new std::vector<int>();   mytree->Branch("nPixelShared",       &m_nPixelShared);
  m_nPixelSplit         = new std::vector<int>();   mytree->Branch("nPixelSplit",        &m_nPixelSplit);
  m_nPixelDeadSensors   = new std::vector<int>();   mytree->Branch("nPixelDeadSensors",  &m_nPixelDeadSensors);
  m_nIBLUsedHits     = new std::vector<int>(); mytree->Branch("trackNIBLUsedHits",    &m_nIBLUsedHits);
  m_nBLUsedHits      = new std::vector<int>(); mytree->Branch("trackNBLUsedHits",     &m_nBLUsedHits);
  m_nSCTHits         = new std::vector<int>(); mytree->Branch("trackNSCTHits",        &m_nSCTHits);
  m_nSCTHoles        = new std::vector<int>(); mytree->Branch("trackNSCTHoles",       &m_nSCTHoles);
  m_nSCTOutliers        = new std::vector<int>();   mytree->Branch("nSCTOutliers",       &m_nSCTOutliers);
  m_nSCTDeadSensors     = new std::vector<int>();   mytree->Branch("nSCTDeadSensors",    &m_nSCTDeadSensors);
  m_nTRTHits         = new std::vector<int>(); mytree->Branch("trackNTRTHits",        &m_nTRTHits);
  m_nTRTOutliers        = new std::vector<int>();   mytree->Branch("nTRTOutliers",       &m_nTRTOutliers);
  m_nTRTHoles           = new std::vector<int>();   mytree->Branch("nTRTHoles",          &m_nTRTHoles);
  m_nTRTHTHits          = new std::vector<int>();   mytree->Branch("nTRTHTHits",         &m_nTRTHTHits);
  m_nIBLSplitHits    = new std::vector<int>(); mytree->Branch("trackNSplitIBLHits",   &m_nIBLSplitHits);
  m_nBLSplitHits     = new std::vector<int>(); mytree->Branch("trackNSplitBLHits",    &m_nBLSplitHits);
  m_nIBLSharedHits   = new std::vector<int>(); mytree->Branch("trackNSharedIBLHits",  &m_nIBLSharedHits);
  m_nBLSharedHits    = new std::vector<int>(); mytree->Branch("trackNSharedBLHits",   &m_nBLSharedHits);
  m_nIBLHits         = new std::vector<int>(); mytree->Branch("trackNIBLHits",        &m_nIBLHits);
  m_nBLHits          = new std::vector<int>(); mytree->Branch("trackNBLHits",         &m_nBLHits);
  m_nL1Hits          = new std::vector<int>(); mytree->Branch("trackNL1Hits",         &m_nL1Hits);
  m_nL2Hits          = new std::vector<int>(); mytree->Branch("trackNL2Hits",         &m_nL2Hits);
  m_nECHits          = new std::vector<int>(); mytree->Branch("trackNECHits",         &m_nECHits);
  m_nIBLExpectedHits = new std::vector<int>(); mytree->Branch("trackNIBLExpectedHits",&m_nIBLExpectedHits);
  m_nBLExpectedHits  = new std::vector<int>(); mytree->Branch("trackNBLExpectedHits", &m_nBLExpectedHits);
  m_nSCTSharedHits   = new std::vector<int>(); mytree->Branch("trackNSCTSharedHits",  &m_nSCTSharedHits);
  m_TruncateddEdx    = new std::vector<float>(); mytree->Branch("trackTruncateddEdx", &m_TruncateddEdx);
  m_nTruncateddEdx   = new std::vector<int>(); mytree->Branch("trackNTruncateddEdx",  &m_nTruncateddEdx);
  m_extrapolatedIBLX = new std::vector<float>(); mytree->Branch("extrapolatedIBLX", &m_extrapolatedIBLX);
  m_extrapolatedIBLY = new std::vector<float>(); mytree->Branch("extrapolatedIBLY", &m_extrapolatedIBLY);
  m_extrapolatedIBLZ = new std::vector<float>(); mytree->Branch("extrapolatedIBLZ", &m_extrapolatedIBLZ);
  m_extrapolatedBLX  = new std::vector<float>(); mytree->Branch("extrapolatedBLX",  &m_extrapolatedBLX);
  m_extrapolatedBLY  = new std::vector<float>(); mytree->Branch("extrapolatedBLY",  &m_extrapolatedBLY);
  m_extrapolatedBLZ  = new std::vector<float>(); mytree->Branch("extrapolatedBLZ",  &m_extrapolatedBLZ);
  m_extrapolatedL1X  = new std::vector<float>(); mytree->Branch("extrapolatedL1X",  &m_extrapolatedL1X);
  m_extrapolatedL1Y  = new std::vector<float>(); mytree->Branch("extrapolatedL1Y",  &m_extrapolatedL1Y);
  m_extrapolatedL1Z  = new std::vector<float>(); mytree->Branch("extrapolatedL1Z",  &m_extrapolatedL1Z);
  m_extrapolatedL2X  = new std::vector<float>(); mytree->Branch("extrapolatedL2X",  &m_extrapolatedL2X);
  m_extrapolatedL2Y  = new std::vector<float>(); mytree->Branch("extrapolatedL2Y",  &m_extrapolatedL2Y);
  m_extrapolatedL2Z  = new std::vector<float>(); mytree->Branch("extrapolatedL2Z",  &m_extrapolatedL2Z);

  m_truePt         = new std::vector<float>(); mytree->Branch("truePt",        &m_truePt);
  m_truePhi        = new std::vector<float>(); mytree->Branch("truePhi",       &m_truePhi);
  m_trueEta        = new std::vector<float>(); mytree->Branch("trueEta",       &m_trueEta);
  m_trueE          = new std::vector<float>(); mytree->Branch("trueE",         &m_trueE);
  m_trued0         = new std::vector<float>(); mytree->Branch("trued0",        &m_trued0);
  m_truez0         = new std::vector<float>(); mytree->Branch("truez0",        &m_truez0);
  m_truephi        = new std::vector<float>(); mytree->Branch("truephi0",      &m_truephi);
  m_truetheta      = new std::vector<float>(); mytree->Branch("truetheta",     &m_truetheta);
  m_trueqoverp     = new std::vector<float>(); mytree->Branch("trueqoverp",    &m_trueqoverp);
  m_truepdgid      = new std::vector<int>();   mytree->Branch("truepdgid",     &m_truepdgid);
  m_truebarcode    = new std::vector<int>();   mytree->Branch("truebarcode",   &m_truebarcode);
  m_truthmatchprob = new std::vector<float>(); mytree->Branch("truthmatchprob",&m_truthmatchprob);
  m_trueMindR      = new std::vector<float>(); mytree->Branch("trueMindR",     &m_trueMindR);
  m_genVtxR        = new std::vector<float>(); mytree->Branch("genVtxR",       &m_genVtxR);
  m_genVtxZ        = new std::vector<float>(); mytree->Branch("genVtxZ",       &m_genVtxZ);
  m_parentFlav     = new std::vector<int>();   mytree->Branch("parentFlavour", &m_parentFlav);

  m_hitIsEndCap     = new std::vector<std::vector<int>>();   mytree->Branch("hitIsEndCap",    &m_hitIsEndCap);
  m_hitIsHole       = new std::vector<std::vector<int>>();   mytree->Branch("hitIsHole",      &m_hitIsHole);
  m_hitIsOutlier    = new std::vector<std::vector<int>>();   mytree->Branch("hitIsOutlier",   &m_hitIsOutlier);
  m_hitLayer        = new std::vector<std::vector<int>>();   mytree->Branch("hitLayer",       &m_hitLayer);
  m_hitEtaModule    = new std::vector<std::vector<int>>();   mytree->Branch("hitEtaModule",   &m_hitEtaModule);
  m_hitPhiModule    = new std::vector<std::vector<int>>();   mytree->Branch("hitPhiModule",   &m_hitPhiModule);
  m_hitCharge       = new std::vector<std::vector<float>>(); mytree->Branch("hitCharge",      &m_hitCharge);
  m_hitToT          = new std::vector<std::vector<int>>();   mytree->Branch("hitToT",         &m_hitToT);
  m_hitLVL1A        = new std::vector<std::vector<int>>();   mytree->Branch("hitLVL1A",       &m_hitLVL1A);
  m_hitNPixel       = new std::vector<std::vector<int>>();   mytree->Branch("hitNPixel",      &m_hitNPixel);
  m_hitNPixelX      = new std::vector<std::vector<int>>();   mytree->Branch("hitNPixelX",     &m_hitNPixelX);
  m_hitNPixelY      = new std::vector<std::vector<int>>();   mytree->Branch("hitNPixelY",     &m_hitNPixelY);
  m_hitBSerr        = new std::vector<std::vector<int>>();   mytree->Branch("hitBSerr",       &m_hitBSerr);
  m_hitDCSstate     = new std::vector<std::vector<int>>();   mytree->Branch("hitDCSstate",    &m_hitDCSstate);
  m_hitVBias        = new std::vector<std::vector<float>>(); mytree->Branch("hitVBias",       &m_hitVBias);
  m_hitTemp         = new std::vector<std::vector<float>>(); mytree->Branch("hitTemp",        &m_hitTemp);
  m_hitLorentzShift = new std::vector<std::vector<float>>(); mytree->Branch("hitLorentzShift",&m_hitLorentzShift);
  m_hitIsSplit      = new std::vector<std::vector<int>>();  mytree->Branch("hitIsSplit",     &m_hitIsSplit);
  m_hitIsEdge       = new std::vector<std::vector<bool>>();  mytree->Branch("hitIsEdge",      &m_hitIsEdge);
  m_hitIsOverflow   = new std::vector<std::vector<bool>>();  mytree->Branch("hitIsOverflow",  &m_hitIsOverflow);
  m_hitIsolation10x2= new std::vector<std::vector<int>>();   mytree->Branch("hitIsolation10x2",&m_hitIsolation10x2);
  m_hitIsolation20x4= new std::vector<std::vector<int>>();   mytree->Branch("hitIsolation20x4",&m_hitIsolation20x4);
  m_hitGlobalX      = new std::vector<std::vector<float>>(); mytree->Branch("hitGlobalX",     &m_hitGlobalX);
  m_hitGlobalY      = new std::vector<std::vector<float>>(); mytree->Branch("hitGlobalY",     &m_hitGlobalY);
  m_hitGlobalZ      = new std::vector<std::vector<float>>(); mytree->Branch("hitGlobalZ",     &m_hitGlobalZ);
  m_hitLocalX       = new std::vector<std::vector<float>>(); mytree->Branch("hitLocalX",      &m_hitLocalX);
  m_hitLocalY       = new std::vector<std::vector<float>>(); mytree->Branch("hitLocalY",      &m_hitLocalY);
  m_trkLocalX       = new std::vector<std::vector<float>>(); mytree->Branch("trkLocalX",      &m_trkLocalX);
  m_trkLocalY       = new std::vector<std::vector<float>>(); mytree->Branch("trkLocalY",      &m_trkLocalY);
  m_unbiasedResidualX = new std::vector<std::vector<float>>(); mytree->Branch("unbiasedResidualX",&m_unbiasedResidualX);
  m_unbiasedResidualY = new std::vector<std::vector<float>>(); mytree->Branch("unbiasedResidualY",&m_unbiasedResidualY);
  m_unbiasedPullX     = new std::vector<std::vector<float>>(); mytree->Branch("unbiasedPullX",&m_unbiasedPullX);
  m_unbiasedPullY     = new std::vector<std::vector<float>>(); mytree->Branch("unbiasedPullY",&m_unbiasedPullY);
  m_trkPhiOnSurface   = new std::vector<std::vector<float>>(); mytree->Branch("trkPhiOnSurface",  &m_trkPhiOnSurface);
  m_trkThetaOnSurface = new std::vector<std::vector<float>>(); mytree->Branch("trkThetaOnSurface",&m_trkThetaOnSurface);
  m_numTotalClustersPerModule = new std::vector<std::vector<int>>(); mytree->Branch("numTotalClustersPerModule",&m_numTotalClustersPerModule);
  m_numTotalPixelsPerModule   = new std::vector<std::vector<int>>(); mytree->Branch("numTotalPixelsPerModule",  &m_numTotalPixelsPerModule);
  m_RdoToT          = new std::vector<std::vector<std::vector<int>>>(); mytree->Branch("RdoToT",    &m_RdoToT);
  m_RdoCharge       = new std::vector<std::vector<std::vector<float>>>(); mytree->Branch("RdoCharge", &m_RdoCharge);
  m_RdoPhi          = new std::vector<std::vector<std::vector<int>>>(); mytree->Branch("RdoPhi",    &m_RdoPhi);
  m_RdoEta          = new std::vector<std::vector<std::vector<int>>>(); mytree->Branch("RdoEta",    &m_RdoEta);

  m_hitTruthPdgId      = new std::vector<std::vector<std::vector<int>>>();   mytree->Branch("hitTruthPdgId",      &m_hitTruthPdgId);
  m_siHitPdgId         = new std::vector<std::vector<std::vector<int>>>();   mytree->Branch("siHitPdgId",         &m_siHitPdgId);
  m_siHitBarcode       = new std::vector<std::vector<std::vector<int>>>();   mytree->Branch("siHitBarcode",       &m_siHitBarcode);
  m_siHitStartPosX     = new std::vector<std::vector<std::vector<float>>>(); mytree->Branch("siHitStartPosX",     &m_siHitStartPosX);
  m_siHitStartPosY     = new std::vector<std::vector<std::vector<float>>>(); mytree->Branch("siHitStartPosY",     &m_siHitStartPosY);
  m_siHitEndPosX       = new std::vector<std::vector<std::vector<float>>>(); mytree->Branch("siHitEndPosX",       &m_siHitEndPosX);
  m_siHitEndPosY       = new std::vector<std::vector<std::vector<float>>>(); mytree->Branch("siHitEndPosY",       &m_siHitEndPosY);
  m_siHitEnergyDeposit = new std::vector<std::vector<std::vector<float>>>(); mytree->Branch("siHitEnergyDeposit", &m_siHitEnergyDeposit);


  m_truthEta     = new std::vector<float>(); mytree->Branch("truthEta",    &m_truthEta);
  m_truthPhi     = new std::vector<float>(); mytree->Branch("truthPhi",    &m_truthPhi);
  m_truthPt      = new std::vector<float>(); mytree->Branch("truthPt",     &m_truthPt);
  m_truthE       = new std::vector<float>(); mytree->Branch("truthE",      &m_truthE);
  m_truthCharge  = new std::vector<float>(); mytree->Branch("truthCharge", &m_truthCharge);
  m_truthPdgId   = new std::vector<int>();   mytree->Branch("truthPdgId",  &m_truthPdgId);
  m_truthBarcode = new std::vector<int>();   mytree->Branch("truthBarcode",&m_truthBarcode);
  m_truthStatus  = new std::vector<int>();   mytree->Branch("truthStatus", &m_truthStatus);

  m_muonEta = new std::vector<float>(); mytree->Branch("muonEta", &m_muonEta);
  m_muonPhi = new std::vector<float>(); mytree->Branch("muonPhi", &m_muonPhi);
  m_muonPt  = new std::vector<float>(); mytree->Branch("muonPt",  &m_muonPt);
  m_muonE   = new std::vector<float>(); mytree->Branch("muonE",   &m_muonE);

  m_jetEta     = new std::vector<float>(); mytree->Branch("jetEta", &m_jetEta);
  m_jetPhi     = new std::vector<float>(); mytree->Branch("jetPhi", &m_jetPhi);
  m_jetPt      = new std::vector<float>(); mytree->Branch("jetPt",  &m_jetPt);
  m_jetE       = new std::vector<float>(); mytree->Branch("jetE",   &m_jetE);
  m_jetPassJVT = new std::vector<int>();   mytree->Branch("jetPassJVT", &m_jetPassJVT);

  m_tauEta     = new std::vector<float>(); mytree->Branch("tauEta",    &m_tauEta);
  m_tauPhi     = new std::vector<float>(); mytree->Branch("tauPhi",    &m_tauPhi);
  m_tauPt      = new std::vector<float>(); mytree->Branch("tauPt",     &m_tauPt);
  m_tauM       = new std::vector<float>(); mytree->Branch("tauM",      &m_tauM);
  m_tauCharge  = new std::vector<float>(); mytree->Branch("tauCharge", &m_tauCharge);
  m_tau_nTracksCharged               = new std::vector<int>();   mytree->Branch("tauNumTracksCharged",        &m_tau_nTracksCharged);
  m_tau_nTracksIsolation             = new std::vector<int>();   mytree->Branch("tauNumTracksIsolation",      &m_tau_nTracksIsolation);
  m_tau_nAllTracks                   = new std::vector<int>();   mytree->Branch("tauNumAllTracks",            &m_tau_nAllTracks);
  m_tau_trackFilterProngs            = new std::vector<int>();   mytree->Branch("tauTrackFilterProngs",       &m_tau_trackFilterProngs);
  m_tau_trackFilterQuality           = new std::vector<int>();   mytree->Branch("tauTrackFilterQuality",      &m_tau_trackFilterQuality);
  m_tau_nClusters                    = new std::vector<int>();   mytree->Branch("tauNumClusters",             &m_tau_nClusters);
  m_tau_nPi0s                        = new std::vector<int>();   mytree->Branch("tauNumPi0s",                 &m_tau_nPi0s);
  m_tau_numCells                     = new std::vector<int>();   mytree->Branch("tauNumCells",                &m_tau_numCells);
  m_tau_isTauFlags                   = new std::vector<int>();   mytree->Branch("tauIsTauFlags",              &m_tau_isTauFlags);
  m_tau_BDTJetScore                  = new std::vector<float>(); mytree->Branch("tauBDTJetScore",             &m_tau_BDTJetScore);
  m_tau_BDTEleScore                  = new std::vector<float>(); mytree->Branch("tauBDTEleScore",             &m_tau_BDTEleScore);
  m_tau_EleMatchLikelihoodScore      = new std::vector<float>(); mytree->Branch("tauEleMatchLikelihoodScore", &m_tau_EleMatchLikelihoodScore);
  m_tau_BDTJetScoreSigTrans          = new std::vector<float>(); mytree->Branch("tauBDTJetScoreSigTrans",     &m_tau_BDTJetScoreSigTrans);
  m_tau_RNNJetScore                  = new std::vector<float>(); mytree->Branch("tauRNNJetScore",             &m_tau_RNNJetScore);
  m_tau_RNNJetScoreSigTrans          = new std::vector<float>(); mytree->Branch("tauRNNJetScoreSigTrans",     &m_tau_RNNJetScoreSigTrans);
  m_tau_ipZ0SinThetaSigLeadTrk       = new std::vector<float>(); mytree->Branch("tauIpZ0SinThetaSigLeadTrk",  &m_tau_ipZ0SinThetaSigLeadTrk);
  m_tau_etOverPtLeadTrk              = new std::vector<float>(); mytree->Branch("tauEtOverPtLeadTrk",         &m_tau_etOverPtLeadTrk);
  m_tau_leadTrkPt                    = new std::vector<float>(); mytree->Branch("tauLeadTrkPt",               &m_tau_leadTrkPt);
  m_tau_ipSigLeadTrk                 = new std::vector<float>(); mytree->Branch("tauIpSigLeadTrk",            &m_tau_ipSigLeadTrk);
  m_tau_massTrkSys                   = new std::vector<float>(); mytree->Branch("tauMassTrkSys",              &m_tau_massTrkSys);
  m_tau_trkWidth2                    = new std::vector<float>(); mytree->Branch("tauTrkWidth2",               &m_tau_trkWidth2);
  m_tau_trFlightPathSig              = new std::vector<float>(); mytree->Branch("tauTrFlightPathSig",         &m_tau_trFlightPathSig);
  m_tau_EMRadius                     = new std::vector<float>(); mytree->Branch("tauEMRadius",                &m_tau_EMRadius);
  m_tau_hadRadius                    = new std::vector<float>(); mytree->Branch("tauHadRadius",               &m_tau_hadRadius);
  m_tau_etEMAtEMScale                = new std::vector<float>(); mytree->Branch("tauEtEMAtEMScale",           &m_tau_etEMAtEMScale);
  m_tau_etHadAtEMScale               = new std::vector<float>(); mytree->Branch("tauEtHadAtEMScale",          &m_tau_etHadAtEMScale);
  m_tau_isolFrac                     = new std::vector<float>(); mytree->Branch("tauIsolFrac",                &m_tau_isolFrac);
  m_tau_centFrac                     = new std::vector<float>(); mytree->Branch("tauCentFrac",                &m_tau_centFrac);
  m_tau_stripWidth2                  = new std::vector<float>(); mytree->Branch("tauStripWidth2",             &m_tau_stripWidth2);
  m_tau_nStrip                       = new std::vector<int>();   mytree->Branch("tauNumStrip",                &m_tau_nStrip);
  m_tau_trkAvgDist                   = new std::vector<float>(); mytree->Branch("tauTrkAvgDist",              &m_tau_trkAvgDist);
  m_tau_dRmax                        = new std::vector<float>(); mytree->Branch("tauDRmax",                   &m_tau_dRmax);

  mytree->Branch("metCaloPx",          &m_metCaloPx);
  mytree->Branch("metCaloPy",          &m_metCaloPy);
  mytree->Branch("metCaloET",          &m_metCaloET);
  mytree->Branch("metCaloSumET",       &m_metCaloSumET);
                                               
  mytree->Branch("metTrackPx",         &m_metTrackPx);
  mytree->Branch("metTrackPy",         &m_metTrackPy);
  mytree->Branch("metTrackET",         &m_metTrackET);
  mytree->Branch("metTrackSumET",      &m_metTrackSumET);
                                               
  mytree->Branch("metLocHadPx",        &m_metLocHadPx);
  mytree->Branch("metLocHadPy",        &m_metLocHadPy);
  mytree->Branch("metLocHadET",        &m_metLocHadET);
  mytree->Branch("metLocHadSumET",     &m_metLocHadSumET);
                                               
  mytree->Branch("metCoreLCTopoPx",    &m_metCoreLCTopoPx);
  mytree->Branch("metCoreLCTopoPy",    &m_metCoreLCTopoPy);
  mytree->Branch("metCoreLCTopoET",    &m_metCoreLCTopoET);
  mytree->Branch("metCoreLCTopoSumET", &m_metCoreLCTopoSumET);
                                               
  mytree->Branch("metRefLCTopoPx",     &m_metRefLCTopoPx);
  mytree->Branch("metRefLCTopoPy",     &m_metRefLCTopoPy);
  mytree->Branch("metRefLCTopoET",     &m_metRefLCTopoET);
  mytree->Branch("metRefLCTopoSumET",  &m_metRefLCTopoSumET);
                                               
  mytree->Branch("metTruthPx",         &m_metTruthPx);
  mytree->Branch("metTruthPy",         &m_metTruthPy);
  mytree->Branch("metTruthET",         &m_metTruthET);
  mytree->Branch("metTruthSumET",      &m_metTruthSumET);


/*
  // Histgrams
  ANA_CHECK(book(TH1F("muValue",    "muValue",    50,  0,100)));
  ANA_CHECK(book(TH1F("mcEvWeight", "mcEvWeight", 50,-10, 40)));
  ANA_CHECK(book(TH1F("lumiBlk",    "lumiBlk",   100,  0,1500)));
  ANA_CHECK(book(TH1F("numVtx",     "numVtx",     50,-0.5,49.5)));

  ANA_CHECK(book(TH1F("numTruthMuon",       "numTruthMuon",        6,-0.5,5.5)));
  ANA_CHECK(book(TH1F("numTruthElectron",   "numTruthElectron",    6,-0.5,5.5)));
  ANA_CHECK(book(TH1F("numTruthVisTau",     "numTruthVisTau",      6,-0.5,5.5)));
  ANA_CHECK(book(TH1F("numTruthJet",        "numTruthJet",        20,-0.5,19.5)));
  ANA_CHECK(book(TH1F("numJet",             "numJet",             20,-0.5,19.5)));
  ANA_CHECK(book(TH1F("numJetjvt",          "numJetjvt",          20,-0.5,19.5)));

  ANA_CHECK(book(TH1F("muon_pt1", "muon_pt1", 60,0,120)));
  ANA_CHECK(book(TH1F("muon_eta1","muon_eta1",50,-2.5,2.5)));
  ANA_CHECK(book(TH1F("muon_pt2", "muon_pt2", 60,0,120)));
  ANA_CHECK(book(TH1F("muon_eta2","muon_eta2",50,-2.5,2.5)));
  ANA_CHECK(book(TH1F("dimuon_mass", "dimuon_mass", 100,0,200)));
  ANA_CHECK(book(TH1F("dimuon_pt",   "dimuon_pt",   100,0,200)));
  ANA_CHECK(book(TH1F("dimuon_eta",  "dimuon_eta",  50,-5,5)));

  trkHist_muon = new TrackHists("muon");
  trkHist_jet  = new TrackHists("jet");
  trkHist_iso  = new TrackHists("iso");

  trkHist_muon -> Init(wk());
  trkHist_jet  -> Init(wk());
  trkHist_iso  -> Init(wk());
*/

  return StatusCode::SUCCESS;
}

StatusCode ZmumuAnalysis::execute(){
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.
  ANA_MSG_DEBUG("Execute()");

  if (m_eventCounter%1000==0) { ANA_MSG_INFO(m_eventCounter << " processed..."); }
  m_eventCounter++;

  // retrieve the eventInfo object from the event store
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK(evtStore()->retrieve(eventInfo, "EventInfo"));

  // print out run and event number from retrieved object
  ANA_MSG_DEBUG("in execute, runNumber = " << eventInfo->runNumber() << ", eventNumber = " << eventInfo->eventNumber());

  bool isMC = false;
  if (eventInfo->eventType(xAOD::EventInfo::IS_SIMULATION)) { isMC=true; } // can do something with this later

  //=================
  // Truth container
  //=================
  const xAOD::TruthParticleContainer* truthParticle = 0;
  const xAOD::TruthVertexContainer* truthVertices(nullptr);
  if (isMC) { ANA_CHECK(evtStore()->retrieve(truthParticle,"TruthParticles")); }
  if (isMC) { ANA_CHECK(evtStore()->retrieve(truthVertices,"TruthVertices")); }

  //=======================================
  // Store PIXELVALID format in IDTRKVALID
  //=======================================
  if (m_flagTRKSTREAM) { ANA_CHECK(PixelNtupleMaker(isMC)); }

  //======================
  // RECONSTRUCTED TRACKS
  //======================
  const xAOD::TrackParticleContainer* recoTracksOrig = 0;
  ANA_CHECK(evtStore()->retrieve(recoTracksOrig,"PixelMonitoringTrack"));

  // make a shallow copy
  std::pair<xAOD::TrackParticleContainer*,xAOD::ShallowAuxContainer*> recoTracksShallowCopyPair = xAOD::shallowCopyContainer(*recoTracksOrig);
  xAOD::TrackParticleContainer* recoTracks = recoTracksShallowCopyPair.first;

  //==================
  // Vertex container
  //==================
  const xAOD::VertexContainer* primaryVertex = 0;
  ANA_CHECK(evtStore()->retrieve(primaryVertex,"PrimaryVertices"));

  //================
  // Muon container
  //================
  const xAOD::MuonContainer* muonOrig = 0;
  ANA_CHECK(evtStore()->retrieve(muonOrig,"Muons"));

  // make a shallow copy
//  std::pair<xAOD::MuonContainer*,xAOD::ShallowAuxContainer*> muonPair = xAOD::shallowCopyContainer(*muonOrig);
//  xAOD::MuonContainer* muon = muonPair.first;

  // create a shallow copy of the muons container
  auto muons_shallowCopy = xAOD::shallowCopyContainer( *muonOrig );
  std::unique_ptr<xAOD::MuonContainer> muon(muons_shallowCopy.first);
  std::unique_ptr<xAOD::ShallowAuxContainer> muonsAuxSC(muons_shallowCopy.second);

  //===============
  // Jet container
  //===============
  const xAOD::JetContainer* jetAntiKt4LCTopo = 0;
  ANA_CHECK(evtStore()->retrieve(jetAntiKt4LCTopo,"AntiKt4LCTopoJets"));

  //===============
  // Tau container
  //===============
  const xAOD::TauJetContainer* tauOrig = 0;
  ANA_CHECK(evtStore()->retrieve(tauOrig,"TauJets"));

  std::pair<xAOD::TauJetContainer*,xAOD::ShallowAuxContainer*> tauPair = xAOD::shallowCopyContainer(*tauOrig);
  xAOD::TauJetContainer* tau = tauPair.first;

  //===============
  // MissingET container
  //===============
  const xAOD::MissingETContainer* METCaloOrig = 0;
  const xAOD::MissingETContainer* METTrackOrig = 0;
  const xAOD::MissingETContainer* METLocHadTopoOrig = 0;
  const xAOD::MissingETContainer* METCore_AntiKt4LCTopoOrig = 0;
  const xAOD::MissingETContainer* METRef_AntiKt4LCTopoOrig = 0;
  const xAOD::MissingETContainer* METTruthOrig = 0;
  ANA_CHECK(evtStore()->retrieve(METCaloOrig,"MET_Calo"));
  ANA_CHECK(evtStore()->retrieve(METTrackOrig,"MET_Track"));
  ANA_CHECK(evtStore()->retrieve(METLocHadTopoOrig,"MET_LocHadTopo"));
  ANA_CHECK(evtStore()->retrieve(METCore_AntiKt4LCTopoOrig,"MET_Core_AntiKt4LCTopo"));
  ANA_CHECK(evtStore()->retrieve(METRef_AntiKt4LCTopoOrig,"MET_Reference_AntiKt4LCTopo"));
  if (isMC) { ANA_CHECK(evtStore()->retrieve(METTruthOrig,"MET_Truth")); }

  std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METCaloPair = xAOD::shallowCopyContainer(*METCaloOrig);
  std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METTrackPair = xAOD::shallowCopyContainer(*METTrackOrig);
  std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METLocHadTopoPair = xAOD::shallowCopyContainer(*METLocHadTopoOrig);
  std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METCore_AntiKt4LCTopoPair = xAOD::shallowCopyContainer(*METCore_AntiKt4LCTopoOrig);
  std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METRef_AntiKt4LCTopoPair = xAOD::shallowCopyContainer(*METRef_AntiKt4LCTopoOrig);
  xAOD::MissingETContainer* METCalo = METCaloPair.first;
  xAOD::MissingETContainer* METTrack = METTrackPair.first;
  xAOD::MissingETContainer* METLocHadTopo = METLocHadTopoPair.first;
  xAOD::MissingETContainer* METCore_AntiKt4LCTopo = METCore_AntiKt4LCTopoPair.first;
  xAOD::MissingETContainer* METRef_AntiKt4LCTopo = METRef_AntiKt4LCTopoPair.first;
  xAOD::MissingETContainer* METTruth = 0;
  std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METTruthPair;
  if (isMC) { 
//    std::pair<xAOD::MissingETContainer*,xAOD::ShallowAuxContainer*> METTruthPair = xAOD::shallowCopyContainer(*METTruthOrig);
    METTruthPair = xAOD::shallowCopyContainer(*METTruthOrig);
    METTruth = METTruthPair.first;
  }

  //==========================================================================================================================
  // Event selection
  //==========================================================================================================================

  //=============== 
  // Good Run List
  //=============== 
  if (!isMC && m_GRLFile!="DUMMY") {
    if (!m_grl->passRunLB(*eventInfo)){ return StatusCode::SUCCESS; }
  }

  //================
  // Event cleaning
  //================
  if (!isMC) {
    if (eventInfo->errorState(xAOD::EventInfo::Tile)==xAOD::EventInfo::Error) { return StatusCode::SUCCESS; }
    if (eventInfo->errorState(xAOD::EventInfo::LAr)==xAOD::EventInfo::Error)  { return StatusCode::SUCCESS; } 
    if (eventInfo->errorState(xAOD::EventInfo::SCT)==xAOD::EventInfo::Error)  { return StatusCode::SUCCESS; }
    if (eventInfo->isEventFlagBitSet(xAOD::EventInfo::Core, 18))              { return StatusCode::SUCCESS; }
  }

  //=========
  // Trigger
  //=========
  float triggerWeight = 1.0;
/*
  if (m_trigDecTool) {
    bool pass_HLT_mu20_iloose_L1MU15 = m_trigDecTool->isPassed("HLT_mu20_iloose_L1MU15");
    bool pass_HLT_mu50               = m_trigDecTool->isPassed("HLT_mu50");
  }

  auto chainGroup = m_trigDecisionTool->getChainGroup("HLT_mu*");
  std::map<std::string,int> triggerCounts;
  for (auto &trig : chainGroup->getListOfTriggers()) {
    auto cg = m_trigDecisionTool->getChainGroup(trig);
    std::string thisTrig = trig;
    ANA_MSG_INFO ("execute(): " << thisTrig << ", chain passed(1)/failed(0) = " << cg->isPassed() << ", total chain prescale (L1*HLT) = " << cg->getPrescale());
  }
*/

  //===============
  // pileup weight
  //===============
  float pileupWeight = 1.0;
  float mcEvWeight = 1.0;
  float xsecWeight = 1.0;
  float muValue = 0.0;
  float muActual = 0.0;
  uint32_t lumibk = 0.0;

  if (isMC) {
    if (m_pileupWeightFile!="DUMMY") {
      m_pileuptool->apply(*eventInfo);
//      pileupWeight = eventInfo->auxdata<double>("PileupWeight");
      pileupWeight = eventInfo->auxdata<float>("PileupWeight");
    }
    muValue    = eventInfo->auxdata<float>("averageInteractionsPerCrossing");
    muActual   = eventInfo->auxdata<float>("actualInteractionsPerCrossing");
    mcEvWeight = eventInfo->mcEventWeight(0)>0.0?1.0:-1.0;

//    std::cout << "STSTST " << pileupWeight << " " << mcEvWeight << std::endl;

    int mcDSID = eventInfo->mcChannelNumber();
    if      (mcDSID==361020) { xsecWeight=78.420e6*1.0/400000.0; }         // JZ0W : 361020 : 400000 : 78.420mb : 1.00
    else if (mcDSID==361021) { xsecWeight=78.420e6*6.7198e-4/399500.0; }   // JZ1W : 361021 : 400000 : 78.420mb : 6.7198E-04
    else if (mcDSID==361022) { xsecWeight= 2.433e6*3.3264e-4/286000.0; }   // JZ2W : 361022 : 400000 :  2.433mb : 3.3264E-04  2433200 2.4332e6
    else if (mcDSID==361023) { xsecWeight=26.454e3*3.1953e-4/400000.0; }   // JZ3W : 361023 : 400000 : 26.454ub : 3.1953E-04    26454 26.454e3
    else if (mcDSID==361024) { xsecWeight=  254.63*5.3009e-4/399398.0; }   // JZ4W : 361024 : 399400 : 254.63nb : 5.3009E-04      254.63
    else if (mcDSID==361025) { xsecWeight=   4.553*9.2325e-4/399300.0; }   // JZ5W : 361025 : 399300 :  4.553nb : 9.2325E-04
  }
  else {
    muValue = eventInfo->auxdata<float>("averageInteractionsPerCrossing");
    lumibk  = eventInfo->lumiBlock();
  }

  if (pileupWeight==0.0) { return StatusCode::SUCCESS; }

  // weight for histogram
  float histWeight = pileupWeight*xsecWeight*mcEvWeight*triggerWeight;

  //================
  // Find muon pair
  //================
  int numMuon = 0;
  xAOD::Muon* zMuon[5];
  for (auto muonSC : *muon) {
    if (muonSC->muonType()!=xAOD::Muon::Combined) { continue; }
    if (m_muonSelection->getQuality(*muonSC)<=xAOD::Muon::Loose) {
      if (muonSC->passesIDCuts()) {

//        std::cout << "before " << muonSC->pt() << std::endl;
//
//        if (m_muonCalibrationAndSmearingTool->applyCorrection(*muonSC)==CP::CorrectionCode::Error) {
//          ANA_MSG_INFO ("execute(): Problem with Muon Calibration And Smearing Tool (Error or OutOfValidityRange) ");
//        }
//        std::cout << "after " << muonSC->pt() << std::endl;

        if (muonSC->pt()/1000.0>25.0) { zMuon[numMuon]=muonSC; numMuon++; }
      }
    }
  }
//STSTST  if (numMuon!=2) { return StatusCode::SUCCESS; }
//STSTST  if (zMuon[0]->charge()*zMuon[1]->charge()>=0.0) { return StatusCode::SUCCESS; }

  // sorting...
  for (int i=0; i<numMuon; i++) {
    for (int j=i+1; j<numMuon; j++) {
      if (zMuon[j]->pt()>zMuon[i]->pt()) {
        xAOD::Muon* indx=zMuon[i]; zMuon[i]=zMuon[j]; zMuon[j]=indx;
      }
    }
  }

  TLorentzVector muon1,muon2,Zboson;
  if (numMuon>1) {
    muon1.SetPtEtaPhiM(zMuon[0]->pt(),zMuon[0]->eta(),zMuon[0]->phi(),zMuon[0]->m());
    muon2.SetPtEtaPhiM(zMuon[1]->pt(),zMuon[1]->eta(),zMuon[1]->phi(),zMuon[1]->m());
    Zboson = muon1 + muon2;
  }



/*
  int numMuon = 0;
  xAOD::MuonContainer::const_iterator muZitr[5];
//  for (xAOD::MuonContainer::const_iterator mu_itr=muon->begin(); mu_itr!=muon->end(); mu_itr++) {
  for (xAOD::MuonContainer::iterator mu_itr=muon->begin(); mu_itr!=muon->end(); mu_itr++) {
    std::cout << "before " << (*mu_itr)->pt() << std::endl;
    xAOD::Muon *muon = (*mu_itr);
    if (muon->muonType()!=xAOD::Muon::Combined) { continue; }
    if (m_muonCalibrationAndSmearingTool->applyCorrection(*muon)==CP::CorrectionCode::Error) {
      Error("execute()", "MuonCalibrationAndSmearingTool returns Error CorrectionCode");
    }
//      if (m_muonCalibrationAndSmearingTool->applyCorrection(*muonSC) != CP::CorrectionCode::Ok) {
    std::cout << "after " << (*mu_itr)->pt() << " " << muon->pt() << std::endl;
    if ((*mu_itr)->pt()/1000.0>25.0) {
      if (m_muonSelection->getQuality(*(*mu_itr))<=xAOD::Muon::Loose) {
        if ((*mu_itr)->passesIDCuts()) {
          muZitr[numMuon]=mu_itr; numMuon++;
        }
      }
    }
  }
  if (numMuon!=2) { return StatusCode::SUCCESS; }
  if ((*muZitr[0])->charge()*(*muZitr[1])->charge()>=0.0) { return StatusCode::SUCCESS; }

  // sorting...
  for (int i=0; i<numMuon; i++) {
    for (int j=i+1; j<numMuon; j++) {
      if ((*muZitr[j])->pt()>(*muZitr[i])->pt()) {
        xAOD::MuonContainer::const_iterator indx=muZitr[i]; muZitr[i]=muZitr[j]; muZitr[j]=indx;
      }
    }
  }

  TLorentzVector muon1,muon2,Zboson;
  if (numMuon>1) {
    muon1.SetPtEtaPhiM((*muZitr[0])->pt(),(*muZitr[0])->eta(),(*muZitr[0])->phi(),(*muZitr[0])->m());
    muon2.SetPtEtaPhiM((*muZitr[1])->pt(),(*muZitr[1])->eta(),(*muZitr[1])->phi(),(*muZitr[1])->m());
    Zboson = muon1 + muon2;
  }
*/

  //====================
  // Di-lepton mass cut
  //====================
//STSTST  if (Zboson.M()/1000.0<76.0)  { return StatusCode::SUCCESS; }
//STSTST  if (Zboson.M()/1000.0>106.0) { return StatusCode::SUCCESS; }

  //==========================================================================================================================
  // Analize data
  //==========================================================================================================================

  //========
  // Vertex
  //========
  int numVtx = 0;
  float pVtxX = -999.;
  float pVtxY = -999.;
  float pVtxZ = -999.;
  float pVtxXErr = -999.;
  float pVtxYErr = -999.;
  float pVtxZErr = -999.;
  for (xAOD::VertexContainer::const_iterator vtx_itr=primaryVertex->begin(); vtx_itr!=primaryVertex->end(); vtx_itr++) {
    if ((*vtx_itr)->vertexType()==xAOD::VxType::PriVtx) {
      const Amg::MatrixX& pVtxCov = (*vtx_itr)->covariancePosition();
      pVtxX = (*vtx_itr)->x();
      pVtxY = (*vtx_itr)->y();
      pVtxZ = (*vtx_itr)->z();
      pVtxXErr = TMath::Sqrt(pVtxCov(0,0));
      pVtxYErr = TMath::Sqrt(pVtxCov(1,1));
      pVtxZErr = TMath::Sqrt(pVtxCov(2,2));
    }
    if ((*vtx_itr)->vertexType()!=0) { numVtx++; }
  }

  float truthPVtxX = -999.;
  float truthPVtxY = -999.;
  float truthPVtxZ = -999.;
  if (isMC) {
    for (auto truthVtx_itr = truthVertices->begin(); truthVtx_itr != truthVertices->end(); truthVtx_itr++) {
      if ((*truthVtx_itr)->isAvailable<float>("x")) { truthPVtxX=(*truthVtx_itr)->x(); }
      if ((*truthVtx_itr)->isAvailable<float>("y")) { truthPVtxX=(*truthVtx_itr)->y(); }
      if ((*truthVtx_itr)->isAvailable<float>("z")) { truthPVtxX=(*truthVtx_itr)->z(); }
      break;
    }
  }

  //================
  // Truth particle
  //================
  int numTruthMuon = 0;
  int numTruthElectron = 0;
  int numTruthTau = 0;
  int numTruthVisTau = 0;
  xAOD::TruthParticleContainer::const_iterator muonTruthItr[10];
  xAOD::TruthParticleContainer::const_iterator electronTruthItr[10];
  xAOD::TruthParticleContainer::const_iterator tauTruthItr[10];
  TLorentzVector tauVisTruth[2];
  if (isMC) {   
    for (xAOD::TruthParticleContainer::const_iterator tr_it=truthParticle->begin(); tr_it!=truthParticle->end(); tr_it++) {
      if (TMath::Abs((*tr_it)->pdgId())==13 && (*tr_it)->pt()/1000.0>15.0 && TMath::Abs((*tr_it)->eta())<2.5) {
        if ((*tr_it)->barcode()<10000) { muonTruthItr[numTruthMuon]=tr_it; numTruthMuon++; }
      }
    }

    for (xAOD::TruthParticleContainer::const_iterator tr_it=truthParticle->begin(); tr_it!=truthParticle->end(); tr_it++) {
      if (TMath::Abs((*tr_it)->pdgId())==11 && (*tr_it)->pt()/1000.0>15.0 && TMath::Abs((*tr_it)->eta())<2.5) {
        if ((*tr_it)->barcode()<10000) { 
          bool checkOverlap = false;
          for (int i=0; i<numTruthMuon; i++) {
            if (deltaR((*tr_it),(*muonTruthItr[i]))<0.2) { checkOverlap=true; }
          }
          if (!checkOverlap) { electronTruthItr[numTruthElectron]=tr_it; numTruthElectron++; }
        }
      }
    }

    for (xAOD::TruthParticleContainer::const_iterator tr_it=truthParticle->begin(); tr_it!=truthParticle->end(); tr_it++) {
      if (TMath::Abs((*tr_it)->pdgId())==15 && (*tr_it)->pt()/1000.0>15.0 && TMath::Abs((*tr_it)->eta())<2.5) {
        if ((*tr_it)->barcode()<10000) { 
          bool checkOverlap = false;
          for (int i=0; i<numTruthMuon; i++) {
            if (deltaR((*tr_it),(*muonTruthItr[i]))<0.2) { checkOverlap=true; }
          }
          for (int i=0; i<numTruthElectron; i++) {
            if (deltaR((*tr_it),(*electronTruthItr[i]))<0.2) { checkOverlap=true; }
          }
          if (!checkOverlap) { tauTruthItr[numTruthTau]=tr_it; numTruthTau++; }
        }
      }
    }

    for (int i=0; i<numTruthTau; i++) {
      double mindR = 100.0;
      xAOD::TruthParticleContainer::const_iterator closestNeutrino;
      for (xAOD::TruthParticleContainer::const_iterator tr_it=truthParticle->begin(); tr_it!=truthParticle->end(); tr_it++) {
        if (TMath::Abs((*tr_it)->pdgId())==16) {
          double dR = deltaR((*tr_it),(*tauTruthItr[i]));
          if (dR<mindR && (*tr_it)->pdgId()*(*tauTruthItr[i])->pdgId()>0) { closestNeutrino=tr_it; mindR=dR; }
        }
      }
      if (mindR<0.8) {
        TLorentzVector tauV;     tauV.SetPtEtaPhiM((*tauTruthItr[i])->pt(),(*tauTruthItr[i])->eta(),(*tauTruthItr[i])->phi(),(*tauTruthItr[i])->m());
        TLorentzVector neutrino; neutrino.SetPtEtaPhiM((*closestNeutrino)->pt(),(*closestNeutrino)->eta(),(*closestNeutrino)->phi(),(*closestNeutrino)->m());
        tauVisTruth[numTruthVisTau] = tauV-neutrino; numTruthVisTau++;
      }
    }
  }

  //=================
  // Count truth jet
  //=================
  int numTruthJet = 0;

  //===============
  // Jet selection
  //===============
  int numJet = 0;
  xAOD::JetContainer::const_iterator jetItr[50];
  if (jetAntiKt4LCTopo) {
    for (xAOD::JetContainer::const_iterator jet_it=jetAntiKt4LCTopo->begin(); jet_it!=jetAntiKt4LCTopo->end(); jet_it++) {

      if (!m_jetCleaning->keep(**jet_it)) { continue; } //only keep good clean jets

      if ((*jet_it)->pt()/1000.0>25.0 && TMath::Abs((*jet_it)->eta())<4.5) {
        bool checkOverlap = false;

/*
        for (int i=0; i<numTruthMuon; i++) {
          if (deltaR((*jet_it),(*muonTruthItr[i]))<0.2) { checkOverlap=true; }
        }
        for (int i=0; i<numTruthElectron; i++) {
          if (deltaR((*jet_it),(*electronTruthItr[i]))<0.2) { checkOverlap=true; }
        }
        for (int i=0; i<numTruthTau; i++) {
          if (deltaR((*jet_it),(*tauTruthItr[i]))<0.4) { checkOverlap=true; }
        }
*/
        for (int i=0; i<numMuon; i++) {
//          if (deltaR((*jet_it),(*muZitr[i]))<0.2) { checkOverlap=true; }
          if (deltaR((*jet_it),zMuon[i])<0.2) { checkOverlap=true; }
        }

        if (!checkOverlap) { 
          jetItr[numJet]=jet_it; numJet++; 
        }
      }
    }
  }

  //======================
  // Count number of jets
  //======================
  int numJetjvt = 0;
  for (int i=0; i<numJet; i++) {
    bool passJvt = true;
    if ((*jetItr[i])->pt()/1000.0<60.0 && TMath::Abs((*jetItr[i])->eta())<2.4) { passJvt = m_jetsf->passesJvtCut(*(*jetItr[i])); }
    if ((*jetItr[i])->pt()/1000.0<50.0 && TMath::Abs((*jetItr[i])->eta())>2.5) { passJvt = m_fjetsf->passesJvtCut(**jetItr[i]); }
    if (passJvt) { numJetjvt++; }
  }

  //=========================
  // Track matched with muon
  //=========================
  std::vector<xAOD::TrackParticleContainer::const_iterator> muonTrkIter;
  for (int i=0; i<numMuon; i++) {
    xAOD::TrackParticleContainer::const_iterator candTrk;
    double mindR = 100000.0;
    for (xAOD::TrackParticleContainer::const_iterator recoTrk_itr=recoTracks->begin(); recoTrk_itr!=recoTracks->end(); recoTrk_itr++) {
      if ((*recoTrk_itr)->pt()/1000.0>20.0) {
//        double dR = deltaR((*muZitr[i]),(*recoTrk_itr));
        double dR = deltaR(zMuon[i],(*recoTrk_itr));
        if (dR<mindR) { mindR=dR; candTrk=recoTrk_itr; }
      }
    }
    if (mindR<0.1) { muonTrkIter.push_back(candTrk); }
  }

  //===================================
  // Track inside jets in hard process
  //===================================
  std::vector<xAOD::TrackParticleContainer::const_iterator> jetTrkIter;
  for (int i=0; i<numJet; i++) {
    for (xAOD::TrackParticleContainer::const_iterator recoTrk_itr=recoTracks->begin(); recoTrk_itr!=recoTracks->end(); recoTrk_itr++) {
      bool checkOverlap = false;
      for (int j=0; j<(int)muonTrkIter.size(); j++) {
        if (recoTrk_itr==muonTrkIter[j]) { checkOverlap = true; break; }
      }
      if (!checkOverlap) {
        if (deltaR((*jetItr[i]),(*recoTrk_itr))<0.4) { jetTrkIter.push_back(recoTrk_itr); }
      }
    }
  }

  //================
  // Isolated track
  //================
  std::vector<xAOD::TrackParticleContainer::const_iterator> isoTrkIter;
  for (xAOD::TrackParticleContainer::const_iterator recoTrk_itr=recoTracks->begin(); recoTrk_itr!=recoTracks->end(); recoTrk_itr++) {
    bool checkOverlap = false;
    for (int j=0; j<(int)muonTrkIter.size(); j++) {
      if (recoTrk_itr==muonTrkIter[j]) { checkOverlap=true; break; }
    }
    if (!checkOverlap) {
      for (int j=0; j<(int)jetTrkIter.size(); j++) {
        if (recoTrk_itr==jetTrkIter[j]) { checkOverlap=true; break; }
      }
    }
    if (!checkOverlap) { isoTrkIter.push_back(recoTrk_itr); }
  }

/*
  //==========================================================================================================================
  // Fill histograms
  //==========================================================================================================================
  hist("muValue")    -> Fill(muValue,histWeight);
  hist("mcEvWeight") -> Fill(mcEvWeight,histWeight);
  hist("lumiBlk")    -> Fill(lumibk,histWeight);
  hist("numVtx")     -> Fill(1.0*numVtx);

  hist("numTruthMuon")     -> Fill(1.0*numTruthMuon);
  hist("numTruthElectron") -> Fill(1.0*numTruthElectron);
  hist("numTruthVisTau")   -> Fill(1.0*numTruthVisTau);
  hist("numTruthJet")      -> Fill(1.0*numTruthJet);
  hist("numJet")           -> Fill(1.0*numJet);
  hist("numJetjvt")        -> Fill(1.0*numJetjvt);

  hist("muon_pt1")  -> Fill(muon1.Pt()/1000.0,histWeight);
  hist("muon_eta1") -> Fill(muon1.Eta(),histWeight);
  hist("muon_pt2")  -> Fill(muon2.Pt()/1000.0,histWeight);
  hist("muon_eta2") -> Fill(muon2.Eta(),histWeight);
  hist("dimuon_mass") -> Fill(Zboson.M()/1000.0,histWeight);
  hist("dimuon_pt")   -> Fill(Zboson.Pt()/1000.0,histWeight);
  hist("dimuon_eta")  -> Fill(Zboson.Eta(),histWeight);

  for (int i=0; i<(int)muonTrkIter.size(); i++) {
    if (!checkQuality((*muonTrkIter[i]))) { continue; }
    trkHist_muon  -> FillHists((*muonTrkIter[i]),histWeight);
  }

  for (int i=0; i<(int)jetTrkIter.size(); i++) {
    if (!checkQuality((*jetTrkIter[i]))) { continue; }
    trkHist_jet  -> FillHists((*jetTrkIter[i]),histWeight);
  }

  for (int i=0; i<(int)isoTrkIter.size(); i++) {
    if (!checkQuality((*isoTrkIter[i]))) { continue; }
    trkHist_iso  -> FillHists((*isoTrkIter[i]),histWeight);
  }
*/

  // Fill Root Tree
  m_runNumber   = eventInfo->runNumber();
  m_eventNumber = eventInfo->eventNumber();
  m_pileupWeight = pileupWeight;
  m_mcWeight     = mcEvWeight;

  m_lumiB     = lumibk;
  m_averagePU = muValue;
  m_eventPU   = muActual;
  m_mcFlag    = isMC;

  m_numVtx = numVtx;
  m_pVtxX  = pVtxX;
  m_pVtxY  = pVtxY;
  m_pVtxZ  = pVtxZ;

  m_pVtxXErr = pVtxXErr;
  m_pVtxYErr = pVtxYErr;
  m_pVtxZErr = pVtxZErr;

  m_truthPVtxX = truthPVtxX;
  m_truthPVtxY = truthPVtxY;
  m_truthPVtxZ = truthPVtxZ;

  m_trackPt             -> clear();
  m_trackPhi            -> clear();
  m_trackEta            -> clear();
  m_trackTheta          -> clear();
  m_trackCharge         -> clear();
  m_trackqOverP         -> clear();
  m_trackD0             -> clear();
  m_trackZ0             -> clear();
  m_trackD0Err          -> clear();
  m_trackZ0Err          -> clear();
  m_trackqOverPErr      -> clear();
  m_trackDeltaZSinTheta -> clear();
  m_trackMindR          -> clear();
  m_trackClass          -> clear();
  m_trackPassCut        -> clear();
  m_trackOutliers       -> clear();
  m_trackChiSqPerDof    -> clear();
  m_trackStdDevChi2OS   -> clear();
  m_nPixelHits          -> clear();
  m_nPixelHoles         -> clear();
  m_nPixelLayers        -> clear();
  m_nPixelOutliers      -> clear();
  m_nPixelGanged        -> clear();
  m_nPixelShared        -> clear();
  m_nPixelSplit         -> clear();
  m_nPixelDeadSensors   -> clear();
  m_nIBLUsedHits        -> clear();
  m_nBLUsedHits         -> clear();
  m_nSCTHits            -> clear();
  m_nSCTHoles           -> clear();
  m_nSCTOutliers        -> clear();
  m_nSCTDeadSensors     -> clear();
  m_nTRTHits            -> clear();
  m_nTRTOutliers        -> clear();
  m_nTRTHoles           -> clear();
  m_nTRTHTHits          -> clear();
  m_nIBLSplitHits       -> clear();
  m_nBLSplitHits        -> clear();
  m_nIBLSharedHits      -> clear();
  m_nBLSharedHits       -> clear();
  m_nIBLHits            -> clear();
  m_nBLHits             -> clear();
  m_nL1Hits             -> clear();
  m_nL2Hits             -> clear();
  m_nECHits             -> clear();
  m_nIBLExpectedHits    -> clear();
  m_nBLExpectedHits     -> clear();
  m_nSCTSharedHits      -> clear();
  m_TruncateddEdx       -> clear();
  m_nTruncateddEdx      -> clear();
  m_extrapolatedIBLX    -> clear();
  m_extrapolatedIBLY    -> clear();
  m_extrapolatedIBLZ    -> clear();
  m_extrapolatedBLX     -> clear();
  m_extrapolatedBLY     -> clear();
  m_extrapolatedBLZ     -> clear();
  m_extrapolatedL1X     -> clear();
  m_extrapolatedL1Y     -> clear();
  m_extrapolatedL1Z     -> clear();
  m_extrapolatedL2X     -> clear();
  m_extrapolatedL2Y     -> clear();
  m_extrapolatedL2Z     -> clear();
  m_truePt              -> clear();
  m_truePhi             -> clear();
  m_trueEta             -> clear();
  m_trueE               -> clear();
  m_trued0              -> clear();
  m_truez0              -> clear();
  m_truephi             -> clear();
  m_truetheta           -> clear();
  m_trueqoverp          -> clear();
  m_truepdgid           -> clear();
  m_truebarcode         -> clear();
  m_truthmatchprob      -> clear();
  m_trueMindR           -> clear();
  m_genVtxR             -> clear();
  m_genVtxZ             -> clear();
  m_parentFlav          -> clear();
  m_hitIsEndCap         -> clear();
  m_hitIsHole           -> clear();
  m_hitIsOutlier        -> clear();
  m_hitLayer            -> clear();
  m_hitEtaModule        -> clear();
  m_hitPhiModule        -> clear();
  m_hitCharge           -> clear();
  m_hitToT              -> clear();
  m_hitLVL1A            -> clear();
  m_hitNPixel           -> clear();
  m_hitNPixelX          -> clear();
  m_hitNPixelY          -> clear();
  m_hitBSerr            -> clear();
  m_hitDCSstate         -> clear();
  m_hitVBias            -> clear();
  m_hitTemp             -> clear();
  m_hitLorentzShift     -> clear();
  m_hitIsSplit          -> clear();
  m_hitIsEdge           -> clear();
  m_hitIsOverflow       -> clear();
  m_hitIsolation10x2    -> clear();
  m_hitIsolation20x4    -> clear();
  m_hitGlobalX          -> clear();
  m_hitGlobalY          -> clear();
  m_hitGlobalZ          -> clear();
  m_hitLocalX           -> clear();
  m_hitLocalY           -> clear();
  m_trkLocalX           -> clear();
  m_trkLocalY           -> clear();
  m_unbiasedResidualX   -> clear();
  m_unbiasedResidualY   -> clear();
  m_unbiasedPullX       -> clear();
  m_unbiasedPullY       -> clear();
  m_trkPhiOnSurface     -> clear();
  m_trkThetaOnSurface   -> clear();
  m_numTotalClustersPerModule -> clear();
  m_numTotalPixelsPerModule   -> clear();
  m_RdoToT              -> clear();
  m_RdoCharge           -> clear();
  m_RdoPhi              -> clear();
  m_RdoEta              -> clear();
  m_hitTruthPdgId       -> clear();
  m_siHitPdgId          -> clear();
  m_siHitBarcode        -> clear();
  m_siHitStartPosX      -> clear();
  m_siHitStartPosY      -> clear();
  m_siHitEndPosX        -> clear();
  m_siHitEndPosY        -> clear();
  m_siHitEnergyDeposit  -> clear();

  for (xAOD::TrackParticleContainer::const_iterator recoTrk_itr=recoTracks->begin(); recoTrk_itr!=recoTracks->end(); recoTrk_itr++) {

//    if (TMath::Abs(((*recoTrk_itr)->z0()+(*recoTrk_itr)->vz()-pVtxZ)*TMath::Sin((*recoTrk_itr)->theta()))>3.0) { continue; }

    uint8_t nPixelDeadSensor = 0;     (*recoTrk_itr)->summaryValue(nPixelDeadSensor,xAOD::numberOfPixelDeadSensors);
    uint8_t numberOfPixelHits= 0;     (*recoTrk_itr)->summaryValue(numberOfPixelHits,xAOD::numberOfPixelHits);
    uint8_t numberOfPixelHoles= 0;    (*recoTrk_itr)->summaryValue(numberOfPixelHoles,xAOD::numberOfPixelHoles);
    uint8_t numberOfPixelOutliers= 0; (*recoTrk_itr)->summaryValue(numberOfPixelOutliers,xAOD::numberOfPixelOutliers);

    std::vector<int>   clusterLayer;
    std::vector<int>   clusterBEC;
    std::vector<bool>  clusterIsEdge;
    std::vector<bool>  clusterIsOverflow;
    std::vector<int>   clusterIsSplit;
    std::vector<int>   clusterIsolation20x4;
    if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterLayer")) {
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterLayer"))              { clusterLayer              = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterLayer"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterBEC"))                { clusterBEC                = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterBEC"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<bool>>("ClusterIsEdge"))            { clusterIsEdge             = (*recoTrk_itr)->auxdata<std::vector<bool>>("ClusterIsEdge"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<bool>>("ClusterIsOverflow"))        { clusterIsOverflow         = (*recoTrk_itr)->auxdata<std::vector<bool>>("ClusterIsOverflow"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterIsSplit"))            { clusterIsSplit            = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterIsSplit"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterIsolation20x4"))      { clusterIsolation20x4      = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterIsolation20x4"); }
    }
    else { continue; }

    // Good tracks must be required for the dE/dx and Lorentz angle measurements
    int checkIBL(0),checkBLY(0),checkLY1(0),checkLY2(0),checkED1(0),checkED2(0),checkED3(0);
    for (int i=0; i<(int)clusterLayer.size(); i++) {
      if      (clusterBEC.at(i)==0 && clusterLayer.at(i)==0) { checkIBL++; }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==1) { checkBLY++; }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==2) { checkLY1++; }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==3) { checkLY2++; }
      else if (TMath::Abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==0) { checkED1++; }
      else if (TMath::Abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==1) { checkED2++; }
      else if (TMath::Abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==2) { checkED3++; }
    }

    bool passCut = false;

    if ((*recoTrk_itr)->pt()/1000.0>1.0) { passCut=true; }
    if (!checkQuality((*recoTrk_itr))) { passCut=false; }

    // Cluster should not contain edge pixels
    int isEdge = 0;
    for (int i=0; i<(int)clusterLayer.size(); i++) { isEdge+=clusterIsEdge.at(i); }

    // Cluster should not contain overflow pixels
    int isOverflow = 0;
    for (int i=0; i<(int)clusterLayer.size(); i++) { isOverflow+=clusterIsOverflow.at(i); }

    // Cluster should not contain split state
    int isSplit = 0;
    for (int i=0; i<(int)clusterLayer.size(); i++) { isSplit+=clusterIsSplit.at(i); }

    // Strong isolation
    int iso20x4 = 0;
    for (int i=0; i<(int)clusterLayer.size(); i++) { iso20x4+=clusterIsolation20x4.at(i); }

    if (numberOfPixelHits>3 && numberOfPixelHoles==0 && nPixelDeadSensor==0 && numberOfPixelOutliers==0 && isEdge==0 && isOverflow==0 && isSplit==0 && iso20x4==0) {
      if (checkIBL>0 && checkBLY>0 && checkLY1>0 && checkLY2>0) { // Barrel
        passCut = true;
      }
      else if (checkIBL>0 && checkED1>0 && checkED2>0 && checkED3>0) { // Endcap
        passCut = true;
      }
    }

    if (!passCut) { continue; }



    // track Helix parameters
    float d0err(-999.0),z0err(-999.0),qOverperr(-999.0);
    if ((*recoTrk_itr)->isAvailable<float>("d0err")) { 
      d0err = (*recoTrk_itr)->auxdata<float>("d0err"); 
      z0err = (*recoTrk_itr)->auxdata<float>("z0err");
      if ((*recoTrk_itr)->isAvailable<float>("qOverPerr")) { qOverperr = (*recoTrk_itr)->auxdata<float>("qOverPerr"); }
    }

    m_trackPt             -> push_back((*recoTrk_itr)->pt()/1000.0);
    m_trackPhi            -> push_back((*recoTrk_itr)->phi());
    m_trackEta            -> push_back((*recoTrk_itr)->eta());
    m_trackTheta          -> push_back((*recoTrk_itr)->theta());
    m_trackCharge         -> push_back((*recoTrk_itr)->charge());
    m_trackqOverP         -> push_back((*recoTrk_itr)->qOverP());
    m_trackD0             -> push_back((*recoTrk_itr)->d0());
    m_trackZ0             -> push_back((*recoTrk_itr)->z0());
    m_trackD0Err          -> push_back(d0err);
    m_trackZ0Err          -> push_back(z0err);
    m_trackqOverPErr      -> push_back(qOverperr);
    m_trackDeltaZSinTheta -> push_back(((*recoTrk_itr)->z0()+((*recoTrk_itr)->vz())-pVtxZ)*TMath::Sin((*recoTrk_itr)->theta()));

    float trackMindR = 10000.0;
    for (xAOD::TrackParticleContainer::const_iterator recoNextTrk_itr=recoTracks->begin(); recoNextTrk_itr!=recoTracks->end(); recoNextTrk_itr++) {
      double dR = deltaR((*recoNextTrk_itr),(*recoTrk_itr));
      if (dR<trackMindR) { trackMindR=dR; }
    }
    m_trackMindR          -> push_back(trackMindR);

    // Tack classification
    int trackClass = 0;
    for (int i=0; i<(int)muonTrkIter.size(); i++) {
      if (recoTrk_itr==muonTrkIter[i]) { trackClass=1; break; }
    }

    for (int i=0; i<(int)jetTrkIter.size(); i++) {
      if (recoTrk_itr==jetTrkIter[i]) { trackClass=2; break; }
    }
    m_trackClass   -> push_back(trackClass);
    m_trackPassCut -> push_back(passCut);

    // Hit multiplicity
    uint8_t numberOfOutliersOnTrack=0; (*recoTrk_itr)->summaryValue(numberOfOutliersOnTrack,xAOD::numberOfOutliersOnTrack);
    float chiSqPerDoF=0;               if ((*recoTrk_itr)->numberDoF()>0) { chiSqPerDoF=(*recoTrk_itr)->chiSquared()/(*recoTrk_itr)->numberDoF(); }
    uint8_t stdDeviationOfChi2OS=0;    (*recoTrk_itr)->summaryValue(stdDeviationOfChi2OS,xAOD::standardDeviationOfChi2OS);
    uint8_t numberOfGangedPixels=0;    (*recoTrk_itr)->summaryValue(numberOfGangedPixels,xAOD::numberOfGangedPixels);
    uint8_t numberOfPixelSharedHits=0; (*recoTrk_itr)->summaryValue(numberOfPixelSharedHits,xAOD::numberOfPixelSharedHits);
    uint8_t numberOfPixelSplitHits=0;  (*recoTrk_itr)->summaryValue(numberOfPixelSplitHits,xAOD::numberOfPixelSplitHits);
    uint8_t numberOfSCTHits=0;         (*recoTrk_itr)->summaryValue(numberOfSCTHits,xAOD::numberOfSCTHits);
    uint8_t numberOfSCTHoles=0;        (*recoTrk_itr)->summaryValue(numberOfSCTHoles,xAOD::numberOfSCTHoles);
    uint8_t numberOfSCTOutliers=0;     (*recoTrk_itr)->summaryValue(numberOfSCTOutliers,xAOD::numberOfSCTOutliers);
    uint8_t numberOfSCTDeadSensors=0;  (*recoTrk_itr)->summaryValue(numberOfSCTDeadSensors,xAOD::numberOfSCTDeadSensors);
    uint8_t numberOfTRTHits=0;         (*recoTrk_itr)->summaryValue(numberOfTRTHits,xAOD::numberOfTRTHits);
    uint8_t numberOfPixelLayers=0;     (*recoTrk_itr)->summaryValue(numberOfPixelLayers,xAOD::numberOfContribPixelLayers);
    uint8_t numberOfIBLHits=0;         (*recoTrk_itr)->summaryValue(numberOfIBLHits,xAOD::numberOfInnermostPixelLayerHits);
    uint8_t numberOfIBLSplitHits=0;    (*recoTrk_itr)->summaryValue(numberOfIBLSplitHits,xAOD::numberOfInnermostPixelLayerSplitHits);
    uint8_t numberOfIBLSharedHits=0;   (*recoTrk_itr)->summaryValue(numberOfIBLSharedHits,xAOD::numberOfInnermostPixelLayerSharedHits);
    uint8_t numberOfBLHits=0;          (*recoTrk_itr)->summaryValue(numberOfBLHits,xAOD::numberOfNextToInnermostPixelLayerHits);
    uint8_t numberOfBLSplitHits=0;     (*recoTrk_itr)->summaryValue(numberOfBLSplitHits,xAOD::numberOfNextToInnermostPixelLayerSplitHits);
    uint8_t numberOfBLSharedHits=0;    (*recoTrk_itr)->summaryValue(numberOfBLSharedHits,xAOD::numberOfNextToInnermostPixelLayerSharedHits);
    uint8_t numberOfIBLExpectedHits=0; (*recoTrk_itr)->summaryValue(numberOfIBLExpectedHits,xAOD::expectInnermostPixelLayerHit);
    uint8_t numberOfBLExpectedHits=0;  (*recoTrk_itr)->summaryValue(numberOfBLExpectedHits,xAOD::expectNextToInnermostPixelLayerHit);
    uint8_t numberOfSCTSharedHits=0;   (*recoTrk_itr)->summaryValue(numberOfSCTSharedHits,xAOD::numberOfSCTSharedHits);
    uint8_t numberOfTRTOutliers=0;     (*recoTrk_itr)->summaryValue(numberOfTRTOutliers,xAOD::numberOfTRTOutliers);
    uint8_t numberOfTRTHoles=0;        (*recoTrk_itr)->summaryValue(numberOfTRTHoles,xAOD::numberOfTRTHoles);
    uint8_t numberOfTRTHighThresholdHits=0; (*recoTrk_itr)->summaryValue(numberOfTRTHighThresholdHits,xAOD::numberOfTRTHighThresholdHits);

    if (numberOfPixelOutliers==0) {
      if ((int)numberOfIBLHits!=checkIBL) { 
        ANA_MSG_ERROR("IBL hits are not consistent with cluster counting " << (int)numberOfIBLHits << " aaa " << checkIBL << " " << (int)numberOfPixelHits << " " << (int)numberOfPixelHoles << " " << (int)numberOfPixelOutliers); 
      }
      if ((int)numberOfBLHits!=checkBLY)  { 
        ANA_MSG_ERROR("B-layer hits are not consistent with cluster counting " << (int)numberOfBLHits << " aaa " << checkBLY<< " " << (int)numberOfPixelHits << " " << (int)numberOfPixelHoles << " " << (int)numberOfPixelOutliers); 
      }
    }

    m_trackOutliers    -> push_back(numberOfOutliersOnTrack);
    m_trackChiSqPerDof -> push_back(chiSqPerDoF);
    m_trackStdDevChi2OS-> push_back(stdDeviationOfChi2OS);
    m_nPixelHits       -> push_back(numberOfPixelHits);
    m_nPixelHoles      -> push_back(numberOfPixelHoles);
    m_nPixelLayers     -> push_back(numberOfPixelLayers);
    m_nPixelOutliers   -> push_back(numberOfPixelOutliers);
    m_nPixelGanged     -> push_back(numberOfGangedPixels);
    m_nPixelShared     -> push_back(numberOfPixelSharedHits);
    m_nPixelSplit      -> push_back(numberOfPixelSplitHits);
    m_nPixelDeadSensors-> push_back(nPixelDeadSensor);
    m_nIBLUsedHits     -> push_back(numberOfIBLHits);
    m_nBLUsedHits      -> push_back(numberOfBLHits);
    m_nSCTHits         -> push_back(numberOfSCTHits);
    m_nSCTHoles        -> push_back(numberOfSCTHoles);
    m_nSCTOutliers     -> push_back(numberOfSCTOutliers);
    m_nSCTDeadSensors  -> push_back(numberOfSCTDeadSensors);
    m_nTRTHits         -> push_back(numberOfTRTHits);
    m_nTRTOutliers     -> push_back(numberOfTRTOutliers);
    m_nTRTHoles        -> push_back(numberOfTRTHoles);
    m_nTRTHTHits       -> push_back(numberOfTRTHighThresholdHits);
    m_nIBLSplitHits    -> push_back(numberOfIBLSplitHits);
    m_nBLSplitHits     -> push_back(numberOfBLSplitHits);
    m_nIBLSharedHits   -> push_back(numberOfIBLSharedHits);
    m_nBLSharedHits    -> push_back(numberOfBLSharedHits);
    m_nIBLHits         -> push_back(checkIBL);
    m_nBLHits          -> push_back(checkBLY);
    m_nL1Hits          -> push_back(checkLY1);
    m_nL2Hits          -> push_back(checkLY2);
    m_nECHits          -> push_back(checkED1+checkED2+checkED3);
    m_nIBLExpectedHits -> push_back(numberOfIBLExpectedHits);
    m_nBLExpectedHits  -> push_back(numberOfBLExpectedHits);
    m_nSCTSharedHits   -> push_back(numberOfSCTSharedHits);

    m_TruncateddEdx    -> push_back((*recoTrk_itr)->auxdata<float>("pixeldEdx"));
    m_nTruncateddEdx   -> push_back((*recoTrk_itr)->numberOfUsedHitsdEdx());

    m_extrapolatedIBLX -> push_back((*recoTrk_itr)->auxdata<float>("TrkIBLX"));
    m_extrapolatedIBLY -> push_back((*recoTrk_itr)->auxdata<float>("TrkIBLY"));
    m_extrapolatedIBLZ -> push_back((*recoTrk_itr)->auxdata<float>("TrkIBLZ"));
    m_extrapolatedBLX -> push_back((*recoTrk_itr)->auxdata<float>("TrkBLX"));
    m_extrapolatedBLY -> push_back((*recoTrk_itr)->auxdata<float>("TrkBLY"));
    m_extrapolatedBLZ -> push_back((*recoTrk_itr)->auxdata<float>("TrkBLZ"));
    m_extrapolatedL1X -> push_back((*recoTrk_itr)->auxdata<float>("TrkL1X"));
    m_extrapolatedL1Y -> push_back((*recoTrk_itr)->auxdata<float>("TrkL1Y"));
    m_extrapolatedL1Z -> push_back((*recoTrk_itr)->auxdata<float>("TrkL1Z"));
    m_extrapolatedL2X -> push_back((*recoTrk_itr)->auxdata<float>("TrkL2X"));
    m_extrapolatedL2Y -> push_back((*recoTrk_itr)->auxdata<float>("TrkL2Y"));
    m_extrapolatedL2Z -> push_back((*recoTrk_itr)->auxdata<float>("TrkL2Z"));

    float truePt(-999.0),truePhi(-999.0),trueEta(-999.0),trueE(-999.0),trueMindR(-999.0);
    float trueD0(-999.0),trueZ0(-999.0),truePhi0(-999.0),trueTheta(-999.0),trueqOverP(-999.0),truthMatchProb(-1.0),genVtxR(0.0),genVtxZ(0.0);
    int truebarcode(0),truepdgid(0),parentFlav(1);
    if (isMC) {
      if ((*recoTrk_itr)->isAvailable<float>("truthMatchProbability")) { truthMatchProb=(*recoTrk_itr)->auxdataConst<float>("truthMatchProbability"); }
      typedef ElementLink< xAOD::TruthParticleContainer > Link_t;
      static const char* NAME = "truthParticleLink";
      if ((*recoTrk_itr)->isAvailable<Link_t>(NAME)) {
        const Link_t& link = (*recoTrk_itr)->auxdata<Link_t>(NAME);
        if (link.isValid()) {
          xAOD::TruthParticle *truthPtcs = (xAOD::TruthParticle*) *link;
          truePt  = truthPtcs->pt()/1000.0;
          truePhi = truthPtcs->phi();
          trueEta = truthPtcs->eta();
          trueE   = truthPtcs->e()/1000.0;
          if (truthPtcs->isAvailable<float>("d0"))     { trueD0=truthPtcs->auxdataConst<float>("d0"); }
          if (truthPtcs->isAvailable<float>("z0"))     { trueZ0=truthPtcs->auxdataConst<float>("z0"); }
          if (truthPtcs->isAvailable<float>("phi"))    { truePhi0=truthPtcs->auxdataConst<float>("phi"); }
          if (truthPtcs->isAvailable<float>("theta"))  { trueTheta=truthPtcs->auxdataConst<float>("theta"); }
          if (truthPtcs->isAvailable<float>("qOverP")) { trueqOverP=truthPtcs->auxdataConst<float>("qOverP"); }
          truebarcode = truthPtcs->barcode();
          truepdgid   = truthPtcs->pdgId();

          double mindR = 100000.0;
          for (xAOD::TruthParticleContainer::const_iterator tr_it=truthParticle->begin(); tr_it!=truthParticle->end(); tr_it++) {
            if ((*tr_it)==truthPtcs || !(*tr_it)->isCharged() ||  (*tr_it)->abseta()>2.75 || (*tr_it)->status()!=1) { continue; }
            double dR = deltaR((*tr_it),truthPtcs);
            if (dR<mindR) { mindR=dR; }
          }
          trueMindR = mindR;

          if (truthPtcs->hasProdVtx()) {
            if (truthPtcs->prodVtx()->isAvailable<float>("x") && truthPtcs->prodVtx()->isAvailable<float>("y") && truthPtcs->prodVtx()->isAvailable<float>("z")) {
              genVtxR = TMath::Sqrt(truthPtcs->prodVtx()->x()*truthPtcs->prodVtx()->x()+truthPtcs->prodVtx()->y()*truthPtcs->prodVtx()->y());
              genVtxZ = truthPtcs->prodVtx()->z();
            }
          }
          for (int ip=0; ip<(int)truthPtcs->nParents(); ip++) {
            if ((TMath::Abs(truthPtcs->parent(ip)->pdgId())>300 && TMath::Abs(truthPtcs->parent(ip)->pdgId())<400) || (TMath::Abs(truthPtcs->parent(ip)->pdgId())>3000 && TMath::Abs(truthPtcs->parent(ip)->pdgId())<4000)) { parentFlav=3; }
            if ((TMath::Abs(truthPtcs->parent(ip)->pdgId())>400 && TMath::Abs(truthPtcs->parent(ip)->pdgId())<500) || (TMath::Abs(truthPtcs->parent(ip)->pdgId())>4000 && TMath::Abs(truthPtcs->parent(ip)->pdgId())<5000)) { parentFlav=4; }
            if ((TMath::Abs(truthPtcs->parent(ip)->pdgId())>500 && TMath::Abs(truthPtcs->parent(ip)->pdgId())<600) || (TMath::Abs(truthPtcs->parent(ip)->pdgId())>5000 && TMath::Abs(truthPtcs->parent(ip)->pdgId())<6000)) { parentFlav=5; }
          }
        }
      }
    }
    m_truePt         -> push_back(truePt);
    m_truePhi        -> push_back(truePhi);
    m_trueEta        -> push_back(trueEta);
    m_trueE          -> push_back(trueE);
    m_trued0         -> push_back(trueD0);
    m_truez0         -> push_back(trueZ0);
    m_truephi        -> push_back(truePhi0);
    m_truetheta      -> push_back(trueTheta);
    m_trueqoverp     -> push_back(trueqOverP);
    m_truepdgid      -> push_back(truepdgid);
    m_truebarcode    -> push_back(truebarcode);
    m_truthmatchprob -> push_back(truthMatchProb);
    m_trueMindR      -> push_back(trueMindR);
    m_genVtxR        -> push_back(genVtxR);
    m_genVtxZ        -> push_back(genVtxZ);
    m_parentFlav     -> push_back(parentFlav);

    // Cluster iformation
    std::vector<int>   holeIndex;
    std::vector<int>   outlierIndex;
    std::vector<int>   clusterModulePhi;
    std::vector<int>   clusterModuleEta;
    std::vector<float> clusterCharge;
    std::vector<int>   clusterToT;
    std::vector<int>   clusterL1A;
    std::vector<int>   clusterSize;
    std::vector<int>   clusterSizePhi;
    std::vector<int>   clusterSizeZ;
    std::vector<int>   moduleBSerr;
    std::vector<int>   moduleDCSstate;
    std::vector<float> moduleBiasVoltage;
    std::vector<float> moduleTemperature;
    std::vector<float> moduleLorentzShift;
    std::vector<float> clusterGlobalX;
    std::vector<float> clusterGlobalY;
    std::vector<float> clusterGlobalZ;
    std::vector<float> clusterLocalX;
    std::vector<float> clusterLocalY;
    std::vector<int>   clusterIsolation10x2;
    std::vector<float> trackLocalX;
    std::vector<float> trackLocalY;
    std::vector<float> unbiasedResidualX;
    std::vector<float> unbiasedResidualY;
    std::vector<float> unbiasedPullX;
    std::vector<float> unbiasedPullY;
    std::vector<float> trackLocalPhi;
    std::vector<float> trackLocalTheta;
    std::vector<int>   numTotalClustersPerModule;
    std::vector<int>   numTotalPixelsPerModule;

    if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterLayer")) {
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("holeIndex"))                 { holeIndex                 = (*recoTrk_itr)->auxdata<std::vector<int>>("holeIndex"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("outlierIndex"))              { outlierIndex              = (*recoTrk_itr)->auxdata<std::vector<int>>("outlierIndex"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterModulePhi"))          { clusterModulePhi          = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterModulePhi"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterModuleEta"))          { clusterModuleEta          = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterModuleEta"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ClusterCharge"))           { clusterCharge             = (*recoTrk_itr)->auxdata<std::vector<float>>("ClusterCharge"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterToT"))                { clusterToT                = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterToT"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterL1A"))                { clusterL1A                = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterL1A"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterSize"))               { clusterSize               = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterSize"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterSizePhi"))            { clusterSizePhi            = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterSizePhi"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterSizeZ"))              { clusterSizeZ              = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterSizeZ"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ModuleBSError"))             { moduleBSerr               = (*recoTrk_itr)->auxdata<std::vector<int>>("ModuleBSError"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ModuleDCSState"))            {  moduleDCSstate            = (*recoTrk_itr)->auxdata<std::vector<int>>("ModuleDCSState"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ModuleBiasVoltage"))       { moduleBiasVoltage         = (*recoTrk_itr)->auxdata<std::vector<float>>("ModuleBiasVoltage"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ModuleTemperature"))       { moduleTemperature         = (*recoTrk_itr)->auxdata<std::vector<float>>("ModuleTemperature"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ModuleLorentzShift"))      { moduleLorentzShift        = (*recoTrk_itr)->auxdata<std::vector<float>>("ModuleLorentzShift"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ClusterGlobalX"))          { clusterGlobalX            = (*recoTrk_itr)->auxdata<std::vector<float>>("ClusterGlobalX"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ClusterGlobalY"))          { clusterGlobalY            = (*recoTrk_itr)->auxdata<std::vector<float>>("ClusterGlobalY"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ClusterGlobalZ"))          { clusterGlobalZ            = (*recoTrk_itr)->auxdata<std::vector<float>>("ClusterGlobalZ"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ClusterLocalX"))           { clusterLocalX             = (*recoTrk_itr)->auxdata<std::vector<float>>("ClusterLocalX"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("ClusterLocalY"))           { clusterLocalY             = (*recoTrk_itr)->auxdata<std::vector<float>>("ClusterLocalY"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("ClusterIsolation10x2"))      { clusterIsolation10x2      = (*recoTrk_itr)->auxdata<std::vector<int>>("ClusterIsolation10x2"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("TrackLocalX"))             { trackLocalX               = (*recoTrk_itr)->auxdata<std::vector<float>>("TrackLocalX"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("TrackLocalY"))             { trackLocalY               = (*recoTrk_itr)->auxdata<std::vector<float>>("TrackLocalY"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("UnbiasedResidualX"))       { unbiasedResidualX         = (*recoTrk_itr)->auxdata<std::vector<float>>("UnbiasedResidualX"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("UnbiasedResidualY"))       { unbiasedResidualY         = (*recoTrk_itr)->auxdata<std::vector<float>>("UnbiasedResidualY"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("UnbiasedPullX"))           { unbiasedPullX             = (*recoTrk_itr)->auxdata<std::vector<float>>("UnbiasedPullX"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("UnbiasedPullY"))           { unbiasedPullY             = (*recoTrk_itr)->auxdata<std::vector<float>>("UnbiasedPullY"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("TrackLocalPhi"))           { trackLocalPhi             = (*recoTrk_itr)->auxdata<std::vector<float>>("TrackLocalPhi"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<float>>("TrackLocalTheta"))         { trackLocalTheta           = (*recoTrk_itr)->auxdata<std::vector<float>>("TrackLocalTheta"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("NumTotalClustersPerModule")) { numTotalClustersPerModule = (*recoTrk_itr)->auxdata<std::vector<int>>("NumTotalClustersPerModule"); }
      if ((*recoTrk_itr)->isAvailable<std::vector<int>>("NumTotalPixelsPerModule"))   { numTotalPixelsPerModule   = (*recoTrk_itr)->auxdata<std::vector<int>>("NumTotalPixelsPerModule"); }
    }

    // Special... fill hole information
    if (!m_flagTRKSTREAM) {
      holeIndex.clear();
      if (checkIBL==0) {
        float posZ = (*recoTrk_itr)->auxdata<float>("TrkIBLZ");
        if (TMath::Abs(posZ)<332.0) { holeIndex.push_back(0); }
      }
      if (checkBLY==0) {
        float posZ = (*recoTrk_itr)->auxdata<float>("TrkBLZ");
        if (TMath::Abs(posZ)<400.5) { holeIndex.push_back(1); }
      }
      if (checkLY1==0) {
        float posZ = (*recoTrk_itr)->auxdata<float>("TrkL1Z");
        if (TMath::Abs(posZ)<400.5) { holeIndex.push_back(2); }
      }
      if (checkLY2==0) {
        float posZ = (*recoTrk_itr)->auxdata<float>("TrkL2Z");
        if (TMath::Abs(posZ)<400.5) { holeIndex.push_back(3); }
      }

      unbiasedPullX.clear();
      unbiasedPullY.clear();
      for (int i=0; i<(int)clusterLayer.size(); i++) {
        unbiasedPullX.push_back(0.0);
        unbiasedPullY.push_back(0.0);
      }
    }

    m_hitIsEndCap       -> push_back(clusterBEC);
    m_hitIsHole         -> push_back(holeIndex);
    m_hitIsOutlier      -> push_back(outlierIndex);
    m_hitLayer          -> push_back(clusterLayer);
    m_hitEtaModule      -> push_back(clusterModuleEta);
    m_hitPhiModule      -> push_back(clusterModulePhi);
    m_hitCharge         -> push_back(clusterCharge);
    m_hitToT            -> push_back(clusterToT);
    m_hitLVL1A          -> push_back(clusterL1A);
    m_hitNPixel         -> push_back(clusterSize);
    m_hitNPixelX        -> push_back(clusterSizePhi);
    m_hitNPixelY        -> push_back(clusterSizeZ);
    m_hitBSerr          -> push_back(moduleBSerr);
    m_hitDCSstate       -> push_back(moduleDCSstate);
    m_hitVBias          -> push_back(moduleBiasVoltage);
    m_hitTemp           -> push_back(moduleTemperature);
    m_hitLorentzShift   -> push_back(moduleLorentzShift);
    m_hitIsSplit        -> push_back(clusterIsSplit);
    m_hitIsEdge         -> push_back(clusterIsEdge);
    m_hitIsOverflow     -> push_back(clusterIsOverflow);
    m_hitIsolation10x2  -> push_back(clusterIsolation10x2);
    m_hitIsolation20x4  -> push_back(clusterIsolation20x4);
    m_hitGlobalX        -> push_back(clusterGlobalX);
    m_hitGlobalY        -> push_back(clusterGlobalY);
    m_hitGlobalZ        -> push_back(clusterGlobalZ);
    m_hitLocalX         -> push_back(clusterLocalX);
    m_hitLocalY         -> push_back(clusterLocalY);
    m_trkLocalX         -> push_back(trackLocalX);
    m_trkLocalY         -> push_back(trackLocalY);
    m_unbiasedResidualX -> push_back(unbiasedResidualX);
    m_unbiasedResidualY -> push_back(unbiasedResidualY);
    m_unbiasedPullX     -> push_back(unbiasedPullX);
    m_unbiasedPullY     -> push_back(unbiasedPullY);
    m_trkPhiOnSurface   -> push_back(trackLocalPhi);
    m_trkThetaOnSurface -> push_back(trackLocalTheta);
    m_numTotalClustersPerModule -> push_back(numTotalClustersPerModule);
    m_numTotalPixelsPerModule   -> push_back(numTotalPixelsPerModule);

    // RDO information
    std::vector<std::vector<int>>   RdoToT;
    std::vector<std::vector<float>> RdoCharge;
    std::vector<std::vector<int>>   RdoPhi;
    std::vector<std::vector<int>>   RdoEta;
    if ((*recoTrk_itr)->pt()>2000.0) {
      if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("RdoToT")) {
        if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("RdoToT")) { RdoToT = (*recoTrk_itr)->auxdata<std::vector<std::vector<int>>>("RdoToT"); }
        if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<float>>>("RdoCharge")) { RdoCharge = (*recoTrk_itr)->auxdata<std::vector<std::vector<float>>>("RdoCharge"); }
        if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("RdoPhi")) { RdoPhi = (*recoTrk_itr)->auxdata<std::vector<std::vector<int>>>("RdoPhi"); }
        if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("RdoEta")) { RdoEta = (*recoTrk_itr)->auxdata<std::vector<std::vector<int>>>("RdoEta"); }
      }
    }
    m_RdoToT    -> push_back(RdoToT);
    m_RdoCharge -> push_back(RdoCharge);
    m_RdoPhi    -> push_back(RdoPhi);
    m_RdoEta    -> push_back(RdoEta);

    std::vector<std::vector<int>>   clusterTruthPdgId;
    std::vector<std::vector<int>>   siHitPdgId;
    std::vector<std::vector<int>>   siHitBarcode;
    std::vector<std::vector<float>> siHitStartPosX;
    std::vector<std::vector<float>> siHitStartPosY;
    std::vector<std::vector<float>> siHitEndPosX;
    std::vector<std::vector<float>> siHitEndPosY;
    std::vector<std::vector<float>> siHitEnergyDeposit;
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("ClusterTruthPdgId"))    { clusterTruthPdgId   = (*recoTrk_itr)->auxdata<std::vector<std::vector<int>>>("ClusterTruthPdgId"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("SiHitPdgId"))           { siHitPdgId          = (*recoTrk_itr)->auxdata<std::vector<std::vector<int>>>("SiHitPdgId"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<int>>>("SiHitBarcode"))         { siHitBarcode        = (*recoTrk_itr)->auxdata<std::vector<std::vector<int>>>("SiHitBarcode"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<float>>>("SiHitStartPosX"))     { siHitStartPosX      = (*recoTrk_itr)->auxdata<std::vector<std::vector<float>>>("SiHitStartPosX"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<float>>>("SiHitStartPosY"))     { siHitStartPosY      = (*recoTrk_itr)->auxdata<std::vector<std::vector<float>>>("SiHitStartPosY"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<float>>>("SiHitEndPosX"))       { siHitEndPosX        = (*recoTrk_itr)->auxdata<std::vector<std::vector<float>>>("SiHitEndPosX"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<float>>>("SiHitEndPosY"))       { siHitEndPosY        = (*recoTrk_itr)->auxdata<std::vector<std::vector<float>>>("SiHitEndPosY"); }
    if ((*recoTrk_itr)->isAvailable<std::vector<std::vector<float>>>("SiHitEnergyDeposit")) { siHitEnergyDeposit  = (*recoTrk_itr)->auxdata<std::vector<std::vector<float>>>("SiHitEnergyDeposit"); }
    m_hitTruthPdgId      -> push_back(clusterTruthPdgId);
    m_siHitPdgId         -> push_back(siHitPdgId);
    m_siHitBarcode       -> push_back(siHitBarcode);
    m_siHitStartPosX     -> push_back(siHitStartPosX);
    m_siHitStartPosY     -> push_back(siHitStartPosY);
    m_siHitEndPosX       -> push_back(siHitEndPosX);
    m_siHitEndPosY       -> push_back(siHitEndPosY);
    m_siHitEnergyDeposit -> push_back(siHitEnergyDeposit);

  }

  m_truthEta->clear();
  m_truthPhi->clear();
  m_truthPt->clear();
  m_truthE->clear();
  m_truthCharge ->clear();
  m_truthPdgId  ->clear();
  m_truthBarcode->clear();
  m_truthStatus ->clear();
  if (isMC) {   
    for (xAOD::TruthParticleContainer::const_iterator tr_it=truthParticle->begin(); tr_it!=truthParticle->end(); tr_it++) {
      m_truthEta->push_back((*tr_it)->eta());
      m_truthPhi->push_back((*tr_it)->phi());
      m_truthPt ->push_back((*tr_it)->pt()/1000.0);
      m_truthE  ->push_back((*tr_it)->e()/1000.0);
      m_truthCharge ->push_back((*tr_it)->charge());
      m_truthPdgId  ->push_back((*tr_it)->pdgId());
      m_truthBarcode->push_back((*tr_it)->barcode());
      m_truthStatus ->push_back((*tr_it)->status());
    }
  }

  m_muonEta->clear();
  m_muonPhi->clear();
  m_muonPt->clear();
  m_muonE->clear();
  for (int i=0; i<numMuon; i++) {
//    m_muonEta->push_back((*muZitr[i])->eta());
//    m_muonPhi->push_back((*muZitr[i])->phi());
//    m_muonPt ->push_back((*muZitr[i])->pt()/1000.0);
//    m_muonE  ->push_back((*muZitr[i])->e()/1000.0);
    m_muonEta->push_back(zMuon[i]->eta());
    m_muonPhi->push_back(zMuon[i]->phi());
    m_muonPt ->push_back(zMuon[i]->pt()/1000.0);
    m_muonE  ->push_back(zMuon[i]->e()/1000.0);
  }

  m_jetEta->clear();
  m_jetPhi->clear();
  m_jetPt->clear();
  m_jetE->clear();
  m_jetPassJVT->clear();
  for (int i=0; i<numJet; i++) {
    m_jetEta->push_back((*jetItr[i])->eta());
    m_jetPhi->push_back((*jetItr[i])->phi());
    m_jetPt ->push_back((*jetItr[i])->pt()/1000.0);
    m_jetE  ->push_back((*jetItr[i])->e()/1000.0);

    bool passJvt = true;
    if ((*jetItr[i])->pt()/1000.0<60.0 && TMath::Abs((*jetItr[i])->eta())<2.4) { passJvt = m_jetsf->passesJvtCut(*(*jetItr[i])); }
    if ((*jetItr[i])->pt()/1000.0<50.0 && TMath::Abs((*jetItr[i])->eta())>2.5) { passJvt = m_fjetsf->passesJvtCut(**jetItr[i]); }
    m_jetPassJVT -> push_back(passJvt);
  }

  m_tauEta->clear();
  m_tauPhi->clear();
  m_tauPt->clear();
  m_tauM->clear();
  m_tauCharge ->clear();
  m_tau_nTracksCharged->clear();
  m_tau_nTracksIsolation->clear();
  m_tau_nAllTracks->clear();
  m_tau_trackFilterProngs->clear();
  m_tau_trackFilterQuality->clear();
  m_tau_nClusters->clear();
  m_tau_nPi0s->clear();
  m_tau_numCells->clear();
  m_tau_isTauFlags->clear();
  m_tau_BDTJetScore->clear();
  m_tau_BDTEleScore->clear();
  m_tau_EleMatchLikelihoodScore->clear();
  m_tau_BDTJetScoreSigTrans->clear();
  m_tau_RNNJetScore->clear();
  m_tau_RNNJetScoreSigTrans->clear();
  m_tau_ipZ0SinThetaSigLeadTrk->clear();
  m_tau_etOverPtLeadTrk->clear();
  m_tau_leadTrkPt->clear();
  m_tau_ipSigLeadTrk->clear();
  m_tau_massTrkSys->clear();
  m_tau_trkWidth2->clear();
  m_tau_trFlightPathSig->clear();
  m_tau_EMRadius->clear();
  m_tau_hadRadius->clear();
  m_tau_etEMAtEMScale->clear();
  m_tau_etHadAtEMScale->clear();
  m_tau_isolFrac->clear();
  m_tau_centFrac->clear();
  m_tau_stripWidth2->clear();
  m_tau_nStrip->clear();
  m_tau_trkAvgDist->clear();
  m_tau_dRmax->clear();
  for (xAOD::TauJetContainer::const_iterator it=tau->begin(); it!=tau->end(); it++) {
    m_tauEta->push_back((*it)->eta());
    m_tauPhi->push_back((*it)->phi());
    m_tauPt ->push_back((*it)->pt()/1000.0);
    m_tauM  ->push_back((*it)->m()/1000.0);
    m_tauCharge ->push_back((*it)->charge());
    m_tau_nTracksCharged          ->push_back((*it)->auxdata<int>("nChargedTracks"));
    m_tau_nTracksIsolation        ->push_back((*it)->auxdata<int>("nIsolatedTracks"));
    m_tau_nAllTracks              ->push_back((*it)->nAllTracks());
    m_tau_trackFilterProngs       ->push_back((*it)->auxdata<int>("trackFilterProngs"));
    m_tau_trackFilterQuality      ->push_back((*it)->auxdata<int>("trackFilterQuality"));
    m_tau_nClusters               ->push_back((*it)->nClusters());
    m_tau_nPi0s                   ->push_back((*it)->nPi0s());
    m_tau_numCells                ->push_back((*it)->auxdata<int>("numCells"));
    m_tau_isTauFlags              ->push_back((*it)->auxdata<uint32_t>("isTauFlags"));
    m_tau_BDTJetScore             ->push_back((*it)->auxdata<float>("BDTJetScore"));
    m_tau_BDTEleScore             ->push_back((*it)->auxdata<float>("BDTEleScore"));
    m_tau_EleMatchLikelihoodScore ->push_back((*it)->auxdata<float>("EleMatchLikelihoodScore"));
    m_tau_BDTJetScoreSigTrans     ->push_back((*it)->auxdata<float>("BDTJetScoreSigTrans"));
    m_tau_RNNJetScore             ->push_back((*it)->auxdata<float>("RNNJetScore"));
    m_tau_RNNJetScoreSigTrans     ->push_back((*it)->auxdata<float>("RNNJetScoreSigTrans"));
    m_tau_ipZ0SinThetaSigLeadTrk  ->push_back((*it)->auxdata<float>("ipZ0SinThetaSigLeadTrk"));
    m_tau_etOverPtLeadTrk         ->push_back((*it)->auxdata<float>("etOverPtLeadTrk"));
    m_tau_leadTrkPt               ->push_back((*it)->auxdata<float>("leadTrkPt"));
    m_tau_ipSigLeadTrk            ->push_back((*it)->auxdata<float>("ipSigLeadTrk"));
    m_tau_massTrkSys              ->push_back((*it)->auxdata<float>("massTrkSys"));
    m_tau_trkWidth2               ->push_back((*it)->auxdata<float>("trkWidth2"));
    m_tau_trFlightPathSig         ->push_back((*it)->auxdata<float>("trFlightPathSig"));
    m_tau_EMRadius                ->push_back((*it)->auxdata<float>("EMRadius"));
    m_tau_hadRadius               ->push_back((*it)->auxdata<float>("hadRadius"));
    m_tau_etEMAtEMScale           ->push_back((*it)->auxdata<float>("etEMAtEMScale"));
    m_tau_etHadAtEMScale          ->push_back((*it)->auxdata<float>("etHadAtEMScale"));
    m_tau_isolFrac                ->push_back((*it)->auxdata<float>("isolFrac"));
    m_tau_centFrac                ->push_back((*it)->auxdata<float>("centFrac"));
    m_tau_stripWidth2             ->push_back((*it)->auxdata<float>("stripWidth2"));
    m_tau_nStrip                  ->push_back((*it)->auxdata<int>("nStrip"));
    m_tau_trkAvgDist              ->push_back((*it)->auxdata<float>("trkAvgDist"));
    m_tau_dRmax                   ->push_back((*it)->auxdata<float>("dRmax"));
  }

  m_metCaloPx    = (*METCalo->begin())->auxdata<double>("mpx");
  m_metCaloPy    = (*METCalo->begin())->auxdata<double>("mpy");
  m_metCaloET    = (*METCalo->begin())->auxdata<double>("met");
  m_metCaloSumET = (*METCalo->begin())->auxdata<double>("sumet");

  m_metTrackPx    = (*METTrack->begin())->auxdata<double>("mpx");
  m_metTrackPy    = (*METTrack->begin())->auxdata<double>("mpy");
  m_metTrackET    = (*METTrack->begin())->auxdata<double>("met");
  m_metTrackSumET = (*METTrack->begin())->auxdata<double>("sumet");

  m_metLocHadPx    = (*METLocHadTopo->begin())->auxdata<double>("mpx");
  m_metLocHadPy    = (*METLocHadTopo->begin())->auxdata<double>("mpy");
  m_metLocHadET    = (*METLocHadTopo->begin())->auxdata<double>("met");
  m_metLocHadSumET = (*METLocHadTopo->begin())->auxdata<double>("sumet");

  m_metCoreLCTopoPx    = (*METCore_AntiKt4LCTopo->begin())->auxdata<double>("mpx");
  m_metCoreLCTopoPy    = (*METCore_AntiKt4LCTopo->begin())->auxdata<double>("mpy");
  m_metCoreLCTopoET    = (*METCore_AntiKt4LCTopo->begin())->auxdata<double>("met");
  m_metCoreLCTopoSumET = (*METCore_AntiKt4LCTopo->begin())->auxdata<double>("sumet");

  m_metRefLCTopoPx    = (*METRef_AntiKt4LCTopo->begin())->auxdata<double>("mpx");
  m_metRefLCTopoPy    = (*METRef_AntiKt4LCTopo->begin())->auxdata<double>("mpy");
  m_metRefLCTopoET    = (*METRef_AntiKt4LCTopo->begin())->auxdata<double>("met");
  m_metRefLCTopoSumET = (*METRef_AntiKt4LCTopo->begin())->auxdata<double>("sumet");

  if (isMC) {
    m_metTruthPx    = (*METTruth->begin())->auxdata<double>("mpx");
    m_metTruthPy    = (*METTruth->begin())->auxdata<double>("mpy");
    m_metTruthET    = (*METTruth->begin())->auxdata<double>("met");
    m_metTruthSumET = (*METTruth->begin())->auxdata<double>("sumet");
  }

  // Fill the event into the tree:
  tree("eventtree")->Fill();


  delete recoTracksShallowCopyPair.first;
  delete recoTracksShallowCopyPair.second;
//  delete muonPair.first;
//  delete muonPair.second;

  delete tauPair.first;
  delete tauPair.second;
  delete METCaloPair.first;
  delete METTrackPair.first;
  delete METLocHadTopoPair.first;
  delete METCore_AntiKt4LCTopoPair.first;
  delete METRef_AntiKt4LCTopoPair.first;
  delete METTruthPair.first;
  delete METCaloPair.second;
  delete METTrackPair.second;
  delete METLocHadTopoPair.second;
  delete METCore_AntiKt4LCTopoPair.second;
  delete METRef_AntiKt4LCTopoPair.second;
  delete METTruthPair.second;


  return StatusCode::SUCCESS;
}

StatusCode ZmumuAnalysis::finalize() {
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.

  return StatusCode::SUCCESS;
}

//=============
bool ZmumuAnalysis::checkQuality(const xAOD::TrackParticle* trk) {
  // start with loose track quality cuts. (see https://indico.cern.ch/event/368819/contribution/4/material/slides/0.pdf )
  uint8_t getInt(0);
  int nSiHits = xAOD::TrackHelper::numberOfSiHits(trk);
  trk->summaryValue(getInt,xAOD::numberOfPixelHits); 
  int nPixHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfSCTHits); 
  int nSCTHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfPixelSharedHits); 
  int nPixSharedHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfSCTSharedHits); 
  int nSCTSharedHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfPixelHoles); 
  int nPixHoles = getInt;
  trk->summaryValue(getInt,xAOD::numberOfSCTHoles); 
  int nSCTHoles = getInt;
  trk->summaryValue(getInt,xAOD::numberOfInnermostPixelLayerHits);
  int nIBLHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfNextToInnermostPixelLayerHits);
  int nBLYHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfPixelSplitHits);
  int nPixSplitHits = getInt;

//  if (nSiHits>=7 && nPixSharedHits+nSCTSharedHits/2<=1 && nPixHoles+nSCTHoles<=2 && nPixHoles<=1) {
//  if (nSiHits>=9 && nPixHits>3 && nPixSplitClus==0 && nIsEdge==0 && nIsOverflow==0 && nIsolation20x4==0) {
//  if (nSiHits>=9) {
  if ((fabs(trk->eta())<=1.65 && nPixHits>0 && nSCTHits>=6) || (fabs(trk->eta())>1.65 && nPixHits>0 && nSCTHits>=8)) {
//  if (trk->pt()/1000.0>1.0 && nSiHits>=8 && nIBLHits==0) {
//  if (nSiHits>=9 && nIBLHits+nBLYHits>0 && nPixHoles==0) {
    return true;
  }
  return false;
}

//==========================================================================================================================
// Store PIXELVALID format in IDTRKVALID
//==========================================================================================================================
StatusCode ZmumuAnalysis::PixelNtupleMaker(bool isMC) {

  const xAOD::TrackParticleContainer* idTracks = 0;
  ANA_CHECK(evtStore()->retrieve(idTracks,"InDetTrackParticles"));
  std::pair<xAOD::TrackParticleContainer*,xAOD::ShallowAuxContainer*> recoTracksShallowCopyPair = xAOD::shallowCopyContainer(*idTracks);
  xAOD::TrackParticleContainer* tracks = recoTracksShallowCopyPair.first;

  const xAOD::TruthParticleContainer* truthPtc = 0;
  if (isMC) { ANA_CHECK(evtStore()->retrieve(truthPtc,"TruthParticles")); }

  const xAOD::TrackMeasurementValidationContainer* pixClustersOrig = 0;
  ANA_CHECK(evtStore()->retrieve(pixClustersOrig,"PixelClusters"));
  std::pair< xAOD::TrackMeasurementValidationContainer*, xAOD::ShallowAuxContainer* > pixClustersPair = xAOD::shallowCopyContainer( *pixClustersOrig );
  xAOD::TrackMeasurementValidationContainer* pixClusters =  pixClustersPair.first;

  xAOD::TrackParticleContainer* PixelMonitoringTrack = new xAOD::TrackParticleContainer();
  xAOD::TrackParticleAuxContainer* PixelMonitoringTrackAux = new xAOD::TrackParticleAuxContainer();
  PixelMonitoringTrack->setStore(PixelMonitoringTrackAux);
  ATH_CHECK(evtStore()->record(PixelMonitoringTrack,"PixelMonitoringTrack"));
  ATH_CHECK(evtStore()->record(PixelMonitoringTrackAux,"PixelMonitoringTrackAux."));

  std::vector<float> tmpCov(15,0.);
  typedef std::vector<ElementLink< xAOD::TrackStateValidationContainer > > MeasurementsOnTrack;
  typedef std::vector<ElementLink< xAOD::TrackStateValidationContainer > >::const_iterator MeasurementsOnTrackIter;
  static SG::AuxElement::ConstAccessor<MeasurementsOnTrack>  acc_MeasurementsOnTrack("msosLink");
  for (xAOD::TrackParticleContainer::const_iterator trk=tracks->begin(); trk!=tracks->end(); trk++) {

    bool passTrack = true;
    if ((*trk)->pt()<1000.0) {
      uint8_t getInt = 0;
      (*trk)->summaryValue(getInt,xAOD::numberOfPixelHits); int nPixHits = getInt;
      (*trk)->summaryValue(getInt,xAOD::numberOfSCTHits);   int nSCTHits = getInt;
      if (nPixHits<4) { passTrack=false; }
      if (nSCTHits<1) { passTrack=false; }
    }

    if (passTrack) {
      xAOD::TrackParticle* tp = new xAOD::TrackParticle();
      tp->makePrivateStore(**trk);
      tp->setDefiningParametersCovMatrixVec(tmpCov);

      std::vector<int> holeIndex;
      std::vector<int> outlierIndex;
      std::vector<int> clusterLayer;
      std::vector<int> clusterBEC;
      std::vector<int> clusterModulePhi;
      std::vector<int> clusterModuleEta;
      std::vector<float> clusterCharge;
      std::vector<int> clusterToT;
      std::vector<int> clusterL1A;
      std::vector<int> clusterIsSplit;
      std::vector<int> clusterSize;
      std::vector<int> clusterSizePhi;
      std::vector<int> clusterSizeZ;
      std::vector<bool> isEdge;
      std::vector<bool> isOverflow;
      std::vector<float> trackPhi;
      std::vector<float> trackTheta;
      std::vector<float> trackX;
      std::vector<float> trackY;
      std::vector<float> localX;
      std::vector<float> localY;
      std::vector<float> globalX;
      std::vector<float> globalY;
      std::vector<float> globalZ;
      std::vector<float> unbiasedResidualX;
      std::vector<float> unbiasedResidualY;
      std::vector<float> unbiasedPullX;
      std::vector<float> unbiasedPullY;
      std::vector<int> clusterIsolation10x2;
      std::vector<int> clusterIsolation20x4;
      std::vector<int> numTotalClustersPerModule;
      std::vector<int> numTotalPixelsPerModule;
      std::vector<int>   moduleBSerr;
      std::vector<int>   moduleDCSstate;
      std::vector<float> moduleBiasVoltage;
      std::vector<float> moduleTemperature;
      std::vector<float> moduleLorentzShift;

      std::vector<std::vector<int>> rdoToT;
      std::vector<std::vector<float>> rdoCharge;
      std::vector<std::vector<int>> rdoPhi;
      std::vector<std::vector<int>> rdoEta;

      std::vector<std::vector<int>> clusterTruthPdgId;
      std::vector<std::vector<int>> siHitPdgId;
      std::vector<std::vector<int>> siHitBarcode;
      std::vector<std::vector<float>> siHitStartPosX;
      std::vector<std::vector<float>> siHitStartPosY;
      std::vector<std::vector<float>> siHitEndPosX;
      std::vector<std::vector<float>> siHitEndPosY;
      std::vector<std::vector<float>> siHitEnergyDeposit;

      const MeasurementsOnTrack& measurementsOnTrack = acc_MeasurementsOnTrack(*(*trk));
      for (MeasurementsOnTrackIter msos_iter=measurementsOnTrack.begin(); msos_iter!=measurementsOnTrack.end(); ++msos_iter) {  
        if (!(*msos_iter).isValid()) { continue; }
        const xAOD::TrackStateValidation* msos = *(*msos_iter); 

        if (msos->detType()==1) { // its a pixel 
          if (msos->type()==6) { 
            holeIndex.push_back(msos->detElementId());
          }
          if (msos->type()==5) { 
            outlierIndex.push_back(msos->detElementId());
          }

          if (msos->trackMeasurementValidationLink().isValid() && *(msos->trackMeasurementValidationLink())) {
            const xAOD::TrackMeasurementValidation* msosClus =  *(msos->trackMeasurementValidationLink());        

            for (xAOD::TrackMeasurementValidationContainer::iterator clus_itr=(pixClusters)->begin(); clus_itr!=(pixClusters)->end(); ++clus_itr) {
              if ((*clus_itr)->identifier()!=(msosClus)->identifier()) { continue; }
              if ((*clus_itr)->auxdata<float>("charge")!=(msosClus)->auxdata<float>("charge")) { continue; }

              clusterLayer.push_back((*clus_itr)->auxdata<int>("layer"));
              clusterBEC.push_back((*clus_itr)->auxdata<int>("bec"));
              clusterModulePhi.push_back((*clus_itr)->auxdata<int>("phi_module"));
              clusterModuleEta.push_back((*clus_itr)->auxdata<int>("eta_module"));
              clusterCharge.push_back((*clus_itr)->auxdata<float>("charge"));
              clusterToT.push_back((*clus_itr)->auxdata<int>("ToT"));
              clusterL1A.push_back((*clus_itr)->auxdata<int>("LVL1A"));
              clusterIsSplit.push_back((*clus_itr)->auxdata<int>("isSplit"));
              clusterSize.push_back((*clus_itr)->auxdata<int>("nRDO"));
              clusterSizePhi.push_back((*clus_itr)->auxdata<int>("sizePhi"));
              clusterSizeZ.push_back((*clus_itr)->auxdata<int>("sizeZ"));
              trackPhi.push_back(msos->localPhi());
              trackTheta.push_back(msos->localTheta());
              trackX.push_back(msos->localX());
              trackY.push_back(msos->localY());
              localX.push_back((*clus_itr)->localX());
              localY.push_back((*clus_itr)->localY());
              globalX.push_back((*clus_itr)->globalX());
              globalY.push_back((*clus_itr)->globalY());
              globalZ.push_back((*clus_itr)->globalZ());
              unbiasedResidualX.push_back(msos->unbiasedResidualX());
              unbiasedResidualY.push_back(msos->unbiasedResidualY());
              unbiasedPullX.push_back(msos->auxdata<float>("unbiasedPullX"));
              unbiasedPullY.push_back(msos->auxdata<float>("unbiasedPullY"));

              moduleBSerr.push_back((*clus_itr)->auxdata<int>("isBSError"));
//              moduleDCSstate.push_back((*clus_itr)->auxdata<int>("DCSState"));

              moduleBiasVoltage.push_back((*clus_itr)->auxdata<float>("BiasVoltage"));
              moduleTemperature.push_back((*clus_itr)->auxdata<float>("Temperature"));
              moduleLorentzShift.push_back((*clus_itr)->auxdata<float>("LorentzShift"));

              // cluster isolation   IBL:50x250um, PIXEL:50x400um
              //    - isolation region 10x2 = 500x500um for IBL,  500x800um for PIXEL
              int numNeighborCluster10x2 = 0;
              int numNeighborCluster20x4 = 0;
              int nTotalClustersPerModule = 0;
              int nTotalPixelsPerModule = 0;
              for (xAOD::TrackMeasurementValidationContainer::iterator clus_neighbor=(pixClusters)->begin(); clus_neighbor!=(pixClusters)->end(); ++clus_neighbor) {
                if ((*clus_neighbor)->auxdata<int>("layer")==(*clus_itr)->auxdata<int>("layer")
                    && (*clus_neighbor)->auxdata<int>("bec")==(*clus_itr)->auxdata<int>("bec")
                    && (*clus_neighbor)->auxdata<int>("phi_module")==(*clus_itr)->auxdata<int>("phi_module")
                    && (*clus_neighbor)->auxdata<int>("eta_module")==(*clus_itr)->auxdata<int>("eta_module")) {
                  float deltaX = std::abs((*clus_neighbor)->localX()-(*clus_itr)->localX());
                  float deltaY = std::abs((*clus_neighbor)->localY()-(*clus_itr)->localY());
                  nTotalClustersPerModule++;
                  nTotalPixelsPerModule += (*clus_neighbor)->auxdata<int>("nRDO");
                  if (deltaX>0.0 && deltaY>0.0) {
                    if ((*clus_itr)->auxdata<int>("layer")==0 && (*clus_itr)->auxdata<int>("bec")==0) {  // IBL
                      if (deltaX<0.500 && deltaY<0.500) { numNeighborCluster10x2++; }
                      if (deltaX<1.000 && deltaY<1.000) { numNeighborCluster20x4++; }
                    }
                    else {
                      if (deltaX<0.500 && deltaY<0.800) { numNeighborCluster10x2++; }
                      if (deltaX<1.000 && deltaY<1.600) { numNeighborCluster20x4++; }
                    }
                  }
                }
              }
              clusterIsolation10x2.push_back(numNeighborCluster10x2);
              clusterIsolation20x4.push_back(numNeighborCluster20x4);
              numTotalClustersPerModule.push_back(nTotalClustersPerModule);
              numTotalPixelsPerModule.push_back(nTotalPixelsPerModule);

              // is edge pixel?
              // contain overlflow hit?
              bool checkEdge = false;
              bool checkOverflow = false;
              if ((*clus_itr)->isAvailable<std::vector<int>>("rdo_phi_pixel_index")) {
                for (int i=0; i<(int)(*clus_itr)->auxdata<std::vector<int>>("rdo_phi_pixel_index").size(); i++) {

                  int phi = (*clus_itr)->auxdata<std::vector<int>>("rdo_phi_pixel_index")[i];
                  if (phi<5)   { checkEdge=true; }
                  if (phi>320) { checkEdge=true; }

                  int eta = (*clus_itr)->auxdata<std::vector<int>>("rdo_eta_pixel_index")[i];
                  if ((*clus_itr)->auxdata<int>("layer")==0 && (*clus_itr)->auxdata<int>("bec")==0) {  // IBL
                    if ((*clus_itr)->auxdata<int>("eta_module")>-7 && (*clus_itr)->auxdata<int>("eta_module")<6) { // IBL Planar
                      if (eta<5)   { checkEdge=true; }
                      if (eta>154) { checkEdge=true; }
                    }
                    else {  // IBL 3D
                      if (eta<5)  { checkEdge=true; }
                      if (eta>74) { checkEdge=true; }
                    }
                  }
                  else {
                    if (eta<5)   { checkEdge=true; }
                    if (eta>154) { checkEdge=true; }
                  }

                  int tot = (*clus_itr)->auxdata<std::vector<int>>("rdo_tot")[i];
                  if ((*clus_itr)->auxdata<int>("layer")==0 && (*clus_itr)->auxdata<int>("bec")==0) {  // IBL
                    if (tot==16) { checkOverflow=true; }
                  }
                  else if ((*clus_itr)->auxdata<int>("layer")==1 && (*clus_itr)->auxdata<int>("bec")==0) {  // b-layer
                    if (tot==150) { checkOverflow=true; }
                  }
                  else {
                    if (tot==255) { checkOverflow=true; }
                  }
                }
              }
              isEdge.push_back(checkEdge);
              isOverflow.push_back(checkOverflow);

              // rdo information 
              std::vector<int> tmpToT;
              std::vector<float> tmpCharge;
              std::vector<int> tmpPhi;
              std::vector<int> tmpEta;
              if ((*trk)->pt()>2000.0) {
                if ((*clus_itr)->isAvailable<std::vector<int>>("rdo_phi_pixel_index")) {
                  tmpToT    = (*clus_itr)->auxdata<std::vector<int>>("rdo_tot");
                  tmpCharge = (*clus_itr)->auxdata<std::vector<float>>("rdo_charge");
                  tmpPhi    = (*clus_itr)->auxdata<std::vector<int>>("rdo_phi_pixel_index");
                  tmpEta    = (*clus_itr)->auxdata<std::vector<int>>("rdo_eta_pixel_index");
                }
              }
              rdoToT.push_back(tmpToT);
              rdoCharge.push_back(tmpCharge);
              rdoPhi.push_back(tmpPhi);
              rdoEta.push_back(tmpEta);

              // truth information
              std::vector<int> tmpTruthBarcode;
              std::vector<int> tmpTruthPdg;
              if (isMC) {
                if ((*clus_itr)->isAvailable<std::vector<int>>("truth_barcode")) {
                  tmpTruthBarcode = (*clus_itr)->auxdata<std::vector<int>>("truth_barcode");

                  for (int i=0; i<(int)tmpTruthBarcode.size(); i++) {
                    int pdgmatch = 0;
                    for (xAOD::TruthParticleContainer::const_iterator tr_it=truthPtc->begin(); tr_it!=truthPtc->end(); tr_it++) {
                      if ((*tr_it)->barcode()==tmpTruthBarcode.at(i)) {
                        pdgmatch = (*tr_it)->pdgId();
                        if (TMath::Abs(tmpTruthBarcode.at(i))>200000) {
                          if (pdgmatch>0) { pdgmatch+=200000; }
                          else            { pdgmatch-=200000; }
                        }
                        break;
                      }
                    }
                    tmpTruthPdg.push_back(pdgmatch);
                  }
                }
              }
              clusterTruthPdgId.push_back(tmpTruthPdg);

              if (isMC && (*clus_itr)->isAvailable<std::vector<int>>("sihit_barcode")) {
                static SG::AuxElement::ConstAccessor<std::vector<int>>   acc_sihit_barcode("sihit_barcode");
                static SG::AuxElement::ConstAccessor<std::vector<int>>   acc_sihit_pdgid("sihit_pdgid");
                static SG::AuxElement::ConstAccessor<std::vector<float>> acc_sihit_startPosX("sihit_startPosX");
                static SG::AuxElement::ConstAccessor<std::vector<float>> acc_sihit_startPosY("sihit_startPosY");
                static SG::AuxElement::ConstAccessor<std::vector<float>> acc_sihit_endPosX("sihit_endPosX");
                static SG::AuxElement::ConstAccessor<std::vector<float>> acc_sihit_endPosY("sihit_endPosY");
                static SG::AuxElement::ConstAccessor<std::vector<float>> acc_sihit_energyDeposit("sihit_energyDeposit");

                const std::vector<int>   &sihit_barcode       = acc_sihit_barcode(*(*clus_itr));
                const std::vector<int>   &sihit_pdgid         = acc_sihit_pdgid(*(*clus_itr));
                const std::vector<float> &sihit_startPosX     = acc_sihit_startPosX(*(*clus_itr));
                const std::vector<float> &sihit_startPosY     = acc_sihit_startPosY(*(*clus_itr));
                const std::vector<float> &sihit_endPosX       = acc_sihit_endPosX(*(*clus_itr));
                const std::vector<float> &sihit_endPosY       = acc_sihit_endPosY(*(*clus_itr));
                const std::vector<float> &sihit_energyDeposit = acc_sihit_energyDeposit(*(*clus_itr));

                siHitPdgId.push_back(sihit_pdgid);
                siHitBarcode.push_back(sihit_barcode);
                siHitStartPosX.push_back(sihit_startPosX);
                siHitStartPosY.push_back(sihit_startPosY);
                siHitEndPosX.push_back(sihit_endPosX);
                siHitEndPosY.push_back(sihit_endPosY);
                siHitEnergyDeposit.push_back(sihit_energyDeposit);
              }

              break;
            }
          }
        }
      }

      static SG::AuxElement::Decorator<float> d0err("d0err");
      static SG::AuxElement::Decorator<float> z0err("z0err");
      static SG::AuxElement::Decorator<float> qOverPerr("qOverPerr");
      static SG::AuxElement::Decorator<std::vector<int>>   HoleIndex("HoleIndex");
      static SG::AuxElement::Decorator<std::vector<int>>   OutlierIndex("OutlierIndex");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterLayer("ClusterLayer");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterBEC("ClusterBEC");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterModulePhi("ClusterModulePhi");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterModuleEta("ClusterModuleEta");
      static SG::AuxElement::Decorator<std::vector<float>> ClusterCharge("ClusterCharge");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterToT("ClusterToT");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterL1A("ClusterL1A");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterIsSplit("ClusterIsSplit");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterSize("ClusterSize");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterSizePhi("ClusterSizePhi");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterSizeZ("ClusterSizeZ");
      static SG::AuxElement::Decorator<std::vector<bool>>  ClusterIsEdge("ClusterIsEdge");
      static SG::AuxElement::Decorator<std::vector<bool>>  ClusterIsOverflow("ClusterIsOverflow");
      static SG::AuxElement::Decorator<std::vector<float>> TrackLocalPhi("TrackLocalPhi");
      static SG::AuxElement::Decorator<std::vector<float>> TrackLocalTheta("TrackLocalTheta");
      static SG::AuxElement::Decorator<std::vector<float>> TrackLocalX("TrackLocalX");
      static SG::AuxElement::Decorator<std::vector<float>> TrackLocalY("TrackLocalY");
      static SG::AuxElement::Decorator<std::vector<float>> ClusterLocalX("ClusterLocalX");
      static SG::AuxElement::Decorator<std::vector<float>> ClusterLocalY("ClusterLocalY");
      static SG::AuxElement::Decorator<std::vector<float>> ClusterGlobalX("ClusterGlobalX");
      static SG::AuxElement::Decorator<std::vector<float>> ClusterGlobalY("ClusterGlobalY");
      static SG::AuxElement::Decorator<std::vector<float>> ClusterGlobalZ("ClusterGlobalZ");
      static SG::AuxElement::Decorator<std::vector<float>> UnbiasedResidualX("UnbiasedResidualX");
      static SG::AuxElement::Decorator<std::vector<float>> UnbiasedResidualY("UnbiasedResidualY");
      static SG::AuxElement::Decorator<std::vector<float>> UnbiasedPullX("UnbiasedPullX");
      static SG::AuxElement::Decorator<std::vector<float>> UnbiasedPullY("UnbiasedPullY");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterIsolation10x2("ClusterIsolation10x2");
      static SG::AuxElement::Decorator<std::vector<int>>   ClusterIsolation20x4("ClusterIsolation20x4");
      static SG::AuxElement::Decorator<std::vector<int>>   NumTotalClustersPerModule("NumTotalClustersPerModule");
      static SG::AuxElement::Decorator<std::vector<int>>   NumTotalPixelsPerModule("NumTotalPixelsPerModule");
      static SG::AuxElement::Decorator<std::vector<int>>   ModuleBSError("ModuleBSError");
      static SG::AuxElement::Decorator<std::vector<int>>   ModuleDCSState("ModuleDCSState");
      static SG::AuxElement::Decorator<std::vector<float>> ModuleBiasVoltage("ModuleBiasVoltage");
      static SG::AuxElement::Decorator<std::vector<float>> ModuleTemperature("ModuleTemperature");
      static SG::AuxElement::Decorator<std::vector<float>> ModuleLorentzShift("ModuleLorentzShift");
      static SG::AuxElement::Decorator<std::vector<std::vector<int>>>   RdoToT("RdoToT");
      static SG::AuxElement::Decorator<std::vector<std::vector<float>>> RdoCharge("RdoCharge");
      static SG::AuxElement::Decorator<std::vector<std::vector<int>>>   RdoPhi("RdoPhi");
      static SG::AuxElement::Decorator<std::vector<std::vector<int>>>   RdoEta("RdoEta");
      static SG::AuxElement::Decorator<std::vector<std::vector<int>>> ClusterTruthPdgId("ClusterTruthPdgId");
      static SG::AuxElement::Decorator<std::vector<std::vector<int>>> SiHitPdgId("SiHitPdgId");
      static SG::AuxElement::Decorator<std::vector<std::vector<int>>> SiHitBarcode("SiHitBarcode");
      static SG::AuxElement::Decorator<std::vector<std::vector<float>>> SiHitStartPosX("SiHitStartPosX");
      static SG::AuxElement::Decorator<std::vector<std::vector<float>>> SiHitStartPosY("SiHitStartPosY");
      static SG::AuxElement::Decorator<std::vector<std::vector<float>>> SiHitEndPosX("SiHitEndPosX");
      static SG::AuxElement::Decorator<std::vector<std::vector<float>>> SiHitEndPosY("SiHitEndPosY");
      static SG::AuxElement::Decorator<std::vector<std::vector<float>>> SiHitEnergyDeposit("SiHitEnergyDeposit");

      d0err(*tp)             = TMath::Sqrt((*trk)->definingParametersCovMatrix()(0,0));
      z0err(*tp)             = TMath::Sqrt((*trk)->definingParametersCovMatrix()(1,1));
      qOverPerr(*tp)         = TMath::Sqrt((*trk)->definingParametersCovMatrix()(4,4));

      HoleIndex(*tp)         = holeIndex;
      OutlierIndex(*tp)      = outlierIndex;
      ClusterLayer(*tp)      = clusterLayer;
      ClusterBEC(*tp)        = clusterBEC;
      ClusterModulePhi(*tp)  = clusterModulePhi;
      ClusterModuleEta(*tp)  = clusterModuleEta;
      ClusterCharge(*tp)     = clusterCharge;
      ClusterToT(*tp)        = clusterToT;
      ClusterL1A(*tp)        = clusterL1A;
      ClusterIsSplit(*tp)    = clusterIsSplit;
      ClusterSize(*tp)       = clusterSize;
      ClusterSizePhi(*tp)    = clusterSizePhi;
      ClusterSizeZ(*tp)      = clusterSizeZ;
      ClusterIsEdge(*tp)     = isEdge;
      ClusterIsOverflow(*tp) = isOverflow;
      TrackLocalPhi(*tp)     = trackPhi;
      TrackLocalTheta(*tp)   = trackTheta;
      TrackLocalX(*tp)       = trackX;
      TrackLocalY(*tp)       = trackY;
      ClusterLocalX(*tp)     = localX;
      ClusterLocalY(*tp)     = localY;
      ClusterGlobalX(*tp)    = globalX;
      ClusterGlobalY(*tp)    = globalY;
      ClusterGlobalZ(*tp)    = globalZ;
      UnbiasedResidualX(*tp) = unbiasedResidualX;
      UnbiasedResidualY(*tp) = unbiasedResidualY;
      UnbiasedPullX(*tp)     = unbiasedPullX;
      UnbiasedPullY(*tp)     = unbiasedPullY;
      ClusterIsolation10x2(*tp) = clusterIsolation10x2;
      ClusterIsolation20x4(*tp) = clusterIsolation20x4;
      NumTotalClustersPerModule(*tp) = numTotalClustersPerModule;
      NumTotalPixelsPerModule(*tp)   = numTotalPixelsPerModule;
      ModuleBSError(*tp)      = moduleBSerr;
      ModuleDCSState(*tp)     = moduleDCSstate;
      ModuleBiasVoltage(*tp)  = moduleBiasVoltage;
      ModuleTemperature(*tp)  = moduleTemperature;
      ModuleLorentzShift(*tp) = moduleLorentzShift;
      RdoToT(*tp)    = rdoToT;
      RdoCharge(*tp) = rdoCharge;
      RdoPhi(*tp)    = rdoPhi;
      RdoEta(*tp)    = rdoEta;

      ClusterTruthPdgId(*tp)  = clusterTruthPdgId;
      SiHitPdgId(*tp)         = siHitPdgId;
      SiHitBarcode(*tp)       = siHitBarcode;
      SiHitStartPosX(*tp)     = siHitStartPosX;
      SiHitStartPosY(*tp)     = siHitStartPosY;
      SiHitEndPosX(*tp)       = siHitEndPosX;
      SiHitEndPosY(*tp)       = siHitEndPosY;
      SiHitEnergyDeposit(*tp) = siHitEnergyDeposit;

      PixelMonitoringTrack->push_back(tp);
    }
  }
  return StatusCode::SUCCESS;
}

