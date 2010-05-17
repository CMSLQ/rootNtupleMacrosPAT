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
   TH1F *h_probPt1stSc = new TH1F ("probPt1stSc","probPt1stSc",200,0,1000);  h_probPt1stSc->Sumw2();  //N events based on fake rate
   TH1F *h_matchedPt1stSc = new TH1F ("matchedPt1stSc","matchedPt1stSc",200,0,1000);  h_matchedPt1stSc->Sumw2();  //N events with at least 1 HEEP ele
   TH1F *h_probSt = new TH1F ("probSt","probSt",200,0,1000);  h_probSt->Sumw2();  //N events based on fake rate
   TH1F *h_matchedSt = new TH1F ("matchedSt","matchedSt",200,0,1000);  h_matchedSt->Sumw2();  //N events with at least 1 HEEP ele
   TH1F *h_NeleHEEP = new TH1F ("NeleHEEP","NeleHEEP",4,-0.5,3.5);  h_NeleHEEP->Sumw2();
   TH1F *h_NscISO = new TH1F ("NscISO","NscISO",4,-0.5,3.5);  h_NscISO->Sumw2();
   TH1F *h_dRsc = new TH1F ("dRsc","dRsc",500,-0.01,4.99); h_dRsc->Sumw2();
//    TH2F *h2_Mej_MTnuj_good = new TH2F ("h2_Mej_MTnuj_good","h2_Mej_MTnuj_good",100,0,2000,100,0,2000);  
//    TH2F *h2_Mej_MTnuj_bad = new TH2F ("h2_Mej_MTnuj_bad","h2_Mej_MTnuj_bad",100,0,2000,100,0,2000);  
   TH1F *h_goodEleSCPt = new TH1F ("goodEleSCPt","goodEleSCPt",200,0,1000); h_goodEleSCPt->Sumw2();
   TH1F *h_HEEPallEta = new TH1F ("HEEPallEta","HEEPallEta",100,-3.,3.); h_HEEPallEta->Sumw2();
   TH1F *h_HEEPallPt = new TH1F ("HEEPallPt","HEEPallPt",200,0,1000); h_HEEPallPt->Sumw2();
   TH1F *h_HEEP_2SC_Pt = new TH1F ("HEEP_2SC_Pt","HEEP_2SC_Pt",200,0,1000); h_HEEP_2SC_Pt->Sumw2();
   TH1F *h_HEEP_2SC2Jets_Pt = new TH1F ("HEEP_2SC2Jets_Pt","HEEP_2SC2Jets_Pt",200,0,1000); h_HEEP_2SC2Jets_Pt->Sumw2();
   TH1F *h_HEEP_St_Pt = new TH1F ("HEEP_St_Pt","HEEP_St_Pt",200,0,1000); h_HEEP_St_Pt->Sumw2();
   TH1F *h_HEEP_Mee_St_Pt = new TH1F ("HEEP_Mee_St_Pt","HEEP_Mee_St_Pt",200,0,1000); h_HEEP_Mee_St_Pt->Sumw2();
   TH1F *h_HEEP_Mee_St_Eta_Pt = new TH1F ("HEEP_Mee_St_Eta_Pt","HEEP_Mee_St_Eta_Pt",200,0,1000); h_HEEP_Mee_St_Eta_Pt->Sumw2();
   TH1F *h_HEEP_All_Pt = new TH1F ("HEEP_All_Pt","HEEP_All_Pt",200,0,1000); h_HEEP_All_Pt->Sumw2();
   TH1F *h_HEEP_PassMee_St = new TH1F ("HEEP_PassMee_St","HEEP_PassMee_St",200,0,1000); h_HEEP_PassMee_St->Sumw2();
   TH1F *h_HEEP_Mee_Pt = new TH1F ("HEEP_Mee_Pt","HEEP_Mee_Pt",200,0,1000); h_HEEP_Mee_Pt->Sumw2();
   TH1F *h_goodSCPt = new TH1F ("goodSCPt","goodSCPt",200,0,1000); h_goodSCPt->Sumw2();

   TH1F *h_goodEleSCPt_Barrel_2SC2Jets = new TH1F ("goodEleSCPt_Barrel_2SC2Jets","goodEleSCPt_Barrel_2SC2Jets",200,0,1000); h_goodEleSCPt_Barrel_2SC2Jets->Sumw2();
   TH1F *h_goodSCPt_Barrel_2SC2Jets = new TH1F ("goodSCPt_Barrel_2SC2Jets","goodSCPt_Barrel_2SC2Jets",200,0,1000); h_goodSCPt_Barrel_2SC2Jets->Sumw2();
   TH1F *h_goodEleSCPt_Barrel_2SC2Jets_JetEta = new TH1F ("goodEleSCPt_Barrel_2SC2Jets_JetEta","goodEleSCPt_Barrel_2SC2Jets_JetEta",200,0,1000); h_goodEleSCPt_Barrel_2SC2Jets_JetEta->Sumw2();
   TH1F *h_goodSCPt_Barrel_2SC2Jets_JetEta = new TH1F ("goodSCPt_Barrel_2SC2Jets_JetEta","goodSCPt_Barrel_2SC2Jets_JetEta",200,0,1000); h_goodSCPt_Barrel_2SC2Jets_JetEta->Sumw2();

   /////////initialize variables

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

   ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
   ////// If the root version is updated and rootNtupleClass regenerated,     /////
   ////// these lines may need to be updated.                                 /////    
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //for (Long64_t jentry=0; jentry<1000;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry < 10 || jentry%10000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     // if (Cut(ientry) < 0) continue;

     ////////////////////// User's code starts here ///////////////////////

     ///Stuff to be done every event


     //cout << "Electrons" << endl;

     //## Electrons
     vector<int> v_idx_ele_all;
     vector<int> v_idx_ele_PtCut;
     vector<int> v_idx_ele_PtCut_final;

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
	 if ( (eleID & 1<< eleIDType) > 0  && eleOverlaps[iele]==0 ) 
	   {
	     v_idx_ele_PtCut_final.push_back(iele);
	     h_HEEPallPt->Fill(elePt[iele]);
	     h_HEEPallEta->Fill(eleEta[iele]);
	   }
	 
       } //loop over electrons     
     

    //## Superclusters
    vector<int> v_idx_sc_all;
    vector<int> v_idx_sc_PtCut;
    vector<int> v_idx_sc_iso;
    bool matchHEEP = false;

     ///Find two highest Pt SC, since they are not ordered 
     float scHighestPt = -99;
     float scNextPt = -99;
     int idx_scHighestPt = -1;
     int idx_scNextPt = -1;
    for(int isc=0;isc<scCount;isc++){
      if ( scPt[isc] < getPreCutValue1("sc_PtCut") ) continue;
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
    if (idx_scNextPt != -1) v_idx_sc_iso.push_back(idx_scNextPt);

    //////now fill in the rest of the sc in whatever order they are
    for(int isc=0;isc<scCount;isc++){
      if (isc==idx_scHighestPt || isc==idx_scNextPt) continue;
      if ( scPt[isc] < getPreCutValue1("sc_PtCut") ) continue;
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


     //## Jets
     vector<int> v_idx_jet_all;
     vector<int> v_idx_jet_PtCut;
     vector<int> v_idx_jet_PtCut_noOverlapSC;
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

	 //pT pre-cut + no overlaps with electrons or SC
	 if( ( caloJetOverlaps[ijet] & 1 << eleIDType) == 0  && minDRsc>0.5)/* NO overlap with electrons or SC */  
	   v_idx_jet_PtCut_noOverlapSC.push_back(ijet);

       }     


     // Set the evaluation of the cuts to false and clear the variable values and filled status
     resetCuts();
     
     // Set the value of the variableNames listed in the cutFile to their current value


     //## nEle
     fillVariableWithValue( "nSc_PtCut_Iso", v_idx_sc_iso.size() ) ;

     //cout << "nJet" << endl;

     //## nJet
     fillVariableWithValue( "nJet_PtCut_noOvrlpEle", v_idx_jet_PtCut_noOverlapSC.size() ) ;


     //cout << "1st Ele" << endl;
     //## 1st ele
     double MT=-999;
     if( v_idx_sc_iso.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stSc_Iso", scPt[v_idx_sc_iso[0]] );
	 fillVariableWithValue( "mEta1stSc_Iso", fabs(scEta[v_idx_sc_iso[0]]) );
       }

      if( v_idx_sc_iso.size() >= 2 ) 
       {
	 fillVariableWithValue( "Pt2ndSc_Iso", scPt[v_idx_sc_iso[1]] );
	 fillVariableWithValue( "mEta2ndSc_Iso", fabs(scEta[v_idx_sc_iso[1]]) );
       }

    //cout << "1st Jet" << endl;
     //## 1st jet
     if( v_idx_jet_PtCut_noOverlapSC.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapSC[0]] );
	 fillVariableWithValue( "mEta1stJet_noOvrlpEle", fabs(caloJetEta[v_idx_jet_PtCut_noOverlapSC[0]]) );
       }


     //cout << "2nd Jet" << endl;
     //## 2nd jet
     if( v_idx_jet_PtCut_noOverlapSC.size() >= 2 ) 
       {
	 fillVariableWithValue( "Pt2ndJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapSC[1]] );
	 fillVariableWithValue( "mEta2ndJet_noOvrlpEle", fabs(caloJetEta[v_idx_jet_PtCut_noOverlapSC[1]]) );
       }

     //## define "2ele" and "2jets" booleans
     bool TwoSc=false;
     bool TwoJets=false;
     if( v_idx_sc_iso.size() >= 2 ) TwoSc = true;
     if( v_idx_jet_PtCut_noOverlapSC.size() >= 2 ) TwoJets = true;

     //cout << "Mee" << endl;

     double MassEE = -99;
     if (TwoSc)
       {
 	 TLorentzVector sc1, sc2, ee;
	 sc1.SetPtEtaPhiM(scPt[v_idx_sc_iso[0]],
			   scEta[v_idx_sc_iso[0]],
			   scPhi[v_idx_sc_iso[0]],0);
	 sc2.SetPtEtaPhiM(scPt[v_idx_sc_iso[1]],
			   scEta[v_idx_sc_iso[1]],
			   scPhi[v_idx_sc_iso[1]],0);
	 ee = sc1+sc2;
	 fillVariableWithValue("Mee", ee.M());
	 MassEE = ee.M();

	 double sc_deltaR = sc1.DeltaR(sc2);
	 h_dRsc->Fill(sc_deltaR);
       }

     //cout << "ST" << endl;

     //## ST
     double calc_sT=-999.; 
     if ( (TwoSc) && (TwoJets) ) 
       {
	 calc_sT = 
	   scPt[v_idx_sc_iso[0]]
	   + scPt[v_idx_sc_iso[1]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapSC[0]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapSC[1]];
	 fillVariableWithValue("sT", calc_sT);

       }


     //--------------------------------------------------
     
     // Evaluate cuts (but do not apply them)
     evaluateCuts();

     // Fill histograms and do analysis based on cut evaluation
     for (int iele=0; iele<v_idx_ele_PtCut_final.size(); iele++){
       if (fabs(eleSCEta[v_idx_ele_PtCut_final[iele]])<1.45 && TwoSc && TwoJets) {
	       h_goodEleSCPt_Barrel_2SC2Jets->Fill(eleSCPt[v_idx_ele_PtCut_final[iele]]);
	       if (passedCut("mEta1stJet_noOvrlpEle") && passedCut ("mEta2ndJet_noOvrlpEle") )
		 h_goodEleSCPt_Barrel_2SC2Jets_JetEta->Fill(eleSCPt[v_idx_ele_PtCut_final[iele]]);
	     }

       if ( passedCut("nSc_PtCut_Iso") && passedCut("mEta1stSc_Iso") && passedCut("mEta2ndSc_Iso") ){
	   h_HEEP_2SC_Pt->Fill(elePt[v_idx_ele_PtCut_final[iele]]);
	   if ( passedCut("nJet_PtCut_noOvrlpEle") && passedCut("mEta1stJet_noOvrlpEle") && passedCut ("mEta2ndJet_noOvrlpEle") ) {
	     h_HEEP_2SC2Jets_Pt->Fill(elePt[v_idx_ele_PtCut_final[iele]]);
	     if ( passedCut("Mee") ){
	       h_HEEP_Mee_Pt->Fill(elePt[v_idx_ele_PtCut_final[iele]]);
	       h_HEEP_PassMee_St->Fill(calc_sT);
	       if ( passedCut("sT") )
		 h_HEEP_Mee_St_Pt->Fill(elePt[v_idx_ele_PtCut_final[iele]]);
	     }
	   }
       }

     for(int isc=0;isc<v_idx_sc_iso.size();isc++)
	   {
	     if (fabs(scEta[v_idx_sc_iso[isc]])<1.45 && TwoSc && TwoJets) {
	       h_goodSCPt_Barrel_2SC2Jets->Fill(scPt[v_idx_sc_iso[isc]]);
	       if (passedCut("mEta1stJet_noOvrlpEle") && passedCut ("mEta2ndJet_noOvrlpEle") )
		 h_goodSCPt_Barrel_2SC2Jets_JetEta->Fill(scPt[v_idx_sc_iso[isc]]);
	     }
	   }


     if ( passedCut("sT") )
	       h_HEEP_St_Pt->Fill(elePt[v_idx_ele_PtCut_final[iele]]);
     }

     if( passedCut("all") ) 
       {
	 for (int iele=0; iele<v_idx_ele_PtCut_final.size(); iele++){
	   h_HEEP_All_Pt->Fill(elePt[v_idx_ele_PtCut_final[iele]]);
	   h_matchedPt1stSc->Fill(eleSCPt[v_idx_ele_PtCut_final[iele]]);
	   h_matchedSt->Fill(calc_sT);
	 }

	 h_NeleHEEP->Fill(v_idx_ele_PtCut_final.size());
	 h_NscISO->Fill(v_idx_sc_iso.size());

	 double probSC1 = 0, probSC2 = 0;
	 if (fabs(scEta[v_idx_sc_iso[0]])<1.442) probSC1 = 0.0023;
	 if (fabs(scEta[v_idx_sc_iso[0]])>1.56) probSC1 = 0.05;
	 if (fabs(scEta[v_idx_sc_iso[1]])<1.442) probSC2 = 0.0023;
	 if (fabs(scEta[v_idx_sc_iso[1]])>1.56) probSC2 = 0.05;
      
// 	 probSC1 = -0.000308 + (0.0000448*scPt[v_idx_sc_iso[0]]);
// 	 probSC2 = -0.000308 + (0.0000448*scPt[v_idx_sc_iso[1]]);
// 	 double probSC1 = 0.01, probSC2 = 0.01;


	 h_probPt1stSc->Fill(scPt[v_idx_sc_iso[0]],probSC1+probSC2);
	 h_probSt->Fill(calc_sT,probSC1+probSC2);


	 ///////Calculate FakeRate based on events that pass

	 for (int iele=0; iele<v_idx_ele_PtCut_final.size(); iele++)
	   {
	     h_goodEleSCPt->Fill(eleSCPt[v_idx_ele_PtCut_final[iele]]);
	   }

	 for(int isc=0;isc<v_idx_sc_iso.size();isc++){
	   h_goodSCPt->Fill(scPt[v_idx_sc_iso[isc]]);
	 }

       }  //end if passedCut("all")


     ////////////////////// User's code ends here ///////////////////////

   } // End loop over events

   //////////write histos 
   h_Mej->Write();
   h_probPt1stSc->Write();
   h_matchedPt1stSc->Write();
   h_probSt->Write();
   h_matchedSt->Write();
   h_NeleHEEP->Write();
   h_NscISO->Write();
   h_dRsc->Write();
//    h2_Mej_MTnuj_good->Write();
//    h2_Mej_MTnuj_bad->Write();
   h_HEEPallPt->Write();
   h_HEEP_2SC_Pt->Write();
   h_HEEP_2SC2Jets_Pt->Write();
   h_HEEP_Mee_Pt->Write();
   h_HEEP_Mee_St_Pt->Write();
   h_HEEP_Mee_St_Eta_Pt->Write();
   h_HEEP_All_Pt->Write();
   h_HEEP_St_Pt->Write();
   h_HEEP_PassMee_St->Write();
   h_HEEPallEta->Write();
   h_goodEleSCPt->Write();
   h_goodSCPt->Write();

   h_goodEleSCPt_Barrel_2SC2Jets->Write();
   h_goodSCPt_Barrel_2SC2Jets->Write();
   h_goodEleSCPt_Barrel_2SC2Jets_JetEta->Write();
   h_goodSCPt_Barrel_2SC2Jets_JetEta->Write();


   std::cout << "analysisClass::Loop() ends" <<std::endl;   
}
