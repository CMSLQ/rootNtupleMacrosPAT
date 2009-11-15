#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>

int id_W_plus = 24;
int id_W_minus = -24;

int id_Ele_plus = -11;
int id_Ele_minus = 11;

int id_NeutrEle = 12;
int id_AntiNeutrEle = -12;


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
   //TH1F *h_Mej = new TH1F ("Mej","Mej",200,0,2000);  h_Mej->Sumw2();
   TH2F *h2_Mej_MTnuj_good = new TH2F ("h2_Mej_MTnuj_good","h2_Mej_MTnuj_good",100,0,2000,100,0,2000);  
   TH2F *h2_Mej_MTnuj_bad = new TH2F ("h2_Mej_MTnuj_bad","h2_Mej_MTnuj_bad",100,0,2000,100,0,2000);  

   //    TH1F *h_MT = new TH1F ("h_MT","h_MT",
   // 			  getHistoNBins("MT"),
   // 			  getHistoMin("MT"),
   // 			  getHistoMax("MT")
   // 			  );  

   int Nbins_pT = int(getPreCutValue1("bins_pT"));
   double min_pT = getPreCutValue2("bins_pT");
   double max_pT = getPreCutValue3("bins_pT");

   int Nbins_eta = int(getPreCutValue1("bins_eta"));
   double min_eta = getPreCutValue2("bins_eta");
   double max_eta = getPreCutValue3("bins_eta");

   //inclusive
   TH1F *h_W_minus_pT = new TH1F ("h_W_minus_pT","h_W_minus_pT",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_minus_eta = new TH1F ("h_W_minus_eta","h_W_minus_eta",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_pT = new TH1F ("h_W_plus_pT","h_W_plus_pT",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_plus_eta = new TH1F ("h_W_plus_eta","h_W_plus_eta",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_mass = new TH1F ("h_W_plus_mass","h_W_plus_mass",500,0,1000);  
   TH1F *h_W_minus_mass = new TH1F ("h_W_minus_mass","h_W_minus_mass",500,0,1000);  

   TH1F *h_genEle_minus_pT = new TH1F ("h_genEle_minus_pT","h_genEle_minus_pT",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_minus_eta = new TH1F ("h_genEle_minus_eta","h_genEle_minus_eta",Nbins_eta,min_eta,max_eta);  
   TH1F *h_genEle_plus_pT = new TH1F ("h_genEle_plus_pT","h_genEle_plus_pT",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_plus_eta = new TH1F ("h_genEle_plus_eta","h_genEle_plus_eta",Nbins_eta,min_eta,max_eta);  

   TH1F *h_Wasymmetry_WpT = new TH1F ("h_Wasymmetry_WpT","h_Wasymmetry_WpT",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_Weta = new TH1F ("h_Wasymmetry_Weta","h_Wasymmetry_Weta",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_genElepT = new TH1F ("h_Wasymmetry_genElepT","h_Wasymmetry_genElepT",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_genEleeta = new TH1F ("h_Wasymmetry_genEleeta","h_Wasymmetry_genEleeta",Nbins_eta,min_eta,max_eta);  

   //X+0j
   TH1F *h_W_minus_pT_0j = new TH1F ("h_W_minus_pT_0j","h_W_minus_pT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_minus_eta_0j = new TH1F ("h_W_minus_eta_0j","h_W_minus_eta_0j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_pT_0j = new TH1F ("h_W_plus_pT_0j","h_W_plus_pT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_plus_eta_0j = new TH1F ("h_W_plus_eta_0j","h_W_plus_eta_0j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_mass_0j = new TH1F ("h_W_plus_mass_0j","h_W_plus_mass_0j",500,0,1000);  
   TH1F *h_W_minus_mass_0j = new TH1F ("h_W_minus_mass_0j","h_W_minus_mass_0j",500,0,1000);  

   TH1F *h_ST_plus_0j = new TH1F ("h_ST_plus_0j","h_ST_plus_0j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_ST_minus_0j = new TH1F ("h_ST_minus_0j","h_ST_minus_0j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_plus_0j = new TH1F ("h_MT_plus_0j","h_MT_plus_0j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_minus_0j = new TH1F ("h_MT_minus_0j","h_MT_minus_0j",Nbins_pT,min_pT,max_pT); 

   TH1F *h_ST_plus_0j_reco = new TH1F ("h_ST_plus_0j_reco","h_ST_plus_0j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_ST_minus_0j_reco = new TH1F ("h_ST_minus_0j_reco","h_ST_minus_0j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_plus_0j_reco = new TH1F ("h_MT_plus_0j_reco","h_MT_plus_0j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_minus_0j_reco = new TH1F ("h_MT_minus_0j_reco","h_MT_minus_0j_reco",Nbins_pT,min_pT,max_pT); 

   TH1F *h_genEle_minus_pT_0j = new TH1F ("h_genEle_minus_pT_0j","h_genEle_minus_pT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_minus_eta_0j = new TH1F ("h_genEle_minus_eta_0j","h_genEle_minus_eta_0j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_genEle_plus_pT_0j = new TH1F ("h_genEle_plus_pT_0j","h_genEle_plus_pT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_plus_eta_0j = new TH1F ("h_genEle_plus_eta_0j","h_genEle_plus_eta_0j",Nbins_eta,min_eta,max_eta);  

   TH1F *h_Wasymmetry_WpT_0j = new TH1F ("h_Wasymmetry_WpT_0j","h_Wasymmetry_WpT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_Weta_0j = new TH1F ("h_Wasymmetry_Weta_0j","h_Wasymmetry_Weta_0j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_genElepT_0j = new TH1F ("h_Wasymmetry_genElepT_0j","h_Wasymmetry_genElepT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_genEleeta_0j = new TH1F ("h_Wasymmetry_genEleeta_0j","h_Wasymmetry_genEleeta_0j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_ST_0j = new TH1F ("h_Wasymmetry_ST_0j","h_Wasymmetry_ST_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_MT_0j = new TH1F ("h_Wasymmetry_MT_0j","h_Wasymmetry_MT_0j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_ST_0j_reco = new TH1F ("h_Wasymmetry_ST_0j_reco","h_Wasymmetry_ST_0j_reco",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_MT_0j_reco = new TH1F ("h_Wasymmetry_MT_0j_reco","h_Wasymmetry_MT_0j_reco",Nbins_pT,min_pT,max_pT);  

   //X+1j
   TH1F *h_W_minus_pT_1j = new TH1F ("h_W_minus_pT_1j","h_W_minus_pT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_minus_eta_1j = new TH1F ("h_W_minus_eta_1j","h_W_minus_eta_1j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_pT_1j = new TH1F ("h_W_plus_pT_1j","h_W_plus_pT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_plus_eta_1j = new TH1F ("h_W_plus_eta_1j","h_W_plus_eta_1j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_mass_1j = new TH1F ("h_W_plus_mass_1j","h_W_plus_mass_1j",500,0,1000);  
   TH1F *h_W_minus_mass_1j = new TH1F ("h_W_minus_mass_1j","h_W_minus_mass_1j",500,0,1000);  

   TH1F *h_ST_plus_1j = new TH1F ("h_ST_plus_1j","h_ST_plus_1j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_ST_minus_1j = new TH1F ("h_ST_minus_1j","h_ST_minus_1j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_plus_1j = new TH1F ("h_MT_plus_1j","h_MT_plus_1j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_minus_1j = new TH1F ("h_MT_minus_1j","h_MT_minus_1j",Nbins_pT,min_pT,max_pT); 

   TH1F *h_ST_plus_1j_reco = new TH1F ("h_ST_plus_1j_reco","h_ST_plus_1j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_ST_minus_1j_reco = new TH1F ("h_ST_minus_1j_reco","h_ST_minus_1j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_plus_1j_reco = new TH1F ("h_MT_plus_1j_reco","h_MT_plus_1j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_minus_1j_reco = new TH1F ("h_MT_minus_1j_reco","h_MT_minus_1j_reco",Nbins_pT,min_pT,max_pT); 

   TH1F *h_genEle_minus_pT_1j = new TH1F ("h_genEle_minus_pT_1j","h_genEle_minus_pT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_minus_eta_1j = new TH1F ("h_genEle_minus_eta_1j","h_genEle_minus_eta_1j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_genEle_plus_pT_1j = new TH1F ("h_genEle_plus_pT_1j","h_genEle_plus_pT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_plus_eta_1j = new TH1F ("h_genEle_plus_eta_1j","h_genEle_plus_eta_1j",Nbins_eta,min_eta,max_eta);  

   TH1F *h_Wasymmetry_WpT_1j = new TH1F ("h_Wasymmetry_WpT_1j","h_Wasymmetry_WpT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_Weta_1j = new TH1F ("h_Wasymmetry_Weta_1j","h_Wasymmetry_Weta_1j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_genElepT_1j = new TH1F ("h_Wasymmetry_genElepT_1j","h_Wasymmetry_genElepT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_genEleeta_1j = new TH1F ("h_Wasymmetry_genEleeta_1j","h_Wasymmetry_genEleeta_1j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_ST_1j = new TH1F ("h_Wasymmetry_ST_1j","h_Wasymmetry_ST_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_MT_1j = new TH1F ("h_Wasymmetry_MT_1j","h_Wasymmetry_MT_1j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_ST_1j_reco = new TH1F ("h_Wasymmetry_ST_1j_reco","h_Wasymmetry_ST_1j_reco",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_MT_1j_reco = new TH1F ("h_Wasymmetry_MT_1j_reco","h_Wasymmetry_MT_1j_reco",Nbins_pT,min_pT,max_pT);  

   //X+2j
   TH1F *h_W_minus_pT_2j = new TH1F ("h_W_minus_pT_2j","h_W_minus_pT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_minus_eta_2j = new TH1F ("h_W_minus_eta_2j","h_W_minus_eta_2j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_pT_2j = new TH1F ("h_W_plus_pT_2j","h_W_plus_pT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_W_plus_eta_2j = new TH1F ("h_W_plus_eta_2j","h_W_plus_eta_2j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_W_plus_mass_2j = new TH1F ("h_W_plus_mass_2j","h_W_plus_mass_2j",500,0,1000);  
   TH1F *h_W_minus_mass_2j = new TH1F ("h_W_minus_mass_2j","h_W_minus_mass_2j",500,0,1000);  

   TH1F *h_ST_plus_2j = new TH1F ("h_ST_plus_2j","h_ST_plus_2j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_ST_minus_2j = new TH1F ("h_ST_minus_2j","h_ST_minus_2j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_plus_2j = new TH1F ("h_MT_plus_2j","h_MT_plus_2j",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_minus_2j = new TH1F ("h_MT_minus_2j","h_MT_minus_2j",Nbins_pT,min_pT,max_pT); 

   TH1F *h_ST_plus_2j_reco = new TH1F ("h_ST_plus_2j_reco","h_ST_plus_2j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_ST_minus_2j_reco = new TH1F ("h_ST_minus_2j_reco","h_ST_minus_2j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_plus_2j_reco = new TH1F ("h_MT_plus_2j_reco","h_MT_plus_2j_reco",Nbins_pT,min_pT,max_pT); 
   TH1F *h_MT_minus_2j_reco = new TH1F ("h_MT_minus_2j_reco","h_MT_minus_2j_reco",Nbins_pT,min_pT,max_pT); 

   TH1F *h_genEle_minus_pT_2j = new TH1F ("h_genEle_minus_pT_2j","h_genEle_minus_pT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_minus_eta_2j = new TH1F ("h_genEle_minus_eta_2j","h_genEle_minus_eta_2j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_genEle_plus_pT_2j = new TH1F ("h_genEle_plus_pT_2j","h_genEle_plus_pT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_genEle_plus_eta_2j = new TH1F ("h_genEle_plus_eta_2j","h_genEle_plus_eta_2j",Nbins_eta,min_eta,max_eta);  

   TH1F *h_Wasymmetry_WpT_2j = new TH1F ("h_Wasymmetry_WpT_2j","h_Wasymmetry_WpT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_Weta_2j = new TH1F ("h_Wasymmetry_Weta_2j","h_Wasymmetry_Weta_2j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_genElepT_2j = new TH1F ("h_Wasymmetry_genElepT_2j","h_Wasymmetry_genElepT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_genEleeta_2j = new TH1F ("h_Wasymmetry_genEleeta_2j","h_Wasymmetry_genEleeta_2j",Nbins_eta,min_eta,max_eta);  
   TH1F *h_Wasymmetry_ST_2j = new TH1F ("h_Wasymmetry_ST_2j","h_Wasymmetry_ST_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_MT_2j = new TH1F ("h_Wasymmetry_MT_2j","h_Wasymmetry_MT_2j",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_ST_2j_reco = new TH1F ("h_Wasymmetry_ST_2j_reco","h_Wasymmetry_ST_2j_reco",Nbins_pT,min_pT,max_pT);  
   TH1F *h_Wasymmetry_MT_2j_reco = new TH1F ("h_Wasymmetry_MT_2j_reco","h_Wasymmetry_MT_2j_reco",Nbins_pT,min_pT,max_pT);  

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

     int eleIDType = int( getPreCutValue1("eleIDType") );

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

	 int eleID = elePassID[iele];

	 //ID + ISO + NO overlap with good muons	 	 
	 if ( (eleID & 1 << eleIDType ) > 0 
	      && elePassIso[iele]==1 
	      && eleOverlaps[iele]==0 ) 
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
	 if( (caloJetOverlaps[ijet] & 1 << eleIDType ) == 0 ) /* NO overlap with electrons */  
	   //&& (caloJetOverlaps[ijet] & 1 << 5) == 0 ) /* NO overlap with muons */   
	   {
	     v_idx_jet_PtCut_noOverlapEle.push_back(ijet);
	   }

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

     // DeltaPhiMET1stJet     0.35	   +inf			-		-		6	100 -4	4	
     // DeltaPhiMET2ndJet     0.35	   +inf			-		-		6	100 -4	4	
     // DeltaPhiMETEle	      0.7	   +inf			-		-		6	100 -4	4	

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
     double MT=-999;
     double mDeltaPhiMETEle = -999;
     if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stEle_IDISO_NoOvrlp", elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] );
	 fillVariableWithValue( "Eta1stEle_IDISO_NoOvrlp", eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] );
	 fillVariableWithValue( "mEta1stEle_IDISO_NoOvrlp", fabs(eleEta[v_idx_ele_PtCut_ID_ISO_noOverlap[0]]) );

	 // DeltaPhi - MET vs 1st ele
	 TVector2 v_MET;
	 TVector2 v_ele;
	 v_MET.SetMagPhi(1,caloMETPhi);
	 v_ele.SetMagPhi(1,elePhi[v_idx_ele_PtCut_ID_ISO_noOverlap[0]]);	 
	 float deltaphi = v_MET.DeltaPhi(v_ele);
	 fillVariableWithValue( "mDeltaPhiMETEle", fabs(deltaphi) );

	 mDeltaPhiMETEle = fabs(deltaphi);    

	 // transverse mass
	 MT = sqrt(2 * elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] * caloMET * (1 - cos(deltaphi)) );
	 fillVariableWithValue("MT", MT);

       }

     //cout << "1st Jet" << endl;
     //## 1st jet

     if( v_idx_jet_PtCut_noOverlapEle.size() >= 1 ) 
       {
	 fillVariableWithValue( "Pt1stJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]] );
	 fillVariableWithValue( "Eta1stJet_noOvrlpEle", caloJetEta[v_idx_jet_PtCut_noOverlapEle[0]] );
	 fillVariableWithValue( "mEta1stJet_noOvrlpEle", fabs(caloJetEta[v_idx_jet_PtCut_noOverlapEle[0]]) );

	 //DeltaPhi - MET vs 1st jet
	 TVector2 v_MET;
	 TVector2 v_jet;
	 v_MET.SetMagPhi(1,caloMETPhi);
	 v_jet.SetMagPhi(1,caloJetPhi[v_idx_jet_PtCut_noOverlapEle[0]]);
	 float deltaphi = v_MET.DeltaPhi(v_jet);
	 fillVariableWithValue( "mDeltaPhiMET1stJet", fabs(deltaphi) );
       }


     //cout << "2nd Jet" << endl;
     //## 2nd jet
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 2 ) 
       {
	 fillVariableWithValue( "Pt2ndJet_noOvrlpEle", caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]] );
	 fillVariableWithValue( "Eta2ndJet_noOvrlpEle", caloJetEta[v_idx_jet_PtCut_noOverlapEle[1]] );
	 fillVariableWithValue( "mEta2ndJet_noOvrlpEle", fabs(caloJetEta[v_idx_jet_PtCut_noOverlapEle[1]]) );

	 //DeltaPhi - MET vs 2nd jet
	 TVector2 v_MET;
	 TVector2 v_jet;
	 v_MET.SetMagPhi(1,caloMETPhi);
	 v_jet.SetMagPhi(1,caloJetPhi[v_idx_jet_PtCut_noOverlapEle[1]]);
	 float deltaphi = v_MET.DeltaPhi(v_jet);
	 fillVariableWithValue( "mDeltaPhiMET2ndJet", fabs(deltaphi) );
       }

     //## define "2ele" and "2jets" booleans
     bool OneEle=false;
     bool TwoJets=false;
     if( v_idx_ele_PtCut_ID_ISO_noOverlap.size() == 1 ) OneEle = true;
     if( v_idx_jet_PtCut_noOverlapEle.size() >= 2 ) TwoJets = true;

     //cout << "ST" << endl;

     //## caloMET
     fillVariableWithValue("caloMET", caloMET);

     //## ST
     double calc_sT=-999.; 
     if ( (OneEle) && (TwoJets) ) 
       {
	 calc_sT = 
	   elePt[v_idx_ele_PtCut_ID_ISO_noOverlap[0]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]]
	   + caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]]
	   + caloMET;
	 fillVariableWithValue("sT", calc_sT);
       }

     //cout << "Mej" << endl;
     /*
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
     */
     
     //cout << "Mej, MTnuj" << endl;

     //## Mej , MTnuj
     double Me1j1, Me1j2, MTn1j1, MTn1j2 = -999;
     double diff_e1j1_n1j2, diff_e1j2_n1j1;
     //used later for 2D histograms
     double good_Mej, good_MTnuj = -999;
     double bad_Mej, bad_MTnuj = -999;
     if ( (OneEle) && (TwoJets) )  
       {
	 //invariant mass electron-jet
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
	 TLorentzVector jet1ele1, jet2ele1, jet1nu1, jet2nu1;
	 jet1ele1 = jet1 + ele1;
	 jet2ele1 = jet2 + ele1;
	 Me1j1 = jet1ele1.M();
	 Me1j2 = jet2ele1.M();
	 
	 //transverse mass neutrino-jet
	 TVector2 v_MET;
	 TVector2 v_jet1;
	 TVector2 v_jet2;
	 v_MET.SetMagPhi(1,caloMETPhi);
	 v_jet1.SetMagPhi(1,caloJetPhi[v_idx_jet_PtCut_noOverlapEle[0]]);
	 v_jet2.SetMagPhi(1,caloJetPhi[v_idx_jet_PtCut_noOverlapEle[1]]);
	 float deltaphi1 = v_MET.DeltaPhi(v_jet1);
	 float deltaphi2 = v_MET.DeltaPhi(v_jet2);
	 double MTn1j1 = sqrt(2 * caloMET * caloJetPt[v_idx_jet_PtCut_noOverlapEle[0]] * (1 - cos(deltaphi1)) );
	 double MTn1j2 = sqrt(2 * caloMET * caloJetPt[v_idx_jet_PtCut_noOverlapEle[1]] * (1 - cos(deltaphi2)) );

	 //cout << "Me1j1:  " << Me1j1 << "  Me1j2:  " << Me1j2 << "  MTn1j1:  " << MTn1j1 << "  MTn1j2:  " << MTn1j2 << endl;

	 diff_e1j1_n1j2 = fabs( Me1j1 - MTn1j2 );
	 diff_e1j2_n1j1 = fabs( Me1j2 - MTn1j1);

	 if ( diff_e1j1_n1j2 < diff_e1j2_n1j1 ) 
	   {
	     fillVariableWithValue("Mej", Me1j1);	       
	     fillVariableWithValue("MTnuj", MTn1j2);

	     //used later for 2D histograms
	     good_Mej = Me1j1;
	     good_MTnuj = MTn1j2;
	     bad_Mej = Me1j2; 
	     bad_MTnuj = MTn1j1;

	   }
	 else 
	   {
	     fillVariableWithValue("Mej", Me1j2);	       
	     fillVariableWithValue("MTnuj", MTn1j1);

	     //used later for 2D histograms
	     good_Mej = Me1j2; 
	     good_MTnuj = MTn1j1;
	     bad_Mej = Me1j1;
	     bad_MTnuj = MTn1j2;

	   }

       }
     
     
     //--------------------------------------------------
     
     // Evaluate cuts (but do not apply them)
     evaluateCuts();

     // Fill histograms and do analysis based on cut evaluation


     if( passedCut("all") ) 
       {
	 h2_Mej_MTnuj_good->Fill(good_Mej,good_MTnuj);
	 h2_Mej_MTnuj_bad->Fill(bad_Mej,bad_MTnuj);

	 // 	 //print out
	 // 	 cout << "jentry" << jentry << endl;
	 // 	 Show(jentry);	 
	 // 	 cout << "calc_sT: " << calc_sT << endl;
	 // 	 cout << "MT: " << MT << endl;

       }


     // Get electron and neutrino from W at gen level

     TLorentzVector leptonPlus;
     TLorentzVector leptonMinus;
     TLorentzVector neutrino;
     TLorentzVector antineutrino;
     TLorentzVector WPlus;
     TLorentzVector WMinus;
     
     bool isLeptonPlus=false;
     bool isLeptonMinus=false;
     bool isNeutrino=false;
     bool isAntiNeutrino=false;

     for (int genp = 0; genp<GenParticleCount; genp++)
       {	

	 //print out
	 /* 
	 cout << "W index = " << GenParticlePdgId[genp] 
	      << "  with status = " << GenParticleStatus[genp] << endl;		     
	 
	 cout << "W has: " << GenParticleNumDaught[genp] << " daughters that are.." << endl;	     
	 
	 for (int genp1 = 0; genp1<GenParticleCount; genp1++)
	   {
	     if(GenParticleMotherIndex[genp1]==genp)
	       {
		 cout << "dauther index = " << GenParticlePdgId[genp1] 
		      << "  with status = " << GenParticleStatus[genp1] << endl;		     
	       }
	   }	     
	 cout << endl;		 
	 */

	 if( GenParticlePdgId[genp] == id_Ele_plus	       
	     && GenParticleStatus[genp] == 3 )
	   {
	     isLeptonPlus=true;
	     leptonPlus.SetPtEtaPhiM(GenParticlePt[genp],
				     GenParticleEta[genp],
				     GenParticlePhi[genp],
				     0);
	   }
	 if( GenParticlePdgId[genp] == id_Ele_minus	       
	     && GenParticleStatus[genp] == 3 )
	   {
	     isLeptonMinus=true;
	     leptonMinus.SetPtEtaPhiM(GenParticlePt[genp],
				      GenParticleEta[genp],
				      GenParticlePhi[genp],
				      0);
	   }
	 if( GenParticlePdgId[genp] == id_NeutrEle	       
	     && GenParticleStatus[genp] == 3 )
	   {
	     isNeutrino=true;
	     neutrino.SetPtEtaPhiM(GenParticlePt[genp],
				   GenParticleEta[genp],
				   GenParticlePhi[genp],
				   0);
	   }
	 if( GenParticlePdgId[genp] == id_AntiNeutrEle	       
	     && GenParticleStatus[genp] == 3 )
	   {
	     isAntiNeutrino=true;
	     antineutrino.SetPtEtaPhiM(GenParticlePt[genp],
				       GenParticleEta[genp],
				       GenParticlePhi[genp],
				       0);
	   }


       }//end first loop over gen particles   

	 
     // reject events that did not pass level 0 cuts
     // if( !passedCut("0") ) continue;
     // ......
     
     // reject events that did not pass level 1 cuts
     // if( !passedCut("1") ) continue;
     // ......
     
     // reject events that did not pass the full cut list
     // if( !passedCut("all") ) continue;
     // ......
     

     //## W Charge Asymmetry ##

     //############ reco level #############

     //X + 0j - plus
     if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	 passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	 getVariableValue("nJet_PtCut_noOvrlpEle")==0 && 
	 eleCharge[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] > 0 )
       {
	 float ST_0j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	   + getVariableValue("caloMET");

	 h_ST_plus_0j_reco->Fill(ST_0j);
	 h_MT_plus_0j_reco->Fill(getVariableValue("MT"));
       }

     //X + 1j - plus
     if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	 passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	 getVariableValue("nJet_PtCut_noOvrlpEle")==1 && 
	 eleCharge[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] > 0 )
       {
	 float ST_1j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	   + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle");
	 
	 h_ST_plus_1j_reco->Fill(ST_1j);
	 h_MT_plus_1j_reco->Fill(getVariableValue("MT"));
       }

     //X + 2j - plus
     if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	 passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	 getVariableValue("nJet_PtCut_noOvrlpEle")>=2 && 
	 eleCharge[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] > 0 )
       {	 
	 float ST_2j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	   + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle")
	   + getVariableValue("Pt2ndJet_noOvrlpEle");

	 h_ST_plus_2j_reco->Fill(ST_2j);
	 h_MT_plus_2j_reco->Fill(getVariableValue("MT"));
       }

     //X + 0j - minus
     if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	 passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	 getVariableValue("nJet_PtCut_noOvrlpEle")==0 && 
	 eleCharge[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] < 0 )
       {
	 float ST_0j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	   + getVariableValue("caloMET");

	 h_ST_minus_0j_reco->Fill(ST_0j);
	 h_MT_minus_0j_reco->Fill(getVariableValue("MT"));
       }

     //X + 1j - minus
     if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	 passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	 getVariableValue("nJet_PtCut_noOvrlpEle")==1 && 
	 eleCharge[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] < 0 )
       {	 
	 float ST_1j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	   + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle");

	 h_ST_minus_1j_reco->Fill(ST_1j);
	 h_MT_minus_1j_reco->Fill(getVariableValue("MT"));
       }

     //X + 2j - minus
     if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	 passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	 getVariableValue("nJet_PtCut_noOvrlpEle")>=2 && 
	 eleCharge[v_idx_ele_PtCut_ID_ISO_noOverlap[0]] < 0 )
       {
	 float ST_2j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	   + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle")
	   + getVariableValue("Pt2ndJet_noOvrlpEle");

	 h_ST_minus_2j_reco->Fill(ST_2j);
	 h_MT_minus_2j_reco->Fill(getVariableValue("MT"));
       }




     //############ gen level ##############

     //plus
     if( isLeptonPlus && isNeutrino )
       {

	 //inclusive
	 WPlus = leptonPlus + neutrino;	

	 h_W_plus_mass->Fill(WPlus.M());
	 h_W_plus_pT->Fill(WPlus.Pt());
	 h_W_plus_eta->Fill(WPlus.Eta());

	 h_genEle_plus_pT->Fill(leptonPlus.Pt());
	 h_genEle_plus_eta->Fill(leptonPlus.Eta());
	 
	 //X + 0j
	 if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	     passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	     getVariableValue("nJet_PtCut_noOvrlpEle")==0 )
	   {
	     
	     float ST_0j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	       + getVariableValue("caloMET");
	     
	     h_W_plus_mass_0j->Fill(WPlus.M());
	     h_W_plus_pT_0j->Fill(WPlus.Pt());
	     h_W_plus_eta_0j->Fill(WPlus.Eta());
	     
	     h_genEle_plus_pT_0j->Fill(leptonPlus.Pt());
	     h_genEle_plus_eta_0j->Fill(leptonPlus.Eta());
	     
	     h_ST_plus_0j->Fill(ST_0j);
	     h_MT_plus_0j->Fill(getVariableValue("MT"));
	     
	   }
	 
	 //X + 1j
	 if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	     passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	     getVariableValue("nJet_PtCut_noOvrlpEle")==1 )
	   {
	     
	     float ST_1j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	       + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle");
	     
	     h_W_plus_mass_1j->Fill(WPlus.M());
	     h_W_plus_pT_1j->Fill(WPlus.Pt());
	     h_W_plus_eta_1j->Fill(WPlus.Eta());
	     
	     h_genEle_plus_pT_1j->Fill(leptonPlus.Pt());
	     h_genEle_plus_eta_1j->Fill(leptonPlus.Eta());
	     
	     h_ST_plus_1j->Fill(ST_1j);
	     h_MT_plus_1j->Fill(getVariableValue("MT"));
	     
	   }
	 
	 //X + >2j
	 if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	     passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	     getVariableValue("nJet_PtCut_noOvrlpEle")>=2 )
	   {
	     
	     float ST_2j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	       + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle")
	       + getVariableValue("Pt2ndJet_noOvrlpEle");
	     
	     h_W_plus_mass_2j->Fill(WPlus.M());
	     h_W_plus_pT_2j->Fill(WPlus.Pt());
	     h_W_plus_eta_2j->Fill(WPlus.Eta());
	     
	     h_genEle_plus_pT_2j->Fill(leptonPlus.Pt());
	     h_genEle_plus_eta_2j->Fill(leptonPlus.Eta());
	     
	     h_ST_plus_2j->Fill(ST_2j);
	     h_MT_plus_2j->Fill(getVariableValue("MT"));
	   }

       }

     //minus
     if( isLeptonMinus && isAntiNeutrino )
       {

	 //inclusive
	 WMinus = leptonMinus + antineutrino; 

	 h_W_minus_mass->Fill(WMinus.M());
	 h_W_minus_pT->Fill(WMinus.Pt());
	 h_W_minus_eta->Fill(WMinus.Eta());

	 h_genEle_minus_pT->Fill(leptonMinus.Pt());
	 h_genEle_minus_eta->Fill(leptonMinus.Eta());

	 //X + 0j
	 if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	     passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	     getVariableValue("nJet_PtCut_noOvrlpEle")==0 )
	   {
	     
	     float ST_0j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	       + getVariableValue("caloMET");
	     
	     h_W_minus_mass_0j->Fill(WMinus.M());
	     h_W_minus_pT_0j->Fill(WMinus.Pt());
	     h_W_minus_eta_0j->Fill(WMinus.Eta());
	     
	     h_genEle_minus_pT_0j->Fill(leptonMinus.Pt());
	     h_genEle_minus_eta_0j->Fill(leptonMinus.Eta());

	     h_ST_minus_0j->Fill(ST_0j);
	     h_MT_minus_0j->Fill(getVariableValue("MT"));
	   }

	 //X + 1j
	 if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	     passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	     getVariableValue("nJet_PtCut_noOvrlpEle")==1 )
	   {
	     
	     float ST_1j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	       + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle");
	     
	     h_W_minus_mass_1j->Fill(WMinus.M());
	     h_W_minus_pT_1j->Fill(WMinus.Pt());
	     h_W_minus_eta_1j->Fill(WMinus.Eta());
	     
	     h_genEle_minus_pT_1j->Fill(leptonMinus.Pt());
	     h_genEle_minus_eta_1j->Fill(leptonMinus.Eta());
	     
	     h_ST_minus_1j->Fill(ST_1j);
	     h_MT_minus_1j->Fill(getVariableValue("MT"));
	   }


	 //X + >2j
	 if( variableIsFilled("nJet_PtCut_noOvrlpEle") && 
	     passedAllPreviousCuts("nJet_PtCut_noOvrlpEle") && 
	     getVariableValue("nJet_PtCut_noOvrlpEle")>=2 )
	   {
	     
	     float ST_2j = getVariableValue("Pt1stEle_IDISO_NoOvrlp") 
	       + getVariableValue("caloMET") + getVariableValue("Pt1stJet_noOvrlpEle")
	       + getVariableValue("Pt2ndJet_noOvrlpEle");
	     
	     h_W_minus_mass_2j->Fill(WMinus.M());
	     h_W_minus_pT_2j->Fill(WMinus.Pt());
	     h_W_minus_eta_2j->Fill(WMinus.Eta());
	     
	     h_genEle_minus_pT_2j->Fill(leptonMinus.Pt());
	     h_genEle_minus_eta_2j->Fill(leptonMinus.Eta());
	     
	     h_ST_minus_2j->Fill(ST_2j);
	     h_MT_minus_2j->Fill(getVariableValue("MT"));
	   }


       }






     ////////////////////// User's code ends here ///////////////////////

   } // End loop over events


   //Calculate charge asymmetry using histogram created above


   //### inclusive ###
   for(int bin=1; bin <= Nbins_pT; bin++)
     {

       //W
       float Nplus_W = h_W_plus_pT->GetBinContent(bin); 
       float Nminus_W = h_W_minus_pT->GetBinContent(bin);        
       float Ndiff_W = Nplus_W - Nminus_W;
       float Ntot_W = Nplus_W + Nminus_W;
       if( Ntot_W > 0 )
	 {
	   float asymmetry_W = Ndiff_W / Ntot_W;
	   float err_asymmetry_W = sqrt( ( Ntot_W * Ntot_W + Ndiff_W * Ndiff_W ) 
					 / ( Ntot_W * Ntot_W * Ntot_W ) );
	   h_Wasymmetry_WpT->SetBinContent( bin , asymmetry_W );
	   h_Wasymmetry_WpT->SetBinError( bin , err_asymmetry_W );
	 }

       //genEle
       float Nplus_genEle = h_genEle_plus_pT->GetBinContent(bin); 
       float Nminus_genEle = h_genEle_minus_pT->GetBinContent(bin);        
       float Ndiff_genEle = Nplus_genEle - Nminus_genEle;
       float Ntot_genEle = Nplus_genEle + Nminus_genEle;
       if( Ntot_genEle > 0 )
	 {
	   float asymmetry_genEle = Ndiff_genEle / Ntot_genEle;
	   float err_asymmetry_genEle = sqrt( ( Ntot_genEle * Ntot_genEle + Ndiff_genEle * Ndiff_genEle ) 
					      / ( Ntot_genEle * Ntot_genEle * Ntot_genEle ) );	   
	   h_Wasymmetry_genElepT->SetBinContent( bin , asymmetry_genEle );
	   h_Wasymmetry_genElepT->SetBinError( bin , err_asymmetry_genEle );
	 }

     }

   for(int bin=1; bin<= Nbins_eta; bin++)
     {

       //W
       float Nplus_W = h_W_plus_eta->GetBinContent(bin); 
       float Nminus_W = h_W_minus_eta->GetBinContent(bin);
       float Ndiff_W = Nplus_W - Nminus_W;
       float Ntot_W = Nplus_W + Nminus_W;

       if( Ntot_W > 0 )
	 {	   
	   float asymmetry_W = Ndiff_W / Ntot_W;	   
	   float err_asymmetry_W = sqrt( ( Ntot_W * Ntot_W + Ndiff_W * Ndiff_W ) 
					 / ( Ntot_W * Ntot_W * Ntot_W ) );
	   h_Wasymmetry_Weta->SetBinContent( bin , asymmetry_W );
	   h_Wasymmetry_Weta->SetBinError( bin , err_asymmetry_W );
	 }

       //genEle
       float Nplus_genEle = h_genEle_plus_eta->GetBinContent(bin); 
       float Nminus_genEle = h_genEle_minus_eta->GetBinContent(bin);        
       float Ndiff_genEle = Nplus_genEle - Nminus_genEle;
       float Ntot_genEle = Nplus_genEle + Nminus_genEle;
       if( Ntot_genEle > 0 )
	 {
	   float asymmetry_genEle = Ndiff_genEle / Ntot_genEle;
	   float err_asymmetry_genEle = sqrt( ( Ntot_genEle * Ntot_genEle + Ndiff_genEle * Ndiff_genEle ) 
					      / ( Ntot_genEle * Ntot_genEle * Ntot_genEle ) );
	   h_Wasymmetry_genEleeta->SetBinContent( bin , asymmetry_genEle );
	   h_Wasymmetry_genEleeta->SetBinError( bin , err_asymmetry_genEle );
	 }

     }


   //### X + 0j ###
   for(int bin=1; bin <= Nbins_pT; bin++)
     {

       //W
       float Nplus_W_0j = h_W_plus_pT_0j->GetBinContent(bin); 
       float Nminus_W_0j = h_W_minus_pT_0j->GetBinContent(bin);        
       float Ndiff_W_0j = Nplus_W_0j - Nminus_W_0j;
       float Ntot_W_0j = Nplus_W_0j + Nminus_W_0j;
       if( Ntot_W_0j > 0 )
	 {
	   float asymmetry_W_0j = Ndiff_W_0j / Ntot_W_0j;
	   float err_asymmetry_W_0j = sqrt( ( Ntot_W_0j * Ntot_W_0j + Ndiff_W_0j * Ndiff_W_0j ) 
					 / ( Ntot_W_0j * Ntot_W_0j * Ntot_W_0j ) );
	   h_Wasymmetry_WpT_0j->SetBinContent( bin , asymmetry_W_0j );
	   h_Wasymmetry_WpT_0j->SetBinError( bin , err_asymmetry_W_0j );
	 }

       //genEle
       float Nplus_genEle_0j = h_genEle_plus_pT_0j->GetBinContent(bin); 
       float Nminus_genEle_0j = h_genEle_minus_pT_0j->GetBinContent(bin);        
       float Ndiff_genEle_0j = Nplus_genEle_0j - Nminus_genEle_0j;
       float Ntot_genEle_0j = Nplus_genEle_0j + Nminus_genEle_0j;
       if( Ntot_genEle_0j > 0 )
	 {
	   float asymmetry_genEle_0j = Ndiff_genEle_0j / Ntot_genEle_0j;
	   float err_asymmetry_genEle_0j = sqrt( ( Ntot_genEle_0j * Ntot_genEle_0j + Ndiff_genEle_0j * Ndiff_genEle_0j ) 
					      / ( Ntot_genEle_0j * Ntot_genEle_0j * Ntot_genEle_0j ) );	   
	   h_Wasymmetry_genElepT_0j->SetBinContent( bin , asymmetry_genEle_0j );
	   h_Wasymmetry_genElepT_0j->SetBinError( bin , err_asymmetry_genEle_0j );
	 }

       //ST
       float Nplus_ST_0j = h_ST_plus_0j->GetBinContent(bin); 
       float Nminus_ST_0j = h_ST_minus_0j->GetBinContent(bin);        
       float Ndiff_ST_0j = Nplus_ST_0j - Nminus_ST_0j;
       float Ntot_ST_0j = Nplus_ST_0j + Nminus_ST_0j;
       if( Ntot_ST_0j > 0 )
	 {
	   float asymmetry_ST_0j = Ndiff_ST_0j / Ntot_ST_0j;
	   float err_asymmetry_ST_0j = sqrt( ( Ntot_ST_0j * Ntot_ST_0j + Ndiff_ST_0j * Ndiff_ST_0j ) 
					 / ( Ntot_ST_0j * Ntot_ST_0j * Ntot_ST_0j ) );
	   h_Wasymmetry_ST_0j->SetBinContent( bin , asymmetry_ST_0j );
	   h_Wasymmetry_ST_0j->SetBinError( bin , err_asymmetry_ST_0j );
	 }

       //MT
       float Nplus_MT_0j = h_MT_plus_0j->GetBinContent(bin); 
       float Nminus_MT_0j = h_MT_minus_0j->GetBinContent(bin);        
       float Ndiff_MT_0j = Nplus_MT_0j - Nminus_MT_0j;
       float Ntot_MT_0j = Nplus_MT_0j + Nminus_MT_0j;
       if( Ntot_MT_0j > 0 )
	 {
	   float asymmetry_MT_0j = Ndiff_MT_0j / Ntot_MT_0j;
	   float err_asymmetry_MT_0j = sqrt( ( Ntot_MT_0j * Ntot_MT_0j + Ndiff_MT_0j * Ndiff_MT_0j ) 
					 / ( Ntot_MT_0j * Ntot_MT_0j * Ntot_MT_0j ) );
	   h_Wasymmetry_MT_0j->SetBinContent( bin , asymmetry_MT_0j );
	   h_Wasymmetry_MT_0j->SetBinError( bin , err_asymmetry_MT_0j );
	 }

       //ST reco
       float Nplus_ST_0j_reco = h_ST_plus_0j_reco->GetBinContent(bin); 
       float Nminus_ST_0j_reco = h_ST_minus_0j_reco->GetBinContent(bin);        
       float Ndiff_ST_0j_reco = Nplus_ST_0j_reco - Nminus_ST_0j_reco;
       float Ntot_ST_0j_reco = Nplus_ST_0j_reco + Nminus_ST_0j_reco;
       if( Ntot_ST_0j_reco > 0 )
	 {
	   float asymmetry_ST_0j_reco = Ndiff_ST_0j_reco / Ntot_ST_0j_reco;
	   float err_asymmetry_ST_0j_reco = sqrt( ( Ntot_ST_0j_reco * Ntot_ST_0j_reco + Ndiff_ST_0j_reco * Ndiff_ST_0j_reco ) 
					 / ( Ntot_ST_0j_reco * Ntot_ST_0j_reco * Ntot_ST_0j_reco ) );
	   h_Wasymmetry_ST_0j_reco->SetBinContent( bin , asymmetry_ST_0j_reco );
	   h_Wasymmetry_ST_0j_reco->SetBinError( bin , err_asymmetry_ST_0j_reco );
	 }

       //MT reco
       float Nplus_MT_0j_reco = h_MT_plus_0j_reco->GetBinContent(bin); 
       float Nminus_MT_0j_reco = h_MT_minus_0j_reco->GetBinContent(bin);        
       float Ndiff_MT_0j_reco = Nplus_MT_0j_reco - Nminus_MT_0j_reco;
       float Ntot_MT_0j_reco = Nplus_MT_0j_reco + Nminus_MT_0j_reco;
       if( Ntot_MT_0j_reco > 0 )
	 {
	   float asymmetry_MT_0j_reco = Ndiff_MT_0j_reco / Ntot_MT_0j_reco;
	   float err_asymmetry_MT_0j_reco = sqrt( ( Ntot_MT_0j_reco * Ntot_MT_0j_reco + Ndiff_MT_0j_reco * Ndiff_MT_0j_reco ) 
					 / ( Ntot_MT_0j_reco * Ntot_MT_0j_reco * Ntot_MT_0j_reco ) );
	   h_Wasymmetry_MT_0j_reco->SetBinContent( bin , asymmetry_MT_0j_reco );
	   h_Wasymmetry_MT_0j_reco->SetBinError( bin , err_asymmetry_MT_0j_reco );
	 }
       

     }

   for(int bin=1; bin<= Nbins_eta; bin++)
     {

       //W
       float Nplus_W_0j = h_W_plus_eta_0j->GetBinContent(bin); 
       float Nminus_W_0j = h_W_minus_eta_0j->GetBinContent(bin);
       float Ndiff_W_0j = Nplus_W_0j - Nminus_W_0j;
       float Ntot_W_0j = Nplus_W_0j + Nminus_W_0j;

       if( Ntot_W_0j > 0 )
	 {	   
	   float asymmetry_W_0j = Ndiff_W_0j / Ntot_W_0j;	   
	   float err_asymmetry_W_0j = sqrt( ( Ntot_W_0j * Ntot_W_0j + Ndiff_W_0j * Ndiff_W_0j ) 
					 / ( Ntot_W_0j * Ntot_W_0j * Ntot_W_0j ) );
	   h_Wasymmetry_Weta_0j->SetBinContent( bin , asymmetry_W_0j );
	   h_Wasymmetry_Weta_0j->SetBinError( bin , err_asymmetry_W_0j );
	 }

       //genEle
       float Nplus_genEle_0j = h_genEle_plus_eta_0j->GetBinContent(bin); 
       float Nminus_genEle_0j = h_genEle_minus_eta_0j->GetBinContent(bin);        
       float Ndiff_genEle_0j = Nplus_genEle_0j - Nminus_genEle_0j;
       float Ntot_genEle_0j = Nplus_genEle_0j + Nminus_genEle_0j;
       if( Ntot_genEle_0j > 0 )
	 {
	   float asymmetry_genEle_0j = Ndiff_genEle_0j / Ntot_genEle_0j;
	   float err_asymmetry_genEle_0j = sqrt( ( Ntot_genEle_0j * Ntot_genEle_0j + Ndiff_genEle_0j * Ndiff_genEle_0j ) 
					      / ( Ntot_genEle_0j * Ntot_genEle_0j * Ntot_genEle_0j ) );
	   h_Wasymmetry_genEleeta_0j->SetBinContent( bin , asymmetry_genEle_0j );
	   h_Wasymmetry_genEleeta_0j->SetBinError( bin , err_asymmetry_genEle_0j );
	 }

     }


   //### X + 1j ###
   for(int bin=1; bin <= Nbins_pT; bin++)
     {

       //W
       float Nplus_W_1j = h_W_plus_pT_1j->GetBinContent(bin); 
       float Nminus_W_1j = h_W_minus_pT_1j->GetBinContent(bin);        
       float Ndiff_W_1j = Nplus_W_1j - Nminus_W_1j;
       float Ntot_W_1j = Nplus_W_1j + Nminus_W_1j;
       if( Ntot_W_1j > 0 )
	 {
	   float asymmetry_W_1j = Ndiff_W_1j / Ntot_W_1j;
	   float err_asymmetry_W_1j = sqrt( ( Ntot_W_1j * Ntot_W_1j + Ndiff_W_1j * Ndiff_W_1j ) 
					 / ( Ntot_W_1j * Ntot_W_1j * Ntot_W_1j ) );
	   h_Wasymmetry_WpT_1j->SetBinContent( bin , asymmetry_W_1j );
	   h_Wasymmetry_WpT_1j->SetBinError( bin , err_asymmetry_W_1j );
	 }

       //genEle
       float Nplus_genEle_1j = h_genEle_plus_pT_1j->GetBinContent(bin); 
       float Nminus_genEle_1j = h_genEle_minus_pT_1j->GetBinContent(bin);        
       float Ndiff_genEle_1j = Nplus_genEle_1j - Nminus_genEle_1j;
       float Ntot_genEle_1j = Nplus_genEle_1j + Nminus_genEle_1j;
       if( Ntot_genEle_1j > 0 )
	 {
	   float asymmetry_genEle_1j = Ndiff_genEle_1j / Ntot_genEle_1j;
	   float err_asymmetry_genEle_1j = sqrt( ( Ntot_genEle_1j * Ntot_genEle_1j + Ndiff_genEle_1j * Ndiff_genEle_1j ) 
					      / ( Ntot_genEle_1j * Ntot_genEle_1j * Ntot_genEle_1j ) );	   
	   h_Wasymmetry_genElepT_1j->SetBinContent( bin , asymmetry_genEle_1j );
	   h_Wasymmetry_genElepT_1j->SetBinError( bin , err_asymmetry_genEle_1j );
	 }

       //ST
       float Nplus_ST_1j = h_ST_plus_1j->GetBinContent(bin); 
       float Nminus_ST_1j = h_ST_minus_1j->GetBinContent(bin);        
       float Ndiff_ST_1j = Nplus_ST_1j - Nminus_ST_1j;
       float Ntot_ST_1j = Nplus_ST_1j + Nminus_ST_1j;
       if( Ntot_ST_1j > 0 )
	 {
	   float asymmetry_ST_1j = Ndiff_ST_1j / Ntot_ST_1j;
	   float err_asymmetry_ST_1j = sqrt( ( Ntot_ST_1j * Ntot_ST_1j + Ndiff_ST_1j * Ndiff_ST_1j ) 
					 / ( Ntot_ST_1j * Ntot_ST_1j * Ntot_ST_1j ) );
	   h_Wasymmetry_ST_1j->SetBinContent( bin , asymmetry_ST_1j );
	   h_Wasymmetry_ST_1j->SetBinError( bin , err_asymmetry_ST_1j );
	 }

       //MT
       float Nplus_MT_1j = h_MT_plus_1j->GetBinContent(bin); 
       float Nminus_MT_1j = h_MT_minus_1j->GetBinContent(bin);        
       float Ndiff_MT_1j = Nplus_MT_1j - Nminus_MT_1j;
       float Ntot_MT_1j = Nplus_MT_1j + Nminus_MT_1j;
       if( Ntot_MT_1j > 0 )
	 {
	   float asymmetry_MT_1j = Ndiff_MT_1j / Ntot_MT_1j;
	   float err_asymmetry_MT_1j = sqrt( ( Ntot_MT_1j * Ntot_MT_1j + Ndiff_MT_1j * Ndiff_MT_1j ) 
					 / ( Ntot_MT_1j * Ntot_MT_1j * Ntot_MT_1j ) );
	   h_Wasymmetry_MT_1j->SetBinContent( bin , asymmetry_MT_1j );
	   h_Wasymmetry_MT_1j->SetBinError( bin , err_asymmetry_MT_1j );
	 }

       //ST reco
       float Nplus_ST_1j_reco = h_ST_plus_1j_reco->GetBinContent(bin); 
       float Nminus_ST_1j_reco = h_ST_minus_1j_reco->GetBinContent(bin);        
       float Ndiff_ST_1j_reco = Nplus_ST_1j_reco - Nminus_ST_1j_reco;
       float Ntot_ST_1j_reco = Nplus_ST_1j_reco + Nminus_ST_1j_reco;
       if( Ntot_ST_1j_reco > 0 )
	 {
	   float asymmetry_ST_1j_reco = Ndiff_ST_1j_reco / Ntot_ST_1j_reco;
	   float err_asymmetry_ST_1j_reco = sqrt( ( Ntot_ST_1j_reco * Ntot_ST_1j_reco + Ndiff_ST_1j_reco * Ndiff_ST_1j_reco ) 
					 / ( Ntot_ST_1j_reco * Ntot_ST_1j_reco * Ntot_ST_1j_reco ) );
	   h_Wasymmetry_ST_1j_reco->SetBinContent( bin , asymmetry_ST_1j_reco );
	   h_Wasymmetry_ST_1j_reco->SetBinError( bin , err_asymmetry_ST_1j_reco );
	 }

       //MT reco
       float Nplus_MT_1j_reco = h_MT_plus_1j_reco->GetBinContent(bin); 
       float Nminus_MT_1j_reco = h_MT_minus_1j_reco->GetBinContent(bin);        
       float Ndiff_MT_1j_reco = Nplus_MT_1j_reco - Nminus_MT_1j_reco;
       float Ntot_MT_1j_reco = Nplus_MT_1j_reco + Nminus_MT_1j_reco;
       if( Ntot_MT_1j_reco > 0 )
	 {
	   float asymmetry_MT_1j_reco = Ndiff_MT_1j_reco / Ntot_MT_1j_reco;
	   float err_asymmetry_MT_1j_reco = sqrt( ( Ntot_MT_1j_reco * Ntot_MT_1j_reco + Ndiff_MT_1j_reco * Ndiff_MT_1j_reco ) 
					 / ( Ntot_MT_1j_reco * Ntot_MT_1j_reco * Ntot_MT_1j_reco ) );
	   h_Wasymmetry_MT_1j_reco->SetBinContent( bin , asymmetry_MT_1j_reco );
	   h_Wasymmetry_MT_1j_reco->SetBinError( bin , err_asymmetry_MT_1j_reco );
	 }
       

     }

   for(int bin=1; bin<= Nbins_eta; bin++)
     {

       //W
       float Nplus_W_1j = h_W_plus_eta_1j->GetBinContent(bin); 
       float Nminus_W_1j = h_W_minus_eta_1j->GetBinContent(bin);
       float Ndiff_W_1j = Nplus_W_1j - Nminus_W_1j;
       float Ntot_W_1j = Nplus_W_1j + Nminus_W_1j;

       if( Ntot_W_1j > 0 )
	 {	   
	   float asymmetry_W_1j = Ndiff_W_1j / Ntot_W_1j;	   
	   float err_asymmetry_W_1j = sqrt( ( Ntot_W_1j * Ntot_W_1j + Ndiff_W_1j * Ndiff_W_1j ) 
					 / ( Ntot_W_1j * Ntot_W_1j * Ntot_W_1j ) );
	   h_Wasymmetry_Weta_1j->SetBinContent( bin , asymmetry_W_1j );
	   h_Wasymmetry_Weta_1j->SetBinError( bin , err_asymmetry_W_1j );
	 }

       //genEle
       float Nplus_genEle_1j = h_genEle_plus_eta_1j->GetBinContent(bin); 
       float Nminus_genEle_1j = h_genEle_minus_eta_1j->GetBinContent(bin);        
       float Ndiff_genEle_1j = Nplus_genEle_1j - Nminus_genEle_1j;
       float Ntot_genEle_1j = Nplus_genEle_1j + Nminus_genEle_1j;
       if( Ntot_genEle_1j > 0 )
	 {
	   float asymmetry_genEle_1j = Ndiff_genEle_1j / Ntot_genEle_1j;
	   float err_asymmetry_genEle_1j = sqrt( ( Ntot_genEle_1j * Ntot_genEle_1j + Ndiff_genEle_1j * Ndiff_genEle_1j ) 
					      / ( Ntot_genEle_1j * Ntot_genEle_1j * Ntot_genEle_1j ) );
	   h_Wasymmetry_genEleeta_1j->SetBinContent( bin , asymmetry_genEle_1j );
	   h_Wasymmetry_genEleeta_1j->SetBinError( bin , err_asymmetry_genEle_1j );
	 }

     }



   //### X + 2j ###
   for(int bin=1; bin <= Nbins_pT; bin++)
     {

       //W
       float Nplus_W_2j = h_W_plus_pT_2j->GetBinContent(bin); 
       float Nminus_W_2j = h_W_minus_pT_2j->GetBinContent(bin);        
       float Ndiff_W_2j = Nplus_W_2j - Nminus_W_2j;
       float Ntot_W_2j = Nplus_W_2j + Nminus_W_2j;
       if( Ntot_W_2j > 0 )
	 {
	   float asymmetry_W_2j = Ndiff_W_2j / Ntot_W_2j;
	   float err_asymmetry_W_2j = sqrt( ( Ntot_W_2j * Ntot_W_2j + Ndiff_W_2j * Ndiff_W_2j ) 
					 / ( Ntot_W_2j * Ntot_W_2j * Ntot_W_2j ) );
	   h_Wasymmetry_WpT_2j->SetBinContent( bin , asymmetry_W_2j );
	   h_Wasymmetry_WpT_2j->SetBinError( bin , err_asymmetry_W_2j );
	 }

       //genEle
       float Nplus_genEle_2j = h_genEle_plus_pT_2j->GetBinContent(bin); 
       float Nminus_genEle_2j = h_genEle_minus_pT_2j->GetBinContent(bin);        
       float Ndiff_genEle_2j = Nplus_genEle_2j - Nminus_genEle_2j;
       float Ntot_genEle_2j = Nplus_genEle_2j + Nminus_genEle_2j;
       if( Ntot_genEle_2j > 0 )
	 {
	   float asymmetry_genEle_2j = Ndiff_genEle_2j / Ntot_genEle_2j;
	   float err_asymmetry_genEle_2j = sqrt( ( Ntot_genEle_2j * Ntot_genEle_2j + Ndiff_genEle_2j * Ndiff_genEle_2j ) 
					      / ( Ntot_genEle_2j * Ntot_genEle_2j * Ntot_genEle_2j ) );	   
	   h_Wasymmetry_genElepT_2j->SetBinContent( bin , asymmetry_genEle_2j );
	   h_Wasymmetry_genElepT_2j->SetBinError( bin , err_asymmetry_genEle_2j );
	 }

       //ST
       float Nplus_ST_2j = h_ST_plus_2j->GetBinContent(bin); 
       float Nminus_ST_2j = h_ST_minus_2j->GetBinContent(bin);        
       float Ndiff_ST_2j = Nplus_ST_2j - Nminus_ST_2j;
       float Ntot_ST_2j = Nplus_ST_2j + Nminus_ST_2j;
       if( Ntot_ST_2j > 0 )
	 {
	   float asymmetry_ST_2j = Ndiff_ST_2j / Ntot_ST_2j;
	   float err_asymmetry_ST_2j = sqrt( ( Ntot_ST_2j * Ntot_ST_2j + Ndiff_ST_2j * Ndiff_ST_2j ) 
					 / ( Ntot_ST_2j * Ntot_ST_2j * Ntot_ST_2j ) );
	   h_Wasymmetry_ST_2j->SetBinContent( bin , asymmetry_ST_2j );
	   h_Wasymmetry_ST_2j->SetBinError( bin , err_asymmetry_ST_2j );
	 }

       //MT
       float Nplus_MT_2j = h_MT_plus_2j->GetBinContent(bin); 
       float Nminus_MT_2j = h_MT_minus_2j->GetBinContent(bin);        
       float Ndiff_MT_2j = Nplus_MT_2j - Nminus_MT_2j;
       float Ntot_MT_2j = Nplus_MT_2j + Nminus_MT_2j;
       if( Ntot_MT_2j > 0 )
	 {
	   float asymmetry_MT_2j = Ndiff_MT_2j / Ntot_MT_2j;
	   float err_asymmetry_MT_2j = sqrt( ( Ntot_MT_2j * Ntot_MT_2j + Ndiff_MT_2j * Ndiff_MT_2j ) 
					 / ( Ntot_MT_2j * Ntot_MT_2j * Ntot_MT_2j ) );
	   h_Wasymmetry_MT_2j->SetBinContent( bin , asymmetry_MT_2j );
	   h_Wasymmetry_MT_2j->SetBinError( bin , err_asymmetry_MT_2j );
	 }
       
       //ST reco
       float Nplus_ST_2j_reco = h_ST_plus_2j_reco->GetBinContent(bin); 
       float Nminus_ST_2j_reco = h_ST_minus_2j_reco->GetBinContent(bin);        
       float Ndiff_ST_2j_reco = Nplus_ST_2j_reco - Nminus_ST_2j_reco;
       float Ntot_ST_2j_reco = Nplus_ST_2j_reco + Nminus_ST_2j_reco;
       if( Ntot_ST_2j_reco > 0 )
	 {
	   float asymmetry_ST_2j_reco = Ndiff_ST_2j_reco / Ntot_ST_2j_reco;
	   float err_asymmetry_ST_2j_reco = sqrt( ( Ntot_ST_2j_reco * Ntot_ST_2j_reco + Ndiff_ST_2j_reco * Ndiff_ST_2j_reco ) 
					 / ( Ntot_ST_2j_reco * Ntot_ST_2j_reco * Ntot_ST_2j_reco ) );
	   h_Wasymmetry_ST_2j_reco->SetBinContent( bin , asymmetry_ST_2j_reco );
	   h_Wasymmetry_ST_2j_reco->SetBinError( bin , err_asymmetry_ST_2j_reco );
	 }

       //MT reco
       float Nplus_MT_2j_reco = h_MT_plus_2j_reco->GetBinContent(bin); 
       float Nminus_MT_2j_reco = h_MT_minus_2j_reco->GetBinContent(bin);        
       float Ndiff_MT_2j_reco = Nplus_MT_2j_reco - Nminus_MT_2j_reco;
       float Ntot_MT_2j_reco = Nplus_MT_2j_reco + Nminus_MT_2j_reco;
       if( Ntot_MT_2j_reco > 0 )
	 {
	   float asymmetry_MT_2j_reco = Ndiff_MT_2j_reco / Ntot_MT_2j_reco;
	   float err_asymmetry_MT_2j_reco = sqrt( ( Ntot_MT_2j_reco * Ntot_MT_2j_reco + Ndiff_MT_2j_reco * Ndiff_MT_2j_reco ) 
					 / ( Ntot_MT_2j_reco * Ntot_MT_2j_reco * Ntot_MT_2j_reco ) );
	   h_Wasymmetry_MT_2j_reco->SetBinContent( bin , asymmetry_MT_2j_reco );
	   h_Wasymmetry_MT_2j_reco->SetBinError( bin , err_asymmetry_MT_2j_reco );
	 }


     }

   for(int bin=1; bin<= Nbins_eta; bin++)
     {

       //W
       float Nplus_W_2j = h_W_plus_eta_2j->GetBinContent(bin); 
       float Nminus_W_2j = h_W_minus_eta_2j->GetBinContent(bin);
       float Ndiff_W_2j = Nplus_W_2j - Nminus_W_2j;
       float Ntot_W_2j = Nplus_W_2j + Nminus_W_2j;

       if( Ntot_W_2j > 0 )
	 {	   
	   float asymmetry_W_2j = Ndiff_W_2j / Ntot_W_2j;	   
	   float err_asymmetry_W_2j = sqrt( ( Ntot_W_2j * Ntot_W_2j + Ndiff_W_2j * Ndiff_W_2j ) 
					 / ( Ntot_W_2j * Ntot_W_2j * Ntot_W_2j ) );
	   h_Wasymmetry_Weta_2j->SetBinContent( bin , asymmetry_W_2j );
	   h_Wasymmetry_Weta_2j->SetBinError( bin , err_asymmetry_W_2j );
	 }

       //genEle
       float Nplus_genEle_2j = h_genEle_plus_eta_2j->GetBinContent(bin); 
       float Nminus_genEle_2j = h_genEle_minus_eta_2j->GetBinContent(bin);        
       float Ndiff_genEle_2j = Nplus_genEle_2j - Nminus_genEle_2j;
       float Ntot_genEle_2j = Nplus_genEle_2j + Nminus_genEle_2j;
       if( Ntot_genEle_2j > 0 )
	 {
	   float asymmetry_genEle_2j = Ndiff_genEle_2j / Ntot_genEle_2j;
	   float err_asymmetry_genEle_2j = sqrt( ( Ntot_genEle_2j * Ntot_genEle_2j + Ndiff_genEle_2j * Ndiff_genEle_2j ) 
					      / ( Ntot_genEle_2j * Ntot_genEle_2j * Ntot_genEle_2j ) );
	   h_Wasymmetry_genEleeta_2j->SetBinContent( bin , asymmetry_genEle_2j );
	   h_Wasymmetry_genEleeta_2j->SetBinError( bin , err_asymmetry_genEle_2j );
	 }

     }



   //////////write histos 
   //h_Mej->Write();
   h2_Mej_MTnuj_good->Write();
   h2_Mej_MTnuj_bad->Write();	 

   //inclusive
   h_W_minus_pT->Write();	 
   h_W_minus_eta->Write();	 
   h_W_plus_pT->Write();	 
   h_W_plus_eta->Write();	 
   h_W_plus_mass->Write();	 
   h_W_minus_mass->Write();	 
   h_genEle_minus_pT->Write();	 
   h_genEle_minus_eta->Write();	 
   h_genEle_plus_pT->Write();	 
   h_genEle_plus_eta->Write();	 

   h_Wasymmetry_WpT->Write();
   h_Wasymmetry_Weta->Write();
   h_Wasymmetry_genElepT->Write();
   h_Wasymmetry_genEleeta->Write();

   //X+0j
   h_W_minus_pT_0j->Write();	 
   h_W_minus_eta_0j->Write();	 
   h_W_plus_pT_0j->Write();	 
   h_W_plus_eta_0j->Write();	 
   h_W_plus_mass_0j->Write();	 
   h_W_minus_mass_0j->Write();	 
   h_genEle_minus_pT_0j->Write();	 
   h_genEle_minus_eta_0j->Write();	 
   h_genEle_plus_pT_0j->Write();	 
   h_genEle_plus_eta_0j->Write();	 
   h_ST_plus_0j->Write();
   h_MT_plus_0j->Write();
   h_ST_plus_0j_reco->Write();
   h_MT_plus_0j_reco->Write();
   h_ST_minus_0j->Write();
   h_MT_minus_0j->Write();
   h_ST_minus_0j_reco->Write();
   h_MT_minus_0j_reco->Write();

   h_Wasymmetry_WpT_0j->Write();
   h_Wasymmetry_Weta_0j->Write();
   h_Wasymmetry_genElepT_0j->Write();
   h_Wasymmetry_genEleeta_0j->Write();
   h_Wasymmetry_ST_0j->Write();
   h_Wasymmetry_MT_0j->Write();
   h_Wasymmetry_ST_0j_reco->Write();
   h_Wasymmetry_MT_0j_reco->Write();

   //X+1j
   h_W_minus_pT_1j->Write();	 
   h_W_minus_eta_1j->Write();	 
   h_W_plus_pT_1j->Write();	 
   h_W_plus_eta_1j->Write();	 
   h_W_plus_mass_1j->Write();	 
   h_W_minus_mass_1j->Write();	 
   h_genEle_minus_pT_1j->Write();	 
   h_genEle_minus_eta_1j->Write();	 
   h_genEle_plus_pT_1j->Write();	 
   h_genEle_plus_eta_1j->Write();	 
   h_ST_plus_1j->Write();
   h_MT_plus_1j->Write();
   h_ST_plus_1j_reco->Write();
   h_MT_plus_1j_reco->Write();
   h_ST_minus_1j->Write();
   h_MT_minus_1j->Write();
   h_ST_minus_1j_reco->Write();
   h_MT_minus_1j_reco->Write();

   h_Wasymmetry_WpT_1j->Write();
   h_Wasymmetry_Weta_1j->Write();
   h_Wasymmetry_genElepT_1j->Write();
   h_Wasymmetry_genEleeta_1j->Write();
   h_Wasymmetry_ST_1j->Write();
   h_Wasymmetry_MT_1j->Write();
   h_Wasymmetry_ST_1j_reco->Write();
   h_Wasymmetry_MT_1j_reco->Write();

   //X+2j
   h_W_minus_pT_2j->Write();	 
   h_W_minus_eta_2j->Write();	 
   h_W_plus_pT_2j->Write();	 
   h_W_plus_eta_2j->Write();	 
   h_W_plus_mass_2j->Write();	 
   h_W_minus_mass_2j->Write();	 
   h_genEle_minus_pT_2j->Write();	 
   h_genEle_minus_eta_2j->Write();	 
   h_genEle_plus_pT_2j->Write();	 
   h_genEle_plus_eta_2j->Write();	 
   h_ST_plus_2j->Write();
   h_MT_plus_2j->Write();
   h_ST_plus_2j_reco->Write();
   h_MT_plus_2j_reco->Write();
   h_ST_minus_2j->Write();
   h_MT_minus_2j->Write();
   h_ST_minus_2j_reco->Write();
   h_MT_minus_2j_reco->Write();

   h_Wasymmetry_WpT_2j->Write();
   h_Wasymmetry_Weta_2j->Write();
   h_Wasymmetry_genElepT_2j->Write();
   h_Wasymmetry_genEleeta_2j->Write();
   h_Wasymmetry_ST_2j->Write();
   h_Wasymmetry_MT_2j->Write();
   h_Wasymmetry_ST_2j_reco->Write();
   h_Wasymmetry_MT_2j_reco->Write();

   std::cout << "analysisClass::Loop() ends" <<std::endl;   
}
