#include "RunAction.h"
#include "ConfigArray.h"

#include "TFile.h"
#include "TTree.h"
#include "TLeafD.h"
#include "TF1.h"
#include "G4Event.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include <cmath>

EventAction::EventAction(RunAction* run)
{
runaction=run;
EventData.EventID = 0;
EventData.ParticleEnergy = EventData.EnergyLoss = EventData.X = 
EventData.Y = EventData.Z = EventData.DirX = EventData.DirY = EventData.DirZ = 0.;

}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* event)
{
    EventData.EventID = event->GetEventID() + 1;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
G4int EventID = event->GetEventID() + 1;
runaction->AddEvent(EventData);

if (EventID % 100 == 0) 
    {
    G4cout << EventID << " events reached\n";
    G4cout.flush();
    }
  part_sec.clear();
}

void EventAction::AddEnergyDeposit(G4double destep)
{
EventData.EnergyLoss+= destep / MeV;
}

void EventAction::SetParticleEnergy(G4double ParticleEnergy)
{
EventData.ParticleEnergy = ParticleEnergy / MeV;
}

void EventAction::SetParticlePosition(G4ThreeVector ParticlePosition)
{
EventData.X = ParticlePosition.getX() / cm;
EventData.Y = ParticlePosition.getY() / cm;
EventData.Z = ParticlePosition.getZ() / cm;
}

void EventAction::SetParticleMomentumDirection(G4ThreeVector ParticleMomentumDirection)
{
EventData.DirX = ParticleMomentumDirection.getX();
EventData.DirY = ParticleMomentumDirection.getY();
EventData.DirZ = ParticleMomentumDirection.getZ();
}

G4double EventAction::GetEventID()
{
return EventData.EventID;
}