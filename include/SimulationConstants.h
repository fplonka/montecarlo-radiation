#ifndef SIMULATIONCONSTANTS_H
#define SIMULATIONCONSTANTS_H

#include "G4SystemOfUnits.hh"

// Radiation Weighting Factors
constexpr double RWF_ALPHA = 20.0;
constexpr double RWF_GAMMA = 1.0;
constexpr double RWF_ELECTRON = 1.0;

// Sensor Dimensions
constexpr double SENSOR_RADIUS = 2.0 * cm;

// Room Dimensions
constexpr double ROOM_WIDTH = 10.0 * m;
constexpr double ROOM_HEIGHT = 3.0 * m;
constexpr double ROOM_DEPTH = 10.0 * m;

constexpr double SENSOR_DIST_FROM_LEFT_WALL = 2.0 * m;

constexpr double SOURCE_ACTIVITY = 100 * becquerel;

#endif  // SIMULATIONCONSTANTS_H
