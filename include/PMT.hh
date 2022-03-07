/// PMT.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA


#ifndef PMT_h
#define PMT_h

#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

class ENLOpticalSimMaterials;
class Scintillator;
class PMT
{
public:

  PMT();
  ~PMT();
  void Construct();

public:

  G4LogicalVolume *GetBADGE_PMTGlass();
  G4LogicalVolume *GetBADGE_Photocathode();
  G4LogicalVolume *Get8InchesPMTGlass();
  G4LogicalVolume *Get8InchesPhotocathode();
  G4LogicalVolume *GetHPDGlass();
  G4LogicalVolume *GetHPDPhotocathode();


private:
  ENLOpticalSimMaterials* scintProp;
  Scintillator *theScint;
  static const G4String path_bin;

  G4Material *Material;

  G4LogicalVolume *LogicalVolume;

};
#endif
