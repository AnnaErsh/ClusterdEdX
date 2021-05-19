#ifndef PrimaryGeneratorAction_header
#define PrimaryGeneratorAction_header 

#include "G4VUserPrimaryGeneratorAction.hh"

#include "RunAction.h"
#include "EventAction.h"

class G4GeneralParticleSource;
class G4Event;

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
    public:
	PrimaryGeneratorAction(RunAction*, EventAction*);
	~PrimaryGeneratorAction();
	void GeneratePrimaries(G4Event*);

    private:
	G4GeneralParticleSource* ParticleGun;
	RunAction* runaction;
	EventAction* eventaction;
};

#endif

