/// ENLOpticalSimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLOpticalSimEventAction_h
#define ENLOpticalSimEventAction_h 1
#include "G4ParticleGun.hh"
#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <vector>
#include "TVector.h"

class G4Event;


//This struct carries statistics for the whole Run
struct RunTally {
  float  IncidentE;
  float  Deposit;
  int    Generated;
  int    Absorbed;
  int    BulkAbs;
  int    Escaped;
  int    Failed;
  int    WLS;
  int    Detected;
  float  FWHM;
  int Count_Scintillation;
  int Count_Cerenkov;

  inline int operator ==(const RunTally& right) const
  {return (this==&right);}
};


//This struct carries statistics for the whole Run
struct RunTallybis {
  float  Angle;
  float  PositionX;
  float  PositionY;
  float  PositionZ;
  float  DeathLambda;
  float  BirthLambda;
  float Time;
  //float  Theta;
  //float  Phi;
  int Total_Reflections;
  int Wrap_Reflections;
  float TotalLength;

  inline int operator ==(const RunTallybis& right) const
  {return (this==&right);}
};


struct RunTallyElectron {
  float E_start;
  float E_dep;
  float TotalLength;
  float InteractionDepth;
  //std::vector<float> E_dep_Gamma;

  inline int operator ==(const RunTallyElectron& right) const
  {return (this==&right);}
};



class ENLOpticalSimEventAction : public G4UserEventAction
{
public:
  ENLOpticalSimEventAction(char*);
  ~ENLOpticalSimEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  //Keeps track of the total number of generated photons
  void AddGenerated(G4int numgenerated){Statistics.Generated+=numgenerated;}
  //Keeps track of the total energy deposited in the scintillator
  void AddEdep(G4float edep){Statistics.Deposit+=edep;}

  //void CountDetected(Tally);
  //void CountDetected_without_CU(){Statistics.Detected_without_CU++;}
  void CountDetected(){Statistics.Detected++;}
  void CountWLS(){Statistics.WLS++;}
  void CountAbsorbed(){Statistics.Absorbed++;}
  void CountBulkAbs(){Statistics.BulkAbs++;}
  void CountEscaped(){Statistics.Escaped++;}
  void CountFailed(){Statistics.Failed++;}

  void Setcpt_without_CU(G4int e){ cpt_without_CU = e;}
  G4int Getcpt_without_CU(){return cpt_without_CU;}

  void Setcpt_photons_lost(G4int d){ cpt_photons_lost = d;}
  G4int Getcpt_photons_lost(){return cpt_photons_lost;}

  void Setnph(int d){ nph = d;}
  int Getnph() {return nph;}

  void CountCerenkov(){Statistics.Count_Cerenkov++;}
  int GetCountCerenkov(){return Statistics.Count_Cerenkov;}
  void CountScintillation(){Statistics.Count_Scintillation++;}
  int GetCountScintillation(){return Statistics.Count_Scintillation;}

  // void Fill_E_dep_Gamma (G4float E) {Statselectron.E_dep_Gamma.push_back(E);};
  // void Fill_Gamma_Interaction_X (G4float x) {Statselectron.Gamma_Interaction_X.push_back(x);};
  // void Fill_Gamma_Interaction_Y (G4float y) {Statselectron.Gamma_Interaction_Y.push_back(y);};
  // void Fill_Gamma_Interaction_Z (G4float z) {Statselectron.Gamma_Interaction_Z.push_back(z);};

  void AddTrackLength(G4double d){Statselectron.TotalLength+=d;}
  float GetTotalTrackLength(){return Statselectron.TotalLength;}
  void AddEdepElectron(G4double d){Statselectron.E_dep+=d;}
  float GetEdepElectron(){return Statselectron.E_dep;}
  void SetEstartElectron(G4double d){Statselectron.E_start+=d;}
  float GetEstartElectron(){return Statselectron.E_start;}
  //Use only for a test protocole (if not change the definition in Stepping)
  void SetInteractionDepthElectron(G4double d){Statselectron.InteractionDepth+=d;}
  float GetInteractionDepthElectron(){return Statselectron.InteractionDepth;}


  //Keeps track of the incident energy of the primary particle
  void SetIncidentE(G4double ince){Statistics.IncidentE=ince;}


private:

  TTree *EventTree;
  TBranch *EventBranch;
  //Tally BranchFiller;
  RunTally Statistics;
  RunTallybis Statsbis;
  RunTallyElectron Statselectron;
  G4int cpt_without_CU;
  G4int cpt_with_CU;
  G4int cpt_photons_lost;
  G4int nph;
  G4int nph_cerenkov;
  G4int nph_scintillation;
  G4int Track;
  G4String suffixe;





};


#endif
