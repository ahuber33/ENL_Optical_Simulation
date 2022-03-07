/// ENLOpticalSimPhysics.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimPhysics.hh"
//#include "G4MuNuclearInteraction.hh"
#include "G4KokoulinMuonNuclearXS.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ios.hh"
#include "G4OpWLS.hh"
#include "G4GenericIon.hh"
#include "G4Decay.hh"
#include "G4IonConstructor.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

using namespace CLHEP;

// Taken from N06 and LXe examples in GEANT4

ENLOpticalSimPhysics::ENLOpticalSimPhysics():  G4VModularPhysicsList()
{
// Here used the default cut value you have typed in

  //defaultCutValue = 0.001*mm; //0.001
  defaultCutValue = 1*mm; //0.001
  //was 0.5*mm

  SetVerboseLevel(1);

 //default physics
  particleList = new G4DecayPhysics();

  //default physics
  raddecayList = new G4RadioactiveDecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics_option3();
}

ENLOpticalSimPhysics::~ENLOpticalSimPhysics(){
  delete raddecayList;
  delete emPhysicsList;
}

void ENLOpticalSimPhysics::ConstructParticle()
{
// Here are constructed all particles you have chosen
  particleList->ConstructParticle();
  //ConstructBosons();
  //ConstructLeptons();
  //ConstructMesons();
  //ConstructBaryons();
  //ConstructAllShortLiveds();
  //G4GenericIon::GenericIonDefinition();
  //G4IonConstructor iConstructor;
  //iConstructor.ConstructParticle();
}

// In this method, static member functions should
// be called for ALL particles to be used.
/*
void ENLOpticalSimPhysics::ConstructBosons()
{
  G4Geantino::GeantinoDefinition();
  G4Gamma::GammaDefinition();
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void ENLOpticalSimPhysics::ConstructLeptons()
{
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonMinus::MuonMinusDefinition();
  G4MuonPlus::MuonPlusDefinition();
}

void ENLOpticalSimPhysics::ConstructMesons(){}

void ENLOpticalSimPhysics::ConstructBaryons()
{

  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

void ENLOpticalSimPhysics::ConstructAllShortLiveds(){}
*/
void ENLOpticalSimPhysics::ConstructProcess()
{
// Transportation, electromagnetic and general processes

  AddTransportation();
  //ConstructEM();
  //ConstructGeneral();
  // Electromagnetic physics list
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();
  raddecayList->ConstructProcess();
  ConstructOp();

}


void ENLOpticalSimPhysics::ConstructOp()
{
  G4Cerenkov *theCerenkovProcess = new G4Cerenkov("Cerenkov");
  G4Scintillation *theScintillationProcess = new G4Scintillation("Scintillation");
  G4Scintillation *theQuenchingScintillationProcess = new G4Scintillation("Scintillation");
  G4OpAbsorption *theAbsorptionProcess     = new G4OpAbsorption();
  G4OpRayleigh *theRayleighScatteringProcess = new G4OpRayleigh();
  G4OpBoundaryProcess *theBoundaryProcess  = new G4OpBoundaryProcess();
  G4OpWLS *theWLSProcess = new G4OpWLS();

  G4int verbosity=0;

  //theCerenkovProcess->SetMaxNumPhotonsPerStep(1);
  //theCerenkovProcess->SetMaxBetaChangePerStep(1);
  theCerenkovProcess->SetTrackSecondariesFirst(false);
  theCerenkovProcess->SetVerboseLevel(verbosity);
  //theCerenkovProcess->DumpPhysicsTable();

  theScintillationProcess->SetVerboseLevel(verbosity);
  theQuenchingScintillationProcess->SetVerboseLevel(verbosity);

  theAbsorptionProcess->SetVerboseLevel(verbosity);
  theRayleighScatteringProcess->SetVerboseLevel(verbosity);
  theBoundaryProcess->SetVerboseLevel(verbosity);
  theWLSProcess->SetVerboseLevel(0);

  //theScintillationProcess->SetScintillationYieldFactor(1.);
  theScintillationProcess->SetTrackSecondariesFirst(true);
  //theQuenchingScintillationProcess->SetScintillationYieldFactor(1.);
  theQuenchingScintillationProcess->SetTrackSecondariesFirst(true);

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  theQuenchingScintillationProcess->AddSaturation(emSaturation);

  //G4OpticalSurfaceModel themodel = unified;
  //theBoundaryProcess->SetModel(themodel);

  G4ProcessManager * pManager = 0;
  pManager = G4OpticalPhoton::OpticalPhoton()->GetProcessManager();
  pManager->AddDiscreteProcess(theAbsorptionProcess);
  pManager->AddDiscreteProcess(theRayleighScatteringProcess);
  pManager->AddDiscreteProcess(theBoundaryProcess);
  pManager->AddDiscreteProcess(theWLSProcess);

	auto theParticleIterator = GetParticleIterator();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (theCerenkovProcess->IsApplicable(*particle))
      {
    	pmanager->AddProcess(theCerenkovProcess);
    	pmanager->SetProcessOrdering(theCerenkovProcess, idxPostStep);
      }

    if(particle->GetParticleName() == "e-")
      {
    	pmanager->AddProcess(theQuenchingScintillationProcess);
    	pmanager->SetProcessOrderingToLast(theQuenchingScintillationProcess, idxAtRest);
    	pmanager->SetProcessOrderingToLast(theQuenchingScintillationProcess, idxPostStep);
      }

    else if (theScintillationProcess->IsApplicable(*particle))
      {
    	pmanager->AddProcess(theScintillationProcess);
    	pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
    	pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
      }


  }
}


void ENLOpticalSimPhysics::SetCuts()
{
// defaultCutValue you have typed in is used

  if (verboseLevel >1){
    G4cout << "opticalPhysics::SetCuts:";
  }
  SetCutsWithDefault();
  //  SetCutValue(5*mm,"opticalphoton");
}
