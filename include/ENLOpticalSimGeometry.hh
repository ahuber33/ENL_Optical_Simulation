/// ENLOpticalSimGeometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLOpticalSimGeometry_h
#define ENLOpticalSimGeometry_h  1

#include "G4MaterialPropertiesTable.hh"

class Scintillator;
class Coupling;
class PMT;
class GdL;
class ENLOpticalSimMaterials;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class  ENLOpticalSimGeometry:  public G4VUserDetectorConstruction
{
public:
  ENLOpticalSimGeometry();
  ~ENLOpticalSimGeometry();

public:
  G4VPhysicalVolume* Construct();
  G4LogicalVolume* GetLWorld() {return LogicalWorld;}

private:
  static const G4String path_bin;
  static const G4String path;
  // Classes for building various components
  //     LogicalHolder *holder;
  ENLOpticalSimMaterials *scintProp;
  Scintillator *theScint;
  Coupling *CouplingGlue;
  PMT *R6594;
  G4Material *Vacuum;
  G4Material *VacuumWorld;
  G4Material *Air;
  G4Material *Alu;

  // Colors for visualizations
  G4VisAttributes *invis;
  G4VisAttributes *white;
  G4VisAttributes *gray;
  G4VisAttributes *gray_bis;
  G4VisAttributes *black;
  G4VisAttributes *black_bis;
  G4VisAttributes *red;
  G4VisAttributes *red_hot;
  G4VisAttributes *orange;
  G4VisAttributes *yellow;
  G4VisAttributes *green;
  G4VisAttributes *green_hot;
  G4VisAttributes *cyan;
  G4VisAttributes *blue;
  G4VisAttributes *magenta;

  // Logical Volumes
  G4LogicalVolume *LogicalWorld;
  G4LogicalVolume *LogicalHolder;
  G4LogicalVolume *LogicalGM_LND;
  G4LogicalVolume *LogicalSc;
  G4LogicalVolume *LogicalTeflon;
  G4LogicalVolume *LogicalMylar;
  G4LogicalVolume *LogicalGlue;
  G4LogicalVolume *LogicalPM;
  G4LogicalVolume *LogicalPhotocathode;
  G4LogicalVolume *LogicalLaBr3;
  G4LogicalVolume *LogicalPMMA;
  G4LogicalVolume *LogicalBoitierAlu;


  // Physical volumes
  G4VPhysicalVolume *PhysicalWorld;
  G4VPhysicalVolume *PhysicalHolder;
  G4VPhysicalVolume *PhysicalGM_LND;
  G4VPhysicalVolume *PhysicalSc;
  G4VPhysicalVolume *PhysicalTeflon;
  G4VPhysicalVolume *PhysicalMylar;
  G4VPhysicalVolume *PhysicalGlue;
  G4VPhysicalVolume *PhysicalPM;
  G4VPhysicalVolume *PhysicalPhotocathode;
  G4VPhysicalVolume *PhysicalPMMA;
  G4VPhysicalVolume *PhysicalBoitierAlu;


  G4LogicalVolume *experimentalHall_log,
  *MS_IP_log,*protective_MS_log,*phosphor_MS_log,*support_MS_log,*magnetic_MS_log,
  *SR_IP_log,*protective_SR_log,*phosphor_SR_log,*support_SR_log,*magnetic_SR_log,
  *TR_IP_log,*phosphor_TR_log,*support_TR_log,*magnetic_TR_log,
  *ND_IP_log,*phosphor_ND_log,*support_ND_log,*magnetic_ND_log,*protective_ND_log,
  *filtre_PEHD_log,*filtre_mylar_log,*filtre_al_log,*filtre_ti_log,*filtre_fe_log,
  *filtre_cu_log,*filtre_mo_log,*filtre_ag_log,*filtre_sn_log,*filtre_ta_log,
  *filtre_au_log,*filtre_pb1_log,*filtre_pb2_log,*filtre_pb3_log,*filtre_pb4_log,
  *filtre_pb5_log,*filtre_pb6_log, *filtre_al_back_log,*filtre_pb_back_log,
  *blindage_1_log, *blindage_2_log, *blindage_3_log, *blindage_4_log, *blindage_5_log, *blindage_6_log;

  G4VPhysicalVolume *experimentalHall_phys,
  *MS_IP_phys, *protective_MS_phys,  *phosphor_MS_phys,  *support_MS_phys,  *magnetic_MS_phys,
  *SR_IP_phys, *protective_SR_phys,  *phosphor_SR_phys,  *support_SR_phys,  *magnetic_SR_phys,
  *ND_IP_phys, *protective_ND_phys,  *phosphor_ND_phys,  *support_ND_phys,  *magnetic_ND_phys,
  *TR_IP_phys,  *phosphor_TR_phys,  *support_TR_phys,  *magnetic_TR_phys, *tung_phys,
  *filtre_PEHD_phys,*filtre_mylar_phys,*filtre_al_phys,*filtre_ti_phys,*filtre_fe_phys,
  *filtre_cu_phys,*filtre_mo_phys,*filtre_ag_phys,*filtre_sn_phys,*filtre_ta_phys,
  *filtre_au_phys,*filtre_pb1_phys,*filtre_pb2_phys,*filtre_pb3_phys,*filtre_pb4_phys,
  *filtre_pb5_phys,*filtre_pb6_phys, *filtre_al_back_phys,*filtre_pb_back_phys,
  *filtre_f1_phys, *filtre_f2_phys, *filtre_f3_phys, *filtre_f4_phys, *filtre_f5_phys, *filtre_f6_phys,
  *filtre_f7_phys, *filtre_f8_phys, *filtre_f9_phys, *filtre_f10_phys, *filtre_f11_phys, *filtre_f12_phys,
  *filtre_f13_phys, *filtre_f14_phys, *filtre_f15_phys,
  *filtre_b1_phys, *filtre_b2_phys, *filtre_b3_phys, *filtre_b4_phys, *filtre_b5_phys, *filtre_b6_phys,
  *filtre_b7_phys, *filtre_b8_phys, *filtre_b9_phys, *filtre_b10_phys, *filtre_b11_phys, *filtre_b12_phys,
  *filtre_b13_phys, *filtre_b14_phys, *filtre_b15_phys,
  *blindage_1_phys, *blindage_2_phys, *blindage_3_phys, *blindage_4_phys, *blindage_5_phys, *blindage_6av_phys, *blindage_6ar_phys;


  // Optical surfaces
  G4OpticalSurface *OpticalTeflon;
  G4OpticalSurface *OpticalMylar;
  G4OpticalSurface *OpticalPMT;
  G4OpticalSurface *OpticalAlu;

  // Material Properties Table
  G4MaterialPropertiesTable *TeflonMPT;
  G4MaterialPropertiesTable *MylarMPT;
  G4MaterialPropertiesTable *AluMPT;
  G4MaterialPropertiesTable *PMT_MPT;

  // // Skin surfaces
  G4LogicalSkinSurface *SSTeflon;
  G4LogicalSkinSurface *SSMylar;
  G4LogicalSkinSurface *SSAlu;
  G4LogicalSkinSurface *SSPhotocathode;
  // G4LogicalSkinSurface *SSScintillateur;

  // Dimension values
  // scint SuperNEMO
  G4double SNMW_ScintStepWidth;
  G4double SNMW_ScintStepHeight;
  G4double SNMW_ScintBodyWidth;
  G4double SNMW_ScintBodyHeight;
  G4double SNMW_CouplingSphereRadius;
  G4double SNMW_CouplingSphereDepth;
  G4double SNMW_FullScintHeight;
  // wrapping
  G4double TeflonGap;
  G4double TeflonThickness;
  G4double MylarGap;
  G4double MylarThickness;
  // glue
  G4double GlueThickness;


};
#endif
