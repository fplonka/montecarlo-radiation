#include "RoomSensor.h"

#include <fstream>

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4TouchableHistory.hh"

// Constructor
RoomSensor::RoomSensor(const G4String& name) : G4VSensitiveDetector(name) {
    // Initialize any necessary variables
}

// Destructor
RoomSensor::~RoomSensor() {
    // Clean-up code if necessary
}

// ProcessHits method
G4bool RoomSensor::ProcessHits(G4Step* step, G4TouchableHistory* /*history*/) {
    G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
    G4int sensorNr = touchable->GetCopyNumber();

    sensorData[sensorNr].hits++;
    std::cout << "HIT: " << sensorNr << "\n";

    if (sensorData[sensorNr].hits == 1) {
        sensorData[sensorNr].position =
            touchable->GetVolume()->GetTranslation();
    }

    // G4double edep = step->GetTotalEnergyDeposit();

    // Get the position of the hit
    G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
    std::cout << "pos: " << pos << "\n";

    // You can add more information if needed

    // Save data to file
    // std::ofstream outFile;
    // outFile.open("radiation_data.csv", std::ios_base::app);  // Append mode
    // outFile << pos.x() / cm << "," << pos.y() / cm << "," << pos.z() / cm <<
    // ","
    //         << edep / keV << "\n";
    // outFile.close();

    return true;
}

void RoomSensor::EndOfRun() {
    std::ofstream file("sensor_data.csv");
    file << "SensorID,HitCount,PositionX,PositionY,PositionZ\n";
    for (const auto& entry : sensorData) {
        file << entry.first << "," << entry.second.hits << ","
             << entry.second.position.x() / cm << ","
             << entry.second.position.y() / cm << ","
             << entry.second.position.z() / cm << "\n";
    }
    file.close();
}