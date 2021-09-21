#ifndef SteppingAction_header
#define SteppingAction_header

#include "G4UserSteppingAction.hh"
#include "G4VUserTrackInformation.hh"
#include "globals.hh"
#include "G4Track.hh"

// Basic particle data
typedef struct {
    G4double EventID;
    G4double ID;
    G4double ParentID;
    G4double ParticleEnergy;
    G4double X;
    G4double Y;
    G4double Z;
    G4double DirX;
    G4double DirY;
    G4double DirZ;
    G4double Momentum_X;
    G4double Momentum_Y;
    G4double Momentum_Z;
} PartData;

typedef struct {
    G4double EventID;
    G4double EDep;
    G4double StepLength;
} EnergyLoss;

// Special structure for the particle names
typedef struct {
    char Name[20];
} PartName;

// Structure for the name of the process, which created the particle
typedef struct {
    char Process[25];
} PartCreatorProcess;
// Basic primary particle data
typedef struct  __attribute__((packed)){
    G4double EventID;
    G4double ID;
    G4double Energy;
    G4double EnergyTot;
    G4double X;
    G4double Y;
    G4double Z;
    G4double Momentum_X;
    G4double Momentum_Y;
    G4double Momentum_Z;
    G4double EDep;
    G4double StepLength;
    G4double Time;
} PrimData;

// Special structure for the primary particle name
typedef struct {
    char Name[20];
} PrimName;

// Structure for the name of the material, in which primary particle interacted
typedef struct {
    char Material[25];
} PrimMaterial;
typedef struct {
    char Process[25];
} PrimProcess;
// Class for user track information (keeps partice data at birth for Birks law)
class BirthInfo : public G4VUserTrackInformation
{
    public:
	BirthInfo() {}
	~BirthInfo() {}
	
	void SetParentdEdx(const G4double _ParentdEdx) { ParentdEdx = _ParentdEdx; }
	G4double GetParentdEdx() { return ParentdEdx; }
	
	void SetBirthEnergy(const G4double _BirthEnergy) { BirthEnergy = _BirthEnergy; }
	G4double GetBirthEnergy() { return BirthEnergy; }
	
    private:
	G4double ParentdEdx;
	G4double BirthEnergy;
};

class DetectorConstruction;
class RunAction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
    public:
	SteppingAction(DetectorConstruction*, RunAction*, EventAction*) ;
	~SteppingAction();
	
	void UserSteppingAction(const G4Step*);
	
    private:
        void PartDataFiller(const G4Track* Track);
        
	DetectorConstruction* detector;
	RunAction* runaction;
	EventAction* eventaction;

	PrimData PrimaryData;
	PrimName PrimaryName;
	PrimMaterial PrimaryMaterial;
        PrimProcess PrimaryProcess;
        EnergyLoss ELoss;
        
        PartData ParticleData;
        PartName ParticleName;
        PartCreatorProcess ParticleCreatorProcess;
};

#endif

