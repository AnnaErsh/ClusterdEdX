#ifndef DetectorConstruction_header
#define DetectorConstruction_header

class G4VPhysicalVolume;

#include "G4UserLimits.hh"
#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction: public G4VUserDetectorConstruction
{
    public:
	DetectorConstruction();
	~DetectorConstruction();
	
	G4VPhysicalVolume* Construct();
	G4UserLimits* fStepLimit;
	
    private:
	G4VPhysicalVolume* World;
	G4VPhysicalVolume* CH_block;
	
};	


#endif

