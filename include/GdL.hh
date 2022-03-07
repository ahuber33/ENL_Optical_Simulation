/// GdL.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

/*This class is used to create Light Guide Geometry.
GetModule() returns the logical volume containing all the components
*/

#ifndef GdL_h
#define GdL_h

#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class ENLOpticalSimMaterials;
class Scintillator;

class GdL
{
public:

  GdL();
  ~GdL();
  void Construct();

public:

  G4LogicalVolume *Get_GdL();

private:
  ENLOpticalSimMaterials* scintProp;
  static const G4String path_bin;
  G4Material *Material;

  G4LogicalVolume *LogicalVolume;



};
#endif
