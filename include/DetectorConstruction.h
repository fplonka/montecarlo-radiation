#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"

const G4double wallThickness = 20.0 * cm;
const G4double wallHeight = 2.0 * m;
const G4double wallWidth = 2.0 * m;
const G4double wallPositionX = 1.0 * m;

// World dimensions
const G4double worldSize = 30.0 * m;

// Sensor dimensions
const G4double sensorRadius = 2.0 * cm;
const G4int numSensorsPerSide = 8;  // Adjust this for more or fewer sensors

class DetectorConstruction : public G4VUserDetectorConstruction {
   public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    void PlaceDetectors();

    virtual G4VPhysicalVolume* Construct() override;
    void ConstructWalls(G4LogicalVolume* logicWorld, G4Material* wallMaterial);
    void ConstructSensors(G4LogicalVolume* logicWorld,
                          G4Material* sensorMaterial);
};

#endif  // DetectorConstruction_h
