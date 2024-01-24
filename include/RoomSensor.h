#ifndef ROOMSENSOR_H
#define ROOMSENSOR_H

#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4VSensitiveDetector.hh"

struct SensorInfo {
    G4int hits;
    G4double dose;
    G4ThreeVector position;
};

class RoomSensor : public G4VSensitiveDetector {
   public:
    RoomSensor(const G4String& name);
    virtual ~RoomSensor();

    virtual G4bool ProcessHits(G4Step* step,
                               G4TouchableHistory* history) override;
    void EndOfRun();

   private:
    std::map<G4int, SensorInfo>
        sensorData;  // Store hit count and position for each sensor
};

#endif  // ROOMSENSOR_H
