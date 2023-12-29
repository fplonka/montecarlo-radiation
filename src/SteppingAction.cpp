#include "SteppingAction.h"

#include "G4Gamma.hh"
#include "G4Step.hh"

void SteppingAction::UserSteppingAction(const G4Step* step) {
    auto track = step->GetTrack();
    auto stepNumber = track->GetCurrentStepNumber();
    auto volume =
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
    auto kineticEnergy = step->GetPreStepPoint()->GetKineticEnergy();
    auto position = step->GetPreStepPoint()->GetPosition();
    auto momentumDirection = track->GetMomentumDirection();
    auto stepLength = step->GetStepLength();

    if (track->GetDefinition() == G4Gamma::Definition()) {
        // G4cout << "Step number: " << stepNumber << G4endl;
        // G4cout << "Photon position: " << position << G4endl;
        // G4cout << "Photon momentum direction: " << momentumDirection <<
        // G4endl; G4cout << "Photon kinetic energy: " << kineticEnergy <<
        // G4endl; G4cout << "Step in volume: " << volume << G4endl; G4cout <<
        // "Step length: " << stepLength << G4endl;
    }
}
