////////////////////////////////////////////////////////////////////////////////
//   SteAct.cc
//
//   Definitions of SteAct class's member functions. Details of user
// actions are here.
//
//                       - 18. Dec. 2023. Hoyong Jeong (hoyong5419@korea.ac.kr)
////////////////////////////////////////////////////////////////////////////////

#include "SteAct.hh"

#include "G4String.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4RootAnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

//////////////////////////////////////////////////
//   Constructor
//////////////////////////////////////////////////
SteAct::SteAct(EveAct* EA): G4UserSteppingAction(), m_EA(EA)
{
}

//////////////////////////////////////////////////
//   Destructor
//////////////////////////////////////////////////
SteAct::~SteAct()
{
}

//////////////////////////////////////////////////
//   User stepping action
//////////////////////////////////////////////////
void SteAct::UserSteppingAction(const G4Step* step)
{
	// I wrote examples of some information which can be extracted from a step.
	// Uncomment whatever you want to use.

	// Who am I? Where am I? What am I undergoing?
	// // Track ID
	G4int trackID = step -> GetTrack() -> GetTrackID();
	// // Particle definition
//	G4ParticleDefinition* par = step -> GetTrack() -> GetDefinition();
	// // Particle name
	G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();
	// // Particle ID
//	G4int parID = step -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
	// // Particle charge
//	G4int parCharge = step -> GetTrack() -> GetDefinition() -> GetPDGCharge();
	// // Process name
	const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();
//	G4String procName = step -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
	// // Physical volume
	G4String namePrePV = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
	G4String namePostPV;
	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
	if ( postPV != 0 ) namePostPV = postPV -> GetName();
	else namePostPV = "outside";
	// // Status
//	G4StepStatus preStat = step -> GetPreStepPoint() -> GetStepStatus();
//	G4StepStatus postStat = step -> GetPostStepPoint() -> GetStepStatus();
	// // Position
//	G4ThreeVector prePos = step -> GetPreStepPoint() -> GetPosition();
//	G4ThreeVector postPos = step -> GetPostStepPoint() -> GetPosition();
	// // Momentum
//	G4ThreeVector preMom = step -> GetPreStepPoint() -> GetMomentum();
//	G4ThreeVector postMom = step -> GetPostStepPoint() -> GetMomentum();
	// // Kinetic energy
//	G4double preKinEgy = step -> GetPreStepPoint() -> GetKineticEnergy();
	G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();
	// // Energy deposition
//	G4double eDep = step -> GetTotalEnergyDeposit();
	// // Time
//	G4double preGTim e = step -> GetPreStepPoint()  -> GetGlobalTime();
	G4double postGTime = step -> GetPostStepPoint() -> GetGlobalTime();


	//------------------------------------------------
	// The optical photon has reached the PMT1!
	//------------------------------------------------
	if ( namePostPV == "PMT1PV" && parName == "opticalphoton" )
	{
		auto AM = G4RootAnalysisManager::Instance();
		AM -> FillNtupleIColumn(0, G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID());
		if      ( creProc -> GetProcessName() == "Cerenkov"      ) AM -> FillNtupleIColumn(1, 0);
		else if ( creProc -> GetProcessName() == "Scintillation" ) AM -> FillNtupleIColumn(1, 1);
		else                                                       AM -> FillNtupleIColumn(1, 2); // Other
		AM -> FillNtupleIColumn(2, 0);
		AM -> FillNtupleDColumn(3, postGTime / ns);
		AM -> FillNtupleDColumn(4, postKinEgy / eV);
		AM -> AddNtupleRow();

		// Once the photon touches the PMT, it is killed.
		step -> GetTrack() -> SetTrackStatus(fStopAndKill);
	}

	//------------------------------------------------
	// The optical photon has reached the PMT2!
	//------------------------------------------------
	if ( namePostPV == "PMT2PV" && parName == "opticalphoton" )
	{
		auto AM = G4RootAnalysisManager::Instance();
		AM -> FillNtupleIColumn(0, G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID());
		if      ( creProc -> GetProcessName() == "Cerenkov"      ) AM -> FillNtupleIColumn(1, 0);
		else if ( creProc -> GetProcessName() == "Scintillation" ) AM -> FillNtupleIColumn(1, 1);
		else                                                       AM -> FillNtupleIColumn(1, 2); // Other
		AM -> FillNtupleIColumn(2, 1);
		AM -> FillNtupleDColumn(3, postGTime / ns);
		AM -> FillNtupleDColumn(4, postKinEgy / eV);
		AM -> AddNtupleRow();

		// Once the photon touches the PMT, it is killed.
		step -> GetTrack() -> SetTrackStatus(fStopAndKill);
	}
}
