#include "/home/local1/Simulations/TP_Simulation/Resultats/Plot.hh"
#include <iostream>
#include <fstream>

using namespace std;

void etalonnage_LaBr3()
{

  float Energie[2] = {511, 1275};
  float Nphotons[2] = {32310, 81968};
  float eEnergie[2] = {0, 0};
  float eNphotons[2] = {180, 286};

  TGraphErrors* calib = new TGraphErrors(2, Nphotons, Energie, eNphotons, eEnergie);
  
  new TCanvas;
  calib->Draw();
  calib->Fit("pol1");
  

}
