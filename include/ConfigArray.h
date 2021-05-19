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
	G4double GetCalibrationSourceYPosition();
	int IsPassiveShieldingAndVetoNeeded();
        int IsConcreteNeeded();
	int GetVetoAssemblyVersion();
	int IsPMTResponseDataReadingNeeded();
	int IsSiPMResponseDataReadingNeeded();
	int IsPMTLongitProfilesFromFileNeeded();
	int IsSiPMLongitProfilesFromFileNeeded();
	int IsEplusAnnihilGammaKillNeeded();
	int IsNCaptureGammaKillNeeded();
	int IsGdCaptureGammaReplacementNeeded();
	int IsSecondaryEKillNeeded();
	int IsSecondaryNKillNeeded();
	int IsOnlyNeutronDataWritingNeeded();
	int IsSignalWritingNeeded();
	int IsVetoSignalWritingNeeded();
	int IsVisualizationNeeded();
	int GetTrackingOutputMode();
	int IsUserSessionNeeded();
	G4String GetInterfaceType();
    
    private:
	int source;
	long int events;
	int cont;
	double energy;
	double calibr_source_pos;
	int passive_shielding_and_veto;
        int concrete_ceiling_and_floor;
	int veto_assembly_version;
	int pmt_response_from_file;
	int sipm_response_from_file;
	int pmt_longit_profiles_from_file;
	int sipm_longit_profiles_from_file;
	int no_eplus_annihil_gamma;
	int no_ncapture_gamma;
	int gd_capture_gamma_replacement;
	int no_secondary_e;
	int no_secondary_n;
	int write_only_neutrons;
	int write_signals;
	int write_veto_signals;
	int visual;
	int tracking;
	int session;
	char interface[20];
};

extern ConfigArray Config;
#endif

