/// ENLOpticalSimRunAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimRunAction.hh"
#include "Randomize.hh"
#include <time.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH2I.h"
#include "TH1D.h"
#include "TAxis.h"
#include <fstream>
#include <iostream>

ENLOpticalSimRunAction::ENLOpticalSimRunAction(char* suff):suffixe(suff){}
ENLOpticalSimRunAction::~ENLOpticalSimRunAction(){}


//-----------------------------------------------------
//  BeginOfRunAction:  used to calculate the start time and
//  to set up information in the run tree.
//-----------------------------------------------------
void ENLOpticalSimRunAction::BeginOfRunAction(const G4Run* aRun){

  //gROOT->ProcessLine("#include <vector>");

  G4String fileName = suffixe+".root";
  //f = new TFile("test.root","UPDATE");

    start = time(NULL);     //start the timer clock to calculate run times

    theRunTree = new TTree("theRunTree","Optical_Information");
    theRunTree_bis = new TTree("theRunTree_bis","Photocathode_Information_Transmitted");

    Tree_electron = new TTree("Tree_electron","Electron Information");  //Tree to access position of energy deposition


    // create the branch for each event.
    // Be careful of the data structure here!  /F is a float  /I is an integer
    RunBranch = theRunTree->Branch("Optical_Information",&Stats.IncidentE,"IncidentE/F:Deposit/F:Generated/I:Absorbed:BulkAbs:Escaped:Failed:WLS:Detected:FWHM/F:Count_Scintillation/I:Count_Cerenkov/I");

    RunBranch = theRunTree_bis->Branch("Photocathode_Information",&Statsbis.Angle,"Angle/F:PositionX/F:PositionY/F:PositionZ/F:DeathLambda/F:BirthLambda/F:Time/F:Total_Reflections/I:Wrap_Reflections/I:Total_Length/F");

    RunBranch = Tree_electron->Branch("E_start", &Statselectron.E_start, "E_start/F" );
    RunBranch = Tree_electron->Branch("E_dep", &Statselectron.E_dep, "E_dep/F" );
    RunBranch = Tree_electron->Branch("TotalLength", &Statselectron.TotalLength, "TotalLength/F" );
    RunBranch = Tree_electron->Branch("InteractionDepth", &Statselectron.InteractionDepth, "InteractionDepth/F" );
    //RunBranch = Tree_electron->Branch("E_dep_Gamma", "vector<float>", &Statselectron.E_dep_Gamma );

    //set the random seed to the CPU clock
  //G4Random::setTheEngine(new CLHEP::HepJamesRandom);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);
    G4cout << "seed = " << seed << G4endl;

    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    if (G4VVisManager::GetConcreteInstance()){
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    }


}  //end BeginOfRunAction


//-----------------------------------------------------
//  EndOfRunAction:  used to calculate the end time and
//  to write information to the run tree.
//-----------------------------------------------------
void ENLOpticalSimRunAction::EndOfRunAction(const G4Run*aRun){

    //update the temp root file
    G4String fileName = suffixe+".root";
    f = new TFile(fileName,"update");
    theRunTree->Write();
    theRunTree_bis->Write();
    Tree_electron->Write();
    f->Close();

    if (G4VVisManager::GetConcreteInstance()){
      G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
    }

    //display run time and write to file Rntime.out
    time_t end = time(NULL);
    G4int elapsed = end-start;
    G4cout << "Run Completed in " << elapsed/3600
	   << ":" << (elapsed%3600)/60 << ":"
	   << ((elapsed%3600)%60) << G4endl;

    // Output the time in the file Runtime.out
    std::ofstream timeout;
    timeout.open("Runtime.out",std::ios::app);
    timeout << "Run " << aRun->GetRunID()
	    << ": " <<elapsed/3600
	    << ":" <<(elapsed%3600)/60
	    << ":" <<((elapsed%3600)%60) << G4endl;
    timeout.close();

      G4cout<<"Leaving Run Action"<<G4endl;
}

//---------------------------------------------------------
//  For each event update the statistics in the Run tree
//---------------------------------------------------------

void ENLOpticalSimRunAction::UpdateStatistics(RunTally aRunTally){
    Stats = aRunTally;
    theRunTree->Fill();
}


void ENLOpticalSimRunAction::UpdateStatisticsbis(RunTallybis aRunTallybis){
    Statsbis = aRunTallybis;
    theRunTree_bis->Fill();
}

void ENLOpticalSimRunAction::UpdateStatisticsElectron(RunTallyElectron aRunTallyElectron){
    Statselectron = aRunTallyElectron;
    Tree_electron->Fill();
}
