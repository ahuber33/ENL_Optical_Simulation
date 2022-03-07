/// ENLOpticalSimVisManager.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLOpticalSimVisManager_h
#define ENLOpticalSimVisManager_h 1

#include "G4VisManager.hh"


class ENLOpticalSimVisManager: public G4VisManager {

public:

  ENLOpticalSimVisManager ();

private:

  void RegisterGraphicsSystems ();

};

#endif
