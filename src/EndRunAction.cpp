#include "EndRunAction.h"

#include "G4Run.hh"
#include "G4SDManager.hh"
#include "RoomSensor.h"

EndRunAction::EndRunAction() : G4UserRunAction() {}

EndRunAction::~EndRunAction() {}

void EndRunAction::EndOfRunAction(const G4Run*) {
    // Retrieve the RoomSensor instance and call EndOfRun
    std::cout << "END OF "
                 "RUN----------------------------------------------------------"
                 "--------------------------\n";
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    RoomSensor* roomSensor = static_cast<RoomSensor*>(
        sdManager->FindSensitiveDetector("WaterSensor"));
    if (roomSensor) {
        roomSensor->EndOfRun();
    }
}
