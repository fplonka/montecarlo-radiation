#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
   public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    void PlaceDetectors();

    virtual G4VPhysicalVolume* Construct() override;
    void ConstructWalls(G4LogicalVolume* logicWorld, G4Material* wallMaterial);
    void ConstructSensors(G4LogicalVolume* logicWorld,
                          G4Material* sensorMaterial);
    void ConstructSensorsExperimental(G4LogicalVolume* logicWorld,
                                      G4Material* sensorMaterial);
};

#endif  // DetectorConstruction_h
