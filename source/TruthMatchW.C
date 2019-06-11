#define TruthMatchW_cxx
#include "TruthMatchW.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

//void TruthMatchW::Loop()
void TruthMatchW::Loop()
{
//   In a ROOT session, you can do:
//      root> .L TruthMatchW.C
//      root> TruthMatchW t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  cout << "Loop"<< endl;
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntries();   
   cout<< nentries<< endl;
   //nentries=5;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     //
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     //      if (Cut(ientry) < 5) continue;
     //cout << "ientry "<< ientry << ",jentry = "<< jentry<< endl;
     //top_pt:antitop_pt:m_truth_pt:m_truth_pdgId
     //cout<< top_pt << " " << antitop_pt << " " << endl;

     int truth_size = m_truth_pdgId->size();
     //cout << truth_size << endl;

     TLorentzVector part_4v[100];

     if(m_truth_pt->size()!=m_truth_pdgId->size()) cout <<"wtf"<<endl;

     Double_t t_pdg=0, t_pt=0,t_eta=0,t_phi=0,t_m=0;
     //cout << "pdgid "<< " pt "<< " eta "<< " phi "<< "  m "<< endl;
     for (int i = 0; i < m_truth_pt->size(); i++) {
       t_pdg=m_truth_pdgId->at(i);
       t_pt=m_truth_pt->at(i);
       t_eta=m_truth_eta->at(i);
       t_phi=m_truth_phi->at(i);
       t_m=m_truth_m->at(i);
       //cout<< t_pdg << " " << t_pt<<" "<< t_eta<<" "<< t_phi <<" "<< t_m<< endl;
       //if(i==1){
	 part_4v[i].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
	 //cout << "         access 4v pt = "<< part_4v[i].Pt()<<endl;
	 //}
       
       //        if(abs(m_truth_pdgId->at(i))==6){
       // 	 cout<<i<<"pt = top = "<<m_truth_pt->at(i) << '\n'<<endl;       
       //        }
       
       //        if(abs(m_truth_pdgId->at(i))==24){
       // 	 cout<<i << "'pt = W = "<<m_truth_pt->at(i) << '\n'<<endl;       
       //        }
       
     }
     
     TLorentzVector sum;
     sum=part_4v[0]+part_4v[1];
     //cout << "W from nu+lep = "<< sum.Pt()<< endl;

     TLorentzVector sumTop;
     sumTop=part_4v[3]+part_4v[4];
     //cout << "top from W+b = "<< sumTop.Pt()<< endl;

     TLorentzVector sumTopBar;
     sumTopBar=part_4v[6]+part_4v[7];
     //cout << "topbar from W+b = "<< sumTopBar.Pt()<< endl;

     //cout << '\n'<<'\n'<<'\n'<<endl;

     if (abs(sumTop.Pt()-top_pt)>0.1  || abs(sumTopBar.Pt()-antitop_pt)>0.1 ){ 
       cout << "fail: sumTop.Pt()-top_pt="<< sumTop.Pt()-top_pt<< ",  or sumTopBar.Pt()-antitop_pt = "<< sumTopBar.Pt()-antitop_pt  << endl;
     }
   }
}
