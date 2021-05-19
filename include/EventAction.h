#ifndef EventAction_header
#define EventAction_header

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "TSpline.h"

typedef struct { 
    G4double EventID;
    G4double ParticleEnergy;
    G4double EnergyLoss;
    // G4double StepLength;
    G4double X;
    G4double Y;
    G4double Z;
    G4double DirX;
    G4double DirY;
    G4double DirZ;
} EvData;


class RunAction;

class EventAction: public G4UserEventAction
{
    public:
	EventAction(RunAction*);
	~EventAction();
	
	void BeginOfEventAction(const G4Event*);
	void EndOfEventAction(const G4Event*);

	void AddEnergyDeposit(G4double);

	void SetParticleEnergy(G4double);
	void SetParticlePosition(G4ThreeVector);
	void SetParticleMomentumDirection(G4ThreeVector);
	G4double GetEventID();
	
    private:

	RunAction* runaction;
	EvData EventData;

	TSpline3 *spline;
	
	double TSplineWrapper(double*, double*);


};

#endif

