#include "DetectorConstruction.h"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "RoomSensor.h"
#include "SimulationConstants.h"

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

    // World volume - slightly larger than the room to contain it
    G4double worldSize = std::max({ROOM_LENGTH, ROOM_WIDTH, ROOM_HEIGHT}) +
                         100 * m;  // Ensure the world is larger than the room

    G4Box* solidWorld =
        new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);
    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld, vacuum, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

    // Wall construction
    ConstructWalls(logicWorld, concrete);

    // Sensor construction
    // ConstructSensors(logicWorld, water);
    ConstructSensorsExperimental(logicWorld, water);

    return physWorld;
}

void DetectorConstruction::ConstructWalls(G4LogicalVolume* logicWorld,
                                          G4Material* wallMaterial) {
    // Create the outer box (room + walls)
    G4Box* outerBox = new G4Box("OuterBox", (ROOM_WIDTH + WALL_THICKNESS) / 2,
                                (ROOM_LENGTH + WALL_THICKNESS) / 2,
                                (ROOM_HEIGHT + WALL_THICKNESS) / 2);

    // Create the inner box (room)
    G4Box* innerBox =
        new G4Box("InnerBox", ROOM_WIDTH / 2, ROOM_LENGTH / 2, ROOM_HEIGHT / 2);

    // Subtract the inner box from the outer box to create the walls
    G4SubtractionSolid* roomWalls =
        new G4SubtractionSolid("RoomWalls", outerBox, innerBox);

    // Logical volume for the walls
    G4LogicalVolume* logicRoomWalls =
        new G4LogicalVolume(roomWalls, wallMaterial, "RoomWalls");

    // Visualization attributes
    G4VisAttributes* wallVisAttributes =
        new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));  // Gray color
    logicRoomWalls->SetVisAttributes(wallVisAttributes);

    // Place the walls in the world
    new G4PVPlacement(0, roomTranslation, logicRoomWalls, "RoomWalls",
                      logicWorld, false, 0, true);
}

void DetectorConstruction::ConstructSensors(G4LogicalVolume* logicWorld,
                                            G4Material* sensorMaterial) {
    G4Sphere* solidSensor = new G4Sphere("Sensor", 0., SENSOR_RADIUS, 0.,
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

    G4double spacingX = ROOM_WIDTH / (NUM_SENSORS_PER_SIDE + 1);
    G4double spacingY = ROOM_LENGTH / (NUM_SENSORS_PER_SIDE + 1);
    G4double spacingZ = ROOM_HEIGHT / (NUM_SENSORS_PER_SIDE + 1);
    for (G4int i = 0; i < NUM_SENSORS_PER_SIDE; ++i) {
        for (G4int j = 0; j < NUM_SENSORS_PER_SIDE; ++j) {
            for (G4int k = 0; k < NUM_SENSORS_PER_SIDE; ++k) {
                // Calculate position for each sensor
                G4double x = (i + 1) * spacingX;
                G4double y = (j + 1) * spacingY;
                G4double z = (k + 1) * spacingZ;

                // Adjust for the translation of the room
                G4ThreeVector sensorPosition = G4ThreeVector(x, y, z);

                // Place each sensor
                new G4PVPlacement(
                    0, sensorPosition, logicSensor, "Sensor", logicWorld, false,
                    i * NUM_SENSORS_PER_SIDE * NUM_SENSORS_PER_SIDE +
                        j * NUM_SENSORS_PER_SIDE + k,
                    true);
            }
        }
    }

    // new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicSensor, "SensorOrigin",
    //   logicWorld, false, -1, true);
}

void DetectorConstruction::ConstructSensorsExperimental(
    G4LogicalVolume* logicWorld, G4Material* sensorMaterial) {
    G4Sphere* solidSensor = new G4Sphere("Sensor", 0., SENSOR_RADIUS, 0.,
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

    // Sensor positions based on experimental data
    std::vector<G4double> yPosListFirstLayer = {1 * m, 1.5 * m, 2 * m, 2.5 * m,
                                                4 * m, 4.5 * m, 5 * m, 5.5 * m,
                                                6 * m, 7 * m,   8 * m};
    std::vector<G4double> yPosListSecondLayer = {
        1 * m, 1.5 * m, 2 * m, 2.5 * m, 4 * m, 4.5 * m, 5 * m, 5.5 * m};
    G4double xPosOffset = 1.0 * m;        // +-1m in the x direction
    G4double firstLayerZPos = 0.9 * m;    // First layer height
    G4double secondLayerZPos = 1.92 * m;  // Second layer height

    G4ThreeVector sourcePosition = SOURCE_POSITION;
    int sensorID = 1;

    // Place sensors for the first layer
    for (auto yPos : yPosListFirstLayer) {
        G4ThreeVector sensorPosition1 =
            G4ThreeVector(sourcePosition.x() + xPosOffset,
                          sourcePosition.y() + yPos, firstLayerZPos);
        new G4PVPlacement(0, sensorPosition1, logicSensor, "Sensor", logicWorld,
                          false, sensorID++, true);

        G4ThreeVector sensorPosition2 =
            G4ThreeVector(sourcePosition.x() - xPosOffset,
                          sourcePosition.y() + yPos, firstLayerZPos);
        new G4PVPlacement(0, sensorPosition2, logicSensor, "Sensor", logicWorld,
                          false, sensorID++, true);
    }

    // Place sensors for the second layer
    for (auto yPos : yPosListSecondLayer) {
        G4ThreeVector sensorPosition1 =
            G4ThreeVector(sourcePosition.x() + xPosOffset,
                          sourcePosition.y() + yPos, secondLayerZPos);
        new G4PVPlacement(0, sensorPosition1, logicSensor, "Sensor", logicWorld,
                          false, sensorID++, true);

        G4ThreeVector sensorPosition2 =
            G4ThreeVector(sourcePosition.x() - xPosOffset,
                          sourcePosition.y() + yPos, secondLayerZPos);
        new G4PVPlacement(0, sensorPosition2, logicSensor, "Sensor", logicWorld,
                          false, sensorID++, true);
    }

    // std::vector<G4double> additionalYPos = {7 * m, 8 * m};
    // G4double middleXPos = sourcePosition.x();  // Same x as the source

    // // Place additional sensors for both layers
    // for (auto yPos : additionalYPos) {
    //     G4ThreeVector sensorPositionFirstLayer = G4ThreeVector(
    //         middleXPos, sourcePosition.y() + yPos, firstLayerZPos);
    //     new G4PVPlacement(0, sensorPositionFirstLayer, logicSensor, "Sensor",
    //                       logicWorld, false, sensorID++, true);

    //     G4ThreeVector sensorPositionSecondLayer = G4ThreeVector(
    //         middleXPos, sourcePosition.y() + yPos, secondLayerZPos);
    //     new G4PVPlacement(0, sensorPositionSecondLayer, logicSensor,
    //     "Sensor",
    //                       logicWorld, false, sensorID++, true);
    // }

    // new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicSensor, "SensorOrigin",
    //                   logicWorld, false, -1, true);
    // new G4PVPlacement(0, SOURCE_POSITION, logicSensor, "SensorSource",
    //                   logicWorld, false, -2, true);
}
