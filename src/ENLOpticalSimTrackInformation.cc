/// ENLOpticalSimTrackInformation.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimTrackInformation.hh"
#include "G4VProcess.hh"

using namespace CLHEP;

G4Allocator<ENLOpticalSimTrackInformation> TrackInformationAllocator;
ENLOpticalSimTrackInformation::ENLOpticalSimTrackInformation(){}
ENLOpticalSimTrackInformation::ENLOpticalSimTrackInformation(const G4Track *aTrack)
{
  //set new TrackInformation for each photon at scintillation
  if(!aTrack->GetUserInformation()){
    BirthPosition = aTrack->GetVertexPosition();
    BirthLambda = 1240/(aTrack->GetTotalEnergy()/eV);
    DistBeforeWLS = 0;
    DistAfterWLS = 0;
    ReflectBeforeWLS = 0;
    ReflectAfterWLS = 0;
    Reflections = 0;
    WLSCount = 0;
    TotalInternalReflections = 0;
    Rayleigh =0;
  }

  else{
    ENLOpticalSimTrackInformation *anInfo = (ENLOpticalSimTrackInformation*)(aTrack->GetUserInformation());

    BirthPosition = aTrack->GetVertexPosition();

    if(WLSCount == 0){
      DistBeforeWLS = aTrack->GetTrackLength()/mm;
    }

    if(WLSCount > 0){
      DistBeforeWLS = aTrack->GetTrackLength()/mm;
    }

    ReflectBeforeWLS = anInfo->GetReflectBeforeWLS();
    ReflectAfterWLS = anInfo->GetReflectAfterWLS();
    Reflections = anInfo->GetReflections();
    WLSCount = anInfo->GetWLSCount()+1;
//G4cout<< "WLS count = " << anInfo->GetWLSCount() << G4endl;

  }
}

void ENLOpticalSimTrackInformation::CountReflections(){
  Reflections++;

  if(WLSCount==0)
    ReflectBeforeWLS++;
  else
    if(WLSCount > 0){
      ReflectAfterWLS++;
    }

}

void ENLOpticalSimTrackInformation::CountTotalInternalReflections(){

    TotalInternalReflections++;
}


void ENLOpticalSimTrackInformation::CountRayleighScattering(){

    Rayleigh++;
}

ENLOpticalSimTrackInformation::~ENLOpticalSimTrackInformation(){}
