#include "/home/local1/Simulations/TP_Simulation/Resultats/Plot.hh"
#include <iostream>
#include <fstream>

using namespace std;

void etalonnage_LaBr3()
{

  //HPD
  float Energie[2] = {511, 1275};
  float NphotonsHPD[2] = {3787, 9585};
  float eEnergie[2] = {0, 0};
  float eNphotonsHPD[2] = {62, 98};

  float NphotonsPMT[2] = {4425, 11568};
  float eNphotonsPMT[2] = {67, 108};  

  TGraphErrors* calibHPD = new TGraphErrors(2, NphotonsHPD, Energie, eNphotonsHPD, eEnergie);
  //TGraphErrors* calib = new TGraphErrors(2, Energie, Nphotons, eEnergie, eNphotons);
  TGraphErrors* calibPMT = new TGraphErrors(2, NphotonsPMT, Energie, eNphotonsPMT, eEnergie);
  
  new TCanvas;
  calibHPD->Draw();
  calibHPD->Fit("pol1");

  new TCanvas;
  calibPMT->Draw();
  calibPMT->Fit("pol1");



  TFile* file = new TFile("Flash_Mo_1M_HPD.root");
  //TFile* file = new TFile("Na22_100k_HPD.root");
  float Detected;
  float Ecalib;
  float Edep;
  TTree *Tree = (TTree*)file->Get("theRunTree");
  float Entries = Tree->GetEntries();
  TH1F* h_Edep = new TH1F("h_Edep","h_Edep", 100, 0, 100);
  TH1F* h_Ecalib = new TH1F("h_Ecalib","h_Ecalib", 100, 0, 100);

  for(int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    Edep = Tree->GetLeaf("Deposit")->GetValue();
    Detected = Tree->GetLeaf("Detected")->GetValue();
    Ecalib = 12+0.132*Detected;
    h_Edep->Fill(Edep);
    h_Ecalib->Fill(Ecalib);
    //cout << "Edep = " << Edep << endl;
    //cout << "Detected = " << Detected << endl;
    //cout << "Ecalib = " << Ecalib << endl;
    
  }


  new TCanvas;
  h_Edep->Draw();
  h_Ecalib->Draw("sames");
  h_Ecalib->SetLineColor(kRed);
  

}
