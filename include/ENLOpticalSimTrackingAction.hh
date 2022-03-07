/// ENLOpticalSimTrackingAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLOpticalSimTrackingAction_h
#define ENLOpticalSimTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class ENLOpticalSimTrackingAction : public G4UserTrackingAction
{
public:
  ENLOpticalSimTrackingAction();
  ~ENLOpticalSimTrackingAction();

  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
};
#endif
