#include <cstdlib>

#include "ConfigArray.h"
#include "globals.hh"

ConfigArray::ConfigArray()
{
const int numparams = 10;	// Number of parameters + 1
FILE* conf_file;
char str[150];
char val[50];
int i=-1;
const char* params[numparams] = {"source=", "events=", "continue=" ,"energy=",
				"density=", "visual=", "tracking=", "session=", "interface=", 
				"NULL"};
val[49]='\0';
interface[19]='\0';
//Default
source=1;
events=1000;
cont=0;
energy=1;
density = 1;
calibr_source_pos=50.;
passive_shielding_and_veto=0;
concrete_ceiling_and_floor=0;
veto_assembly_version=1;
pmt_response_from_file=0;
sipm_response_from_file=0;
pmt_longit_profiles_from_file=0;
sipm_longit_profiles_from_file=0;
no_eplus_annihil_gamma=0;
no_ncapture_gamma=0;
gd_capture_gamma_replacement=0;
no_secondary_e=0;
no_secondary_n=0;
write_only_neutrons=0;
write_signals=1;
write_veto_signals=1;
visual=0;
tracking=0;
session=0;
strcpy(interface,"OGLIX");
//Reading
conf_file=fopen("MuModel.conf","r");
if (conf_file==NULL)
    {
        G4cerr << "Cannot read config file MuModel.conf! Aborting..." << G4endl;
    abort();
    }
G4cout << "Reading config file\n";
while (fgets(str,150,conf_file)!=NULL)
{
    if (strncmp("#",str,1)==0) continue;
    for (i=0;i<numparams;i++) if (strncmp(params[i],str,strlen(params[i]))==0) break;
    if ((i>=0)&&(i<numparams-1)) strncpy(val,&str[strlen(params[i])],49);
    switch (i) 
    {
	case 0: source=strtol(val, NULL, 10);
		break;
	case 1: events=strtol(val, NULL, 10);
		break;
	case 2: cont=strtol(val, NULL, 10);
		break;
	case 3: energy=strtod(val, NULL);
		break;
	case 4: density=strtod(val, NULL);
		break;
	case 5: visual=strtol(val, NULL, 10);  
		break;
	case 6: tracking=strtol(val, NULL, 10);
		break;
	case 7: session=strtol(val, NULL, 10);
		break;
	case 8: strncpy(interface, val, 19);
		break;
	default: G4cerr << "Unknown parameter: ";
    };
G4cout << str;
}
fclose(conf_file);
return;
}

ConfigArray::~ConfigArray()
{
}

int ConfigArray::GetSourceType(void)
{
return source;
}

G4long ConfigArray::GetEventNumber(void)
{
return events;
}

int ConfigArray::IsContinuationNeeded(void)
{
return cont;
}

G4double ConfigArray::GetParticleEnergy(void)
{
return energy;
}

G4double ConfigArray::GetMaterialDensity(void)
{
return density;
}

int ConfigArray::IsVisualizationNeeded(void)
{
return visual;
}

int ConfigArray::GetTrackingOutputMode(void)
{
return tracking;
}

int ConfigArray::IsUserSessionNeeded(void)
{
return session;
}

G4String ConfigArray::GetInterfaceType(void)
{
return interface;
}


