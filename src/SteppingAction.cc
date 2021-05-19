#include "SteppingAction.h"
#include "DetectorConstruction.h"
#include "RunAction.h"
#include "EventAction.h"
#include "ConfigArray.h"

#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NavigationHistory.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTypes.hh"

#include <cmath>

void  SteppingAction::PartDataFiller(const G4Track* Track)
{
	G4ParticleDefinition *particle;
	particle = Track->GetDefinition();
	G4String pname = particle->GetParticleName();
	G4String ptype = particle->GetParticleType();
	const G4VProcess *pprocess = Track->GetCreatorProcess();
	G4String pprocessname = "PrimaryGenerator";
	if (pprocess!=NULL) pprocessname = pprocess->GetProcessName();
	G4ThreeVector pposition = Track->GetPosition();
	G4ThreeVector pdirection = Track->GetMomentumDirection();
	strncpy(ParticleCreatorProcess.Process, pprocessname.data(), 24);
	ParticleCreatorProcess.Process[24]='\0';
	ParticleData.EventID = eventaction->GetEventID();
	// G4cout<<ParticleData.EventID<<G4endl;
	ParticleData.ID = Track->GetTrackID();
	ParticleData.ParentID = Track->GetParentID();
	strncpy(ParticleName.Name, pname.data(), 19);
	ParticleName.Name[19]='\0';
	ParticleData.ParticleEnergy = Track->GetKineticEnergy() / MeV;
	ParticleData.X = pposition.getX() / um;
	ParticleData.Y = pposition.getY() / um;
	ParticleData.Z = pposition.getZ() / um;
	ParticleData.DirX = pdirection.getX();
	ParticleData.DirY = pdirection.getY();
	ParticleData.DirZ = pdirection.getZ();
	G4ThreeVector pmomentum = Track->GetMomentum();
	ParticleData.Momentum_X = pmomentum.getX() / MeV;
	ParticleData.Momentum_Y = pmomentum.getY() / MeV;
	ParticleData.Momentum_Z = pmomentum.getZ() / MeV;
}

SteppingAction::SteppingAction (DetectorConstruction* det, RunAction* ract, EventAction* evt)
{
detector = det;
runaction = ract;
eventaction = evt;
}

SteppingAction::~SteppingAction()
{
}

int64_t muIoniNumber=0;
void SteppingAction::UserSteppingAction(const G4Step* step)
{
// G4int historydepth;
G4TouchableHandle handle;
G4ThreeVector worldpos, localpos;
G4ParticleDefinition *particle;

// Getting volume handle data
handle = step->GetPreStepPoint()->GetTouchableHandle();
// historydepth = handle->GetHistoryDepth();

// Getting position
worldpos = step->GetPostStepPoint()->GetPosition();

// Energy losses to the medium in this step
G4double destep = step->GetTotalEnergyDeposit();
eventaction->AddEnergyDeposit(destep);

ELoss.EventID = eventaction->GetEventID();
ELoss.EDep = step->GetTotalEnergyDeposit() / MeV;
ELoss.StepLength = step->GetStepLength() / um;

// Primary particle data addition
G4Track *Track = step->GetTrack();
G4int ParentID = Track->GetParentID();
if (ParentID==0) // Transferring data
	{
		//processes
		G4String pprocess = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
		if (ParentID==0)
		{
			strncpy(PrimaryProcess.Process, pprocess.data(), 24);
			PrimaryProcess.Process[24]='\0';         
			PrimaryData.ID = Track->GetTrackID();
			particle = Track->GetDefinition();
			G4String pname = particle->GetParticleName();
			strncpy(PrimaryName.Name, pname.data(), 19);
			PrimaryName.Name[19]='\0';
			G4String pmaterial = handle->GetVolume(0)->GetLogicalVolume()->GetMaterial()->GetName();
			strncpy(PrimaryMaterial.Material, pmaterial.data(), 24);
			PrimaryMaterial.Material[24]='\0';
			PrimaryData.Energy = Track->GetKineticEnergy() / MeV;
			G4ThreeVector pposition = Track->GetPosition();    
			PrimaryData.X = pposition.getX() / um;
			PrimaryData.Y = pposition.getY() / um;
			PrimaryData.Z = pposition.getZ() / um;
			G4ThreeVector pmomentum = Track->GetMomentum();
			PrimaryData.Momentum_X = pmomentum.getX() / MeV;
			PrimaryData.Momentum_Y = pmomentum.getY() / MeV;
			PrimaryData.Momentum_Z = pmomentum.getZ() / MeV;
			PrimaryData.EventID = eventaction->GetEventID();
			PrimaryData.EDep = step->GetTotalEnergyDeposit() / MeV;
			PrimaryData.StepLength = step->GetStepLength() / um;
			PrimaryData.Time=step->GetTrack()->GetGlobalTime();
		}
		runaction->AddPrimaryTrackPoint(PrimaryData, PrimaryName, PrimaryMaterial, PrimaryProcess);
	}

// Adding particle to our tree
	const std::vector< const G4Track * > * Vec_Secondaries = step->GetSecondaryInCurrentStep();
	
if (Vec_Secondaries != nullptr && !Vec_Secondaries->empty())
{
	
	for(auto it: *Vec_Secondaries)
	{
		G4ParticleDefinition *particle_child = it->GetDefinition();
		G4String part_name = particle_child->GetParticleName();
		if (part_name == "e-")
		{
			if (Track->GetTrackStatus() != fStopAndKill && ParentID==0) PartDataFiller(Track);
		}
		else 
		{
			PartDataFiller(it);
		}
	}
	
}
runaction->AddParticle(ParticleData, ParticleName, ParticleCreatorProcess, ELoss);

}


