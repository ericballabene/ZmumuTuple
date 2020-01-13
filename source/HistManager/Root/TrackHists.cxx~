#include <HistManager/TrackHists.h>
#include "xAODTruth/TruthParticleContainer.h"
#include "xAODTruth/TruthVertex.h"
#include <HistManager/TrackHelper.h>

TrackHists::TrackHists(TString name) {
  m_name = "TrackHist_" + name;
//  m_label = "Track "; // don't forget the space
  m_label = ""; // don't forget the space
  m_isPseudo = false;
  if (m_name.Contains("pseudo")) { m_label = "Pseduotrack "; m_isPseudo = true; }
}

TrackHists::~TrackHists() {}

void TrackHists::BookHists() {

  std::cout << "Creating histograms for " << m_name << std::endl;

  // from truth particle itself
  m_prodR         = declare1D(m_name, "prodR",         "production R [mm]", 110,    0.0, 1100.0);
  m_prodZ         = declare1D(m_name, "prodZ",         "production Z [mm]", 310,    0.0, 3100.0);
  m_truthPt       = declare1D(m_name, "truthPt",       "Truth p_{T} [GeV]", 200,    0.0, 2000.0); 
  m_truthPtnarrow = declare1D(m_name, "truthPtnarrow", "Truth p_{T} [GeV]", 200,    0.0,   50.0); 
  m_truthEta      = declare1D(m_name, "truthEta",      "Truth #eta",         60,   -3.0,    3.0); 
  m_truthPhi      = declare1D(m_name, "truthPhi",      "Truth #phi",         64,   -3.2,    3.2); 
  m_truthD0       = declare1D(m_name, "truthD0",       "Truth d_{0} [mm]",	100,   -0.1,    0.1); 
  m_truthD0_wide  = declare1D(m_name, "truthD0_wide",  "Truth d_{0} [mm]",  100,   -2.0,    2.0); 
  m_truthZ0       = declare1D(m_name, "truthZ0",       "Truth z_{0} [mm]",  100, -200.0,  200.0); 

  /* track parameterization */
  m_qoverp      = declare1D(m_name, "qoverp",      "#frac{q}{p} [GeV]", 200,  -2e-3,   2e-3); 
  m_pt          = declare1D(m_name, "pt",          "p_{T} [GeV]",       200,    0.0, 2000.0); 
  m_ptnarrow    = declare1D(m_name, "ptnarrow",    "p_{T} [GeV]",       200,    0.0,   50.0); 
  m_eta         = declare1D(m_name, "eta",         "#eta",               60,   -3.0,    3.0); 
  m_phi         = declare1D(m_name, "phi",         "#phi",               64,   -3.2,    3.2); 
  m_d0          = declare1D(m_name, "d0",          "d_{0} [mm]",        100,   -0.2,    0.2); 
  m_z0          = declare1D(m_name, "z0",          "z_{0} [mm]",        100, -200.0,  200.0); 

  m_eta_phi     = declare2D(m_name, "eta_phi", "#eta", "#phi", 60, -3.0, 3.0, 64, -3.2, 3.2); 

  /* track parameterization errors */
  m_qoverp_err = declare1D(m_name, "qoverp_err", "#sigma #frac{q}{p} [GeV]", 100, 0.0, 2e-4); 
  m_eta_err    = declare1D(m_name, "eta_err",    "#sigma #eta",              100, 0.0, 0.02); 
  m_d0_err     = declare1D(m_name, "d0_err",     "#sigma d_{0}",             100, 0.0, 0.4); 
  m_d0signif   = declare1D(m_name, "d0signif",   "d_{0} Significance",       100,-5.0, 5.0); 
  m_z0_err     = declare1D(m_name, "z0_err",     "#sigma z_{0}",             100, 0.0, 1.0); 
  m_phi_err    = declare1D(m_name, "phi_err",    "#sigma #phi",              100, 0.0, 0.02); 

  /* Resolution */
  m_dpt        = declare1D(m_name, "dpt",   "#Delta p_{T} [GeV]", 100, -5.0, 5.0); 
  m_dphi       = declare1D(m_name, "dphi",  "#Delta #phi",        100, -5.0, 5.0); 
  m_deta       = declare1D(m_name, "deta",  "#Delta #eta",        100, -5.0, 5.0); 
  m_dd0        = declare1D(m_name, "dd0",   "#Delta d0 [mm]",     100, -5.0, 5.0); 
  m_dz0        = declare1D(m_name, "dz0",   "#Delta z0 [mm]",     100, -5.0, 5.0); 

  /* track properties */
  m_nPixHits = declare1D(m_name, "nPixHits", "N Pixel Hits",   16, -0.5, 15.5); 
  m_nSCTHits = declare1D(m_name, "nSCTHits", "N SCT Hits",	   25, -0.5, 24.5); 
  m_nSiHits  = declare1D(m_name, "nSiHits",  "N Silicon Hits", 30, -0.5, 29.5);

  m_eta_nPixHits = declare2D(m_name, "eta_nPixHits", "|#eta|", "N Pixel Hits",   30, 0, 3.0, 16, -0.5, 15.5); 
  m_eta_nSCTHits = declare2D(m_name, "eta_nSCTHits", "|#eta|", "N SCT Hits",	   30, 0, 3.0, 25, -0.5, 24.5); 
  m_eta_nSiHits  = declare2D(m_name, "eta_nSiHits",  "|#eta|", "N Silicon Hits", 30, 0, 3.0, 30, -0.5, 29.5);

  m_nGangedPix         = declare1D(m_name, "nGangedPix",         m_label + "N Pixel Ganged Hits",     8, -0.5,  7.5); 
  m_nGangedPixFF       = declare1D(m_name, "nGangedPixFF",       m_label + "N Pixel Ganged FF Hits",  6, -0.5,  5.5); 
  m_nPixLay            = declare1D(m_name, "nPixLay",            m_label + "N Pixel Layers",         10, -0.5,  9.5); 
  m_nPixSharedHits     = declare1D(m_name, "nPixSharedHits",     m_label + "N Pixel Shared Hits",     8, -0.5,  7.5); 
  m_nPixSplitHits      = declare1D(m_name, "nPixSplitHits",      m_label + "N Pixel Split Hits",      8, -0.5,  7.5); 
  m_nPixSpoiltHits     = declare1D(m_name, "nPixSpoiltHits",     m_label + "N Pixel Spoilt Hits",     8, -0.5,  7.5); 
  m_nPixOutliers       = declare1D(m_name, "nPixOutliers",       m_label + "N Pixel Outliers",        8, -0.5,  7.5); 
  m_nPixHoles          = declare1D(m_name, "nPixHoles",          m_label + "N Pixel Holes",           8, -0.5,  7.5); 
  m_nPixelDeadSensors  = declare1D(m_name, "nPixelDeadSensors",  m_label + "N Pixel Dead Sensors",    8, -0.5,  7.5); 
  m_nSCTSharedHits     = declare1D(m_name, "nSCTSharedHits",     m_label + "N SCT Shared Hits",      11, -0.5, 10.5); 
  m_nSCTSpoiltHits     = declare1D(m_name, "nSCTSpoiltHits",     m_label + "N SCT Spoilt Hits",      11, -0.5, 10.5); 
  m_nSCTOutliers       = declare1D(m_name, "nSCTOutliers",	     m_label + "N SCT Outliers",          8, -0.5,  7.5); 
  m_nSCTHoles          = declare1D(m_name, "nSCTHoles",	         m_label + "N SCT Holes",             8, -0.5,  7.5); 
  m_nSCTDoubleHoles    = declare1D(m_name, "nSCTDoubleHoles",    m_label + "N SCT Double Holes",      8, -0.5,  7.5); 
  m_nSCTDeadSensors    = declare1D(m_name, "nSCTDeadSensors",    m_label + "N SCT Dead Sensors",      5, -0.5,  4.5);
  m_nSiDeadSensors     = declare1D(m_name, "nSiDeadSensors",     m_label + "N Silicon Dead Sensors",  9, -0.5,  8.5);

  m_nTRTHits     = declare1D(m_name, "nTRTHits",     m_label + "N TRT Hits",                61, -0.5, 60.5 ); 
  m_nTRTOutliers = declare1D(m_name, "nTRTOutliers", m_label + "N TRT Outliers",            11, -0.5, 10.5 ); 
  m_nTRTHoles    = declare1D(m_name, "nTRTHoles",    m_label + "N TRT Holes",               11, -0.5, 10.5 ); 
  m_nTRTHTHits   = declare1D(m_name, "nTRTHTHits",   m_label + "N High Threshold TRT Hits", 31, -0.5, 30.5 ); 

  m_chiSqPerDof  = declare1D(m_name, "chiSqPerDof",  m_label + "#chi^{2}/DOF", 120,  0.0, 12.0);
  m_nOutliers    = declare1D(m_name, "nOutliers",    m_label + "N Outliers",    20, -0.5, 19.5);
  m_stdDevChi2OS = declare1D(m_name, "stdDevChi2OS", m_label + "100x Std. Dev. #chi^{2} from surface", 100, 0.0, 500.0);

  m_truthMatchProb = declare1D(m_name, "truthMatchProb", m_label + "Truth Match \"Prob\"", 100, 0.0, 1.0);

  // Cluster study
  m_IBLIsEdge      = declare1D(m_name, "IBLIsEdge",     "isEdge at IBL",       2, -0.5, 1.5); 
  m_IBLIsOverflow  = declare1D(m_name, "IBLIsOverflow", "isOverflow at IBL",   2, -0.5, 1.5); 
  m_IBLIsSplit     = declare1D(m_name, "IBLIsSplit",    "isSplit at IBL",      2, -0.5, 1.5); 
  m_IBLL1A         = declare1D(m_name, "IBLL1A",        "L1A[bc] at IBL",      6, -2.5, 3.5);
  m_IBLToT         = declare1D(m_name, "IBLToT",        "ToT at IBL",         60, -0.5, 59.5); 
  m_IBLCharge      = declare1D(m_name, "IBLCharge",     "Charge[ke] at IBL",  50,  0.0, 100.0); 
  m_IBLdEdx        = declare1D(m_name, "IBLdEdx",       "dE/dx[MeV] at IBL",  50,  0.0, 10.0); 
  m_IBLdEdxVsP     = declare2D(m_name, "IBLdEdxVsP",    "p [MeV]", "dE/dx[MeV] at IBL",  500, 0, 5000.0, 200, 0.0, 20.0); 
  m_IBLHitSize     = declare1D(m_name, "IBLHitSize",    "Cluster size(IBL)",     20, 0.0, 20.0); 
  m_IBLHitSizePhi  = declare1D(m_name, "IBLHitSizePhi", "Cluster phi-size(IBL)", 10, 0.0, 20.0); 
  m_IBLHitSizeZ    = declare1D(m_name, "IBLHitSizeZ",   "Cluster z-size(IBL)",    8, 0.0,  8.0); 
  m_IBLunbiasedResidualX = declare1D(m_name, "IBLunbiasedResidualX", "IBL unbiased residual x[mm]", 100, -0.2, 0.2);
  m_IBLunbiasedResidualY = declare1D(m_name, "IBLunbiasedResidualY", "IBL unbiased residual y[mm]", 100, -0.4, 0.4);
  m_IBLIsolation10x2 = declare1D(m_name, "IBLIsolation10x2", "Isolation10x2(IBL)", 20,0,20);
  m_IBLIsolation20x4 = declare1D(m_name, "IBLIsolation20x4", "Isolation20x4(IBL)", 20,0,20);
  m_IBLnumTotalClustersPerModule = declare1D(m_name, "IBLnumTotalClustersPerModule", "N clusters per module (IBL)", 50,0,50);
  m_IBLnumTotalPixelsPerModule   = declare1D(m_name, "IBLnumTotalPixelsPerModule", "N pixels per module (IBL)", 50,0,200);
  m_IBLLorentzAngle = declare2D(m_name, "IBLLorentzAngle", "Incidence angle(#phi) (IBL)", "Cluster size", 50,  0.0, 1.0, 10, 0.0, 20.0);
  m_IBLMap    = declare2D(m_name, "IBLMap",    "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_IBLMapHit = declare2D(m_name, "IBLMapHit", "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_IBLMapEta    = declare1D(m_name, "IBLMapEta",    "track Eta", 30, -3.0, 3.0);
  m_IBLMapHitEta = declare1D(m_name, "IBLMapHitEta", "track Eta", 30, -3.0, 3.0);

  m_BLYIsEdge      = declare1D(m_name, "BLYIsEdge",     "isEdge at BLY",       2, -0.5, 1.5); 
  m_BLYIsOverflow  = declare1D(m_name, "BLYIsOverflow", "isOverflow at BLY",   2, -0.5, 1.5); 
  m_BLYIsSplit     = declare1D(m_name, "BLYIsSplit",    "isSplit at BLY",      2, -0.5, 1.5); 
  m_BLYL1A         = declare1D(m_name, "BLYL1A",        "L1A[bc] at BLY",      6, -2.5, 3.5);
  m_BLYToT         = declare1D(m_name, "BLYToT",        "ToT at BLY",         76, -0.5, 151.5); 
  m_BLYCharge      = declare1D(m_name, "BLYCharge",     "Charge[ke] at BLY",  50,  0.0, 100.0); 
  m_BLYdEdx        = declare1D(m_name, "BLYdEdx",       "dE/dx[MeV] at BLY",  50,  0.0, 10.0); 
  m_BLYdEdxVsP     = declare2D(m_name, "BLYdEdxVsP",    "p [MeV]", "dE/dx[MeV] at BLY",  500, 0, 5000.0, 200, 0.0, 20.0); 
  m_BLYHitSize     = declare1D(m_name, "BLYHitSize",    "Cluster size(BLY)",     20, 0.0, 20.0); 
  m_BLYHitSizePhi  = declare1D(m_name, "BLYHitSizePhi", "Cluster phi-size(BLY)", 10, 0.0, 20.0); 
  m_BLYHitSizeZ    = declare1D(m_name, "BLYHitSizeZ",   "Cluster z-size(BLY)",    8, 0.0,  8.0); 
  m_BLYunbiasedResidualX = declare1D(m_name, "BLYunbiasedResidualX", "BLY unbiased residual x[mm]", 100, -0.2, 0.2);
  m_BLYunbiasedResidualY = declare1D(m_name, "BLYunbiasedResidualY", "BLY unbiased residual y[mm]", 100, -0.4, 0.4);
  m_BLYIsolation10x2 = declare1D(m_name, "BLYIsolation10x2", "Isolation10x2(BLY)", 20,0,20);
  m_BLYIsolation20x4 = declare1D(m_name, "BLYIsolation20x4", "Isolation20x4(BLY)", 20,0,20);
  m_BLYnumTotalClustersPerModule = declare1D(m_name, "BLYnumTotalClustersPerModule", "N clusters per module (BLY)", 50,0,50);
  m_BLYnumTotalPixelsPerModule   = declare1D(m_name, "BLYnumTotalPixelsPerModule", "N pixels per module (BLY)", 50,0,200);
  m_BLYLorentzAngle = declare2D(m_name, "BLYLorentzAngle", "Incidence angle(#phi) (BLY)", "Cluster size", 50,  0.0, 1.0, 10, 0.0, 20.0);
  m_BLYMap    = declare2D(m_name, "BLYMap",    "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_BLYMapHit = declare2D(m_name, "BLYMapHit", "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_BLYMapEta    = declare1D(m_name, "BLYMapEta",    "track Eta", 30, -3.0, 3.0);
  m_BLYMapHitEta = declare1D(m_name, "BLYMapHitEta", "track Eta", 30, -3.0, 3.0);

  m_LY1IsEdge      = declare1D(m_name, "LY1IsEdge",     "isEdge at LY1",       2, -0.5, 1.5); 
  m_LY1IsOverflow  = declare1D(m_name, "LY1IsOverflow", "isOverflow at LY1",   2, -0.5, 1.5); 
  m_LY1IsSplit     = declare1D(m_name, "LY1IsSplit",    "isSplit at LY1",      2, -0.5, 1.5); 
  m_LY1L1A         = declare1D(m_name, "LY1L1A",        "L1A[bc] at LY1",      6, -2.5, 3.5);
  m_LY1ToT         = declare1D(m_name, "LY1ToT",        "ToT at LY1",         76, -0.5, 151.5); 
  m_LY1Charge      = declare1D(m_name, "LY1Charge",     "Charge[ke] at LY1",  50,  0.0, 100.0); 
  m_LY1dEdx        = declare1D(m_name, "LY1dEdx",       "dE/dx[MeV] at LY1",  50,  0.0, 10.0); 
  m_LY1dEdxVsP     = declare2D(m_name, "LY1dEdxVsP",    "p [MeV]", "dE/dx[MeV] at LY1",  500, 0, 5000.0, 200, 0.0, 20.0); 
  m_LY1HitSize     = declare1D(m_name, "LY1HitSize",    "Cluster size(LY1)",     20, 0.0, 20.0); 
  m_LY1HitSizePhi  = declare1D(m_name, "LY1HitSizePhi", "Cluster phi-size(LY1)", 10, 0.0, 20.0); 
  m_LY1HitSizeZ    = declare1D(m_name, "LY1HitSizeZ",   "Cluster z-size(LY1)",    8, 0.0,  8.0); 
  m_LY1unbiasedResidualX = declare1D(m_name, "LY1unbiasedResidualX", "LY1 unbiased residual x[mm]", 100, -0.2, 0.2);
  m_LY1unbiasedResidualY = declare1D(m_name, "LY1unbiasedResidualY", "LY1 unbiased residual y[mm]", 100, -0.4, 0.4);
  m_LY1Isolation10x2 = declare1D(m_name, "LY1Isolation10x2", "Isolation10x2(LY1)", 20,0,20);
  m_LY1Isolation20x4 = declare1D(m_name, "LY1Isolation20x4", "Isolation20x4(LY1)", 20,0,20);
  m_LY1numTotalClustersPerModule = declare1D(m_name, "LY1numTotalClustersPerModule", "N clusters per module (LY1)", 50,0,50);
  m_LY1numTotalPixelsPerModule   = declare1D(m_name, "LY1numTotalPixelsPerModule", "N pixels per module (LY1)", 50,0,200);
  m_LY1LorentzAngle = declare2D(m_name, "LY1LorentzAngle", "Incidence angle(#phi) (LY1)", "Cluster size", 50,  0.0, 1.0, 10, 0.0, 20.0);
  m_LY1Map    = declare2D(m_name, "LY1Map",    "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_LY1MapHit = declare2D(m_name, "LY1MapHit", "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_LY1MapEta    = declare1D(m_name, "LY1MapEta",    "track Eta", 30, -3.0, 3.0);
  m_LY1MapHitEta = declare1D(m_name, "LY1MapHitEta", "track Eta", 30, -3.0, 3.0);

  m_LY2IsEdge      = declare1D(m_name, "LY2IsEdge",     "isEdge at LY2",       2, -0.5, 1.5); 
  m_LY2IsOverflow  = declare1D(m_name, "LY2IsOverflow", "isOverflow at LY2",   2, -0.5, 1.5); 
  m_LY2IsSplit     = declare1D(m_name, "LY2IsSplit",    "isSplit at LY2",      2, -0.5, 1.5); 
  m_LY2L1A         = declare1D(m_name, "LY2L1A",        "L1A[bc] at LY2",      6, -2.5, 3.5);
  m_LY2ToT         = declare1D(m_name, "LY2ToT",        "ToT at LY2",         76, -0.5, 151.5); 
  m_LY2Charge      = declare1D(m_name, "LY2Charge",     "Charge[ke] at LY2",  50,  0.0, 100.0); 
  m_LY2dEdx        = declare1D(m_name, "LY2dEdx",       "dE/dx[MeV] at LY2",  50,  0.0, 10.0); 
  m_LY2dEdxVsP     = declare2D(m_name, "LY2dEdxVsP",    "p [MeV]", "dE/dx[MeV] at LY2",  500, 0, 5000.0, 200, 0.0, 20.0); 
  m_LY2HitSize     = declare1D(m_name, "LY2HitSize",    "Cluster size(LY2)",     20, 0.0, 20.0); 
  m_LY2HitSizePhi  = declare1D(m_name, "LY2HitSizePhi", "Cluster phi-size(LY2)", 10, 0.0, 20.0); 
  m_LY2HitSizeZ    = declare1D(m_name, "LY2HitSizeZ",   "Cluster z-size(LY2)",    8, 0.0,  8.0); 
  m_LY2unbiasedResidualX = declare1D(m_name, "LY2unbiasedResidualX", "LY2 unbiased residual x[mm]", 100, -0.2, 0.2);
  m_LY2unbiasedResidualY = declare1D(m_name, "LY2unbiasedResidualY", "LY2 unbiased residual y[mm]", 100, -0.4, 0.4);
  m_LY2Isolation10x2 = declare1D(m_name, "LY2Isolation10x2", "Isolation10x2(LY2)", 20,0,20);
  m_LY2Isolation20x4 = declare1D(m_name, "LY2Isolation20x4", "Isolation20x4(LY2)", 20,0,20);
  m_LY2numTotalClustersPerModule = declare1D(m_name, "LY2numTotalClustersPerModule", "N clusters per module (LY2)", 50,0,50);
  m_LY2numTotalPixelsPerModule   = declare1D(m_name, "LY2numTotalPixelsPerModule", "N pixels per module (LY2)", 50,0,200);
  m_LY2LorentzAngle = declare2D(m_name, "LY2LorentzAngle", "Incidence angle(#phi) (LY2)", "Cluster size", 50,  0.0, 1.0, 10, 0.0, 20.0);
  m_LY2Map    = declare2D(m_name, "LY2Map",    "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_LY2MapHit = declare2D(m_name, "LY2MapHit", "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_LY2MapEta    = declare1D(m_name, "LY2MapEta",    "track Eta", 30, -3.0, 3.0);
  m_LY2MapHitEta = declare1D(m_name, "LY2MapHitEta", "track Eta", 30, -3.0, 3.0);

  m_ENDIsEdge      = declare1D(m_name, "ENDIsEdge",     "isEdge at END",       2, -0.5, 1.5); 
  m_ENDIsOverflow  = declare1D(m_name, "ENDIsOverflow", "isOverflow at END",   2, -0.5, 1.5); 
  m_ENDIsSplit     = declare1D(m_name, "ENDIsSplit",    "isSplit at END",      2, -0.5, 1.5); 
  m_ENDL1A         = declare1D(m_name, "ENDL1A",        "L1A[bc] at END",      6, -2.5, 3.5);
  m_ENDToT         = declare1D(m_name, "ENDToT",        "ToT at END",         76, -0.5, 151.5); 
  m_ENDCharge      = declare1D(m_name, "ENDCharge",     "Charge[ke] at END",  50,  0.0, 100.0); 
  m_ENDdEdx        = declare1D(m_name, "ENDdEdx",       "dE/dx[MeV] at END",  50,  0.0, 10.0); 
  m_ENDdEdxVsP     = declare2D(m_name, "ENDdEdxVsP",    "p [MeV]", "dE/dx[MeV] at END",  500, 0, 5000.0, 200, 0.0, 20.0); 
  m_ENDHitSize     = declare1D(m_name, "ENDHitSize",    "Cluster size(END)",     20, 0.0, 20.0); 
  m_ENDHitSizePhi  = declare1D(m_name, "ENDHitSizePhi", "Cluster phi-size(END)", 10, 0.0, 20.0); 
  m_ENDHitSizeZ    = declare1D(m_name, "ENDHitSizeZ",   "Cluster z-size(END)",    8, 0.0,  8.0); 
  m_ENDunbiasedResidualX = declare1D(m_name, "ENDunbiasedResidualX", "END unbiased residual x[mm]", 100, -0.2, 0.2);
  m_ENDunbiasedResidualY = declare1D(m_name, "ENDunbiasedResidualY", "END unbiased residual y[mm]", 100, -0.4, 0.4);
  m_ENDIsolation10x2 = declare1D(m_name, "ENDIsolation10x2", "Isolation10x2(END)", 20,0,20);
  m_ENDIsolation20x4 = declare1D(m_name, "ENDIsolation20x4", "Isolation20x4(END)", 20,0,20);
  m_ENDnumTotalClustersPerModule = declare1D(m_name, "ENDnumTotalClustersPerModule", "N clusters per module (END)", 50,0,50);
  m_ENDnumTotalPixelsPerModule   = declare1D(m_name, "ENDnumTotalPixelsPerModule", "N pixels per module (END)", 50,0,200);
  m_ENDLorentzAngle = declare2D(m_name, "ENDLorentzAngle", "Incidence angle(#phi) (END)", "Cluster size", 50,  0.0, 1.0, 10, 0.0, 20.0);
  m_ED1Map       = declare2D(m_name, "ED1Map",    "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_ED1MapHit    = declare2D(m_name, "ED1MapHit", "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_ED1MapEta    = declare1D(m_name, "ED1MapEta",    "track Eta", 30, -3.0, 3.0);
  m_ED1MapHitEta = declare1D(m_name, "ED1MapHitEta", "track Eta", 30, -3.0, 3.0);
  m_ED23Map       = declare2D(m_name, "ED23Map",    "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_ED23MapHit    = declare2D(m_name, "ED23MapHit", "track Eta", "track Phi", 30, -3.0, 3.0, 30, -TMath::Pi(), TMath::Pi());
  m_ED23MapEta    = declare1D(m_name, "ED23MapEta",    "track Eta", 30, -3.0, 3.0);
  m_ED23MapHitEta = declare1D(m_name, "ED23MapHitEta", "track Eta", 30, -3.0, 3.0);

} // BookHists

void TrackHists::FillHists(const xAOD::TrackParticle* trk, float weight) const {

  if(m_usedBarcodes.size() > 100) { 
    std::cout << "WARNING::TrackHists " << m_name << " has " << m_usedBarcodes.size() 
      << " barcodes marked as used" << std::endl;
  }

  uint8_t getInt(0);   // for accessing summary information
  float   getFlt(0.0); // for accessing summary information

  float d0err, z0err;
  const xAOD::ParametersCovMatrix_t covTrk = trk->definingParametersCovMatrix();
  if (trk->isAvailable<float>("d0err")) { 
    d0err = trk->auxdata<float>("d0err"); 
    z0err = trk->auxdata<float>("z0err");
  }
  else                                   { 
    d0err = sqrt(covTrk(0,0)); 
    z0err = sqrt(covTrk(1,1)); 
  }
  float d0signif = trk->d0()/d0err;

  /* track parameterization */
  m_qoverp       ->Fill(trk->qOverP(),weight); 
  m_pt           ->Fill(trk->pt()*1e-3,weight); 
  m_ptnarrow     ->Fill(trk->pt()*1e-3,weight); 
  m_eta          ->Fill(trk->eta(),weight); 
  m_d0           ->Fill(trk->d0(),weight); 
  m_z0           ->Fill(trk->z0(),weight); 
  m_phi          ->Fill(trk->phi(),weight); 

  m_eta_phi      -> Fill(trk->eta(),trk->phi(),weight);

  /* track parameterization errors */
  m_qoverp_err -> Fill(sqrt(covTrk(4,4)),weight); 
  m_eta_err    -> Fill(sqrt(covTrk(3,3)),weight);  // really theta - FIXME
  m_d0_err     -> Fill(d0err,weight);
  m_d0signif   -> Fill(d0signif,weight);
  m_z0_err     -> Fill(sqrt(covTrk(1,1)),weight); 
  m_phi_err    -> Fill(sqrt(covTrk(2,2)),weight); 

  /* track properties */
  trk->summaryValue(getInt,xAOD::numberOfPixelHits); int nPixHits = getInt;
  trk->summaryValue(getInt,xAOD::numberOfSCTHits);   int nSCTHits = getInt;
  int nSiHits  = xAOD::TrackHelper::numberOfSiHits(trk);
  m_nPixHits -> Fill(1.0*nPixHits);
  m_nSCTHits -> Fill(1.0*nSCTHits); 
  m_nSiHits  -> Fill(1.0*nSiHits);

  m_eta_nPixHits -> Fill(TMath::Abs(trk->eta()),1.0*nPixHits);
  m_eta_nSCTHits -> Fill(TMath::Abs(trk->eta()),1.0*nSCTHits); 
  m_eta_nSiHits  -> Fill(TMath::Abs(trk->eta()),1.0*nSiHits);

  trk->summaryValue(getInt,xAOD::numberOfGangedPixels);       m_nGangedPix        -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfGangedFlaggedFakes); m_nGangedPixFF      -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfContribPixelLayers); m_nPixLay           -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelSharedHits);    m_nPixSharedHits    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelSplitHits);     m_nPixSplitHits     -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelSpoiltHits);    m_nPixSpoiltHits    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelOutliers);      m_nPixOutliers      -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelHoles);         m_nPixHoles         -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfPixelDeadSensors);   m_nPixelDeadSensors -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTSharedHits);      m_nSCTSharedHits    -> Fill(getInt,weight); 
  trk->summaryValue(getInt,xAOD::numberOfSCTSpoiltHits);      m_nSCTSpoiltHits    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTOutliers);        m_nSCTOutliers      -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTHoles);           m_nSCTHoles         -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTDoubleHoles);     m_nSCTDoubleHoles   -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfSCTDeadSensors);     m_nSCTDeadSensors   -> Fill(getInt,weight);

  uint8_t numberOfPixelHoles= 0;    trk->summaryValue(numberOfPixelHoles,xAOD::numberOfPixelHoles);
  uint8_t numberOfPixelOutliers= 0; trk->summaryValue(numberOfPixelOutliers,xAOD::numberOfPixelOutliers);

  m_nSiDeadSensors -> Fill(xAOD::TrackHelper::numberOfSiDeadSensors(trk),weight);

  trk->summaryValue(getInt,xAOD::numberOfTRTHits);              m_nTRTHits     -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::numberOfTRTOutliers);          m_nTRTOutliers -> Fill(getInt,weight); 
  trk->summaryValue(getInt,xAOD::numberOfTRTHoles);             m_nTRTHoles    -> Fill(getInt,weight); 
  trk->summaryValue(getInt,xAOD::numberOfTRTHighThresholdHits); m_nTRTHTHits   -> Fill(getInt,weight); 
  //numberOfTRTHighThresholdOutliers
  //numberOfTRTDeadStraws
  //numberOfTRTTubeHits
  //numberOfTRTXenonHits
  //numberOfPrecisionLayers
  //numberOfPrecisionHoleLayers
  //numberOfPhiLayers
  //numberOfPhiHoleLayers
  //numberOfTriggerEtaLayers
  //numberOfTriggerEtaHoleLayers

  m_chiSqPerDof -> Fill(xAOD::TrackHelper::chiSqPerDoF(trk),weight);

  trk->summaryValue(getInt,xAOD::numberOfOutliersOnTrack);   m_nOutliers    -> Fill(getInt,weight);
  trk->summaryValue(getInt,xAOD::standardDeviationOfChi2OS); m_stdDevChi2OS -> Fill(getInt,weight);

  //===========================
  // Efficiency and fake study
  //===========================

  const xAOD::TruthParticle *truthParticle = xAOD::TrackHelper::truthParticle(trk);
  if (truthParticle) {
    if (truthParticle->hasProdVtx()) {
      m_prodR -> Fill(truthParticle->prodVtx()->perp(),weight);
      m_prodZ -> Fill(truthParticle->prodVtx()->z(),weight);
    }

    float truthd0 = 0.0;
    if (truthParticle->isAvailable<float>("d0")) {
      truthd0 = truthParticle->auxdata<float>("d0");
    }

    float truthz0 = 0.0;
    if (truthParticle->isAvailable<float>("z0")) {
      truthz0 = truthParticle->auxdata<float>("z0");
    }

    m_truthPt       -> Fill(truthParticle->pt()*1e-3,weight);
    m_truthPtnarrow -> Fill(truthParticle->pt()*1e-3,weight);
    m_truthEta      -> Fill(truthParticle->eta(),weight);
    m_truthPhi      -> Fill(truthParticle->phi(),weight);
    m_truthD0       -> Fill(truthd0,weight);
    m_truthZ0       -> Fill(truthz0,weight);

    m_dpt  -> Fill((trk->pt()-truthParticle->pt())/truthParticle->pt(),weight);
    m_dphi -> Fill((trk->phi()-truthParticle->phi())/truthParticle->phi(),weight);
    m_deta -> Fill((trk->eta()-truthParticle->eta())/truthParticle->eta(),weight);
    if (truthd0) { m_dd0->Fill((trk->d0()-truthd0)/truthd0,weight); }
    if (truthz0) { m_dz0->Fill((trk->z0()-truthz0)/truthz0,weight); }

    m_truthMatchProb -> Fill(xAOD::TrackHelper::truthMatchProb(trk),weight);
  }

  // Cluster study
//  static SG::AuxElement::Decorator<std::vector<int>>   HoleIndex("HoleIndex");

  if (trk->isAvailable<std::vector<int>>("ClusterLayer")) {
    std::vector<int>   clusterLayer;              if (trk->isAvailable<std::vector<int>>("ClusterLayer"))              { clusterLayer              = trk->auxdata<std::vector<int>>("ClusterLayer"); }
    std::vector<int>   clusterBEC;                if (trk->isAvailable<std::vector<int>>("ClusterBEC"))                { clusterBEC                = trk->auxdata<std::vector<int>>("ClusterBEC"); }
    std::vector<int>   clusterModulePhi;          if (trk->isAvailable<std::vector<int>>("ClusterModulePhi"))          { clusterModulePhi          = trk->auxdata<std::vector<int>>("ClusterModulePhi"); }
    std::vector<int>   clusterModuleEta;          if (trk->isAvailable<std::vector<int>>("ClusterModuleEta"))          { clusterModuleEta          = trk->auxdata<std::vector<int>>("ClusterModuleEta"); }
    std::vector<float> clusterCharge;             if (trk->isAvailable<std::vector<float>>("ClusterCharge"))           { clusterCharge             = trk->auxdata<std::vector<float>>("ClusterCharge"); }
    std::vector<int>   clusterToT;                if (trk->isAvailable<std::vector<int>>("ClusterToT"))                { clusterToT                = trk->auxdata<std::vector<int>>("ClusterToT"); }
    std::vector<int>   clusterL1A;                if (trk->isAvailable<std::vector<int>>("ClusterL1A"))                { clusterL1A                = trk->auxdata<std::vector<int>>("ClusterL1A"); }
    std::vector<int>   clusterIsSplit;            if (trk->isAvailable<std::vector<int>>("ClusterIsSplit"))            { clusterIsSplit            = trk->auxdata<std::vector<int>>("ClusterIsSplit"); }
    std::vector<int>   clusterSize;               if (trk->isAvailable<std::vector<int>>("ClusterSize"))               { clusterSize               = trk->auxdata<std::vector<int>>("ClusterSize"); }
    std::vector<int>   clusterSizePhi;            if (trk->isAvailable<std::vector<int>>("ClusterSizePhi"))            { clusterSizePhi            = trk->auxdata<std::vector<int>>("ClusterSizePhi"); }
    std::vector<int>   clusterSizeZ;              if (trk->isAvailable<std::vector<int>>("ClusterSizeZ"))              { clusterSizeZ              = trk->auxdata<std::vector<int>>("ClusterSizeZ"); }
    std::vector<bool>  clusterIsEdge;             if (trk->isAvailable<std::vector<bool>>("ClusterIsEdge"))            { clusterIsEdge             = trk->auxdata<std::vector<bool>>("ClusterIsEdge"); }
    std::vector<bool>  clusterIsOverflow;         if (trk->isAvailable<std::vector<bool>>("ClusterIsOverflow"))        { clusterIsOverflow         = trk->auxdata<std::vector<bool>>("ClusterIsOverflow"); }
    std::vector<float> trackLocalPhi;             if (trk->isAvailable<std::vector<float>>("TrackLocalPhi"))           { trackLocalPhi             = trk->auxdata<std::vector<float>>("TrackLocalPhi"); }
    std::vector<float> trackLocalTheta;           if (trk->isAvailable<std::vector<float>>("TrackLocalTheta"))         { trackLocalTheta           = trk->auxdata<std::vector<float>>("TrackLocalTheta"); }
    std::vector<float> trackLocalX;               if (trk->isAvailable<std::vector<float>>("TrackLocalX"))             { trackLocalX               = trk->auxdata<std::vector<float>>("TrackLocalX"); }
    std::vector<float> trackLocalY;               if (trk->isAvailable<std::vector<float>>("TrackLocalY"))             { trackLocalY               = trk->auxdata<std::vector<float>>("TrackLocalY"); }
    std::vector<float> clusterLocalX;             if (trk->isAvailable<std::vector<float>>("ClusterLocalX"))           { clusterLocalX             = trk->auxdata<std::vector<float>>("ClusterLocalX"); }
    std::vector<float> clusterLocalY;             if (trk->isAvailable<std::vector<float>>("ClusterLocalY"))           { clusterLocalY             = trk->auxdata<std::vector<float>>("ClusterLocalY"); }
    std::vector<float> clusterGlobalX;            if (trk->isAvailable<std::vector<float>>("ClusterGlobalX"))          { clusterGlobalX            = trk->auxdata<std::vector<float>>("ClusterGlobalX"); }
    std::vector<float> clusterGlobalY;            if (trk->isAvailable<std::vector<float>>("ClusterGlobalY"))          { clusterGlobalY            = trk->auxdata<std::vector<float>>("ClusterGlobalY"); }
    std::vector<float> clusterGlobalZ;            if (trk->isAvailable<std::vector<float>>("ClusterGlobalZ"))          { clusterGlobalZ            = trk->auxdata<std::vector<float>>("ClusterGlobalZ"); }
    std::vector<float> unbiasedResidualX;         if (trk->isAvailable<std::vector<float>>("UnbiasedResidualX"))       { unbiasedResidualX         = trk->auxdata<std::vector<float>>("UnbiasedResidualX"); }
    std::vector<float> unbiasedResidualY;         if (trk->isAvailable<std::vector<float>>("UnbiasedResidualY"))       { unbiasedResidualY         = trk->auxdata<std::vector<float>>("UnbiasedResidualY"); }
    std::vector<int>   clusterIsolation10x2;      if (trk->isAvailable<std::vector<int>>("ClusterIsolation10x2"))      { clusterIsolation10x2      = trk->auxdata<std::vector<int>>("ClusterIsolation10x2"); }
    std::vector<int>   clusterIsolation20x4;      if (trk->isAvailable<std::vector<int>>("ClusterIsolation20x4"))      { clusterIsolation20x4      = trk->auxdata<std::vector<int>>("ClusterIsolation20x4"); }
    std::vector<int>   numTotalClustersPerModule; if (trk->isAvailable<std::vector<int>>("NumTotalClustersPerModule")) { numTotalClustersPerModule = trk->auxdata<std::vector<int>>("NumTotalClustersPerModule"); }
    std::vector<int>   numTotalPixelsPerModule;   if (trk->isAvailable<std::vector<int>>("NumTotalPixelsPerModule"))   { numTotalPixelsPerModule   = trk->auxdata<std::vector<int>>("NumTotalPixelsPerModule"); }
    std::vector<float> moduleBiasVoltage;         if (trk->isAvailable<std::vector<float>>("ModuleBiasVoltage"))       { moduleBiasVoltage         = trk->auxdata<std::vector<float>>("ModuleBiasVoltage"); }
    std::vector<float> moduleTemperature;         if (trk->isAvailable<std::vector<float>>("ModuleTemperature"))       { moduleTemperature         = trk->auxdata<std::vector<float>>("ModuleTemperature"); }
    std::vector<float> moduleLorentzShift;        if (trk->isAvailable<std::vector<float>>("ModuleLorentzShift"))      { moduleLorentzShift        = trk->auxdata<std::vector<float>>("ModuleLorentzShift"); }

    // Validation of the basic propoerty
    for (int i=0; i<(int)clusterLayer.size(); i++) {
      if (clusterBEC.at(i)==0 && clusterLayer.at(i)==0) { // IBL
        m_IBLIsEdge     -> Fill(1.0*clusterIsEdge.at(i),weight); 
        m_IBLIsOverflow -> Fill(1.0*clusterIsOverflow.at(i),weight); 
        m_IBLIsSplit    -> Fill(1.0*clusterIsSplit.at(i),weight); 
        m_IBLL1A        -> Fill(1.0*clusterL1A.at(i),weight); 
        m_IBLIsolation10x2 -> Fill(1.0*clusterIsolation10x2.at(i),weight);
        m_IBLIsolation20x4 -> Fill(1.0*clusterIsolation20x4.at(i),weight);
        m_IBLnumTotalClustersPerModule -> Fill(1.0*numTotalClustersPerModule.at(i),weight);
        m_IBLnumTotalPixelsPerModule   -> Fill(1.0*numTotalPixelsPerModule.at(i),weight);
        m_IBLToT              -> Fill(1.0*clusterToT.at(i),weight);
        m_IBLCharge           -> Fill(clusterCharge.at(i)/1000.0,weight); 
        m_IBLHitSize          -> Fill(1.0*clusterSize.at(i),weight); 
        m_IBLHitSizePhi       -> Fill(1.0*clusterSizePhi.at(i),weight); 
        m_IBLHitSizeZ         -> Fill(1.0*clusterSizeZ.at(i),weight); 
        if (unbiasedResidualX.size()==clusterLayer.size()) { m_IBLunbiasedResidualX-> Fill(unbiasedResidualX.at(i),weight); }
        if (unbiasedResidualY.size()==clusterLayer.size()) { m_IBLunbiasedResidualY-> Fill(unbiasedResidualY.at(i),weight); }
      }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==1) { // B-layer
        m_BLYIsEdge     -> Fill(1.0*clusterIsEdge.at(i),weight); 
        m_BLYIsOverflow -> Fill(1.0*clusterIsOverflow.at(i),weight); 
        m_BLYIsSplit    -> Fill(1.0*clusterIsSplit.at(i),weight); 
        m_BLYL1A        -> Fill(1.0*clusterL1A.at(i),weight); 
        m_BLYIsolation10x2 -> Fill(1.0*clusterIsolation10x2.at(i),weight);
        m_BLYIsolation20x4 -> Fill(1.0*clusterIsolation20x4.at(i),weight);
        m_BLYnumTotalClustersPerModule -> Fill(1.0*numTotalClustersPerModule.at(i),weight);
        m_BLYnumTotalPixelsPerModule   -> Fill(1.0*numTotalPixelsPerModule.at(i),weight);
        m_BLYToT              -> Fill(1.0*clusterToT.at(i),weight);
        m_BLYCharge           -> Fill(clusterCharge.at(i)/1000.0,weight); 
        m_BLYHitSize          -> Fill(1.0*clusterSize.at(i),weight); 
        m_BLYHitSizePhi       -> Fill(1.0*clusterSizePhi.at(i),weight); 
        m_BLYHitSizeZ         -> Fill(1.0*clusterSizeZ.at(i),weight); 
        if (unbiasedResidualX.size()==clusterLayer.size()) { m_BLYunbiasedResidualX-> Fill(unbiasedResidualX.at(i),weight); }
        if (unbiasedResidualY.size()==clusterLayer.size()) { m_BLYunbiasedResidualY-> Fill(unbiasedResidualY.at(i),weight); }
      }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==2) { // Layer-1
        m_LY1IsEdge     -> Fill(1.0*clusterIsEdge.at(i),weight); 
        m_LY1IsOverflow -> Fill(1.0*clusterIsOverflow.at(i),weight); 
        m_LY1IsSplit    -> Fill(1.0*clusterIsSplit.at(i),weight); 
        m_LY1L1A        -> Fill(1.0*clusterL1A.at(i),weight); 
        m_LY1Isolation10x2 -> Fill(1.0*clusterIsolation10x2.at(i),weight);
        m_LY1Isolation20x4 -> Fill(1.0*clusterIsolation20x4.at(i),weight);
        m_LY1numTotalClustersPerModule -> Fill(1.0*numTotalClustersPerModule.at(i),weight);
        m_LY1numTotalPixelsPerModule   -> Fill(1.0*numTotalPixelsPerModule.at(i),weight);
        m_LY1ToT              -> Fill(1.0*clusterToT.at(i),weight);
        m_LY1Charge           -> Fill(clusterCharge.at(i)/1000.0,weight); 
        m_LY1HitSize          -> Fill(1.0*clusterSize.at(i),weight); 
        m_LY1HitSizePhi       -> Fill(1.0*clusterSizePhi.at(i),weight); 
        m_LY1HitSizeZ         -> Fill(1.0*clusterSizeZ.at(i),weight); 
        if (unbiasedResidualX.size()==clusterLayer.size()) { m_LY1unbiasedResidualX-> Fill(unbiasedResidualX.at(i),weight); }
        if (unbiasedResidualY.size()==clusterLayer.size()) { m_LY1unbiasedResidualY-> Fill(unbiasedResidualY.at(i),weight); }
      }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==3) { // Layer-2
        m_LY2IsEdge     -> Fill(1.0*clusterIsEdge.at(i),weight); 
        m_LY2IsOverflow -> Fill(1.0*clusterIsOverflow.at(i),weight); 
        m_LY2IsSplit    -> Fill(1.0*clusterIsSplit.at(i),weight); 
        m_LY2L1A        -> Fill(1.0*clusterL1A.at(i),weight); 
        m_LY2Isolation10x2 -> Fill(1.0*clusterIsolation10x2.at(i),weight);
        m_LY2Isolation20x4 -> Fill(1.0*clusterIsolation20x4.at(i),weight);
        m_LY2numTotalClustersPerModule -> Fill(1.0*numTotalClustersPerModule.at(i),weight);
        m_LY2numTotalPixelsPerModule   -> Fill(1.0*numTotalPixelsPerModule.at(i),weight);
        m_LY2ToT              -> Fill(1.0*clusterToT.at(i),weight);
        m_LY2Charge           -> Fill(clusterCharge.at(i)/1000.0,weight); 
        m_LY2HitSize          -> Fill(1.0*clusterSize.at(i),weight); 
        m_LY2HitSizePhi       -> Fill(1.0*clusterSizePhi.at(i),weight); 
        m_LY2HitSizeZ         -> Fill(1.0*clusterSizeZ.at(i),weight); 
        if (unbiasedResidualX.size()==clusterLayer.size()) { m_LY2unbiasedResidualX-> Fill(unbiasedResidualX.at(i),weight); }
        if (unbiasedResidualY.size()==clusterLayer.size()) { m_LY2unbiasedResidualY-> Fill(unbiasedResidualY.at(i),weight); }
      }
      else if (clusterBEC.at(i)!=0) { // Endcap
        m_ENDIsEdge     -> Fill(1.0*clusterIsEdge.at(i),weight); 
        m_ENDIsOverflow -> Fill(1.0*clusterIsOverflow.at(i),weight); 
        m_ENDIsSplit    -> Fill(1.0*clusterIsSplit.at(i),weight); 
        m_ENDL1A        -> Fill(1.0*clusterL1A.at(i),weight); 
        m_ENDIsolation10x2 -> Fill(1.0*clusterIsolation10x2.at(i),weight);
        m_ENDIsolation20x4 -> Fill(1.0*clusterIsolation20x4.at(i),weight);
        m_ENDnumTotalClustersPerModule -> Fill(1.0*numTotalClustersPerModule.at(i),weight);
        m_ENDnumTotalPixelsPerModule   -> Fill(1.0*numTotalPixelsPerModule.at(i),weight);
        m_ENDToT              -> Fill(1.0*clusterToT.at(i),weight);
        m_ENDCharge           -> Fill(clusterCharge.at(i)/1000.0,weight); 
        m_ENDHitSize          -> Fill(1.0*clusterSize.at(i),weight); 
        m_ENDHitSizePhi       -> Fill(1.0*clusterSizePhi.at(i),weight); 
        m_ENDHitSizeZ         -> Fill(1.0*clusterSizeZ.at(i),weight); 
        if (unbiasedResidualX.size()==clusterLayer.size()) { m_ENDunbiasedResidualX-> Fill(unbiasedResidualX.at(i),weight); }
        if (unbiasedResidualY.size()==clusterLayer.size()) { m_ENDunbiasedResidualY-> Fill(unbiasedResidualY.at(i),weight); }
      }
    }

    // Good tracks must be required for the dE/dx and Lorentz angle measurements
    trk->summaryValue(getInt,xAOD::numberOfPixelDeadSensors);
    int nDeadSensor = getInt; 

    int checkIBL = 0;
    int checkBLY = 0;
    int checkLY1 = 0;
    int checkLY2 = 0;
    int checkED1 = 0;
    int checkED2 = 0;
    int checkED3 = 0;
    for (int i=0; i<(int)clusterLayer.size(); i++) {
      if      (clusterBEC.at(i)==0 && clusterLayer.at(i)==0) { checkIBL++; }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==1) { checkBLY++; }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==2) { checkLY1++; }
      else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==3) { checkLY2++; }
      else if (abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==0) { checkED1++; }
      else if (abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==1) { checkED2++; }
      else if (abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==2) { checkED3++; }
    }

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

    double energyPair   = 3.62e-6;   // Electron-hole pair creation energy  e-h/[MeV]
    double siDensity    = 2.329;     // Silicon density [g/cm^3]
    double thicknessIBL = 0.0200;    // thickness for IBL [cm]
    double thicknessPIX = 0.0250;    // thickness for PIXEL [cm]

    for (int i=0; i<(int)clusterLayer.size(); i++) {
//      if (nDeadSensor==0 && isEdge==0 && iso20x4==0) {
      if (nPixHits>3 && numberOfPixelHoles==0 && nDeadSensor==0 && numberOfPixelOutliers==0 && isEdge==0 && isOverflow==0 && isSplit==0 && iso20x4==0) {
        double alpha = TMath::ATan(TMath::Sqrt(TMath::Power(TMath::Tan(trackLocalTheta.at(i)),2)+TMath::Power(TMath::Tan(trackLocalPhi.at(i)),2)));  // incidence angle 3D
        if (checkIBL>0 && checkBLY>0 && checkLY1>0 && checkLY2>0) { // Barrel
          if (clusterBEC.at(i)==0 && clusterLayer.at(i)==0) { // IBL
            m_IBLdEdx         -> Fill(clusterCharge.at(i)*energyPair/thicknessIBL/siDensity*TMath::Cos(alpha),weight); 
            m_IBLdEdxVsP      -> Fill(1.0/fabs(trk->qOverP()),clusterCharge.at(i)*energyPair/thicknessIBL/siDensity*TMath::Cos(alpha),weight); 
            m_IBLLorentzAngle -> Fill(trackLocalPhi.at(i),1.0*clusterSizePhi.at(i),weight);
          }
          else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==1) { // B-layer
            m_BLYdEdx         -> Fill(clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_BLYdEdxVsP      -> Fill(1.0/fabs(trk->qOverP()),clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_BLYLorentzAngle -> Fill(trackLocalPhi.at(i),1.0*clusterSizePhi.at(i),weight);
          }
          else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==2) { // Layer-1
            m_LY1dEdx         -> Fill(clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_LY1dEdxVsP      -> Fill(1.0/fabs(trk->qOverP()),clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_LY1LorentzAngle -> Fill(trackLocalPhi.at(i),1.0*clusterSizePhi.at(i),weight);
          }
          else if (clusterBEC.at(i)==0 && clusterLayer.at(i)==3) { // Layer-2
            m_LY2dEdx         -> Fill(clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_LY2dEdxVsP      -> Fill(1.0/fabs(trk->qOverP()),clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_LY2LorentzAngle -> Fill(trackLocalPhi.at(i),1.0*clusterSizePhi.at(i),weight);
          }
        }
        else if (checkED1>0 && checkED2>0 && checkED3>0) { // Endcap
          if (abs(clusterBEC.at(i))==2) {
            m_ENDdEdx         -> Fill(clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_ENDdEdxVsP      -> Fill(1.0/fabs(trk->qOverP()),clusterCharge.at(i)*energyPair/thicknessPIX/siDensity*TMath::Cos(alpha),weight); 
            m_ENDLorentzAngle -> Fill(trackLocalPhi.at(i),1.0*clusterSizePhi.at(i),weight);
          }
        }
      }
    }

    trk->summaryValue(getInt,xAOD::numberOfContribPixelLayers);            int nPixCondPixLayer    = getInt;
    trk->summaryValue(getInt,xAOD::numberOfInnermostPixelLayerHits);       int nInnermostLayer     = getInt;
    trk->summaryValue(getInt,xAOD::numberOfNextToInnermostPixelLayerHits); int nNextInnermostLayer = getInt;

    trk->summaryValue(getInt,xAOD::numberOfPixelHoles);
    int nPixHoles = getInt;
    std::vector<int> holeIndex; if (trk->isAvailable<std::vector<int>>("HoleIndex")) { holeIndex=trk->auxdata<std::vector<int>>("HoleIndex"); }
 
    if (trk->pt()/1000.0>1.0 && fabs(trk->d0())<2.0 && nDeadSensor==0) {
      // IBL hit efficiency
      if (fabs(trk->eta())<2.1 && checkBLY>0 && checkLY1>0 && checkLY2>0) {
        m_IBLMap    -> Fill(trk->eta(),trk->phi(),weight);
        m_IBLMapEta -> Fill(trk->eta(),weight);
        int checkHit = 0;
        for (int i=0; i<(int)clusterLayer.size(); i++) {
          if (clusterBEC.at(i)==0 && clusterLayer.at(i)==0) { checkHit++; }
        }
        if (checkHit) {
          m_IBLMapHit    -> Fill(trk->eta(),trk->phi(),weight); 
          m_IBLMapHitEta -> Fill(trk->eta(),weight); 
        }
      }
      // b-layer hit efficiency
      if (fabs(trk->eta())<2.1 && checkIBL>0 && checkLY1>0 && checkLY2>0) {
        m_BLYMap    -> Fill(trk->eta(),trk->phi(),weight);
        m_BLYMapEta -> Fill(trk->eta(),weight);
        int checkHit = 0;
        for (int i=0; i<(int)clusterLayer.size(); i++) {
          if (clusterBEC.at(i)==0 && clusterLayer.at(i)==1) { checkHit++; }
        }
        if (checkHit) {
          m_BLYMapHit    -> Fill(trk->eta(),trk->phi(),weight); 
          m_BLYMapHitEta -> Fill(trk->eta(),weight); 
        }
      }
      // L1 hit efficiency
      if (fabs(trk->eta())<2.1 && checkIBL>0 && checkBLY>0 && checkLY2>0) {
        m_LY1Map    -> Fill(trk->eta(),trk->phi(),weight);
        m_LY1MapEta -> Fill(trk->eta(),weight);
        int checkHit = 0;
        for (int i=0; i<(int)clusterLayer.size(); i++) {
          if (clusterBEC.at(i)==0 && clusterLayer.at(i)==2) { checkHit++; }
        }
        if (checkHit) {
          m_LY1MapHit    -> Fill(trk->eta(),trk->phi(),weight); 
          m_LY1MapHitEta -> Fill(trk->eta(),weight); 
        }
      } 
      // L2 hit efficiency
      if (fabs(trk->eta())<2.1 && checkIBL>0 && checkBLY>0 && checkLY1>0) {
        m_LY2Map    -> Fill(trk->eta(),trk->phi(),weight);
        m_LY2MapEta -> Fill(trk->eta(),weight);
        int checkHit = 0;
        for (int i=0; i<(int)clusterLayer.size(); i++) {
          if (clusterBEC.at(i)==0 && clusterLayer.at(i)==3) { checkHit++; }
        }
        if (checkHit) {
          m_LY2MapHit    -> Fill(trk->eta(),trk->phi(),weight); 
          m_LY2MapHitEta -> Fill(trk->eta(),weight); 
        }
      } 
      // Endcap hit efficiency
      if (checkIBL>0) {
        if (checkLY1>0) { // Disk-1
          m_ED1Map    -> Fill(trk->eta(),trk->phi(),weight);
          m_ED1MapEta -> Fill(trk->eta(),weight);
          int checkHit = 0;
          for (int i=0; i<(int)clusterLayer.size(); i++) {
            if (abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==0) { checkHit++; }
          }
          if (checkHit) { 
            m_ED1MapHit    -> Fill(trk->eta(),trk->phi(),weight); 
            m_ED1MapHitEta -> Fill(trk->eta(),weight); 
          }
        }
        if (checkED1+checkED2+checkED3>1) { // Disk-2,3
          m_ED23Map    -> Fill(trk->eta(),trk->phi(),weight);
          m_ED23MapEta -> Fill(trk->eta(),weight);
          int checkHit = 0;
          for (int i=0; i<(int)clusterLayer.size(); i++) {
            if (abs(clusterBEC.at(i))==2 && clusterLayer.at(i)==0) { checkHit++; }
          }
          if (checkHit) {
            m_ED23MapHit    -> Fill(trk->eta(),trk->phi(),weight); 
            m_ED23MapHitEta -> Fill(trk->eta(),weight); 
          }
        }
      }
    }
  }

  //    static SG::AuxElement::Decorator<std::vector<std::vector<int>>>   RdoToT("RdoToT");
  //    static SG::AuxElement::Decorator<std::vector<std::vector<float>>> RdoCharge("RdoCharge");
  //    static SG::AuxElement::Decorator<std::vector<std::vector<int>>>   RdoPhi("RdoPhi");
  //    static SG::AuxElement::Decorator<std::vector<std::vector<int>>>   RdoEta("RdoEta");


} // FillHists

