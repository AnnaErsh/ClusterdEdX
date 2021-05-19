#include "StackingAction.h"
#include "ConfigArray.h"

#include "RunAction.h"
#include "EventAction.h"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4TransportationManager.hh"

#include <cmath>

StackingAction::StackingAction(RunAction* runact, EventAction* evact)
{
runaction = runact;
eventaction = evact;
navigator = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
}

StackingAction::~StackingAction()
{
}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* Track)
{
G4ClassificationOfNewTrack classification = fWaiting;

G4ParticleDefinition *particle = Track->GetDefinition();
G4String pname = particle->GetParticleName();
const G4VProcess *pprocess = Track->GetCreatorProcess();
G4String pprocessname = "PrimaryGenerator";
if (pprocess!=NULL) pprocessname = pprocess->GetProcessName();
if (pname=="e-" && pprocessname=="muIoni") 
{
    classification = fKill;
}

// if (classification==fKill) ParticleData.KillingFlag=1;
//     else ParticleData.KillingFlag=0;

return classification;
}

