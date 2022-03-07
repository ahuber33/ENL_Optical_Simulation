// Scintillator.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLOpticalSimMaterials.hh"
#include "Scintillator.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Transform3D.hh"
#include "G4UnionSolid.hh"
#include <fstream>
#include <iostream>
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include <G4Polycone.hh>
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include <math.h>

//#ifndef disable_gdml
#include "G4GDMLParser.hh"
//#endif


using namespace CLHEP;

// ***********************
// Constructor
// ***********************
const G4String Scintillator::path_bin = "../bin/";


Scintillator::Scintillator(G4String buildfile){

  // Read keys and values from file buildfile defined in x_blockGeometry.cc
  // Some of these variables may not be needed.
  std::ifstream config;
  config.open(buildfile);
  if ( !config.is_open() )
    G4cout << "Error opening file " << buildfile << G4endl;
  else{
    while( config.is_open() ){
      G4String variable;
      G4String unit;
      G4double value;

      config >> variable;
      if(!config.good()) break;
      //####################### COMMON variables ###########################
      if(variable == "ScintillatorLength"){
  	config >> value >> unit;
  	ScintillatorLength = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "ScintillatorThickness"){
  	config >> value >> unit;
  	ScintillatorThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      if(variable == "TeflonThickness"){
        config >> value >> unit;
        TeflonThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "AirGapTeflon"){
        config >> value >> unit;
        AirGapTeflon = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "MylarThickness"){
        config >> value >> unit;
        MylarThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "AirGapMylar"){
        config >> value >> unit;
        AirGapMylar = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "MylarThickness"){
  	config >> value >> unit;
  	MylarThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "AirGapMylar"){
  	config >> value >> unit;
  	AirGapMylar = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "GlueThickness"){
  	config >> value >> unit;
  	GlueThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      // PMT 5 inches Dimensions
    //   else if(variable == "PMTGlassRadius"){
  	// config >> value >> unit;
  	// PMTGlassRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "PMTGlassThickness"){
  	// config >> value >> unit;
  	// PMTGlassThickness = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "PMTRearGlassRadius"){
  	// config >> value >> unit;
  	// PMTRearGlassRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "PMTPhotocathodeThickness"){
  	// config >> value >> unit;
  	// PMTPhotocathodeThickness = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "PMTGlassTubeRadius"){
  	// config >> value >> unit;
  	// PMTGlassTubeRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "PMTGlassTubeHeight"){
  	// config >> value >> unit;
  	// PMTGlassTubeHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   //####################### SuperNEMO Main Wall variables ###########################
      // Scint Block Dimensions
      else if (variable == "SNMW_ScintStepWidth"){
  	config >> value >> unit;
  	SNMW_ScintStepWidth = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "SNMW_ScintStepHeight"){
  	config >> value >> unit;
  	SNMW_ScintStepHeight = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "SNMW_ScintBodyWidth"){
  	config >> value >> unit;
  	SNMW_ScintBodyWidth = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "SNMW_ScintBodyHeight"){
  	config >> value >> unit;
  	SNMW_ScintBodyHeight = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "SNMW_CouplingSphereRadius"){
  	config >> value >> unit;
  	SNMW_CouplingSphereRadius = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "SNMW_CouplingSphereDepth"){
  	config >> value >> unit;
  	SNMW_CouplingSphereDepth = value*G4UnitDefinition::GetValueOf(unit);
      }

    //   //####################### NEMO 3 EC  variables ###########################
    //   // GM Dimensions
    //   else if(variable == "N3EC_ScintWidth"){
  	// config >> value >> unit;
  	// N3EC_ScintWidth = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_ScintHeight"){
  	// config >> value >> unit;
  	// N3EC_ScintHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   // Light Guide Dimensions
    //   else if(variable == "N3EC_LightGuideRadius"){
  	// config >> value >> unit;
  	// N3EC_LightGuideRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_LightGuideHeight"){
  	// config >> value >> unit;
  	// N3EC_LightGuideHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_LightGuideCouplingRadius"){
  	// config >> value >> unit;
  	// N3EC_LightGuideCouplingRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_LightGuideCouplingHeight"){
  	// config >> value >> unit;
  	// N3EC_LightGuideCouplingHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_CouplingSphereDepth"){
  	// config >> value >> unit;
  	// N3EC_CouplingSphereDepth = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_InterfaceLightGuideHeight"){
  	// config >> value >> unit;
  	// N3EC_InterfaceLightGuideHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_LightGuideStepHeight"){
  	// config >> value >> unit;
  	// N3EC_LightGuideStepHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3EC_CouplingSphereRadius"){
  	// config >> value >> unit;
  	// N3EC_CouplingSphereRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   //####################### SuperNEMO XWALL  variables ###########################
    //   // GM Dimensions
    //   else if(variable == "SNXW_ScintWidth"){
  	// config >> value >> unit;
  	// SNXW_ScintWidth = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "SNXW_ScintHeight"){
  	// config >> value >> unit;
  	// SNXW_ScintHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   // Light Guide Dimensions
    //   else if(variable == "SNXW_LightGuideRadius"){
  	// config >> value >> unit;
  	// SNXW_LightGuideRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "SNXW_LightGuideHeight"){
  	// config >> value >> unit;
  	// SNXW_LightGuideHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "SNXW_LightGuideCouplingHeight"){
  	// config >> value >> unit;
  	// SNXW_LightGuideCouplingHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "SNXW_CouplingSphereDepth"){
  	// config >> value >> unit;
  	// SNXW_CouplingSphereDepth = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "SNXW_CouplingSphereRadius"){
  	// config >> value >> unit;
  	// SNXW_CouplingSphereRadius = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   //########################### N3MO3 L4  variables ###########################
    //   // GM Dimensions
    //   else if(variable == "N3L4_ScintLength"){
  	// config >> value >> unit;
  	// N3L4_ScintLength = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3L4_ScintWidth"){
  	// config >> value >> unit;
  	// N3L4_ScintWidth = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    //   else if(variable == "N3L4_ScintHeight"){
  	// config >> value >> unit;
  	// N3L4_ScintHeight = value*G4UnitDefinition::GetValueOf(unit);
    //   }
    }
  }
  config.close();



    G4cout << "\n The Variables that we read in are: "
    << "\n ScintillatorLength = " << ScintillatorLength
    << "\n ScintillatorThickness = " << ScintillatorThickness
    << "\n SNMW_ScintStepWidth = " << SNMW_ScintStepWidth
    << "\n SNMW_ScintStepHeight = " << SNMW_ScintStepHeight
    << "\n SNMW_cintBodyWidth = " << SNMW_ScintBodyWidth
    << "\n SNMW_ScintBodyHeight = " << SNMW_ScintBodyHeight
    << "\n SNMW_CouplingSphereRadius = " << SNMW_CouplingSphereRadius
    << "\n SNMW_CouplingSphereDepth = " << SNMW_CouplingSphereDepth
    << "\n Teflon thickness = " << TeflonThickness
    << "\n Air gap Teflon = " << AirGapTeflon
    << "\n Mylar thickness = " << MylarThickness
    << "\n Air gap Mylar = " << AirGapMylar
    << "\n Glue Thickness = " << GlueThickness
    << "\n " << G4endl;

}
// ***********************
// Destructor
// ***********************
Scintillator::~Scintillator(){
  if(scintProp) { delete scintProp; scintProp = 0; }
  if(clear) { delete clear; clear = 0; }
}


G4LogicalVolume *Scintillator::GetScTest(){

  Material = scintProp->GetMaterial("scintillator");
  //scintillator = scintProp->GetMaterial("Alu");

  G4Box *Box = new G4Box   ("Box",             //its name
  			    ScintillatorLength/2, ScintillatorLength/2, ScintillatorThickness/2);    //its size

  LogicalVolume = new G4LogicalVolume(Box, Material, "Sc_Test",0,0,0);

  return LogicalVolume;
}



G4LogicalVolume *Scintillator::GetLaBr3(){

  Material = scintProp->GetMaterial("LaBr3");

  G4Tubs *Tubs = new G4Tubs   ("Tubs",             //its name
  			    //0., (38.1/2)*mm, (38.1/2)*mm, 0, 360*deg);    //its size
            0., (38.1/2)*mm, (38.1/2)*mm, 0, 360*deg);    //its size
  LogicalVolume = new G4LogicalVolume(Tubs, Material, "LaBr3",0,0,0);

  return LogicalVolume;
}



G4LogicalVolume *Scintillator::GetLaBr3PMMA(){

  Material = scintProp->GetMaterial("PMMA");

  G4Tubs *Tubs = new G4Tubs   ("Tubs",             //its name
  			    0., (38.1/2)*mm, (5./2)*mm, 0, 360*deg);    //its size

  LogicalVolume = new G4LogicalVolume(Tubs, Material, "LaBr3PMMA",0,0,0);

  return LogicalVolume;
}


G4LogicalVolume *Scintillator::GetBoitierAluHPD(){

  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0*deg);

  Material = scintProp->GetMaterial("Alu");

  G4Tubs *Tubs1 = new G4Tubs   ("Tubs1",             //its name
  			    0., (41.5/2)*mm, (45.5/2)*mm, 0, 360*deg);    //its size

  G4Tubs *Tubs2 = new G4Tubs   ("Tubs2",             //its name
  			    0., (40.5/2)*mm, (45.5/2)*mm, 0, 360*deg);    //its size

 G4SubtractionSolid* Tubs = new G4SubtractionSolid("Tubs", Tubs1, Tubs2, G4Transform3D(DontRotate,G4ThreeVector(0,0,0.5*mm)));

  LogicalVolume = new G4LogicalVolume(Tubs, Material, "BoitierAluHPD",0,0,0);

  return LogicalVolume;


}



G4LogicalVolume *Scintillator::GetBoitierAluPM(){

  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0*deg);

  Material = scintProp->GetMaterial("Alu");

G4int N_z_plane = 5;
G4double Phi_start = 0.*deg;
G4double Phi_end = 2*180*deg;

const G4double z_plane[] = {0*mm, 92.5*mm, 97.5*mm, 131*mm, 131.5*mm};

const G4double r_inner[]= {(0/2)*mm, (0/2)*mm, (0/2)*mm, 0*mm, 0*mm};


const G4double r_outer[]= {(58.7/2)*mm, (58.7/2)*mm, (43./2)*mm, (43./2)*mm, 21.5*mm};

  G4Polycone *Polycone1 = new G4Polycone("Polycone1",
			Phi_start,
			Phi_end,
			N_z_plane,
			z_plane,
			r_inner,
			r_outer);

const G4double z_plane2[] = {0*mm, 92.5*mm, 97.5*mm, 131*mm, 131*mm};

const G4double r_inner2[]= {0*mm, 0*mm, 0*mm, 0*mm, 0*mm};

const G4double r_outer2[]= {(57.7/2)*mm, (57.7/2)*mm, (42./2)*mm, (42./2)*mm, (42./2)*mm};

G4Polycone *Polycone2 = new G4Polycone("Polycone2",
    Phi_start,
    Phi_end,
    N_z_plane,
    z_plane2,
    r_inner2,
    r_outer2);

G4SubtractionSolid* Polycone = new G4SubtractionSolid("Polycone", Polycone1, Polycone2, G4Transform3D(DontRotate,G4ThreeVector(0,0,0*mm)));

  LogicalVolume = new G4LogicalVolume(Polycone, Material, "BoitierAluPM",0,0,0);

  return LogicalVolume;
}




G4LogicalVolume *Scintillator::GetGM_LND(){
  // Material Properties for scint
  //scintProp = new ENLOpticalSimMaterials(path_bin+"Materials.cfg");
  Material = scintProp->GetMaterial("Inox");

#ifndef disable_gdm
  //G4NistManager* nist = G4NistManager::Instance();
  G4GDMLParser* parser = new G4GDMLParser();
  //Create Tesselated volume of "Bouchon"
  parser->Clear();
  parser->Read("../gdml_models/GM_Dolphy_complet_GM_LND_71-324.gdml", false);
  LogicalVolume = parser->GetVolume("GM Dolphy complet - GM LND 71-324-1");
  LogicalVolume->SetMaterial(Material);
#else
  //
#endif

  return LogicalVolume;
}

//************************************************************************************
//************************************************************************************
//********************** SUPERNEMO MAIN WALL 8 INCHES(SNMW) **************************
//************************************************************************************
//************************************************************************************

// ***********************
// Builds Scintitllator Block
// ***********************
G4LogicalVolume *Scintillator::GetSNMW_8InchesScint(){
  // Material Properties for scint
  //scintillator = scintProp->GetMaterial("scintillator");
  Material = scintProp->GetMaterial("LaBr3");

  // Define some translations used for joining or subtracting
   Step_BodyUnion = SNMW_ScintStepHeight/2 + SNMW_ScintBodyHeight/2;
   Block_SphereSubtraction = SNMW_ScintStepHeight/2 + SNMW_ScintBodyHeight + SNMW_CouplingSphereRadius - SNMW_CouplingSphereDepth; // Center of union will be center of step


  // Define some rotations
  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0*deg);
  G4RotationMatrix Rotate;
  Rotate.rotateX(180*deg);

  // ####################### SCINT BLOCK #######################
  // Scintillator Step
  G4Box *Step8Inches = new G4Box("Step8Inches",
			  SNMW_ScintStepWidth/2, SNMW_ScintStepWidth/2,
			  SNMW_ScintStepHeight/2);

  // Scintillator Main Body
  G4Box *MainBody8Inches = new G4Box("MainBody8Inches",
			      SNMW_ScintBodyWidth/2, SNMW_ScintBodyWidth/2,
			      SNMW_ScintBodyHeight/2);

  // Union of two volumes: Center will be at the center of first volume defined in union -> Step center
  // Last argument diplaces the body center relative to step center before joining
  G4UnionSolid* SolidScint8Inches = new G4UnionSolid("Step+MainBody",Step8Inches,MainBody8Inches,G4Transform3D(DontRotate,G4ThreeVector(0,0,Step_BodyUnion)));

  // ####################### COUPLING SPHERE #######################
G4int N_z_plane_glue_extrusion = 36;
G4double Phi_start = 0.*deg;
G4double Phi_end = 2*180*deg;

const G4double z_plane_glue_extrusion[] = {-110.*mm, -109.829*mm, -108.647*mm, -108.65*mm, -107.416*mm, -106.481*mm, -103.084*mm, -98.6401*mm, -43.6458*mm, -33.8076*mm, -27.3606*mm, -22.9623*mm, -18.0893*mm, -12.2671*mm, -5.65007*mm, 2.09728*mm, 10.6724*mm, 20.0733*mm, 29.9204*mm, 39.9182*mm, 49.8607*mm, 59.4345*mm, 68.3814*mm, 76.581*mm, 83.5154*mm, 89.9187*mm, 95.2918*mm, 99.6867*mm, 103.405*mm, 106.303*mm, 107.669*mm, 108.556*mm, 108.658*mm, 109.334*mm, 109.825*mm, 110.*mm};

const G4double r_inner_glue_extrusion[]= {0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};


const G4double r_outer_glue_extrusion[]= {2.*mm, 34.0648*mm, 37.6705*mm, 37.6705*mm, 39.4533*mm, 40.4624*mm, 42.5955*mm, 43.5084*mm, 43.9043*mm, 47.2687*mm, 56.2783*mm, 65.2852*mm, 73.4126*mm, 81.2565*mm, 88.3265*mm, 94.3066*mm, 98.803*mm, 101.5055*mm, 102.905*mm, 102.846*mm, 101.3918*mm, 97.9735*mm, 92.7321*mm, 86.4727*mm, 78.9557*mm, 70.9368*mm, 62.0639*mm, 52.8971*mm, 43.1194*mm, 32.596*mm, 27.291*mm, 22.8952*mm, 22.3897*mm, 15.4348*mm, 10.53213*mm, 2.*mm};

  G4Polycone *GlueExtrusion = new G4Polycone("Glue extrusion",
			Phi_start,
			Phi_end,
			N_z_plane_glue_extrusion,
			z_plane_glue_extrusion,
			r_inner_glue_extrusion,
			r_outer_glue_extrusion);


  // ####################### FINAL BLOCK #######################
  // Subtract 2nd volume from the 1st
  // SphereBlockTranslation = dist. from step center to center of sphere position where subtraction will occur

  G4SubtractionSolid* FinalScint8Inches = new G4SubtractionSolid("FinalScint_8inches",SolidScint8Inches,GlueExtrusion,G4Transform3D(Rotate,G4ThreeVector(0,0,+220.*mm)));




  // Logical volume for FinalScint: material = scintillator

  LogicalVolume = new G4LogicalVolume(FinalScint8Inches, Material, "LogicalFinalScint8Inches",0,0,0);

  //G4VisAttributes * clear;
  //clear = new G4VisAttributes( G4Colour(255/255. ,255/255. ,255/255. ));

  return LogicalVolume;
}


// ***********************
// Builds Mylar wrapping
// ***********************
G4LogicalVolume *Scintillator::GetSNMW_8InchesMylar(){
  // Define materials
  Material = scintProp->GetMaterial("mylar");

  // Define some translations used for joining or subtracting
  MylarStep_BodyUnion = (MylarThickness+AirGapMylar+SNMW_ScintStepHeight+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2 + (MylarThickness+AirGapMylar+SNMW_ScintBodyHeight-AirGapTeflon-TeflonThickness-AirGapMylar-MylarThickness)/2 ;
  TeflonStep_BodyUnion = (AirGapMylar+SNMW_ScintStepHeight+AirGapTeflon+TeflonThickness+AirGapMylar)/2 + (AirGapMylar+SNMW_ScintBodyHeight-AirGapTeflon-TeflonThickness-AirGapMylar)/2 ;
  //  G4double Mylar_TeflonSubtraction = (SNMW_ScintStepHeight+AirGapMylar+TeflonThickness+AirGapTeflon)/2 - SNMW_ScintStepHeight/2;
  Mylar_SphereSubtraction = MylarThickness+AirGapMylar+SNMW_ScintStepHeight+SNMW_ScintBodyHeight+SNMW_CouplingSphereRadius-SNMW_CouplingSphereDepth-(MylarThickness+AirGapMylar+SNMW_ScintStepHeight+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2;
   G4cout << "Mylar step + body union translation = " << MylarStep_BodyUnion
          << "\nTeflon step + body union translation = " << TeflonStep_BodyUnion
     //          << "\nMylar - teflon subtraction translation = " << Mylar_TeflonSubtraction
          << "\nMylar - sphere subtraction translation = " << Mylar_SphereSubtraction << G4endl;

  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0*deg);
  G4RotationMatrix Rotate;
  Rotate.rotateX(180*deg);

  // ####################### MYLAR SOLID #######################
  // Mylar step
  G4Box *MylarStep8Inches = new G4Box("MylarStep8Inches",
			       (MylarThickness+AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2, // 2 air gaps & Teflon & Mlyar thickness EACH side
			       (MylarThickness+AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2,
			       (MylarThickness+AirGapMylar+SNMW_ScintStepHeight+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2);  // Bottom to top layers

  // Mylar Main Body
  G4Box *MylarMainBody8Inches = new G4Box("MylarMainBody8Inches",
				   (MylarThickness+AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2,
				   (MylarThickness+AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon+TeflonThickness+AirGapMylar+MylarThickness)/2,
				   (MylarThickness+AirGapMylar+SNMW_ScintBodyHeight-AirGapTeflon-TeflonThickness-AirGapMylar-MylarThickness)/2); //Now accounts for BOTH Teflon and Mylar and all air gaps: top to bottom

  // Union of two volumes: Just as with Teflon above
  G4UnionSolid* SolidMylar8Inches = new G4UnionSolid("MylarStep+MylarMainBody",MylarStep8Inches,MylarMainBody8Inches,G4Transform3D(DontRotate,G4ThreeVector(0,0,MylarStep_BodyUnion)));

  // Easy way again is to subtract a Teflon solid (and air gaps)... but we need to remake it
  // ####################### TEFLON SOLID #######################
  // Teflon step
  G4Box *TeflonStep8Inches = new G4Box("TeflonStep8Inches",
				(AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon+TeflonThickness+AirGapMylar)/2,
				(AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon+TeflonThickness+AirGapMylar)/2,
				(AirGapMylar+SNMW_ScintStepHeight+AirGapTeflon+TeflonThickness+AirGapMylar)/2);  // Teflon doesn't cover top and bottom BUT needs to cover top of step

  // Teflon Main Body
  G4Box *TeflonMainBody8Inches = new G4Box("TeflonMainBody8Inches",
				    (AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon+TeflonThickness+AirGapMylar)/2,
				    (AirGapMylar+TeflonThickness+AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon+TeflonThickness+AirGapMylar)/2,
				    (AirGapMylar+SNMW_ScintBodyHeight-AirGapTeflon-TeflonThickness-AirGapMylar)/2);

  // Union of two Teflon volumes
  G4UnionSolid* SolidTeflon8Inches = new G4UnionSolid("TeflonStep+TeflonMainBody",TeflonStep8Inches,TeflonMainBody8Inches,G4Transform3D(DontRotate,G4ThreeVector(0,0,TeflonStep_BodyUnion)));

  // ####################### MYLAR WRAP #######################
  // Now we just need to subract the Teflon to leave the Mylar wrap on all sides
  G4SubtractionSolid* MylarWrap8Inches = new G4SubtractionSolid("MylarWrap8Inches",
							 SolidMylar8Inches,
							 SolidTeflon8Inches,
							 //							 G4Transform3D(Rotate,G4ThreeVector(0,0,Mylar_TeflonSubtraction)));
							 G4Transform3D(DontRotate,G4ThreeVector(0,0,0)));

  // Lastly, since there is Mylar on top we need to subtract the coupling sphere to leave an opening for the PMT
G4int N_z_plane_glue_extrusion = 36;
G4double Phi_start = 0.*deg;
G4double Phi_end = 2*180*deg;

const G4double z_plane_glue_extrusion[] = {-110.*mm, -109.829*mm, -108.647*mm, -108.65*mm, -107.416*mm, -106.481*mm, -103.084*mm, -98.6401*mm, -43.6458*mm, -33.8076*mm, -27.3606*mm, -22.9623*mm, -18.0893*mm, -12.2671*mm, -5.65007*mm, 2.09728*mm, 10.6724*mm, 20.0733*mm, 29.9204*mm, 39.9182*mm, 49.8607*mm, 59.4345*mm, 68.3814*mm, 76.581*mm, 83.5154*mm, 89.9187*mm, 95.2918*mm, 99.6867*mm, 103.405*mm, 106.303*mm, 107.669*mm, 108.556*mm, 108.658*mm, 109.334*mm, 109.825*mm, 110.*mm};

const G4double r_inner_glue_extrusion[]= {0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm};


const G4double r_outer_glue_extrusion[]= {2.*mm, 34.0648*mm, 37.6705*mm, 37.6705*mm, 39.4533*mm, 40.4624*mm, 42.5955*mm, 43.5084*mm, 43.9043*mm, 47.2687*mm, 56.2783*mm, 65.2852*mm, 73.4126*mm, 81.2565*mm, 88.3265*mm, 94.3066*mm, 98.803*mm, 101.5055*mm, 102.905*mm, 102.846*mm, 101.3918*mm, 97.9735*mm, 92.7321*mm, 86.4727*mm, 78.9557*mm, 70.9368*mm, 62.0639*mm, 52.8971*mm, 43.1194*mm, 32.596*mm, 27.291*mm, 22.8952*mm, 22.3897*mm, 15.4348*mm, 10.53213*mm, 2.*mm};

  G4Polycone *GlueExtrusion = new G4Polycone("Glue extrusion",
			Phi_start,
			Phi_end,
			N_z_plane_glue_extrusion,
			z_plane_glue_extrusion,
			r_inner_glue_extrusion,
			r_outer_glue_extrusion);

  // Subtracting the coupling sphere
  G4SubtractionSolid* FinalMylarWrap8Inches = new G4SubtractionSolid("FinalMylarWrap8Inches", MylarWrap8Inches,GlueExtrusion,G4Transform3D(Rotate,G4ThreeVector(0,0,+219.706*mm)));

  // Logical volume for Mylar: material = coating?

  LogicalVolume = new G4LogicalVolume(FinalMylarWrap8Inches, Material, "LogicalMylarWrap8inches",0,0,0);


  return LogicalVolume;
}


// ***********************
// Builds Teflon wrapping
// ***********************
G4LogicalVolume *Scintillator::GetSNMW_Teflon(){
  // Define materials
  Material = scintProp->GetMaterial("teflon"); // Why is this plastic? Need to add Teflon?

  // Define some translations used for joining or subtracting
  TeflonStep_BodyUnion = SNMW_ScintStepHeight/2 + SNMW_ScintBodyHeight/2;
  Teflon_ScintSubtraction = (SNMW_ScintStepHeight + AirGapTeflon + TeflonThickness)/2 - SNMW_ScintStepHeight/2;
   G4cout << "Teflon step + body union translation = " << TeflonStep_BodyUnion
          << "\nTeflon - scint subtraction translation = " << Teflon_ScintSubtraction << G4endl;

  G4RotationMatrix DontRotate;
  DontRotate.rotateX(0*deg);
  G4RotationMatrix Rotate;
  Rotate.rotateX(180*deg);

  // ####################### TEFLON SOLID #######################
  // Teflon step
  G4Box *TeflonStep = new G4Box("TeflonStep",
				(TeflonThickness+AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon+TeflonThickness)/2, // Add air gap and teflon thickness to EACH side (x2)
				(TeflonThickness+AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon+TeflonThickness)/2, // Length = Width
				(SNMW_ScintStepHeight+AirGapTeflon+TeflonThickness)/2);  // Teflon doesn't cover top and bottom BUT needs to cover top of step

  // Teflon main body
  G4Box *TeflonMainBody = new G4Box("TeflonMainBody",
				    (TeflonThickness+AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon+TeflonThickness)/2,
				    (TeflonThickness+AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon+TeflonThickness)/2,
				    (SNMW_ScintBodyHeight-AirGapTeflon-TeflonThickness)/2); //Overall height must equal Scint block to leave no teflon above or below

  // Union of two volumes: Just as with scintillator
  G4UnionSolid* SolidTeflon = new G4UnionSolid("TeflonStep+TeflonMainBody",TeflonStep,TeflonMainBody,G4Transform3D(DontRotate,G4ThreeVector(0,0,TeflonStep_BodyUnion)));

  // ####################### SCINT SOLID #######################
  // Easy way now is to subtract scint block (and any air gaps) to leave only wrap... be we need to remake it
  // Scintillator Step
  G4Box *Step = new G4Box("Step",
			  (AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon)/2,
			  (AirGapTeflon+SNMW_ScintStepWidth+AirGapTeflon)/2,
			  SNMW_ScintStepHeight/2+AirGapTeflon);

  // Scintillator Main Body
  G4Box *MainBody = new G4Box("MainBody",
			      (AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon)/2,
			      (AirGapTeflon+SNMW_ScintBodyWidth+AirGapTeflon)/2,
			      SNMW_ScintBodyHeight/2+AirGapTeflon);

  // Union of two volumes: Center will be at the center of first volume defined in union -> Step center
  G4UnionSolid* SolidScint = new G4UnionSolid("Step+MainBody",Step,MainBody,G4Transform3D(DontRotate,G4ThreeVector(0,0,TeflonStep_BodyUnion)));

  // ####################### TEFLON WRAP #######################
  // Now we just need to subract the scintillator to leave the Teflon wrap on just the sides
  // Displace solid scint so top and bottom edges match up
  G4SubtractionSolid* TeflonWrap = new G4SubtractionSolid("TeflonWrap",
							  SolidTeflon,
							  SolidScint,
							  G4Transform3D(DontRotate,G4ThreeVector(0,0,-Teflon_ScintSubtraction)));

  // Logical volume for Teflon: material = plastic?

  LogicalVolume = new G4LogicalVolume(TeflonWrap, Material, "LogicalTeflonWrap",0,0,0);

  return LogicalVolume;
}


G4LogicalVolume *Scintillator::GetGM_Plastique(){
  // Material Properties for scint
  Material = scintProp->GetMaterial("plastic");

  G4Box *Box_FULL = new G4Box   ("Box_FULL",             //its name
  			    2.25/2.*cm, 6.5/2.*cm, 11.8/2.*cm);    //its size

  G4Box *Box_SUB = new G4Box   ("Box_SUB",             //its name
  			    (2.25-0.6)/2.*cm, (6.5-0.6)/2.*cm, (11.8-0.6)/2.*cm);    //its size

  G4ThreeVector Trans_NULL(0*mm, 0*mm, 0*mm);//
  G4RotationMatrix* noRot = new G4RotationMatrix(0.*deg,0.*deg,0.*deg);//

  G4SubtractionSolid* Box = new G4SubtractionSolid("Box",
  							  Box_FULL,
  							  Box_SUB,
  							  noRot,
  							  Trans_NULL);



  LogicalVolume = new G4LogicalVolume(Box, Material, "GM_Plastique",0,0,0);

  return LogicalVolume;
}
