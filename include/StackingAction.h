#ifndef StackingAction_header
#define StackingAction_header

#include "G4UserStackingAction.hh"
#include "globals.hh"

#include "G4Track.hh"
#include "G4Navigator.hh"


class RunAction;
class EventAction;

class StackingAction: public G4UserStackingAction
{
    public:
	StackingAction(RunAction*, EventAction*);
	~StackingAction();
	G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
    
    private:
	RunAction* runaction;
	EventAction* eventaction;
	G4Navigator* navigator;

};

#endif
