#include "ActionInitialization.h"

#include "EndRunAction.h"
#include "EventAction.h"
#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.h"
#include "SteppingAction.h"

ActionInitialization::ActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
    SetUserAction(new SteppingAction());
    SetUserAction(new EndRunAction());
}