#include "PhysicsList.h"

#include "G4ParticleTypes.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4StepLimiter.hh"
#include "G4VPhysicsConstructor.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"

PhysicsList::PhysicsList()
{
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::ConstructParticle()
{
ConstructBosons();
ConstructLeptons();
ConstructBaryons();
ConstructMesons();
ConstructIons();
ConstructShortLived();
}

void PhysicsList::ConstructBosons()
{
G4Geantino::GeantinoDefinition();
G4Gamma::GammaDefinition();
}

void PhysicsList::ConstructLeptons()
{
G4LeptonConstructor LeptonConstructor;
LeptonConstructor.ConstructParticle();
}

void PhysicsList::ConstructBaryons()
{
G4BaryonConstructor BaryonConstructor;
BaryonConstructor.ConstructParticle();
}

void PhysicsList::ConstructMesons()
{
G4MesonConstructor MesonConstructor;
MesonConstructor.ConstructParticle();
}

void PhysicsList::ConstructIons()
{
G4IonConstructor IonConstructor;
IonConstructor.ConstructParticle();
}

void PhysicsList::ConstructShortLived()
{
G4ShortLivedConstructor ShortLivedConstructor;
ShortLivedConstructor.ConstructParticle();
}

#include "G4RegionStore.hh"
// void PhysicsList::SetCuts()
// {
//     G4double DetectorCutValue = 2.*um;
    
//     SetDefaultCutValue(100.*um);
//     SetCutsWithDefault();
    
//     G4Region* DetectorRegion = G4RegionStore::GetInstance()->GetRegion("DetectorRegion");
//     G4ProductionCuts* DetectorCuts = new G4ProductionCuts();
//     DetectorCuts->SetProductionCut(DetectorCutValue);
//     DetectorRegion->SetProductionCuts(DetectorCuts);
// }

void PhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructEM();
	ConstructHad();
	ConstructIonPh();
	ConstructStoppingPhysics();

	auto myParticleIterator=GetParticleIterator();
	myParticleIterator->reset();

	while( (*myParticleIterator)() )
	{
		G4ParticleDefinition * particle = myParticleIterator->value();
    G4String               particleName = particle->GetParticleName();
    G4ProcessManager     * manager = particle->GetProcessManager();
   	G4StepLimiter* stepLimiter = new G4StepLimiter();
   	manager->AddDiscreteProcess(stepLimiter);
	}
}

//*********************
// Electromagnetic processes
//*********************

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4OpticalPhysics.hh"

void PhysicsList::ConstructEM()
{
G4VPhysicsConstructor* EmStandardPhysicsList = new G4EmStandardPhysics();
EmStandardPhysicsList->ConstructProcess();

G4EmExtraPhysics* EmExtraPhysicsList = new G4EmExtraPhysics();
EmExtraPhysicsList->ConstructProcess();

// G4VPhysicsConstructor* OpticalPhysicsList = new G4OpticalPhysics();
// OpticalPhysicsList->ConstructProcess();
}

//*********************
// Hadronic processes
//*********************

#include "G4HadronPhysicsINCLXX.hh"
#include "G4ParticleHPManager.hh"

void PhysicsList::ConstructHad()
{
G4VPhysicsConstructor* HadronPhysicsList = new G4HadronPhysicsINCLXX();
HadronPhysicsList->ConstructProcess();
}

// #include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"
void PhysicsList::ConstructIonPh()
{
G4VPhysicsConstructor* IonPhysicsList = new G4IonINCLXXPhysics();
IonPhysicsList->ConstructProcess();
}

//*********************
// Decays
//*********************

#include "G4DecayPhysics.hh"

 void PhysicsList::ConstructDecay()
 {
 G4VPhysicsConstructor* DecayPhysicsList = new G4DecayPhysics();
 DecayPhysicsList->ConstructProcess();
 }

#include "G4StoppingPhysics.hh"

void PhysicsList::ConstructStoppingPhysics()
{
G4VPhysicsConstructor* StoppingPhysicsList = new G4StoppingPhysics();
StoppingPhysicsList->ConstructProcess();
}

// #include "G4RadioactiveDecayPhysics.hh"

// void PhysicsList::ConstructRadioactiveDecay()
// {
// G4VPhysicsConstructor* RadioactiveDecayPhysicsList = new G4RadioactiveDecayPhysics();
// RadioactiveDecayPhysicsList->ConstructProcess();
// }

