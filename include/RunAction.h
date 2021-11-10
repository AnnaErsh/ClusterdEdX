#ifndef RunAction_header
#define RunAction_header

#include "EventAction.h"
#include "SteppingAction.h"
#include "StackingAction.h"

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"

typedef struct __attribute__((packed)) {
    G4double SourceType;
    unsigned char ContinueFlag;
} RData;

class RunAction : public G4UserRunAction
{
    public:
	RunAction();
	~RunAction();
	
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
	void AddEvent(EvData);
	void AddPrimaryTrackPoint(PrimData, PrimName, PrimMaterial, PrimProcess);
	void AddParticle(PartData, PartName, PartCreatorProcess, EnergyLoss);

    private:
	TFile* file;

	TTree* RunTree;
	TBranch* RunBranch;

	TTree* EventTree;
	TBranch* EventBranch;

	TTree* PrimaryTree;
	TBranch* PrimaryDataBranch;
	TBranch* PrimaryNameBranch;
    TBranch* PrimaryProcessBranch;
	TBranch* PrimaryMaterialBranch;

	TTree* ParticleTree;
	TBranch* ParticleDataBranch;
	TBranch* ParticleNameBranch;
	TBranch* ParticleMaterialNameBranch;
	TBranch* ParticleCreatorProcessNameBranch;
	TBranch* ELossBranch;

	RData RunData;
};

#endif



