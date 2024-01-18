#include "DetectorConstruction.h"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "RoomSensor.h"           // Include your RoomSensor header
#include "SimulationConstants.h"  // Include constants

DetectorConstruction::DetectorConstruction() {
    // Constructor implementation can go here
}

DetectorConstruction::~DetectorConstruction() {
    // Destructor implementation can go here
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Obtain the NIST material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Define materials
    G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* concrete = nist->FindOrBuildMaterial("G4_CONCRETE");
    G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

    // World volume
    G4Box* solidWorld =
        new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);
    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld, vacuum, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

    // Wall construction
    ConstructWalls(logicWorld, concrete);

    // Sensor construction
    ConstructSensors(logicWorld, water);

    return physWorld;
}

void DetectorConstruction::ConstructWalls(G4LogicalVolume* logicWorld,
                                          G4Material* wallMaterial) {
    G4Box* solidWall =
        new G4Box("Wall", wallThickness / 2, wallHeight / 2, wallWidth / 2);
    G4LogicalVolume* logicWall =
        new G4LogicalVolume(solidWall, wallMaterial, "Wall");

    G4VisAttributes* wallVisAttributes =
        new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));  // Gray color
    logicWall->SetVisAttributes(wallVisAttributes);

    new G4PVPlacement(0, G4ThreeVector(wallPositionX, 0, 0), logicWall, "Wall1",
                      logicWorld, false, 0, true);
    new G4PVPlacement(0, G4ThreeVector(-wallPositionX, 0, 0), logicWall,
                      "Wall2", logicWorld, false, 1, true);
}

void DetectorConstruction::ConstructSensors(G4LogicalVolume* logicWorld,
                                            G4Material* sensorMaterial) {
    G4Sphere* solidSensor = new G4Sphere("Sensor", 0., sensorRadius, 0.,
                                         2 * CLHEP::pi, 0., CLHEP::pi);
    G4LogicalVolume* logicSensor =
        new G4LogicalVolume(solidSensor, sensorMaterial, "Sensor");

    G4VisAttributes* sensorVisAttributes =
        new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));  // Cyan color
    logicSensor->SetVisAttributes(sensorVisAttributes);

    // Register the RoomSensor
    G4VSensitiveDetector* roomSensor = new RoomSensor("WaterSensor");
    G4SDManager::GetSDMpointer()->AddNewDetector(roomSensor);
    logicSensor->SetSensitiveDetector(roomSensor);

    // Calculate positions and place sensors
    G4double spacing = wallHeight / (numSensorsPerSide + 1);
    for (G4int i = 0; i < numSensorsPerSide; ++i) {
        for (G4int j = 0; j < numSensorsPerSide; ++j) {
            for (G4int k = 0; k < numSensorsPerSide; ++k) {
                G4double x = -wallWidth / 2 + (i + 1) * spacing;
                G4double y = -wallHeight / 2 + (j + 1) * spacing;
                G4double z = -wallWidth / 2 + (k + 1) * spacing;

                new G4PVPlacement(0, G4ThreeVector(x, y, z), logicSensor,
                                  "Sensor", logicWorld, false,
                                  i * numSensorsPerSide * numSensorsPerSide +
                                      j * numSensorsPerSide + k,
                                  true);
            }
        }
    }
}
