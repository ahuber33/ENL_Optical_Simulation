/// ENLOpticalSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimSteppingAction.hh"
#include "G4DynamicParticle.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "ENLOpticalSimRunAction.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "PMT.hh"
#include "ENLOpticalSimEventAction.hh"
#include <iostream>
#include <fstream>
#include "G4Material.hh"
#include "G4Trajectory.hh"
#include "ENLOpticalSimTrackInformation.hh"
#include "ENLOpticalSimGeometry.hh"
#include "G4StepPoint.hh"
#include "TRandom3.h"
#include "TF1.h"
//#include "ENLOpticalSimCaloMap.hh"
//#include "ENLOpticalSimUniformityPMT.hh"



using namespace CLHEP;

const G4String ENLOpticalSimSteppingAction::path = "../simulation_input_files/";

ENLOpticalSimSteppingAction::ENLOpticalSimSteppingAction()
{}

  ENLOpticalSimSteppingAction::~ENLOpticalSimSteppingAction(){}
  void ENLOpticalSimSteppingAction::UserSteppingAction(const G4Step *aStep){

    //#####################
    // Déclaration of Trees
    //#####################
    //RunTally Statistics;
    RunTallybis Statisticsbis;
    RunTallybis Statssphere;
    //RunTallyter Statisticster;


    //###################################
    // Déclaration of functions/variables
    //###################################
    G4Track* theTrack = aStep->GetTrack();
    ENLOpticalSimTrackInformation *trackInformation = (ENLOpticalSimTrackInformation*)theTrack->GetUserInformation();
    G4String partname = aStep->GetTrack()->GetDefinition()->GetParticleName();
    ENLOpticalSimRunAction *runac = (ENLOpticalSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
    G4EventManager *evtman = G4EventManager::GetEventManager();
    ENLOpticalSimEventAction *evtac = (ENLOpticalSimEventAction*)evtman->GetUserEventAction();
    ENLOpticalSimTrackInformation* info = (ENLOpticalSimTrackInformation*)(aStep->GetTrack()->GetUserInformation());
    G4String endproc = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4int Parent_ID = aStep->GetTrack()->GetParentID();
    G4int StepNo = aStep->GetTrack()->GetCurrentStepNumber();

    G4double x = aStep->GetTrack()->GetPosition().x();
    G4double y = aStep->GetTrack()->GetPosition().y();
    G4double z = aStep->GetTrack()->GetPosition().z();
    G4double z_origine = 90. -z; // Limits of photocathode in z plane => Define origine for determine cathode uniformity !!!!
    G4double r = sqrt(x*x + y*y);
    G4double theta = acos((z_origine)/r)/deg;
    G4double my_dist_after = aStep->GetTrack()->GetTrackLength()/mm;




    if(0){                       //set to 1 to ignore generated photons
      if(theTrack->GetDefinition()->GetParticleName()=="opticalphoton")
      theTrack->SetTrackStatus(fStopAndKill);
    }


    //The following lines are for debugging purposes
    if(partname == "opticalphoton" && aStep->GetTrack()->GetUserInformation() ==0) G4cout << "WARNING! No user info attached to photon" << G4endl;


    //if more than 1 secondary is generated, update scintillation statistics

    // if(fpSteppingManager->GetfN2ndariesPostStepDoIt()>0) {
    //
    //   //these two will give you the number of wls photons
    //   //if(theTrack->GetDefinition()->GetParticleName()=="opticalphoton"){
    //    //evtac->AddGenerated(fpSteppingManager->GetfN2ndariesPostStepDoIt());}
    //
    //   //evtac->AddGenerated(fpSteppingManager->GetfN2ndariesPostStepDoIt());
    //   evtac->AddTrackLength(aStep->GetTrack()->GetStepLength()/mm);
    //   //G4cout << " Track Length = " << aStep->GetTrack()->GetTrackLength()/mm << G4endl;
    //   //G4cout << "Count ph" << G4endl;
    // }


    //#######################################################################
    //#######################################################################
    //##########################START OPTICAL PART###########################
    //#######################################################################
    //#######################################################################


    G4OpBoundaryProcessStatus boundaryStatus=Undefined;
    static G4OpBoundaryProcess* boundary=NULL;

    //find the boundary process only once
    if(!boundary){
      G4ProcessManager* pm = aStep->GetTrack()->GetDefinition()->GetProcessManager();
      G4int nprocesses = pm->GetProcessListLength();
      G4ProcessVector* pv = pm->GetProcessList();
      G4int i;
      for( i = 0; i < nprocesses; i++){
        if((*pv)[i]->GetProcessName()=="OpBoundary"){
          boundary = (G4OpBoundaryProcess*)(*pv)[i];
          break;
        }
      }
    }

    if(partname =="opticalphoton"){ //ALL the code in relation with Optical needs to be here !!!!
      boundaryStatus = boundary->GetStatus();
      //G4cout << "BirthLambda = " << info->GetBirthLambda() << G4endl;

      Statisticsbis.Angle = theta;
      Statisticsbis.PositionX = x;
      Statisticsbis.PositionY = y;
      Statisticsbis.PositionZ = z;
      Statisticsbis.DeathLambda = 1240*eV/(aStep->GetTrack()->GetTotalEnergy());
      Statisticsbis.BirthLambda = info->GetBirthLambda();
      Statisticsbis.TotalLength = aStep->GetTrack()->GetTrackLength()/mm;
      Statisticsbis.Time = aStep->GetPostStepPoint()->GetGlobalTime()/ns;
      Statisticsbis.Rayleigh = ((ENLOpticalSimTrackInformation*) (aStep->GetTrack()->GetUserInformation()))->GetRayleigh();
      Statisticsbis.Total_Reflections = ((ENLOpticalSimTrackInformation*) (aStep->GetTrack()->GetUserInformation()))->GetTotalInternalReflections();
      Statisticsbis.Wrap_Reflections = ((ENLOpticalSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->GetReflections();


      //G4cout << "Time =" << aStep->GetPostStepPoint()->GetGlobalTime()/ns << G4endl;

      if(endproc == "OpAbsorption")
      {
        evtac->CountBulkAbs();
        //G4cout << "Photon BulkAbsorbed" << G4endl;
        //runac->UpdateStatisticsbis(Statisticsbis);
      }

      if(endproc == "OpRayleigh")
      {
        ((ENLOpticalSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->CountRayleighScattering();
        //G4cout << "Rayleigh scattering" << G4endl;
        //G4cout << "Number of scattering = " << ((ENLOpticalSimTrackInformation*) (aStep->GetTrack()->GetUserInformation()))->GetRayleigh() << G4endl;
      }

      // If WLS -> Use this !!!
      /*
      else if (endproc == "OpWLS")
      {
      evtac->CountWLS();
      my_dist_after = my_dist_after + aStep->GetTrack()->GetTrackLength()/mm;
      //G4cout << "Count WLS true = " << info->GetWLSCount() << G4endl;
      //G4cout << "Distance d = " << d << G4endl;

      //{
      if (info->GetWLSCount() == 0)
      {
      Length_Track = aStep->GetTrack()->GetTrackLength()/mm;
      //G4cout << "Count WLS = " << info->GetWLSCount() << G4endl;
    }

    if (info->GetWLSCount() > 0)
    {
    Length_Track += aStep->GetTrack()->GetTrackLength()/mm;
    //G4cout << "Count WLS = " << info->GetWLSCount() << G4endl;
  }
  //G4cout << "Track Length = " << aStep->GetTrack()->GetTrackLength()/mm << G4endl;
  //G4cout << "Total Length Track (for different OpWLS) = " << Total_Length_Track << G4endl;
}
*/

else if(partname == "opticalphoton" && endproc != "Transportation")
G4cout << endproc << G4endl;


if(aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary){

  switch(boundaryStatus){
    case Detection:
    {
      evtac->CountDetected();
      //G4cout << "Photon detecté" << G4endl;
      //  evtac->CountDetected_without_CU();
      //evtac->CountDetected(aTally);
      Statisticsbis.Energy_pe = aStep->GetTotalEnergyDeposit()/eV;
      //G4cout << "Energy of pe = " << aStep->GetTotalEnergyDeposit()/eV << " eV" << G4endl;
      runac->UpdateStatisticsbis(Statisticsbis);

      break;
      case Absorption:    // used to get the number TRANSMITTED!!

      if (theTrack->GetNextVolume()->GetName()=="Photocathode")
      {
        evtac->CountFailed();
        //runac->UpdateStatisticsbis(Statisticsbis);

        //  Note that currently it is not set up to root output...see void CountDetected();
        //G4cout << "Photon failed" << G4endl;
      }
      else{  // if not bulk, transmitted, or detected...it must be surface!
        evtac->CountAbsorbed();

        //G4cout << "Photon surface absorbed" << G4endl;
      }

      break;
      case Undefined: G4cout<<"Undefined Boundary Process!"<<G4endl;
      break;
      case NoRINDEX:
      {
        evtac->CountEscaped();
        //G4cout << "count escaped" << G4endl;

      }
      break;

      // if we have any kind of reflections, count them
      case LambertianReflection:
      case LobeReflection:
      case SpikeReflection:
      {
        ((ENLOpticalSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->CountReflections();
        //G4cout << "Reflection" << G4endl;
        break;}
      case TotalInternalReflection:
        {
          ((ENLOpticalSimTrackInformation*)(aStep->GetTrack()->GetUserInformation()))->CountTotalInternalReflections();
          //G4cout << "Reflection totale" << G4endl;
          break;
        }
        default:
        break;
      }
    }
  }


  if(partname == "opticalphoton" && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "Scintillation" && StepNo ==1)
  {
    //G4cout << " Photon Scintillation!!!" << G4endl;
    evtac->CountScintillation();
    //G4cout << "n sc = " << evtac->GetCountScintillation() << G4endl;
    //runac->UpdateStatisticsbis(Statisticsbis);

  }

  if(partname == "opticalphoton" && aStep->GetTrack()->GetCreatorProcess()->GetProcessName() == "Cerenkov" && StepNo ==1)
  {
    //G4cout << " Photon Cerenkov !!!" << G4endl;
    evtac->CountCerenkov();
    //G4cout << "n cerenkov = " << evtac->GetCountCerenkov() << G4endl;
    //G4cout << " Birth = " << info->GetBirthLambda() << G4endl;
    //Statisticsbis.BirthLambda = info->GetBirthLambda();
    //runac->UpdateStatisticsbis(Statisticsbis);
  }


  //If you want to access to the properties of generated photons !!!!
  //if(partname == "opticalphoton" && StepNo==1){runac->UpdateStatisticsbis(Statisticsbis);}

}

//#######################################################################
//#######################################################################
//############################END OPTICAL PART###########################
//#######################################################################
//#######################################################################



//#######################################################################
//#######################################################################
//###########################START EM INFOS PART#########################
//#######################################################################
//#######################################################################


if(partname == "e-"){
  if ((aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator")
  && (aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator")){
    //G4cout << "Step Length = " << aStep->GetTrack()->GetStepLength()/mm << " mm" << G4endl;
    evtac->AddTrackLength(aStep->GetTrack()->GetStepLength()/mm);
    //G4cout << "Track Length dans Scintillateur = " << evtac->GetTotalTrackLength() << " mm"<< G4endl;
    evtac->AddEdepElectron(aStep->GetTotalEnergyDeposit()/keV);
    //G4cout << "E deposée = " << aStep->GetTotalEnergyDeposit()/keV << " keV" << G4endl;
    //G4cout << "E deposée totale = " << evtac->GetEdepElectron() << " keV" << G4endl;
    if(aStep->GetPostStepPoint()->GetKineticEnergy()/keV==0 && evtac->GetEdepElectron() == evtac->GetEstartElectron()){
      evtac->SetInteractionDepthElectron(50+z);
      //G4cout << "Interaction Depth = " << evtac->GetInteractionDepthElectron() << G4endl;
    }
  }
}


if (Parent_ID ==0)
{
  if(StepNo==1)
  {
    evtac->SetEstartElectron(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
    evtac->SetIncidentE(aStep->GetPreStepPoint()->GetKineticEnergy()/keV);
  }
}

if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "Scintillator" && partname != "opticalphoton") {evtac->AddEdep(aStep->GetTotalEnergyDeposit()/keV);}

//
// if(Parent_ID>0)// && aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "PhysicalWorld")
//   {
//     //G4cout << "Ici" << G4endl
//     theTrack->SetTrackStatus(fStopAndKill);
//   }






}
