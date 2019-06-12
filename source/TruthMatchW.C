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
   nentries=5;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     //
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     //      if (Cut(ientry) < 5) continue;
     //cout << "ientry "<< ientry << ",jentry = "<< jentry<< endl;
     //top_pt:antitop_pt:m_truth_pt:m_truth_pdgId
     //cout<<"top "<< top_pt << " antitop= " << antitop_pt << " " << endl;

     int truth_size = m_truth_pdgId->size();
     //cout << truth_size << endl;

     TLorentzVector part_4v[100];

     TLorentzVector W_4v[100];
     TLorentzVector t_4v[100];
     TLorentzVector b_4v[100];
     TLorentzVector qu_4v[100];
     TLorentzVector qd_4v[100];
     TLorentzVector l_4v[100];
     TLorentzVector nu_4v[100];

     if(m_truth_pt->size()!=m_truth_pdgId->size()) cout <<"wtf"<<endl;

     Double_t t_pdg=0, t_pt=0,t_eta=0,t_phi=0,t_m=0;
     int W_count=0, t_count=0, b_count=0, qu_count=0,qd_count=0, l_count=0, nu_count=0;
     //cout << "pdgid "<< " pt "<< " eta "<< " phi "<< "  m "<< endl;
     for (int i = 0; i < m_truth_pt->size(); i++) {
       t_pdg=m_truth_pdgId->at(i);
       t_pt=m_truth_pt->at(i);
       t_eta=m_truth_eta->at(i);
       t_phi=m_truth_phi->at(i);
       t_m=m_truth_m->at(i);
       //cout<< i << " "<< t_pdg << " " << t_pt<<" "<< t_eta<<" "<< t_phi <<" "<< t_m<< endl;
       //if(i==1){
       part_4v[i].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);

       //cout << "         access 4v pt = "<< part_4v[i].Pt()<<endl;
	 //}
       
               if(abs(m_truth_pdgId->at(i))==6){
		 t_4v[t_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 t_count++;
       // 	 cout<<i<<"pt = top = "<<m_truth_pt->at(i) << '\n'<<endl;       
               }
       
               if(abs(m_truth_pdgId->at(i))==24){
		 W_4v[W_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 W_count++;
               }

               if(abs(m_truth_pdgId->at(i))==5){
		 b_4v[b_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 b_count++;
               }

               if(abs(m_truth_pdgId->at(i))==2 || abs(m_truth_pdgId->at(i))==4){
		 qu_4v[qu_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 qu_count++;
               }

               if(abs(m_truth_pdgId->at(i))==1  || abs(m_truth_pdgId->at(i))==3){
		 qd_4v[qd_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 qd_count++;
               }

               if(abs(m_truth_pdgId->at(i))==11 || abs(m_truth_pdgId->at(i))==13 ){
		 l_4v[l_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 l_count++;
               }

               if(abs(m_truth_pdgId->at(i))==12 || abs(m_truth_pdgId->at(i))==14 ){
		 nu_4v[nu_count].SetPtEtaPhiM(t_pt,t_eta,t_phi,t_m);
		 nu_count++;
               }
       
     }
     //cout<<"W_count<< t_count<< b_count<< q_count<< l_count<< nu_count=0;"<< endl;
     //cout << W_count<< t_count<< b_count<< q_count<< l_count << nu_count<< endl;
     TLorentzVector W; TLorentzVector WReco;
     W=part_4v[0]+part_4v[1];
     //WReco=part_4v[19]+part_4v[20];
     //cout << "W from nu+lep = "<< .Pt()<< endl;
     //cout << "W = "<< W.Pt()<< ", reco  = "<<WReco.Pt()<< endl;

     TLorentzVector Top;
     TLorentzVector Wtop; TLorentzVector WtopReco;
     Wtop=part_4v[3];
     Top=part_4v[3]+part_4v[4];


     TLorentzVector TopBar;
     TLorentzVector WtopBar; TLorentzVector WtopBarReco;
     TopBar=part_4v[6]+part_4v[7];
     WtopBar=part_4v[6];
     
     //find match to wtopreco:

     TLorentzVector lepW;
     for(int il=0; il<l_count; il++){
       for(int inu=0; inu<nu_count; inu++){
	 lepW=l_4v[il]+nu_4v[inu];
	 if (abs(Wtop.Pt()-lepW.Pt())<0.1){
	   //cout << "success Wtopreco: "<<WtopReco.Pt()<< " "<< il << " "<< inu<< endl;
	   WtopReco=l_4v[il]+nu_4v[inu];
	 }

	 if (abs(WtopBar.Pt()-lepW.Pt())<0.1){
	   WtopBarReco=l_4v[il]+nu_4v[inu];
	   //cout << "success WtopBarreco: "<<WtopBarReco.Pt()<< " "<< il << " "<< inu<< endl;
	 }

	 if (abs(W.Pt()-lepW.Pt())<0.1){
	   WReco=l_4v[il]+nu_4v[inu];
	   //cout << "success Wreco: "<<WReco.Pt()<< " "<< il << " "<< inu<< endl;
	 }


       }
     }


     //find match to wtopreco:
     TLorentzVector qW;
     for(int iu=0; iu<qu_count; iu++){
       for(int id=0; id<qd_count; id++){
	 qW=qu_4v[iu]+qd_4v[id];
	 if (abs(Wtop.Pt()-qW.Pt())<0.1){
	   WtopReco=qu_4v[iu]+qd_4v[id];
	   //cout << "success Wtopreco: "<<WtopReco.Pt()<< " "<< iu << " "<< id<< endl;
	 }

	 if (abs(WtopBar.Pt()-qW.Pt())<0.1){
	   WtopBarReco=qu_4v[iu]+qd_4v[id];
	   //cout << "success WtopBarreco: "<<WtopBarReco.Pt()<< " "<< iu << " "<< id<< endl;
	 }

	 if (abs(W.Pt()-qW.Pt())<0.1){
	   WReco=qu_4v[iu]+qd_4v[id];
	   //cout << "success Wreco: "<<WReco.Pt()<< " "<< iu << " "<< id<< endl;
	 }

       }
     }

     //WtopReco=part_4v[11]+part_4v[12];
     //cout << "top from W+b = "<< Top.Pt()<< endl;
     //cout << "Wtop = "<< Wtop.Pt()<< ", reco  = "<<WtopReco.Pt()<< endl;
     //WtopBarReco=part_4v[9]+part_4v[10];
     //cout << "WtopBar = "<< WtopBar.Pt()<< ", reco  = "<<WtopBarReco.Pt()<< endl;
     //cout << "topbar from W+b = "<< TopBar.Pt()<< endl;

     //cout << '\n'<<'\n'<<'\n'<<endl;

     if (abs(Top.Pt()-top_pt)>0.1  || abs(TopBar.Pt()-antitop_pt)>0.1 ){ 
       cout << "fail: Top.Pt()-top_pt="<< Top.Pt()-top_pt<< ",  or TopBar.Pt()-antitop_pt = "<< TopBar.Pt()-antitop_pt  << endl;
     }

     if (abs(W.Pt()-WReco.Pt())>0.1 || abs(Wtop.Pt()-WtopReco.Pt())>0.1  || abs(WtopBar.Pt()-WtopBarReco.Pt())>0.1 ){ 
       cout << "fail Wreco: W"<< W.Pt()-WReco.Pt() <<"   wtop="<<Wtop.Pt()-WtopReco.Pt() << ",  or wtopbar = "<< WtopBar.Pt()-WtopBarReco.Pt()  << endl;
     }

   }
}
