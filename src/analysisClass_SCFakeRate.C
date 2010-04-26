#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>

analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  :baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
{
  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

  std::cout << "analysisClass::analysisClass(): ends " << std::endl;
}

analysisClass::~analysisClass()
{
  std::cout << "analysisClass::~analysisClass(): begins " << std::endl;

  std::cout << "analysisClass::~analysisClass(): ends " << std::endl;
}

void analysisClass::Loop()
{
   std::cout << "analysisClass::Loop() begins" <<std::endl;   
    
   if (fChain == 0) return;
   
   //////////book histos here

   //Combinations
   TH1F *h_Mej = new TH1F ("Mej","Mej",200,0,2000);  h_Mej->Sumw2();
   TH1F *h_dR_JetSC = new TH1F("dR_JetSC","dR_JetSC",600,0,3.0); h_dR_JetSC->Sumw2();
   TH1F *h_dR_JetSC_2Jets = new TH1F("dR_JetSC_2Jets","dR_JetSC_2Jets",600,0,3.0); h_dR_JetSC_2Jets->Sumw2();
   TH2F *h_dR_JetSC_EcalIso = new TH2F("dR_JetSC_EcalIso","dR_JetSC_EcalIso",600,0,3.0,500,0,10); h_dR_JetSC->Sumw2();
   TH1F *h_NisoSC = new TH1F ("NisoSC","NisoSC",6,-0.5,5.5);  h_NisoSC->Sumw2();
   TH1F *h_goodEleSCPt = new TH1F ("goodEleSCPt","goodEleSCPt",200,0,1000); h_goodEleSCPt->Sumw2();
   TH1F *h_goodEleSCPt_Barrel = new TH1F ("goodEleSCPt_Barrel","goodEleSCPt_Barrel",200,0,1000); h_goodEleSCPt_Barrel->Sumw2();
   TH1F *h_goodEleSCEta = new TH1F ("goodEleSCEta","goodEleSCEta",100,-3.,3.); h_goodEleSCEta->Sumw2();
   TH1F *h_goodEleSCPt_Barrel_2SC = new TH1F ("goodEleSCPt_Barrel_2SC","goodEleSCPt_Barrel_2SC",200,0,1000); h_goodEleSCPt_Barrel_2SC->Sumw2();
   TH1F *h_goodEleSCPt_Barrel_2Jets = new TH1F ("goodEleSCPt_Barrel_2Jets","goodEleSCPt_Barrel_2Jets",200,0,1000); h_goodEleSCPt_Barrel_2Jets->Sumw2();
   TH1F *h_goodEleSCPt_2SC2Jets = new TH1F ("goodEleSCPt_2SC2Jets","goodEleSCPt_2SC2Jets",200,0,1000); h_goodEleSCPt_2SC2Jets->Sumw2();
   TH1F *h_goodEleSCPt_Barrel_2SC2Jets = new TH1F ("goodEleSCPt_Barrel_2SC2Jets","goodEleSCPt_Barrel_2SC2Jets",200,0,1000); h_goodEleSCPt_Barrel_2SC2Jets->Sumw2();
   TH1F *h_goodEleSCEta_2SC2Jets = new TH1F ("goodEleSCEta_2SC2Jets","goodEleSCEta_2SC2Jets",100,-3.,3.); h_goodEleSCEta_2SC2Jets->Sumw2();
   TH1F *h_goodEle_ST = new TH1F ("goodEle_ST","goodEle_ST",220,-100,1000); h_goodEle_ST->Sumw2();
   TH1F *h_goodEle_SCEcalIso = new TH1F ("goodEle_SCEcalIso","goodEle_SCEcalIso",200,0,100); h_goodEle_SCEcalIso->Sumw2();
   TH2F *h_goodEle_SCEcalIso_PASS = new TH2F ("goodEle_SCEcalIso_PASS","goodEle_SCEcalIso_PASS",100,0,1000,1000,0,100); h_goodEle_SCEcalIso_PASS->Sumw2();
   TH1F *h_goodElePt = new TH1F ("goodElePt","goodElePt",200,0,1000); h_goodElePt->Sumw2();
   TH1F *h_looseEleSCPt = new TH1F ("looseEleSCPt","looseEleSCPt",200,0,1000); h_looseEleSCPt->Sumw2();
   TH1F *h_looseElePt = new TH1F ("looseElePt","looseElePt",200,0,1000); h_looseElePt->Sumw2();
   TH1F *h_goodEleSCPt_PASS = new TH1F ("goodEleSCPt_PASS","goodEleSCPt_PASS",200,0,1000); h_goodEleSCPt_PASS->Sumw2();
   TH1F *h_goodEleSCPt_PASSMee = new TH1F ("goodEleSCPt_PASSMee","goodEleSCPt_PASSMee",200,0,1000); h_goodEleSCPt_PASSMee->Sumw2();
   TH1F *h_goodSCPt = new TH1F ("goodSCPt","goodSCPt",200,0,1000); h_goodSCPt->Sumw2();
   TH1F *h_goodSCPt_Barrel = new TH1F ("goodSCPt_Barrel","goodSCPt_Barrel",200,0,1000); h_goodSCPt_Barrel->Sumw2();
   TH1F *h_goodSCEta = new TH1F ("goodSCEta","goodSCEta",100,-3.,3.); h_goodSCEta->Sumw2();
   TH1F *h_goodSCPt_Barrel_2SC = new TH1F ("goodSCPt_Barrel_2SC","goodSCPt_Barrel_2SC",200,0,1000); h_goodSCPt_Barrel_2SC->Sumw2();
   TH1F *h_goodSCPt_Barrel_2Jets = new TH1F ("goodSCPt_Barrel_2Jets","goodSCPt_Barrel_2Jets",200,0,1000); h_goodSCPt_Barrel_2Jets->Sumw2();
   TH1F *h_goodSCPt_2SC2Jets = new TH1F ("goodSCPt_2SC2Jets","goodSCPt_2SC2Jets",200,0,1000); h_goodSCPt_2SC2Jets->Sumw2();
   TH1F *h_goodSCPt_Barrel_2SC2Jets = new TH1F ("goodSCPt_Barrel_2SC2Jets","goodSCPt_Barrel_2SC2Jets",200,0,1000); h_goodSCPt_Barrel_2SC2Jets->Sumw2();
   TH1F *h_goodSCEta_2SC2Jets = new TH1F ("goodSCEta_2SC2Jets","goodSCEta_2SC2Jets",100,-3.,3.); h_goodSCEta_2SC2Jets->Sumw2();
   TH1F *h_goodSC_ST = new TH1F ("goodSC_ST","goodSC_ST",220,-100,1000); h_goodSC_ST->Sumw2();
   TH1F *h_goodSCPt_PASS = new TH1F ("goodSCPt_PASS","goodSCPt_PASS",200,0,1000); h_goodSCPt_PASS->Sumw2();
   TH1F *h_goodSCPt_PASSMee = new TH1F ("goodSCPt_PASSMee","goodSCPt_PASSMee",200,0,1000); h_goodSCPt_PASSMee->Sumw2();
   TH1F *h_goodSC_EcalIso = new TH1F ("goodSC_EcalIso","goodSC_EcalIso",200,0,100); h_goodSC_EcalIso->Sumw2();
   TH1F *h_goodSC_EcalIso_PASS = new TH1F ("goodSC_EcalIso_PASS","goodSC_EcalIso_PASS",200,0,1000); h_goodSC_EcalIso_PASS->Sumw2();

   TH1F *h_Mee_4obj = new TH1F ("Mee_4obj","Mee_4obj",100,0,1000); h_Mee_4obj->Sumw2();
   TH1F *h_dPhi_SS_MeeCut = new TH1F ("dPhi_SS_MeeCut","dPhi_SS_MeeCut",100,0,6.3); h_dPhi_SS_MeeCut->Sumw2();
   TH1F *h_dR_SS_MeeCut = new TH1F ("dR_SS_MeeCut","dR_SS_MeeCut",100,0,5.0); h_dR_SS_MeeCut->Sumw2();
   TH1F *h_dPhi_SJ_MeeCut = new TH1F ("dPhi_SJ_MeeCut","dPhi_SJ_MeeCut",100,0,6.3); h_dPhi_SJ_MeeCut->Sumw2();
   TH1F *h_dR_SJ_MeeCut = new TH1F ("dR_SJ_MeeCut","dR_SJ_MeeCut",100,0,5.0); h_dR_SJ_MeeCut->Sumw2();
   TH1F *h_dPhi_SS_NoMeeCut = new TH1F ("dPhi_SS_NoMeeCut","dPhi_SS_NoMeeCut",100,0,6.3); h_dPhi_SS_NoMeeCut->Sumw2();
   TH1F *h_dR_SS_NoMeeCut = new TH1F ("dR_SS_NoMeeCut","dR_SS_NoMeeCut",100,0,5.0); h_dR_SS_NoMeeCut->Sumw2();
   TH1F *h_dPhi_SJ_NoMeeCut = new TH1F ("dPhi_SJ_NoMeeCut","dPhi_SJ_NoMeeCut",100,0,6.3); h_dPhi_SJ_NoMeeCut->Sumw2();
   TH1F *h_dR_SJ_NoMeeCut = new TH1F ("dR_SJ_NoMeeCut","dR_SJ_NoMeeCut",100,0,5.0); h_dR_SJ_NoMeeCut->Sumw2();

   /////////initialize variables

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

   ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
   ////// If the root version is updated and rootNtupleClass regenerated,     /////
   ////// these lines may need to be updated.                                 /////    
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //for (Long64_t jentry=0; jentry<1000000;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry < 10 || jentry%100000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     // if (Cut(ientry) < 0) continue;

     ////////////////////// User's code starts here ///////////////////////

     ///Stuff to be done every event


     //cout << "Electrons" << endl;

     //## Electrons
     vector<int> v_idx_ele_all;
     vector<int> v_idx_ele_PtCut;
     vector<int> v_idx_ele_PtCut_ID_ISO_noOverlap;

     int eleIDType = getPreCutValue1("eleIDType");

    for(int iele=0;iele<eleCount;iele++)
       {
	 //no cut on reco electrons
	 v_idx_ele_all.push_back(iele);

	 //pT pre-cut on ele
	 if ( elePt[iele] < getPreCutValue1("ele_PtCut") ) continue;
	 
	 v_idx_ele_PtCut.push_back(iele);
	 
	 //ID + ISO + NO overlap with good muons	 	
	 int eleID = elePassID[iele];
	 if ( (eleID & 1<< eleIDType) > 0 && eleOverlaps[iele]==0  ) 
	   {
	     v_idx_ele_PtCut_ID_ISO_noOverlap.push_back(iele);
	   }
	 
	 if ( (eleID & 1<< 0) > 0 && eleOverlaps[iele]==0  ) 
	   {
	     if (eleSCPt[iele]>50) h_looseEleSCPt->Fill(eleSCPt[iele]);
	     if (eleSCPt[iele]>50) h_looseElePt->Fill(elePt[iele]);
	   }
	 
       } //loop over electrons     
     
    //////// Fill SC histos

     vector<int> v_idx_sc_iso;

     ///Find two highest Pt SC, since they are not ordered 
     float scHighestPt = -99;
     float scNextPt = -99;
     int idx_scHighestPt = -1;
     int idx_scNextPt = -1;
    for(int isc=0;isc<scCount;isc++){
      if ( scPt[isc] < getPreCutValue1("ele_PtCut") ) continue;
      if (scHoE[isc]>0.05) continue;
      if (scSigmaIEIE[isc]>0.0275) continue;
      double scEt = scPt[isc];
      if (scHEEPEcalIso[isc]> (6+(0.01*scEt))) continue;
      if (fabs(scEta[isc])<1.44 && scHEEPTrkIso[isc]>7.5) continue;;
      if (fabs(scEta[isc])>1.56 && scHEEPTrkIso[isc]>15) continue;
      if (scPt[isc]<scNextPt){
	scNextPt = scPt[isc];
	idx_scNextPt = isc;
      }
      if (scPt[isc]<scHighestPt){
	scNextPt = scHighestPt;
	idx_scNextPt = idx_scNextPt;
	scHighestPt = scPt[isc];
	idx_scHighestPt = isc;
      }
    }
    if (idx_scHighestPt != -1) v_idx_sc_iso.push_back(idx_scHighestPt);
    if (idx_scNextPt != -1)v_idx_sc_iso.push_back(idx_scNextPt);

    //////now fill in the rest of the sc in whatever order they are
    for(int isc=0;isc<scCount;isc++){
      if (isc==idx_scHighestPt || isc==idx_scNextPt) continue;
      if ( scPt[isc] < getPreCutValue1("ele_PtCut") ) continue;
      bool scPassHoE= false;
      bool scPassSigmaEE= false;
      bool scPassEcalIso= false;
      bool scPassTrkIso= false;
      if (scHoE[isc]<0.05) scPassHoE=true;
      if (scSigmaIEIE[isc]<0.0275) scPassSigmaEE=true;
      double scEt = scPt[isc];
      if (scHEEPEcalIso[isc]< (6+(0.01*scEt))) scPassEcalIso = true;
      if (fabs(scEta[isc])<1.44 && scHEEPTrkIso[isc]<7.5) scPassTrkIso = true;
      if (fabs(scEta[isc])>1.56 && scHEEPTrkIso[isc]<15) scPassTrkIso = true;
      if (scPassHoE && scPassSigmaEE && scPassEcalIso && scPassTrkIso ){
	v_idx_sc_iso.push_back(isc);
      }
    }
    h_NisoSC->Fill(v_idx_sc_iso.size());

     //cout << "Jets" << endl;

     //## Jets
     vector<int> v_idx_jet_all;
     vector<int> v_idx_jet_PtCut;
     vector<int> v_idx_jet_PtCut_noOverlapEle;
     for(int ijet=0;ijet<caloJetCount;ijet++)
       {
	 //no cut on reco jets
	 v_idx_jet_all.push_back(ijet);

	 //pT pre-cut on reco jets
	 if ( caloJetPt[ijet] < getPreCutValue1("jet_PtCut") ) continue;

	 v_idx_jet_PtCut.push_back(ijet);

	 ///// take the iso SC out of the jet collection
	 TVector3 jet_vec;
	 jet_vec.SetPtEtaPhi(caloJetPt[ijet],caloJetEta[ijet],caloJetPhi[ijet]);
	 float minDRsc = 99;
	 int idx_nearest_sc = -1;
	 for(int isc=0;isc<v_idx_sc_iso.size();isc++)
	     {
	       if (scPt[v_idx_sc_iso[isc]]<30) continue;
	       TVector3 sc_vec;
	       sc_vec.SetPtEtaPhi(scPt[v_idx_sc_iso[isc]],
			   scEta[v_idx_sc_iso[isc]],
			   scPhi[v_idx_sc_iso[isc]]);
	       float DR = jet_vec.DeltaR(sc_vec);
	       if (DR<minDRsc) {
		 minDRsc = DR;
		 idx_nearest_sc = isc;
	       }
	     }

	 //pT pre-cut + no overlaps with electrons
       	 //if( ( caloJetOverlaps[ijet] & 1 << eleIDType) == 0 && minDRsc>0.5 && (caloJetOverlaps[ijet] & 1 << 5)==0 )/* NO overlap with superclusters and electrons or muons*/  
       	 if( ( caloJetOverlaps[ijet] & 1 << eleIDType) == 0 )/* NO overlap with superclusters and electrons */  
	   {
	     v_idx_jet_PtCut_noOverlapEle.push_back(ijet);
	   }

	 //NOTE: We should verify that caloJetOverlaps match with the code above

       }   

     //find dR between isoSC and jets

	 for (int ijet=0; ijet<v_idx_jet_PtCut_noOverlapEle.size(); ijet++){
	   if (ijet>1) break;  // only care about two leading jets
	   TVector3 jet_vec;
	   jet_vec.SetPtEtaPhi(caloJetPt[v_idx_jet_PtCut_noOverlapEle[ijet]],
				    caloJetEta[v_idx_jet_PtCut_noOverlapEle[ijet]],
				    caloJetPhi[v_idx_jet_PtCut_noOverlapEle[ijet]]);
	   float minDR = 99;
	   int idx_nearest_sc = -1;
	   for(int isc=0;isc<v_idx_sc_iso.size();isc++)
	     {
	       if (isc>1) break; //only care about two leading SC
	       TVector3 sc_vec;
	       sc_vec.SetPtEtaPhi(scPt[v_idx_sc_iso[isc]],
			   scEta[v_idx_sc_iso[isc]],
			   scPhi[v_idx_sc_iso[isc]]);
	       float DR = jet_vec.DeltaR(sc_vec);
	       if (DR<minDR) {
		 minDR = DR;
		 idx_nearest_sc = isc;
	       }
	     }
	   if (minDR!=99) h_dR_JetSC->Fill(minDR);
	   if ((minDR!=99)&&(v_idx_jet_PtCut_noOverlapEle.size()>1)) h_dR_JetSC_2Jets->Fill(minDR);
	   if (idx_nearest_sc !=-1) h_dR_JetSC_EcalIso->Fill(minDR,scHEEPEcalIso[v_idx_sc_iso[idx_nearest_sc]]);
	 }

     // Set the evaluation of the cuts to false and clear the variable values and filled status
     resetCuts();
     
     //cout << "nEle" << endl;

     //## nEle
     fillVariableWithValue( "nEle_all", v_idx_ele_all.size() ) ;
     fillVariableWithValue( "nEle_PtCut", v_idx_ele_PtCut.size() ) ;
     fillVariableWithValue( "nEle_PtCut_IDISO_noOvrlp", v_idx_ele_PtCut_ID_ISO_noOverlap.size() ) ;

     //cout << "nJet" << endl;

     //## nJet
     fillVariableWithValue( "nJet_all", v_idx_jet_all.size() ) ;
     fillVariableWithValue( "nJet_PtCut", v_idx_jet_PtCut.size() ) ;
     fillVariableWithValue( "nJet_PtCut_noOvrlpEle", v_idx_jet_PtCut_noOverlapEle.size() ) ;


     //cout << "1st Ele" << endl;
     //## 1st ele
     double MT=-999;
     if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stEle_IDISO_NoOvrlp", elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] );
	 fillVariableWithValue( "Eta1stEle_IDISO_NoOvrlp", eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] );
	 fillVariableWithValue( "mEta1stEle_IDISO_NoOvrlp", fabs(eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[0]]) );
       }

      if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() >= 2 ) 
       {
	 fillVariableWithValue( "Pt2ndEle_IDISO_NoOvrlp", elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[1]] );
	 fillVariableWithValue( "Eta2ndEle_IDISO_NoOvrlp", eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[1]] );
	 fillVariableWithValue( "mEta2ndEle_IDISO_NoOvrlp", fabs(eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[1]]) );
       }

    //cout << "1st Jet" << endl;
     //## 1st jet
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]] );
	 fillVariableWithValue( "Eta1stJet_noOvrlpEle", caloJetEta[v_idx_jet_PtCut_noOverlapEle[0]] );
	 fillVariableWithValue( "mEta1stJet_noOvrlpEle", fabs(caloJetEta[v_idx_jet_PtCut_noOverlapEle[0]]) );
       }


     //cout << "2nd Jet" << endl;
     //## 2nd jet
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 2 ) 
       {
	 fillVariableWithValue( "Pt2ndJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]] );
	 fillVariableWithValue( "Eta2ndJet_noOvrlpEle", caloJetEta[v_idx_jet_PtCut_noOverlapEle[1]] );
	 fillVariableWithValue( "mEta2ndJet_noOvrlpEle", fabs(caloJetEta[v_idx_jet_PtCut_noOverlapEle[1]]) );
       }

     //## define "2ele" and "2jets" booleans
     bool TwoEle=false;
     bool TwoSC=false;
     bool TwoJets=false;
     if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() >= 2 ) TwoEle = true;
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 2 ) TwoJets = true;
     if( v_idx_sc_iso.size()>= 2) TwoSC = true;

     //cout << "ST" << endl;

     //## ST
     double calc_sT=-99.; 
     if ( (TwoSC) && (TwoJets) ) 
       {
	 calc_sT = 
	   scPt[v_idx_sc_iso[0]]
	   + scPt[v_idx_sc_iso[1]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]];
	 fillVariableWithValue("sT", calc_sT);
       }

     //cout << "Mee" << endl;

     double MassEE = -99;
     if (TwoSC)
       {
 	 TLorentzVector ele1, ele2, ee;
	 ele1.SetPtEtaPhiM(scPt[v_idx_sc_iso[0]],
			   scEta[v_idx_sc_iso[0]],
			   scPhi[v_idx_sc_iso[0]],0);
	 ele2.SetPtEtaPhiM(scPt[v_idx_sc_iso[1]],
			   scEta[v_idx_sc_iso[1]],
			   scPhi[v_idx_sc_iso[1]],0);
	 ee = ele1+ele2;
	 fillVariableWithValue("Mee", ee.M());
	 MassEE = ee.M();
       }

     //cout << "Mej" << endl;
     
     if ( (TwoSC) && (TwoJets) ) 
       {
 	 TLorentzVector sc1, sc2, scsc;
	 sc1.SetPtEtaPhiM(scPt[v_idx_sc_iso[0]],
			   scEta[v_idx_sc_iso[0]],
			   scPhi[v_idx_sc_iso[0]],0);
	 sc2.SetPtEtaPhiM(scPt[v_idx_sc_iso[1]],
			   scEta[v_idx_sc_iso[1]],
			   scPhi[v_idx_sc_iso[1]],0);
	 scsc = sc1+sc2;
	 h_Mee_4obj->Fill(scsc.M());
	 double dR_ScSc = sc1.DeltaR(sc2);
	 h_dR_SS_NoMeeCut->Fill(dR_ScSc);
	 double dPhi_ScSc = sc1.DeltaR(sc2);
	 h_dPhi_SS_NoMeeCut->Fill(dPhi_ScSc);

	 double jetMin1 = 99, jetMin2 = 99, jetPhi1 = 99, jetPhi2 = 99;
	 for (int ijet=0; ijet<v_idx_jet_PtCut_noOverlapEle.size(); ijet++){
	   TLorentzVector jet;
	   jet.SetPtEtaPhiM(caloJetPt[v_idx_jet_PtCut_noOverlapEle[ijet]],
			   caloJetEta[v_idx_jet_PtCut_noOverlapEle[ijet]],
			   caloJetPhi[v_idx_jet_PtCut_noOverlapEle[ijet]],0);
	   double dR_sc1_Jet = sc1.DeltaR(jet);
	   double dR_sc2_Jet = sc2.DeltaR(jet);
	   if (dR_sc1_Jet<jetMin1) {
	     jetMin1=dR_sc1_Jet;
	     jetPhi1 = sc1.DeltaPhi(jet);
	   }
	   if (dR_sc2_Jet<jetMin2) {
	     jetMin1=dR_sc2_Jet;
	     jetPhi2 = sc2.DeltaPhi(jet);
	   }
	 }	  
	 if (jetMin1<99) {
	   h_dR_SJ_NoMeeCut->Fill(jetMin1);
	   h_dPhi_SJ_NoMeeCut->Fill(jetPhi1);
	 }
	 if (jetMin2<99) {
	   h_dR_SJ_NoMeeCut->Fill(jetMin2);
	   h_dPhi_SJ_NoMeeCut->Fill(jetPhi2);
	 }

	 if (MassEE>80){
	   double dR_ScSc_Mee = sc1.DeltaR(sc2);
	   h_dR_SS_MeeCut->Fill(dR_ScSc_Mee);
	   double dPhi_ScSc_Mee = sc1.DeltaR(sc2);
	   h_dPhi_SS_MeeCut->Fill(dPhi_ScSc_Mee);
	   double jetMin1_Mee = 99, jetMin2_Mee = 99, jetPhi1_Mee = 99, jetPhi2_Mee = 99;
	   for (int ijet=0; ijet<v_idx_jet_PtCut_noOverlapEle.size(); ijet++){
	     TLorentzVector jet_Mee;
	     jet_Mee.SetPtEtaPhiM(caloJetPt[v_idx_jet_PtCut_noOverlapEle[ijet]],
			   caloJetEta[v_idx_jet_PtCut_noOverlapEle[ijet]],
			   caloJetPhi[v_idx_jet_PtCut_noOverlapEle[ijet]],0);
	     double dR_sc1_Jet_Mee = sc1.DeltaR(jet_Mee);
	     double dR_sc2_Jet_Mee = sc2.DeltaR(jet_Mee);
	     if (dR_sc1_Jet_Mee<jetMin1_Mee) {
	       jetMin1_Mee=dR_sc1_Jet_Mee;
	       jetPhi1_Mee= sc1.DeltaPhi(jet_Mee);
	     }
	     if (dR_sc2_Jet_Mee<jetMin2_Mee) {
	       jetMin1_Mee=dR_sc2_Jet_Mee;
	       jetPhi2_Mee = sc2.DeltaPhi(jet_Mee);
	     }
	   }	  
	   if (jetMin1_Mee<99) {
	     h_dR_SJ_MeeCut->Fill(jetMin1_Mee);
	     h_dPhi_SJ_MeeCut->Fill(jetPhi1_Mee);
	   }
	   if (jetMin2_Mee<99) {
	     h_dR_SJ_MeeCut->Fill(jetMin2_Mee);
	     h_dPhi_SJ_MeeCut->Fill(jetPhi2_Mee);
	   }


	   for(int iele=0;iele<v_idx_ele_PtCut_ID_ISO_noOverlap.size();iele++)
	     {
	       if ((eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]>50) && (fabs(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]])<1.45))
		 h_goodEleSCPt_PASSMee->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     }
	   for(int isc=0;isc<v_idx_sc_iso.size();isc++)
	     {
	       if (fabs(scEta[v_idx_sc_iso[isc]])<1.45)
		 h_goodSCPt_PASSMee->Fill(scPt[v_idx_sc_iso[isc]]);
	     }

	 }
       }
     
     
     //--------------------------------------------------
     
     // Evaluate cuts (but do not apply them)
     evaluateCuts();

     // Fill histograms and do analysis based on cut evaluation

     //// Fill fake rate pltos
	 for(int iele=0;iele<v_idx_ele_PtCut_ID_ISO_noOverlap.size();iele++)
	   {
	     if (eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]<50) continue;
	     h_goodEle_SCEcalIso->Fill(eleSCHEEPEcalIso[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     h_goodEleSCPt->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     h_goodEleSCEta->Fill(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     if (fabs(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]])<1.45) h_goodEleSCPt_Barrel->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     if (fabs(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]])<1.45 && TwoSC) h_goodEleSCPt_Barrel_2SC->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     if (fabs(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]])<1.45 && TwoJets) h_goodEleSCPt_Barrel_2Jets->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     if (fabs(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]])<1.45 && TwoSC && TwoJets) {
	       h_goodEleSCPt_Barrel_2SC2Jets->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	       h_goodEle_ST->Fill(calc_sT);
	     }
	     if (TwoSC && TwoJets) {
	       h_goodEleSCPt_2SC2Jets->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	       h_goodEleSCEta_2SC2Jets->Fill(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     }
	   }
	 for(int isc=0;isc<v_idx_sc_iso.size();isc++)
	   {
	     h_goodSC_EcalIso->Fill(scHEEPEcalIso[v_idx_sc_iso[isc]]);
	     h_goodSCPt->Fill(scPt[v_idx_sc_iso[isc]]);
	     h_goodSCEta->Fill(scEta[v_idx_sc_iso[isc]]);
	     if (fabs(scEta[v_idx_sc_iso[isc]])<1.45) h_goodSCPt_Barrel->Fill(scPt[v_idx_sc_iso[isc]]);
	     if (fabs(scEta[v_idx_sc_iso[isc]])<1.45 && TwoSC) h_goodSCPt_Barrel_2SC->Fill(scPt[v_idx_sc_iso[isc]]);
	     if (fabs(scEta[v_idx_sc_iso[isc]])<1.45 && TwoJets) h_goodSCPt_Barrel_2Jets->Fill(scPt[v_idx_sc_iso[isc]]);
	     if (fabs(scEta[v_idx_sc_iso[isc]])<1.45 && TwoSC && TwoJets) {
	       h_goodSCPt_Barrel_2SC2Jets->Fill(scPt[v_idx_sc_iso[isc]]);
	       h_goodSC_ST->Fill(calc_sT);
	     }
	     if (TwoSC && TwoJets) {
	       h_goodSCPt_2SC2Jets->Fill(scPt[v_idx_sc_iso[isc]]);
	       h_goodSCEta_2SC2Jets->Fill(scEta[v_idx_sc_iso[isc]]);
	     }
	   }


     if( passedCut("sT")){
	 for(int iele=0;iele<v_idx_ele_PtCut_ID_ISO_noOverlap.size();iele++)
	   {
	     if (eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]>50) h_goodEleSCPt_PASS->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	     if (eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]>50) h_goodEle_SCEcalIso_PASS->Fill(eleSCHEEPEcalIso[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
	   }
	 for(int isc=0;isc<v_idx_sc_iso.size();isc++)
	   {
	     h_goodSCPt_PASS->Fill(scPt[v_idx_sc_iso[isc]]);
	     h_goodSC_EcalIso_PASS->Fill(scHEEPEcalIso[v_idx_sc_iso[isc]]);
	   }
     }

//      if( passedCut("Mee") && passedCut("sT")){
// 	 for(int iele=0;iele<v_idx_ele_PtCut_ID_ISO_noOverlap.size();iele++)
// 	   {
// 	     if ((eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]>50) && (fabs(eleSCEta[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]])<1.45))
// 	       h_goodEleSCPt_PASSMee->Fill(eleSCPt[v_idx_ele_PtCut_ID_ISO_noOverlap[iele]]);
// 	   }
// 	 for(int isc=0;isc<v_idx_sc_iso.size();isc++)
// 	   {
// 	     if (fabs(scEta[v_idx_sc_iso[isc]])<1.45)
// 	       h_goodSCPt_PASSMee->Fill(scPt[v_idx_sc_iso[isc]]);
// 	   }

//      }



     ////////////////////// User's code ends here ///////////////////////

   } // End loop over events

   //////////write histos 
   h_Mej->Write();
   h_dR_JetSC->Write();
   h_dR_JetSC_2Jets->Write();
   h_dR_JetSC_EcalIso->Write();
   h_NisoSC->Write();
   h_goodEleSCPt->Write();
   h_goodEleSCPt_Barrel->Write();
   h_goodEleSCEta->Write();
   h_goodEleSCPt_Barrel_2SC->Write();
   h_goodEleSCPt_Barrel_2Jets->Write();
   h_goodEleSCPt_2SC2Jets->Write();
   h_goodEleSCPt_Barrel_2SC2Jets->Write();
   h_goodEleSCEta_2SC2Jets->Write();
   h_goodEle_ST->Write();
   h_goodEle_SCEcalIso->Write();
   h_goodEle_SCEcalIso_PASS->Write();
   h_goodEleSCPt_PASS->Write();
   h_goodEleSCPt_PASSMee->Write();
   h_goodSCPt->Write();
   h_goodSCPt_Barrel->Write();
   h_goodSCEta->Write();
   h_goodSCPt_Barrel_2SC->Write();
   h_goodSCPt_Barrel_2Jets->Write();
   h_goodSCPt_2SC2Jets->Write();
   h_goodSCPt_Barrel_2SC2Jets->Write();
   h_goodSCEta_2SC2Jets->Write();
   h_goodSC_ST->Write();
   h_goodSC_EcalIso->Write();
   h_goodSC_EcalIso_PASS->Write();
   h_goodSCPt_PASS->Write();
   h_goodSCPt_PASSMee->Write();
   h_looseEleSCPt->Write();
   h_looseElePt->Write();

   h_Mee_4obj->Write();
   h_dPhi_SS_MeeCut->Write();
   h_dR_SS_MeeCut->Write();
   h_dPhi_SJ_MeeCut->Write();
   h_dR_SJ_MeeCut->Write();
   h_dPhi_SS_NoMeeCut->Write();
   h_dR_SS_NoMeeCut->Write();
   h_dPhi_SJ_NoMeeCut->Write();
   h_dR_SJ_NoMeeCut->Write();

   std::cout << "analysisClass::Loop() ends" <<std::endl;   
}
