#include "EventAction.h"

#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VVisManager.hh"

EventAction::EventAction() : G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {
    // std::cout << "event beginning!\n";
    // Initialization can be done here
}

void EventAction::EndOfEventAction(const G4Event* event) {
    // Get the number of trajectories in the event
    // std::cout << "EVENT!!\n";
    // G4TrajectoryContainer* trajectoryContainer =
    //     event->GetTrajectoryContainer();
    // G4int numTrajectories = 0;
    // if (trajectoryContainer) numTrajectories =
    // trajectoryContainer->entries();

    // // Count the number of gamma interactions
    // G4int gammaInteractions = 0;
    // for (G4int i = 0; i < numTrajectories; i++) {
    //     G4Trajectory* trj =
    //         (G4Trajectory*)((*(event->GetTrajectoryContainer()))[i]);
    //     if (trj->GetParticleDefinition() == G4Gamma::GammaDefinition()) {
    //         gammaInteractions++;
    //     }
    // }

    // G4cout << "Number of gamma interactions in this event: "
    //        << gammaInteractions << G4endl;
}
