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


   // top/antitop
   TH1F *h_costheta[10];
   char hname[1000];
   vector<string> ts={"top","antitop"};
   for(int i=0;i<ts.size();i++){
       sprintf(hname,"costheta_%s",ts[i].c_str()); 
       h_costheta[i]=new TH1F(hname,hname,20, -1, 1);     
   }




   Long64_t nentries = fChain->GetEntries();   
   cout<< nentries<< endl;
   //nentries=5;
   Long64_t nbytes = 0, nb = 0;
   int tau_flag=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     //
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     //      if (Cut(ientry) < 5) continue;
     //cout << "ientry "<< ientry << ",jentry = "<< jentry<< endl;
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

               if(abs(m_truth_pdgId->at(i))==15 || abs(m_truth_pdgId->at(i))==16 ){
		 tau_flag++;
		 break;
	       }       
     }
     
     if(tau_flag>0){
       tau_flag=0;
       continue;
     }
     //cout<<"W_count<< t_count<< b_count<< q_count<< l_count<< nu_count=0;"<< endl;
     //cout << W_count<< t_count<< b_count<< q_count<< l_count << nu_count<< endl;
     TLorentzVector W; TLorentzVector WReco;     TLorentzVector lW;
     W=part_4v[0]+part_4v[1];
     //cout << "W from nu+lep = "<< .Pt()<< endl;
     //cout << "W = "<< W.Pt()<< ", reco  = "<<WReco.Pt()<< endl;

     TLorentzVector Top;     TLorentzVector Btop;
     TLorentzVector Wtop; TLorentzVector WtopReco;     TLorentzVector lWtop;
     Wtop=part_4v[3];     Btop=part_4v[4];
     Top=part_4v[3]+part_4v[4];

     //cout << "Wtop = "<< Wtop.Pt()<< ", Top  = "<<Top.Pt()<< endl;

     TLorentzVector TopBar;     TLorentzVector BtopBar;
     TLorentzVector WtopBar; TLorentzVector WtopBarReco;     TLorentzVector lWtopBar;
     TopBar=part_4v[6]+part_4v[7];
     WtopBar=part_4v[6];     BtopBar=part_4v[7];
     
     //find match to wtopreco:
     //find match to wtopreco:
     TLorentzVector qW;
     TLorentzVector lepW;
     vector<TLorentzVector> Ws={W,Wtop,WtopBar};
     vector<TLorentzVector> l_Ws={lW,lWtop,lWtopBar};
     vector<TLorentzVector> WsReco={WReco,WtopReco,WtopBarReco};
     for(int iv=0; iv<3; iv++){	   

       for(int il=0; il<l_count; il++){
	 for(int inu=0; inu<nu_count; inu++){
	   lepW=l_4v[il]+nu_4v[inu];
	   //cout <<" l"<<  il<<" "<< lepW.Pt() << " , Ws["<<iv<<"]"<< Ws[iv].Pt() << endl;
	   if( abs(Ws[iv].Pt()-lepW.Pt())<0.1 ){
	     //cout << "success Wtopreco: "<<WtopReco.Pt()<< " "<< il << " "<< inu<< endl;
	     // WtopReco=l_4v[il]+nu_4v[inu];
	     WsReco[iv]=lepW;
	     l_Ws[iv]=l_4v[il];
	     continue;
	   }	   
	 }	     
       }
       for(int iu=0; iu<qu_count; iu++){
	 for(int id=0; id<qd_count; id++){
	   qW=qu_4v[iu]+qd_4v[id];
	   //cout <<"  q "<<iu<<" " << qW.Pt() << " , Ws["<<iv<<"]"<< Ws[iv].Pt() << endl;
	   if( abs(Ws[iv].Pt()-qW.Pt())<0.1 ){
	     WsReco[iv]=qW;
	     continue;
	   }
	 }	 
       }
     }

     WReco=WsReco[0];
     WtopReco=WsReco[1];
     WtopBarReco=WsReco[2];
     //lW,lWtop,lWtopBar
     lW=l_Ws[0];lWtop=l_Ws[1];lWtopBar=l_Ws[2];


     if (abs(Top.Pt()-top_pt)>0.1  || abs(TopBar.Pt()-antitop_pt)>0.1 ){ 
       cout << "fail: Top.Pt()-top_pt="<< Top.Pt()-top_pt<< ",  or TopBar.Pt()-antitop_pt = "<< TopBar.Pt()-antitop_pt  << endl;
       continue;
     }

     if (abs(W.Pt()-WReco.Pt())>0.1 || abs(Wtop.Pt()-WtopReco.Pt())>0.1  || abs(WtopBar.Pt()-WtopBarReco.Pt())>0.1 ){ 
       cout << jentry<< " fail Wreco: W"<< W.Pt()-WReco.Pt() <<"   wtop="<<Wtop.Pt()-WtopReco.Pt() << ",  or wtopbar = "<< WtopBar.Pt()-WtopBarReco.Pt()  << endl;
       continue;
     }

     //Manage to reconstruct everything!!!
     //cout << lW.Pt()<< " "<<part_4v[0].Pt()<< " "<<part_4v[1].Pt() <<endl;
     if(lWtop.Pt()!=0){
       //cout << "angle(lWtop,Btop)=" << angle(lWtop,Btop)<< ";   WHelicity= "<< WHelicity(Top,Wtop,lWtop) << endl;
       h_costheta[0]->Fill(WHelicity(Top,Wtop,lWtop));
     }

     if(lWtopBar.Pt()!=0){
       //cout << "angle(lWtop,Btop)=" << angle(lWtop,Btop)<< ";   WHelicity= "<< WHelicity(Top,Wtop,lWtop) << endl;
       h_costheta[1]->Fill(WHelicity(TopBar,WtopBar,lWtopBar));
     }

   }

   string outname="Res_.root";
   TFile hfile(outname.c_str(),"RECREATE"); //,"tHq"
   for(int i=0;i<ts.size();i++){  
     h_costheta[i]->Write(); 
   }
   hfile.Close();

}
