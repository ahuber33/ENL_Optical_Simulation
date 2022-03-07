/// ENLOpticalSimRunAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLOpticalSimRunAction_h
#define ENLOpticalSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "ENLOpticalSimEventAction.hh"
#include <TFile.h>
#include <vector>

class G4Run;

class ENLOpticalSimRunAction : public G4UserRunAction
{

public:
  ENLOpticalSimRunAction(char*);
  ~ENLOpticalSimRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  //adds the photon fates from an event to the run tree
  void UpdateStatistics(RunTally);
  void UpdateStatisticsbis(RunTallybis);
  void UpdateStatisticsElectron(RunTallyElectron);



private:
  G4String suffixe;
  G4int NumPMTs;
  G4int NumFibers;
  RunTally Stats;
  RunTallybis Statsbis;
  RunTallyElectron Statselectron;
  TFile *f;
  TTree *theRunTree;
  TTree *theRunTree_bis;
  TTree *Tree_electron;
  TBranch *RunBranch;
  time_t start;

};

#endif
