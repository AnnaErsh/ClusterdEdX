#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.h"
#include "PhysicsList.h"
#include "PrimaryGeneratorAction.h"
#include "ConfigArray.h"
#include "RunAction.h"
#include "EventAction.h"
#include "SteppingAction.h"
#include "StackingAction.h"

ConfigArray Config;
G4VisManager* VisManager;
G4UIExecutive* UIEx;

int main(int argc, char** argv)
{
G4String Command(30);

G4RunManager* RunManager= new G4RunManager;

DetectorConstruction* detector = new DetectorConstruction;
RunManager->SetUserInitialization(detector);
RunManager->SetUserInitialization(new PhysicsList);

RunAction* runaction = new RunAction;
RunManager->SetUserAction(runaction);
EventAction* eventaction = new EventAction(runaction);
RunManager->SetUserAction(eventaction);
RunManager->SetUserAction(new SteppingAction(detector, runaction, eventaction));
RunManager->SetUserAction(new StackingAction(runaction, eventaction));
RunManager->SetUserAction(new PrimaryGeneratorAction(runaction, eventaction));

RunManager->Initialize();

if (Config.IsVisualizationNeeded() == 1)
    {
    VisManager = new G4VisExecutive;
    VisManager->Initialize();
    }

G4UImanager* UI = G4UImanager::GetUIpointer();
UI->ApplyCommand("/run/verbose 1");
if (Config.GetTrackingOutputMode() > 0) 
    {

    char buf[10];
    sprintf(buf, "%d", Config.GetTrackingOutputMode());
    Command="/tracking/verbose ";
    Command+=buf;
    UI->ApplyCommand(Command);
    UI->ApplyCommand("/event/verbose 1");
    }

if (Config.IsUserSessionNeeded() == 1)
    {
    UIEx = new G4UIExecutive(argc, argv, "qt");
    }

if (Config.IsVisualizationNeeded() == 1)
    {
    UI->ApplyCommand("/vis/open " + Config.GetInterfaceType());
    UI->ApplyCommand("/vis/viewer/reset");
    UI->ApplyCommand("/vis/viewer/set/style wireframe");
    UI->ApplyCommand("/vis/viewer/zoom 1.2");
    UI->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 30 20");
    UI->ApplyCommand("/vis/drawVolume");
    UI->ApplyCommand("/vis/viewer/flush");
    UI->ApplyCommand("/vis/scene/add/trajectories");
    UI->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    }

if (Config.IsUserSessionNeeded() == 1)
    {
    UIEx->SessionStart();
    delete UIEx;
    }
else
    {
    RunManager->BeamOn(Config.GetEventNumber());
    }

if (Config.IsVisualizationNeeded() == 1)
    {
    delete VisManager;
    }

delete RunManager;

return 0;
}
