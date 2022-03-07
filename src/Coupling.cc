/// Coupling.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimMaterials.hh"
#include "Coupling.hh"
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
#include "G4Box.hh"
#include <G4Polycone.hh>
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

using namespace CLHEP;

const G4String Coupling::path_bin = "../bin/";

Coupling::Coupling(){}

Coupling::~Coupling(){
  if(scintProp) { delete scintProp; scintProp = 0; }
  if(theScint) { delete theScint; theScint = 0; }
}

G4LogicalVolume *Coupling::GetSNMW_8InchesSphericalCoupling(){

  Material = scintProp->GetMaterial("cargille");
  theScint = new Scintillator(path_bin+"ENLOpticalSim.cfg");

  //TEST COUPLING RTV615

  // Read in and define dimensions
  SNMW_CouplingSphereRadius = theScint->GetSNMW_CouplingRadius();
  SNMW_CouplingSphereDepth = theScint->GetSNMW_CouplingDepth();
  PMTGlassRadius = theScint->GetPMTGlassRadius();
  GlueThickness = theScint->GetGlueThickness();
  //  G4cout << " Coupling angle = " << acos((CouplingSphereRadius-CouplingDepth)/CouplingSphereRadius) << G4endl;

  // Define translations used for adding or subtracting volumes
  G4double CouplingSphereSubtraction = SNMW_CouplingSphereRadius - PMTGlassRadius - GlueThickness;

  // Define some rotations
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0.0*deg);
  G4RotationMatrix Flip;
  Flip.rotateX(180.0*deg);


  // ####################### COUPLING SPHERE #######################
  G4int N_z_plane_glue = 17;
  G4double Phi_start = 0.*deg;
  G4double Phi_end = 2*180*deg;

  const G4double z_plane_glue[] = {39.9182*mm, 49.8607*mm, 59.4345*mm, 68.3814*mm, 76.581*mm, 83.5154*mm, 89.9187*mm, 95.2918*mm, 99.6867*mm, 103.405*mm, 106.303*mm, 107.669*mm, 108.556*mm, 108.658*mm, 109.334*mm, 109.825*mm, 110.*mm};

  const G4double r_inner_glue[]= {0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};


  const G4double r_outer_glue[]= {102.846*mm, 101.3918*mm, 97.9735*mm, 92.7321*mm, 86.4727*mm, 78.9557*mm, 70.9368*mm, 62.0639*mm, 52.8971*mm, 43.1194*mm, 32.596*mm, 27.291*mm, 22.8952*mm, 22.3897*mm, 15.4348*mm, 10.53213*mm, 2.*mm};

  G4Polycone *Glue8Inches = new G4Polycone("Glue9Inches",
  Phi_start,
  Phi_end,
  N_z_plane_glue,
  z_plane_glue,
  r_inner_glue,
  r_outer_glue);




  // ####################### PMT GLASS SOLID SUBTRACTION #######################
  G4int N_z_plane = 36;


  const G4double z_plane_extrusion[] = {-110.*mm, -109.829*mm, -108.647*mm, -108.65*mm, -107.416*mm, -106.481*mm, -103.084*mm, -98.6401*mm, -43.6458*mm, -33.8076*mm, -27.3606*mm, -22.9623*mm, -18.0893*mm, -12.2671*mm, -5.65007*mm, 2.09728*mm, 10.6724*mm, 20.0733*mm, 29.9204*mm, 39.9182*mm, 49.8607*mm, 59.4345*mm, 68.3814*mm, 76.581*mm, 83.5154*mm, 89.9187*mm, 95.2918*mm, 99.6867*mm, 103.405*mm, 106.303*mm, 107.669*mm, 108.556*mm, 108.658*mm, 109.334*mm, 109.825*mm, 110.*mm};

  const G4double r_inner_extrusion[]= {0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};

  const G4double r_outer_extrusion[]= {0.*mm, 32.0648*mm, 35.6705*mm, 35.6705*mm, 37.4533*mm, 38.4624*mm, 40.5955*mm, 41.5084*mm, 41.9043*mm, 45.2687*mm, 54.2783*mm, 63.2852*mm, 71.4126*mm, 79.2565*mm, 86.3265*mm, 92.3066*mm, 96.803*mm, 99.5055*mm, 100.905*mm, 100.846*mm, 99.3918*mm, 95.9735*mm, 90.7321*mm, 84.4727*mm, 76.9557*mm, 68.9368*mm, 60.0639*mm, 50.8971*mm, 41.1194*mm, 30.596*mm, 25.291*mm, 20.8952*mm, 20.3897*mm, 13.4348*mm, 8.53213*mm, 0.*mm};

  G4Polycone *PMTGlass8InchesExtrusion = new G4Polycone("PMTGlass8InchesExtrusion",
  Phi_start,
  Phi_end,
  N_z_plane,
  z_plane_extrusion,
  r_inner_extrusion,
  r_outer_extrusion);


  // Subtract smaller sphere from the larger to make shell
  G4SubtractionSolid* FinalCoupling8Inches = new G4SubtractionSolid("FinalCoupling8Inches",
  Glue8Inches,
  PMTGlass8InchesExtrusion,
  G4Transform3D(DontRotate,G4ThreeVector(0, 0, 0)));

  // Llogical volume: material RTV
  LogicalVolume = new G4LogicalVolume(FinalCoupling8Inches, Material,"LogicalSNMW_8InchesCouplingSphere",0,0,0);





  return LogicalVolume;
}



G4LogicalVolume *Coupling::GetHPDGrease(){

  scintProp = new ENLOpticalSimMaterials(path_bin+"Materials.cfg");
  Material = scintProp->GetMaterial("cargille");

  G4Tubs *Tubs = new G4Tubs   ("Tubs",             //its name
  0., (45/2)*mm, (0.1/2)*mm, 0, 360*deg);    //its size

  // Logical volume for FinalScint: material = scintillator
  LogicalVolume = new G4LogicalVolume(Tubs, Material, "LogicalHPDGrease",0,0,0);


  return LogicalVolume;
}
