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
    // Get energy deposit
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep == 0.) {
        return false;
    }

    // Get the position of the hit
    G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();

    // You can add more information if needed

    // Save data to file
    std::ofstream outFile;
    outFile.open("radiation_data.csv", std::ios_base::app);  // Append mode
    outFile << pos.x() / cm << "," << pos.y() / cm << "," << pos.z() / cm << ","
            << edep / keV << "\n";
    outFile.close();

    return true;
}
