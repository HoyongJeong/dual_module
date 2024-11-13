#ifndef DETCON_h
#define DETCON_h 1

////////////////////////////////////////////////////////////////////////////////
//   DetCon.hh
//
//   This file is a header for DetCon class. It's for construction of whole
// geometry of simulation, which includes detector geometry.
//
//                       - 12. Nov. 2024. Hoyong Jeong (hoyong5419@korea.ac.kr)
////////////////////////////////////////////////////////////////////////////////

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4UnionSolid.hh"
#include "G4Tubs.hh"

class G4VPhysicalVolume;

class DetCon: public G4VUserDetectorConstruction
{
  public:
	DetCon();
	virtual ~DetCon();
	virtual G4VPhysicalVolume* Construct();

  private:
	void DefineDimensions();
	void ConstructMaterials();
	void DestructMaterials();

  private:
	// Elements
	G4Element* m_ElH;
	G4Element* m_ElC;
	G4Element* m_ElN;
	G4Element* m_ElO;
	G4Element* m_ElAr;

	// Materials
	G4Material* m_VacMat;
	G4Material* m_AirMat;
	G4Material* m_SciMat;
	G4Material* m_PMTMat;
	G4MaterialPropertiesTable* m_SciMPT;
	G4MaterialPropertiesTable* m_AirMPT;
	G4MaterialPropertiesTable* m_AirST;

	// Dimensions and detector setup
	G4double m_LabX, m_LabY, m_LabZ;
	G4double m_SciX, m_SciY, m_SciZ;
	G4double m_PMTD, m_PMTT;
	G4double m_GapD;
	G4int m_PMT1, m_PMT2;

	// Geometry objects: World
	G4Box* m_WorldSolid;
	G4LogicalVolume* m_WorldLV;
	G4VPhysicalVolume* m_WorldPV;

	// Geometry objects: Lab
	G4Box* m_LabSolid;
	G4LogicalVolume* m_LabLV;
	G4VPhysicalVolume* m_LabPV;


	G4OpticalSurface* m_SciOpS;

	//------------------------------------------------
	// Module1
	//------------------------------------------------
	// Geometry objects: Scint1
	G4Box* m_Sci1Solid1;
	G4Tubs* m_Sci1Solid2;
	G4UnionSolid* m_Sci1Solid;
	G4LogicalVolume* m_Sci1LV;
	G4VPhysicalVolume* m_Sci1PV;
	
	// Geometry objects: PMT1
	G4Tubs* m_PMT1Solid;
	G4LogicalVolume* m_PMT1LV;
	G4VPhysicalVolume* m_PMT1PV;

	// Surface objects: Scint1
	G4LogicalBorderSurface* m_Sci1LBS;


	//------------------------------------------------
	// Module2
	//------------------------------------------------
	// Geometry objects: Scint2
	G4Box* m_Sci2Solid1;
	G4Tubs* m_Sci2Solid2;
	G4UnionSolid* m_Sci2Solid;
	G4LogicalVolume* m_Sci2LV;
	G4VPhysicalVolume* m_Sci2PV;
	
	// Geometry objects: PMT2
	G4Tubs* m_PMT2Solid;
	G4LogicalVolume* m_PMT2LV;
	G4VPhysicalVolume* m_PMT2PV;

	// Surface objects: Scint2
	G4LogicalBorderSurface* m_Sci2LBS;
};

#endif
