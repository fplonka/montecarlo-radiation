#include "DetectorConstruction.h"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"

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
    // G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* lead = nist->FindOrBuildMaterial("G4_CONCRETE");

    // Dimensions
    G4double wallThickness = 20.0 * cm;
    G4double wallHeight = 2.0 * m;
    G4double wallWidth = 2.0 * m;
    G4double wallPositionX =
        1.0 * m;  // Position of the wall in the x-direction

    // World volume
    G4double worldSize = 30.0 * m;
    G4Box* solidWorld =
        new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);
    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld, vacuum, "World");

    // The world volume is the mother volume of all other volumes
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

    // Wall volume
    G4Box* solidWall =
        new G4Box("Wall", wallThickness / 2, wallHeight / 2, wallWidth / 2);
    G4LogicalVolume* logicWall = new G4LogicalVolume(solidWall, lead, "Wall");

    G4VisAttributes* wallVisAttributes =
        new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));  // Gray color
    logicWall->SetVisAttributes(wallVisAttributes);

    // Place the first wall in the world
    new G4PVPlacement(0, G4ThreeVector(wallPositionX, 0, 0), logicWall, "Wall1",
                      logicWorld, false, 0, true);

    // Place the second wall in the world, opposite to the first
    new G4PVPlacement(0, G4ThreeVector(-wallPositionX, 0, 0), logicWall,
                      "Wall2", logicWorld, false, 1, true);

    return physWorld;
}
