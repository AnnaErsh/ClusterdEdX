#ifndef ConfigArray_header
#define ConfigArray_header

#include "globals.hh"

class ConfigArray
{
    public:
	ConfigArray();
	~ConfigArray();
	int GetSourceType();
	G4long GetEventNumber();
	int IsContinuationNeeded();
	G4double GetParticleEnergy();
	G4double GetMaterialDensity();
	int IsVisualizationNeeded();
	int GetTrackingOutputMode();
	int IsUserSessionNeeded();
	G4String GetInterfaceType();
    
    private:
	int source;
	long int events;
	int cont;
	double energy;
	double density;
	int visual;
	int tracking;
	int session;
	char interface[20];
};

extern ConfigArray Config;
#endif

