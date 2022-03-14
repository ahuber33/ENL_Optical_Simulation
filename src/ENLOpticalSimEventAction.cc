/// ENLOpticalSimEventAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "G4SteppingManager.hh"
#include "ENLOpticalSimSteppingAction.hh"
#include "G4Run.hh"
#include "ENLOpticalSimEventAction.hh"
#include "G4RunManager.hh"
#include "ENLOpticalSimRunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include "G4PrimaryVertex.hh"
#include <math.h>
#include "TRandom3.h"
#include "TGraph.h"

using namespace CLHEP;

ENLOpticalSimEventAction::ENLOpticalSimEventAction(char* suff):suffixe(suff){}

ENLOpticalSimEventAction::~ENLOpticalSimEventAction(){}


// Initialize all counters and set up the event branches for
// filling histograms with ROOT
void ENLOpticalSimEventAction::BeginOfEventAction(const G4Event* evt){

  G4int event_id = evt->GetEventID();

  // if(event_id %100 ==1)
  // {
  //   G4cout << "Event " << event_id << " Start" << G4endl;
  //   //G4cout << "Starting EventAction..." << G4endl;
  // }

  Statistics.IncidentE = 0;
  Statistics.Deposit = 0;
  Statistics.Generated = 0;
  Statistics.WLS = 0;
  Statistics.Absorbed = 0;
  Statistics.BulkAbs = 0;
  Statistics.Escaped = 0;
  Statistics.Failed = 0;
  Statistics.Detected = 0;
  Statistics.FWHM = 0;
  Statistics.Count_Scintillation = 0;
  Statistics.Count_Cerenkov = 0;
  cpt_without_CU =0;
  cpt_with_CU = 0;
  cpt_photons_lost =0;
  nph =0;
  nph_cerenkov =0;
  nph_scintillation =0;

  Statselectron.E_start=0;
  Statselectron.E_dep=0;
  Statselectron.TotalLength =0;
  Statselectron.InteractionDepth =0;
  //Statselectron.E_dep_Gamma.clear();

}


// Get the number of stored trajectories and calculate the statistics
void ENLOpticalSimEventAction::EndOfEventAction(const G4Event* evt){
    G4int event_id = evt->GetEventID();

  ENLOpticalSimRunAction *runac = (ENLOpticalSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());



  //if (Statselectron.E_dep_Gamma.size() != 0)
    //if (Statselectron.E_dep == Statselectron.E_start)
      //{
      runac->UpdateStatisticsElectron(Statselectron);
      //}


  G4double Absfrac = 0;
  G4double Bulkfrac = 0;
  G4double Escfrac = 0;
  G4double Failfrac = 0;
  G4double WLSfrac = 0;
  G4double Catfrac = 0;
  G4double efficiency = 0;
  G4double efficiency_final = 0;
  Statistics.Generated = GetCountScintillation() + GetCountCerenkov();


if (Statistics.Generated >0)
{
  efficiency = 100*(1.0*Statistics.Detected)/(1.0*Statistics.Generated);
  Absfrac = 100*(1.0*Statistics.Absorbed)/(1.0*Statistics.Generated);
  Bulkfrac = 100*(1.0*Statistics.BulkAbs)/(1.0*Statistics.Generated);
  Escfrac = 100*(1.0*Statistics.Escaped)/(1.0*Statistics.Generated);
  Failfrac = 100*(1.0*Statistics.Failed)/(1.0*Statistics.Generated);
  WLSfrac = 100*(1.0*Statistics.WLS)/(1.0*Statistics.Generated);
  Catfrac = 100 * (cpt_photons_lost/(1.0*Statistics.Detected));
  efficiency_final = 100 * (Statistics.Detected/(1.0*Statistics.Generated));
  Statistics.FWHM = 100*2.35/sqrt(Statistics.Detected);

  // Output the results
  G4cout  << "\n\nRun " << G4RunManager::GetRunManager()->GetCurrentRun()->GetRunID() <<  " >>> Event " << evt->GetEventID() << G4endl;
  G4cout << "Incident Energy:                    " << Statistics.IncidentE << " keV " << G4endl;
  G4cout << "Energy Deposited:                   " << Statistics.Deposit   << " keV " << G4endl;
  G4cout << "Photons Generated:                  " << Statistics.Generated     << G4endl;
  G4cout << "     from Scintillation :           " << Statistics.Count_Scintillation << "   (" << (float(Statistics.Count_Scintillation))/(float(Statistics.Generated))*100 << " %)"     << G4endl;
  G4cout << "     from Cerenkov :                " << Statistics.Count_Cerenkov     << "    (" << (float(Statistics.Count_Cerenkov))/(float(Statistics.Generated))*100 << " %)"     << G4endl;

  G4cout << "Photons Surface Absorbed  :         " << Statistics.Absorbed      << "        " << Absfrac << " % " << G4endl;
  G4cout << "Photons Bulk Absorbed:              " << Statistics.BulkAbs       << "        " << Bulkfrac << " % " << G4endl;
  G4cout << "Photons Escaped:                    " << Statistics.Escaped       << "        " << Escfrac << " % " << G4endl;
  G4cout << "Photons only Transmitted to PMT:    " << Statistics.Failed        << "        " << Failfrac << " % " << G4endl;
  G4cout << "Photons Collected in PMT (QE):      " << Statistics.Detected      << "        " << efficiency << " % " << G4endl;
  G4cout << "Total Photons Considered:           " << Statistics.Absorbed + Statistics.BulkAbs + Statistics.Escaped + Statistics.Failed + Statistics.Detected  << "        " << Absfrac + Bulkfrac + Escfrac + Failfrac + efficiency << " % " << G4endl;
  G4cout << "Photons WL Shifted:                 " << Statistics.WLS           << "        " << WLSfrac << " % " << G4endl;
  G4cout << ""  <<  G4endl;
  G4cout << "FWHM resolution :                   " << Statistics.FWHM << "% " << G4endl;
  //G4cout << "FWHM resolution (with cathode uniformity):    " << Statistics.FWHM_final << "% " << G4endl;
  G4cout << ""  <<  G4endl;
  G4cout << ""  <<  G4endl;

  //runac->UpdateStatistics(Statistics);
    }

if(Statistics.Deposit >0){runac->UpdateStatistics(Statistics);}

}
