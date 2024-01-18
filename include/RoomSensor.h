#ifndef ROOMSENSOR_H
#define ROOMSENSOR_H

#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4VSensitiveDetector.hh"

class RoomSensor : public G4VSensitiveDetector {
   public:
    RoomSensor(const G4String& name);
    virtual ~RoomSensor();

    virtual G4bool ProcessHits(G4Step* step,
                               G4TouchableHistory* history) override;
};

#endif  // ROOMSENSOR_H
