#ifndef EndOfRunAction_h
#define EndOfRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class EndRunAction : public G4UserRunAction {
   public:
    EndRunAction();
    virtual ~EndRunAction();

    virtual void EndOfRunAction(const G4Run*) override;
};

#endif
