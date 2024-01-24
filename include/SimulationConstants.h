#ifndef SIMULATIONCONSTANTS_H
#define SIMULATIONCONSTANTS_H

#include "G4SystemOfUnits.hh"

// Radiation Weighting Factors
// constexpr double RWF_ALPHA = 20.0;
// constexpr double RWF_GAMMA = 1.0;
// constexpr double RWF_ELECTRON = 1.0;

// constexpr double SENSOR_DIST_FROM_LEFT_WALL = 2.0 * m;

// Sensor dimensions
const G4double SENSOR_RADIUS = 2.0 * cm;
const G4int NUM_SENSORS_PER_SIDE = 8;

// Room dimensions
const G4double ROOM_LENGTH = 10.05 * m;
const G4double ROOM_WIDTH = 5.50 * m;
const G4double ROOM_HEIGHT = 3.22 * m;
const G4double WALL_THICKNESS = 1.0 * m;
const G4ThreeVector roomTranslation((ROOM_WIDTH + WALL_THICKNESS) / 2,
                                    (ROOM_LENGTH + WALL_THICKNESS) / 2,
                                    (ROOM_HEIGHT + WALL_THICKNESS) / 2);

const G4ThreeVector SOURCE_POSITION(2.62 * m, 1.29 * m, 1.66 * m);

const G4long NUM_EVENTS = 100000;

const G4double PROPORTION_LEAVING = 0.00217629;
const G4double SOURCE_ACTIVITY =
    330.0 * 1000000000.0 * becquerel * std::pow(0.5, 15030.0 / 10975.0);

const G4double SIM_TIME = G4double(NUM_EVENTS) /
                          (SOURCE_ACTIVITY * PROPORTION_LEAVING) /
                          hour;  // in hours

#endif  // SIMULATIONCONSTANTS_H
