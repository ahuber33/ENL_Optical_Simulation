/// PMT.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimMaterials.hh"
#include "PMT.hh"
#include "Scintillator.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Transform3D.hh"
#include <fstream>
#include <iostream>
#include "G4Tubs.hh"
#include "G4UnitsTable.hh"
#include "G4Sphere.hh"
#include <G4Polycone.hh>
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

using namespace CLHEP;

const G4String PMT::path_bin = "../bin/";

// ***********************
// Constructor
// ***********************
PMT::PMT(){}
// ***********************
// Destructor
// ***********************
PMT::~PMT(){
  if(scintProp) { delete scintProp; scintProp = 0; }
  if(theScint) { delete theScint; theScint = 0; }
}


G4LogicalVolume *PMT::GetBADGE_PMTGlass(){
  // Materials properties for PMT
  Material = scintProp->GetMaterial("bs_glass");

  // Define some rotations
  G4RotationMatrix Rotate;
  Rotate.rotateX(180.0*deg);
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);


  // ####################### PMT GLASS TUBE SOLID #######################
  // Solid PMT photocathode sphere
  G4int N_z_plane = 7;
  G4double Phi_start = 0.*deg;
  G4double Phi_end = 2*180*deg;


  const G4double z_plane[] = {0*mm, 0.5*mm, 1.*mm, 71*mm, 74*mm, 84*mm, 85*mm};

  const G4double r_inner[]= {0/2*mm, 0/2*mm, 37.7/2*mm, 37.7/2*mm, 32/2*mm, 31/2*mm, 0/2*mm};

  const G4double r_outer[]= {38/2*mm, 38.7/2*mm, 38.7/2*mm, 38.7/2*mm, 33/2*mm, 32/2*mm, 30/2*mm};

  G4Polycone *PMTGlass = new G4Polycone("PMTGlass",
  Phi_start,
  Phi_end,
  N_z_plane,
  z_plane,
  r_inner,
  r_outer);


  // Logical PMT tube:  material borosilicate glass
  LogicalVolume = new G4LogicalVolume(PMTGlass, Material,"LogicalPMTGlass",0,0,0);


  return LogicalVolume;
}


G4LogicalVolume *PMT::GetBADGE_Photocathode(){
  // Materials properties for PMT
  Material = scintProp->GetMaterial("Vacuum");

  // Define some rotations
  G4RotationMatrix Rotate;
  Rotate.rotateX(180.0*deg);
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);


  // ####################### PMT GLASS TUBE SOLID #######################
  // Solid PMT photocathode sphere
  G4int N_z_plane = 3;
  G4double Phi_start = 0.*deg;
  G4double Phi_end = 2*180*deg;


  const G4double z_plane[] = {0*mm, 0.5*mm, 1.*mm};

  const G4double r_inner[]= {0/2*mm, 0/2*mm, 37.7/2*mm};

  const G4double r_outer[]= {38/2*mm, 38.7/2*mm, 38.7/2*mm};

  G4Polycone *Photocathode = new G4Polycone("Photocathode",
  Phi_start,
  Phi_end,
  N_z_plane,
  z_plane,
  r_inner,
  r_outer);


  LogicalVolume = new G4LogicalVolume(Photocathode, Material,"LogicalPhotocathode",0,0,0);


  return LogicalVolume;
}


G4LogicalVolume *PMT::Get8InchesPMTGlass(){
  // Materials properties for PMT
  Material = scintProp->GetMaterial("bs_glass");


  // Define some rotations
  G4RotationMatrix Rotate;
  Rotate.rotateX(180.0*deg);
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);

  // ####################### PMT GLASS SOLID #######################
  G4int N_z_plane = 36;
  G4double Phi_start = 0.*deg;
  G4double Phi_end = 2*180*deg;


  const G4double z_plane[] = {-110.*mm, -109.829*mm, -108.647*mm, -108.65*mm, -107.416*mm, -106.481*mm, -103.084*mm, -98.6401*mm, -43.6458*mm, -33.8076*mm, -27.3606*mm, -22.9623*mm, -18.0893*mm, -12.2671*mm, -5.65007*mm, 2.09728*mm, 10.6724*mm, 20.0733*mm, 29.9204*mm, 39.9182*mm, 49.8607*mm, 59.4345*mm, 68.3814*mm, 76.581*mm, 83.5154*mm, 89.9187*mm, 95.2918*mm, 99.6867*mm, 103.405*mm, 106.303*mm, 107.669*mm, 108.556*mm, 108.658*mm, 109.334*mm, 109.825*mm, 110.*mm};

  const G4double r_inner[]= {0.*mm, 0.*mm, 0.*mm, 31.*mm, 35.*mm, 36.0841*mm, 38.8759*mm, 39.9976*mm, 40.4027*mm, 43.5152*mm, 51.0925*mm, 59.8796*mm, 68.6233*mm, 76.826*mm, 84.2188*mm, 90.4598*mm, 95.1553*mm, 97.9604*mm, 99.4007*mm, 99.3384*mm, 97.8127*mm, 94.2893*mm, 88.9034*mm, 82.4206*mm, 74.5809*mm, 66.2397*mm, 56.6831*mm, 46.8337*mm, 35.3909*mm, 23.8773*mm, 13.4135*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};


  /*const G4double r_inner[]= {0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};
  */

  const G4double r_outer[]= {0.*mm, 32.0648*mm, 35.6705*mm, 35.6705*mm, 37.4533*mm, 38.4624*mm, 40.5955*mm, 41.5084*mm, 41.9043*mm, 45.2687*mm, 54.2783*mm, 63.2852*mm, 71.4126*mm, 79.2565*mm, 86.3265*mm, 92.3066*mm, 96.803*mm, 99.5055*mm, 100.905*mm, 100.846*mm, 99.3918*mm, 95.9735*mm, 90.7321*mm, 84.4727*mm, 76.9557*mm, 68.9368*mm, 60.0639*mm, 50.8971*mm, 41.1194*mm, 30.596*mm, 25.291*mm, 20.8952*mm, 20.3897*mm, 13.4348*mm, 8.53213*mm, 0.*mm};

  G4Polycone *PMTGlass8Inches = new G4Polycone("PMTGlass8Inches",
  Phi_start,
  Phi_end,
  N_z_plane,
  z_plane,
  r_inner,
  r_outer);

  // Logical PMT glass: material borosilicate glass
  LogicalVolume = new G4LogicalVolume(PMTGlass8Inches, Material,"Logical8InchesPMTGlass",0,0,0);


  return LogicalVolume;
}


G4LogicalVolume *PMT::Get8InchesPhotocathode(){
  // Materials properties for PMT
  Material = scintProp->GetMaterial("Vacuum");


  // Define some rotations
  G4RotationMatrix Rotate;
  Rotate.rotateX(180.0*deg);
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);

  // ####################### PMT GLASS TUBE SOLID #######################
  // Solid PMT photocathode sphere
  G4int N_z_plane = 18;
  G4double Phi_start = 0.*deg;
  G4double Phi_end = 2*180*deg;


  const G4double z_plane[] = {29.9204*mm, 39.9182*mm, 49.8607*mm, 59.4345*mm, 68.3814*mm, 76.581*mm, 83.5154*mm, 89.9187*mm, 95.2918*mm, 99.6867*mm, 103.405*mm, 106.303*mm, 107.669*mm, 108.556*mm, 108.658*mm, 109.334*mm, 109.825*mm, 110.*mm};

  const G4double r_inner[]= {98.4007*mm, 98.3384*mm, 96.8127*mm, 93.2893*mm, 87.9034*mm, 81.4206*mm, 73.5809*mm, 65.2397*mm, 55.6831*mm, 45.8337*mm, 34.3909*mm, 22.8773*mm, 12.4135*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};

  const G4double r_outer[]= {99.4007*mm, 99.3384*mm, 97.8127*mm, 94.2893*mm, 88.9034*mm, 82.4206*mm, 74.5809*mm, 66.2397*mm, 56.6831*mm, 46.8337*mm, 35.3909*mm, 23.8773*mm, 13.4135*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};

  G4Polycone *Photocathode8Inches = new G4Polycone("Photocathode8Inches",
  Phi_start,
  Phi_end,
  N_z_plane,
  z_plane,
  r_inner,
  r_outer);

  //G4LogicalVolume *logical_spherical_PMT;
  LogicalVolume = new G4LogicalVolume(Photocathode8Inches,Material,"Logical8InchesPhotocathode",0,0,0);

  return LogicalVolume;
}


G4LogicalVolume *PMT::GetHPDGlass(){
  // Materials properties for PMT
  Material = scintProp->GetMaterial("bs_glass");

  G4Tubs *Tubs = new G4Tubs   ("Tubs",             //its name
  0., (50.8/2)*mm, (1./2)*mm, 0, 360*deg);    //its size

  //G4LogicalVolume *logical_spherical_PMT;
  LogicalVolume = new G4LogicalVolume(Tubs,Material,"LogicalHPDGlass",0,0,0);

  return LogicalVolume;
}


G4LogicalVolume *PMT::GetHPDPhotocathode(){
  // Materials properties for PMT
  Material = scintProp->GetMaterial("Vacuum");

  G4Tubs *Tubs = new G4Tubs   ("Tubs",             //its name
  0., (40/2)*mm, (0.1/2)*mm, 0, 360*deg);    //its size

  //G4LogicalVolume *logical_spherical_PMT;
  LogicalVolume = new G4LogicalVolume(Tubs,Material,"LogicalHPDPhotocathode",0,0,0);

  return LogicalVolume;
}
