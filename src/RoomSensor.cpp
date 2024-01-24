#include "RoomSensor.h"

#include <fstream>

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4TouchableHistory.hh"
#include "SimulationConstants.h"

// Constructor
RoomSensor::RoomSensor(const G4String& name) : G4VSensitiveDetector(name) {
    // Initialize any necessary variables
}

// Destructor
RoomSensor::~RoomSensor() {
    // Clean-up code if necessary
}

const G4double sensorVolume =
    (4.0 / 3.0) * CLHEP::pi * std::pow(SENSOR_RADIUS, 3);
const G4double sensorMass = sensorVolume * 1.0 * g / cm3;

// ProcessHits method
G4bool RoomSensor::ProcessHits(G4Step* step, G4TouchableHistory* /*history*/) {
    G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
    G4int sensorNr = touchable->GetCopyNumber();

    // Get particle type and determine quality factor
    G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
    G4String particleName = particle->GetParticleName();
    G4double qualityFactor;

    if (particleName == "gamma") {
        qualityFactor = 1;  // For gamma rays
    } else if (particleName == "neutron") {
        qualityFactor = 20;  // For neutrons
    } else if (particleName == "alpha") {
        qualityFactor = 20;  // For alpha particles
    } else if (particle->GetParticleType() == "nucleus") {
        qualityFactor = 20;  // For heavy nuclei
    } else {
        qualityFactor = 1;  // Default for other particles, like electrons
    }

    G4double energyDeposit = step->GetTotalEnergyDeposit();
    G4double dose = energyDeposit * qualityFactor / sensorMass;

    sensorData[sensorNr].dose += dose;
    sensorData[sensorNr].hits++;

    if (sensorData[sensorNr].hits == 1) {
        sensorData[sensorNr].position =
            touchable->GetVolume()->GetTranslation();
    }
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

    std::ofstream file2("sensor_data2.csv");
    file2 << "SensorID,Radiation,PositionX,PositionY,PositionZ\n";
    for (const auto& entry : sensorData) {
        file2 << entry.first << "," << entry.second.dose / SIM_TIME << ","
              << entry.second.position.x() / cm << ","
              << entry.second.position.y() / cm << ","
              << entry.second.position.z() / cm << "\n";
    }
    file2.close();
}