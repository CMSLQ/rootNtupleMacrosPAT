#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>

analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, TString * outputFileName, string * cutEfficFile)
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

   /////////initialize variables

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

   ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
   ////// If the root version is updated and rootNtupleClass regenerated,     /////
   ////// these lines may need to be updated.                                 /////    
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   //for (Long64_t jentry=0; jentry<10;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry < 10 || jentry%1000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     // if (Cut(ientry) < 0) continue;

     ////////////////////// User's code starts here ///////////////////////

     ///Stuff to be done every event

     //## HLT
     //      int PassTrig=0;
     //      int TrigBit1_1=int(getPreCutValue1("TriggerBits1"));
     //      int TrigBit1_2=int(getPreCutValue2("TriggerBits1"));
     //      int TrigBit1_3=int(getPreCutValue3("TriggerBits1"));
     //      int TrigBit1_4=int(getPreCutValue4("TriggerBits1"));
     
     //      if ( (HLTResults[TrigBit1_1]) || (HLTResults[TrigBit1_2]) )
     // 	 PassTrig=1;

     /////To print out list of trigger names:
     //      int results_index=0;
     //      string tmp="";
     //      for (int itrig=0;itrig<hltNamesLen;itrig++){
     //        if (HLTNames[itrig]==':') {
     // 	 cout << tmp << "   " << HLTResults[results_index] << endl;
     // 	 tmp.clear(); //reset temporary string of HLT name
     // 	 results_index++; //move to next HLT result
     //        }
     //        else tmp.push_back(HLTNames[itrig]) ;  //build up HLT name until ":" is reached, indicating end of name
     //      }

     //cout << "Electrons" << endl;

     //## Electrons
     vector<int> v_idx_ele_all;
     vector<int> v_idx_ele_PtCut;
     vector<int> v_idx_ele_PtCut_ID_ISO_noOverlap;

     for(int iele=0;iele<eleCount;iele++)
       {

	 //no cut on reco electrons
	 v_idx_ele_all.push_back(iele);

	 //pT pre-cut on ele
	 if ( elePt[iele] < getPreCutValue1("ele_PtCut") ) continue;
	 
	 v_idx_ele_PtCut.push_back(iele);
	 

	 // 	 //barrel-endcap definition
	 // 	 bool in_Barrel=false;
	 //          bool in_Endcap=false;
	 // 	 if( fabs(eleEta[iele]) < getPreCutValue1("eleEta_bar") )  in_Barrel=true;
	 // 	 if( ( fabs(eleEta[iele]) > getPreCutValue1("eleEta_end") )
	 // 	     && 
	 // 	     ( fabs(eleEta[iele]) < getPreCutValue2("eleEta_end") ) 
	 // 	     )  in_Endcap=true;

	 //ID + ISO + NO overlap with good muons	 	 
	 if ( elePassID[iele]==1 && elePassIso[iele]==1 && eleHasOverlaps[iele]==0 ) 
	   {
	     v_idx_ele_PtCut_ID_ISO_noOverlap.push_back(iele);
	   }
	 
       } //loop over electrons     
     
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

	 // 	 //Disambiguation of electrons from jets
	 // 	 float minDeltaR=9999;
	 // 	 TVector3 jet_vec;
	 // 	 jet_vec.SetPtEtaPhi(caloJetPt[ijet],caloJetEta[ijet],caloJetPhi[ijet]);
	 // 	 for (int i=0; i < v_idx_ele_final.size(); i++){
	 // 	   TVector3 ele_vec;
	 // 	   ele_vec.SetPtEtaPhi(elePt[v_idx_ele_final[i]],eleEta[v_idx_ele_final[i]],elePhi[v_idx_ele_final[i]]);
	 // 	   double distance = jet_vec.DeltaR(ele_vec);
	 // 	   if (distance<minDeltaR) minDeltaR=distance;
	 //  	 }
	 // 	 if ( minDeltaR > deltaR_minCut )  v_idx_jet_final.push_back(ijet);

	 //pT pre-cut + no overlaps with electrons
	 if( caloJetHasOverlaps[ijet]!=1 && caloJetHasOverlaps[ijet]!=3 )
	   v_idx_jet_PtCut_noOverlapEle.push_back(ijet);

	 //NOTE: We should verify that caloJetHasOverlaps match with the code above

       }     


     //## Muons
     vector<int> v_idx_muon_all;
     vector<int> v_idx_muon_PtCut;
     vector<int> v_idx_muon_PtCut_ID_ISO;

     for(int imuon=0;imuon<muonCount;imuon++)
       {
	 //no cut on reco muons
	 v_idx_muon_all.push_back(imuon);

	 //pT pre-cut on ele
	 if ( muonPt[imuon] < getPreCutValue1("muon_PtCut") ) continue;
	 
	 v_idx_muon_PtCut.push_back(imuon);

	 //ID + ISO
	 if ( muonPassIso[imuon]==1 && muonPassID[imuon]==1)
	   v_idx_muon_PtCut_ID_ISO.push_back(imuon);

	 // 	 //barrel-endcap definition
	 // 	 bool in_Barrel=false;
	 //          bool in_Endcap=false;
	 // 	 if( fabs(muonEta[imuon]) < getPreCutValue1("muonEta_bar") )  in_Barrel=true;
	 // 	 if( ( fabs(muonEta[imuon]) > getPreCutValue1("muonEta_end") )
	 // 	     && 
	 // 	     ( fabs(muonEta[imuon]) < getPreCutValue2("muonEta_end") ) 
	 // 	     )  in_Endcap=true;
	 
       }// end loop over muons


     // Set the evaluation of the cuts to false and clear the variable values and filled status
     resetCuts();
     
     // Set the value of the variableNames listed in the cutFile to their current value

     //cout << "HLT" << endl;

     //## HLT
     //fillVariableWithValue( "HLT", PassTrig ) ;

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


     //cout << "nMuon" << endl;

     //## nMuon 
     fillVariableWithValue( "nMuon_all", v_idx_muon_all.size() ) ;
     fillVariableWithValue( "nMuon_PtCut", v_idx_muon_PtCut.size() ) ;
     fillVariableWithValue( "nMuon_PtCut_IDISO", v_idx_muon_PtCut_ID_ISO.size() ) ;


     //cout << "1st Ele" << endl;
     //## 1st ele
     if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stEle_IDISO_NoOvrlp", elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] );
	 fillVariableWithValue( "Eta1stEle_IDISO_NoOvrlp", eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] );

	 // DeltaPhi - MET vs 1st ele
	 TVector2 v_MET;
	 TVector2 v_ele;
	 v_MET.SetMagPhi(1,caloMETPhi);
	 v_ele.SetMagPhi(1,elePhi[v_idx_ele_PtCut_ID_ISO_noOverlap[0]]);	 
	 float deltaphi = v_MET.DeltaPhi(v_ele);
	 //fillVariableWithValue( "DeltaPhiMETEle", fabs(deltaphi) );

	 // transverse mass
	 double MT = sqrt(2 * elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] * caloMET * (1 - cos(deltaphi)) );
	 fillVariableWithValue( "MT", MT);

       }

     //cout << "1st Jet" << endl;
     //## 1st jet
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]] );
	 fillVariableWithValue( "Eta1stJet_noOvrlpEle", caloJetEta[v_idx_jet_PtCut_noOverlapEle[0]] );

	 // 	 //DeltaPhi - MET vs 1st jet
	 // 	 TVector2 v_MET;
	 // 	 TVector2 v_jet;
	 // 	 v_MET.SetMagPhi(1,METPhi);
	 // 	 v_jet.SetMagPhi(1,caloJetPhi[v_idx_jet_PtCut_noOverlapEle[0]]);
	 // 	 float deltaphi = v_MET.DeltaPhi(v_jet);
	 // 	 fillVariableWithValue( "DeltaPhiMET1stJet", fabs(deltaphi) );
       }


     //cout << "2nd Jet" << endl;
     //## 2nd jet
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 2 ) 
       {
	 fillVariableWithValue( "Pt2ndJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]] );
	 fillVariableWithValue( "Eta2ndJet_noOvrlpEle", caloJetEta[v_idx_jet_PtCut_noOverlapEle[1]] );

	 // 	 //DeltaPhi - MET vs 2nd jet
	 // 	 TVector2 v_MET;
	 // 	 TVector2 v_jet;
	 // 	 v_MET.SetMagPhi(1,METPhi);
	 // 	 v_jet.SetMagPhi(1,caloJetPhi[v_idx_jet_PtCut_noOverlapEle[1]]);	 
	 // 	 float deltaphi = v_MET.DeltaPhi(v_jet);
	 // 	 fillVariableWithValue( "DeltaPhiMET2ndJet", fabs(deltaphi) );

       }

     //## define "2ele" and "2jets" booleans
     bool OneEle=false;
     bool TwoJets=false;
     if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() == 1 ) OneEle = true;
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 2 ) TwoJets = true;

     //cout << "ST" << endl;

     //## caloMET
     fillVariableWithValue("caloMET", caloMET);

     // DeltaPhiMET1stJet     0.35	   +inf			-		-		6	100 -4	4	
     // DeltaPhiMET2ndJet     0.35	   +inf			-		-		6	100 -4	4	
     // DeltaPhiMETEle	      0.7	   +inf			-		-		6	100 -4	4	

     //## ST
     if ( (OneEle) && (TwoJets) ) 
       {
	 double calc_sT = 
	   elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]]
	   + caloMET;
	 fillVariableWithValue("sT", calc_sT);
       }

     //cout << "Mej" << endl;


     //## Mej 
     double M1, M2 = -999;
     if ( (OneEle) && (TwoJets) ) 
       {
 	 TLorentzVector jet1, jet2, ele1;
	 ele1.SetPtEtaPhiM(elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]],
			   eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[0]],
			   elePhi[v_idx_ele_PtCut_ID_ISO_noOverlap[0]],0);
	 jet1.SetPtEtaPhiM(caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]],
			   caloJetEta[v_idx_jet_PtCut_noOverlapEle[0]],
			   caloJetPhi[v_idx_jet_PtCut_noOverlapEle[0]],0);
	 jet2.SetPtEtaPhiM(caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]],
			   caloJetEta[v_idx_jet_PtCut_noOverlapEle[1]],
			   caloJetPhi[v_idx_jet_PtCut_noOverlapEle[1]],0);
	 TLorentzVector jet1ele1, jet2ele1;
	 jet1ele1 = jet1 + ele1;
	 jet2ele1 = jet2 + ele1;
	 M1 = jet1ele1.M();
	 M2 = jet2ele1.M();

	 if(M1>M2)
	   {
	     fillVariableWithValue("MejMax", M1);	       
	     fillVariableWithValue("MejMin", M2);
	   }
	 else
	   {
	     fillVariableWithValue("MejMax", M2);	       
	     fillVariableWithValue("MejMin", M1);
	   }
	 
       }

     
     //--------------------------------------------------

     // Evaluate cuts (but do not apply them)
     evaluateCuts();

     // Fill histograms and do analysis based on cut evaluation

     if( passedCut("all") )
       {
	 h_Mej->Fill(M1);
	 h_Mej->Fill(M2);
       }
     
     // reject events that did not pass level 0 cuts
     // if( !passedCut("0") ) continue;
     // ......
     
     // reject events that did not pass level 1 cuts
     // if( !passedCut("1") ) continue;
     // ......

     // reject events that did not pass the full cut list
     // if( !passedCut("all") ) continue;
     // ......



     ////////////////////// User's code ends here ///////////////////////

   } // End loop over events

   //////////write histos 
   h_Mej->Write();

   std::cout << "analysisClass::Loop() ends" <<std::endl;   
}
