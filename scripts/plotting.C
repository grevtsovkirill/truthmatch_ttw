#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void plotting()
{

  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10];
  file[0] = TFile::Open("../source/Res_frac2.root");
  //file[2] = TFile::Open("Res_ttW.root");
  TLatex latex2; latex2.SetTextSize(0.04); latex2.SetNDC();
  char text[1000];  char text1[1000];  char text2[1000];
  TString atl_lable = "Internal";
  sprintf(text1,"#sqrt{s} = 13 TeV, ttW");
  sprintf(text2,"");
  
  TH1D* h_sf[10][10][5];
  int wp[4]={85,77,70,60};
  int eta[2]={1,2};
  vector<string>  cut={"top","antitop","nontop"};
  vector<string> variable={"costheta","helicity","d_phiWl"};//"Njet",Nbjet/Nfjet
  //vector<string> variable={"h_averageIntPerXing"};
  vector<string> type={"ttW"}; //,"Other"};
  char sf_name[1000] ;char band_name[1000] ;
  int i=1; int j=1;
  TLegend* legend[1000];
  TCanvas * canv[1000];
  char canvas_name[1000];
  //  for(i=0;i<4;i++){
  // for(j=0;j<2;j++){
  int rebin_val=1;

  Double_t xbins[] = {0,10,20,25,30,33,35,37,40,43,50,60};
  Int_t  binnum = sizeof(xbins)/sizeof(Double_t) - 1; 
  for(i=0;i<variable.size();i++){
    for(j=0;j<cut.size();j++){
    //for(j=0;j<variable.size();j++){
      //sprintf(sf_name,"%s_%s",variable[0].c_str(),cut[0].c_str());   
      sprintf(sf_name,"%s_%s",variable[i].c_str(),cut[j].c_str());   
      //cout << sf_name<< " " << xbins << " "<< binnum << endl;
      h_sf[i][j][1] = (TH1D *)file[0]->Get(sf_name);
      if(h_sf[i][j][1]->Integral()>0)
      h_sf[i][j][1]->Scale(1/h_sf[i][j][1]->Integral());
      //h_sf[i][j][1]->Scale(1/h_sf[i][j][1]->GetEntries());
      h_sf[i][j][1]->Rebin(rebin_val);
      //h_sf[i][j][1]->Rebin(binnum,sf_name,xbins);
      //h_sf[i][j][1]->Sumw2();

//       sprintf(sf_name,"%s_%s",variable[i].c_str(),cut[1].c_str());   
//       h_sf[i][j][2] = (TH1D *)file[0]->Get(sf_name);
//       h_sf[i][j][2]->Scale(1/h_sf[i][j][2]->Integral());
//       h_sf[i][j][2]->Rebin(rebin_val);
//       cout << sf_name << endl;
      //h_sf[i][j][2]->Rebin(binnum,sf_name,xbins);
      //h_sf[i][j][2]->Sumw2();

      //h_sf[i][j][1]->Divide(h_sf[i][j][2]);
      //h_sf[i][j][1]->Scale( 1/h_sf[i][j][1]->GetSumOfWeights());
    }
  }  


  //  int i =1; int j=1;
  
  
  for(i=0;i<variable.size();i++){
    sprintf(canvas_name,"c_total_%s",variable[i].c_str() );
    canv[i] = new TCanvas(canvas_name, "", 800, 600);
    legend[i] = new TLegend(0.6,0.75,0.87,0.9);
    legend[i]->SetTextFont(42);legend[i]->SetFillColor(0);  legend[i]->SetBorderSize(0); legend[i]->SetFillStyle(0);  legend[i]->SetTextSize(0.04);
    for(j=0;j<cut.size();j++){
      if(j==0){
	h_sf[i][j][1]->SetYTitle("Normalized");
	h_sf[i][j][1]->SetXTitle(variable[i].c_str());
	//h_sf[i][j][1]->GetXaxis()->SetRangeUser(20,500);
	h_sf[i][j][1]->SetMaximum(h_sf[i][j][1]->GetMaximum()*2);
	h_sf[i][j][1]->Draw("E1");
      }
      h_sf[i][j][1]->SetLineColor(1+j);
      h_sf[i][j][1]->SetMarkerColor(1+j);
      h_sf[i][j][1]->SetMarkerStyle(20+j);
      if(h_sf[i][j][1]->Integral()>0){
	h_sf[i][j][1]->Draw("E1histsame");
	legend[i]->AddEntry(h_sf[i][j][1],cut[j].c_str(),"LP");
      }      
      
//       h_sf[i][j][2]->SetLineColor(2);
//       h_sf[i][j][2]->SetMarkerColor(2);
//       h_sf[i][j][2]->SetMarkerStyle(24);
//       h_sf[i][j][2]->Draw("psame"); 
//       h_sf[i][j][2]->Draw("histsame");
      //legend[i]->AddEntry(h_sf[i][j][1],cut[0].c_str(),"LP");
      //canv[i+10*j]->Write(); 
      }
      ATLASLabel(0.2,0.85,atl_lable,1,0.05); latex2.DrawLatex(0.20, 0.8, text1);  latex2.DrawLatex(0.20, 0.75, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
      legend[i]->Draw("same");
  }


  /*
    TH1D *h_tmp_tot_up = (TH1D*)h_out_nom[partial_identifier]->Clone((string("tmp_tot_up") + partial_identifier).c_str());
        TH1D *h_tmp_tot_down = (TH1D*)h_out_nom[partial_identifier]->Clone((string("tmp_tot_down") + partial_identifier).c_str());

	h_tmp_tot_up->Multiply(h_out_tot_up[partial_identifier]);
        h_tmp_tot_down->Multiply(h_out_tot_down[partial_identifier]);
	h_tmp_tot_up->Add(h_out_nom[partial_identifier]);
        h_tmp_tot_down->Add(h_out_nom[partial_identifier]);

*/

}

void ATLASLabel(Double_t x,Double_t y,const char* text,Color_t color, Double_t tsize)
{
  TLatex l;   l.SetTextSize(tsize);  l.SetNDC();  l.SetTextFont(72);  l.SetTextColor(color);
  double delx = 0.115*696*gPad->GetWh()/(472*gPad->GetWw());  l.DrawLatex(x,y,"ATLAS");
  if (text) {    
    TLatex p;    p.SetNDC();    p.SetTextFont(42);    
p.SetTextColor(color);    p.SetTextSize(tsize);    p.DrawLatex(x+delx*1,y,text);  
  }
}
