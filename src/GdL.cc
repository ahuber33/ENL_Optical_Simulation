/// GdL.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimMaterials.hh"
#include "GdL.hh"
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
#include "G4Trap.hh"
#include <G4Polycone.hh>
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

using namespace CLHEP;

const G4String GdL::path_bin = "../bin/";

GdL::GdL(){}

GdL::~GdL(){
  if(scintProp) { delete scintProp; scintProp = 0; }
}



G4LogicalVolume *GdL::Get_GdL(){
  // Material Properties for scint
  scintProp = new ENLOpticalSimMaterials(path_bin+"Materials.cfg");
  Material = scintProp->GetMaterial("PMMA");

  G4double larg_scinti      =  12.000;    //en cm
  G4double long_scinti      =  8.500;     //en cm
  G4double larg_light_guide =  13.000;    //en cm
  G4double long_light_guide =  9.500;     //en cm
  G4double ep_light_guide   =  1.000;     //en cm
  G4double prof_emp_scinti =  0.050;     //en cm
  double theta = acos(53.0 / 58.4316);
  double phi = atan(15.0 / 19.765);


  G4Box *fSolidTarget_3_1 = new G4Box   ("Target_3_1",		                                               //its name
  //long_light_guide/2*cm, larg_light_guide/2*cm, ep_light_guide/2*cm);    //its size
  ep_light_guide/2*cm, larg_light_guide/2*cm, long_light_guide/2*cm);    //its size

  G4Box *fSolidTarget_3_2 = new G4Box   ("Target_3_2",	       	                                               //its name
  // (long_scinti+1.)/2.*cm, (larg_scinti+1.)/2.*cm, prof_emp_scinti/2*cm);   //its size -- le "+1" sert à ajouter un peu de place pour mettre le scintillateur
  //(long_scinti)/2.*cm, (larg_scinti)/2.*cm, prof_emp_scinti/2*cm);   //its size -- le "+1" sert à ajouter un peu de place pour mettre le scintillateur
  (prof_emp_scinti)/2.*cm, (larg_scinti+0.2)/2.*cm, (long_scinti+0.2)/2*cm);   //its size -- le "+1" sert à ajouter un peu de place pour mettre le scintillateur



  G4RotationMatrix* noRotGdL = new G4RotationMatrix(0.,0.,0.);
  G4ThreeVector aTransGdL(-(ep_light_guide/2-prof_emp_scinti/2.)*cm, 0*cm, 0*cm);

  G4SubtractionSolid* fSolidTarget_3_3 = new G4SubtractionSolid("Target_3_3", fSolidTarget_3_1,fSolidTarget_3_2,noRotGdL,aTransGdL);


  G4Trap *fSolidTarget_3_4 = new G4Trap("Target_3_4",
  53.0/2.0, //Dz
  theta, //theta
  phi, //phi
  130.0/2.0, //Dy1
  10.0/2.0, //Dx1
  10.0/2.0, //Dx2
  0.*deg, //Alpha1
  29.0/2.0, //Dy2
  20.0/2.0, //Dx3
  20.0/2.0, //Dx4
  0.*deg); //Alpha2


  G4ThreeVector aTransGdL_1(9.7986*mm, 7.44*mm, 74.0*mm);//
  G4RotationMatrix* noRotGdL_1 = new G4RotationMatrix(0.*deg,0.*deg,0.*deg);//


  G4UnionSolid* Light_Guide = new G4UnionSolid("Light_Guide", fSolidTarget_3_3,fSolidTarget_3_4,noRotGdL_1,aTransGdL_1);



  // Logical volume for FinalScint: material = scintillator
  //LogicalLGSc = new G4LogicalVolume(fSolidTarget_3_3, scintillator, "LogicalLGSc",0,0,0);
  LogicalVolume = new G4LogicalVolume(Light_Guide, Material, "LogicalGdL",0,0,0);


  return LogicalVolume;
}
