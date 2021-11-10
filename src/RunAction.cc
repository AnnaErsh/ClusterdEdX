#include "ConfigArray.h"
#include "RunAction.h"
#include "EventAction.h"

#include "globals.hh"
#include "G4Run.hh"
#include "Randomize.hh"

#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"

RunAction::RunAction()
{
RunData.SourceType = 0;
RunData.ContinueFlag = 0;
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
run->GetRunID();
if (Config.IsContinuationNeeded()==1) 
    // It is the only way to save/restore status into/from the user defined file
    CLHEP::HepRandom::getTheEngine()->restoreStatus("MMRandom.status"); 
CLHEP::HepRandom::showEngineStatus();
if (Config.IsContinuationNeeded()==1) 
    {
    int filenum=0;
    FILE* opened = NULL;
    G4String name(30);
    char buf[20];
    do 
	{
	if (filenum!=0) fclose(opened);
	filenum++; 
	sprintf(buf, "%d", filenum-1);
	name = "Mu";
	name += buf;
	name += ".root";
	opened = fopen(name.data(), "r");
	}
    while (opened!=NULL);
    file = new TFile(name, "RECREATE");
    }
else file = new TFile("Mu.root", "RECREATE");
RunTree = new TTree("MuRun", "Mu run tree");
EventTree = new TTree("MuEvent", "Mu event tree");
PrimaryTree = new TTree("MuPrimary", "Mu primary particle track tree");
ParticleTree = new TTree("MuParticle", "Mu particle tree");
RunBranch = RunTree->Branch("RunData", &RunData,
	    "SourceType/D:ContinueFlag/B");
EventBranch = EventTree->Branch("EventData", 0,
	    "EventID/D:ParticleEnergy:EnergyLoss:X:Y:Z:DirX:DirY:DirZ");
PrimaryDataBranch = PrimaryTree->Branch("PrimaryData", 0,
                                        "EventID/D:ID:Energy:EnergyTot:X:Y:Z:Momentum_X:Momentum_Y:Momentum_Z:EDep:Ecorr:StepLength:Time");
PrimaryNameBranch = PrimaryTree->Branch("PrimaryName", 0,
	    "Name/C");
PrimaryMaterialBranch = PrimaryTree->Branch("PrimaryMaterialName", 0,
	    "Material/C");
PrimaryProcessBranch = PrimaryTree->Branch("PrimaryProcessName", 0,
                                            "Process/C");
ParticleNameBranch = ParticleTree->Branch("ParticleName", 0,
	    "Name/C");
ParticleDataBranch = ParticleTree->Branch("ParticleData", 0,
                                          "EventID/D:ID:ParentID:ParticleEnergy:X:Y:Z:DirX:DirY:DirZ:Momentum_X:Momentum_Y:Momentum_Z");
ELossBranch = ParticleTree->Branch("ELossBranch", 0, "EventID/D:EDep:StepLength");
ParticleCreatorProcessNameBranch = ParticleTree->Branch("ParticleCreatorProcessName", 0, "Process/C");
}

void RunAction::EndOfRunAction(const G4Run* run)
{
run->GetRunID();

// Filling run data
RunData.SourceType=Config.GetSourceType();
RunData.ContinueFlag=Config.IsContinuationNeeded();
RunTree->Fill();

file->Write();
CLHEP::HepRandom::showEngineStatus();
CLHEP::HepRandom::getTheEngine()->saveStatus("MMRandom.status"); 
delete RunTree;
delete EventTree;
delete PrimaryTree;
delete ParticleTree;
delete file;
}

void RunAction::AddEvent(EvData EvtData)
{
EventBranch->SetAddress(&EvtData);
EventTree->Fill();
}

void RunAction::AddPrimaryTrackPoint(PrimData PrimaryData, 
	PrimName PrimaryName, PrimMaterial PrimaryMaterial, PrimProcess PrimaryProcess)
{
PrimaryDataBranch->SetAddress(&PrimaryData);
PrimaryNameBranch->SetAddress(&PrimaryName);
PrimaryMaterialBranch->SetAddress(&PrimaryMaterial);
PrimaryProcessBranch->SetAddress(&PrimaryProcess);
PrimaryTree->Fill();
}

void RunAction::AddParticle(PartData ParticleData, 
	PartName ParticleName,
	PartCreatorProcess ParticleCreatorProcess, EnergyLoss ELoss)
{
ParticleDataBranch->SetAddress(&ParticleData);
ParticleNameBranch->SetAddress(&ParticleName);
ParticleCreatorProcessNameBranch->SetAddress(&ParticleCreatorProcess);
ELossBranch->SetAddress(&ELoss);
ParticleTree->Fill();
}


