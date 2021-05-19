#ifndef PhysicsList_header
#define PhysicsList_header

#include "G4VUserPhysicsList.hh"

class PhysicsList: public G4VUserPhysicsList
{
    public:
	PhysicsList();
	~PhysicsList();
	
    protected:
	void ConstructParticle();
	void ConstructProcess();
        // void SetCuts();
    private:	
	void ConstructBosons();
	void ConstructLeptons();
	void ConstructBaryons();
	void ConstructMesons();
	void ConstructIons();
	void ConstructShortLived();
	
	void ConstructEM();
	void ConstructHad();
	void ConstructIonPh();
	// void ConstructDecay();
	void ConstructStoppingPhysics();
	// void ConstructRadioactiveDecay();
	// void ConstructMuMinusCapture();
};

#endif

