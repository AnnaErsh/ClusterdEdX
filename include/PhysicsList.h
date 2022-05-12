#ifndef PhysicsList_header
#define PhysicsList_header

#include "G4VUserPhysicsList.hh"
#include "G4ProcessManager.hh"

class PhysicsList: public G4VUserPhysicsList
{
    public:
	PhysicsList();
	~PhysicsList();

	G4ProcessManager* pmanager = NULL;
	
    protected:
	void ConstructParticle();
	void ConstructProcess();

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
	void ConstructDecay();
	void ConstructStoppingPhysics();
};

#endif

