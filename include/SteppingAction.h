#include "G4UserSteppingAction.hh"

class SteppingAction : public G4UserSteppingAction {
   public:
    virtual void UserSteppingAction(const G4Step*);
};