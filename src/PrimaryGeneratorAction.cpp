#include "PrimaryGeneratorAction.h"

#include <CLHEP/Random/RandFlat.h>

#include <cmath>

#include "G4GeneralParticleSource.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RandomDirection.hh"
#include "G4SystemOfUnits.hh"
#include "SimulationConstants.h"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr) {}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    if (!fParticleGun) {
        fParticleGun = new G4ParticleGun(10);
        G4int Z = 55;   // Cesium
        G4int A = 137;  // Mass number 137
        G4double ionCharge = 0. * eplus;
        G4double excitEnergy = 0. * keV;

        G4ParticleDefinition* ion =
            G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);
        fParticleGun->SetParticleDefinition(ion);
        // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 1, 0));
        fParticleGun->SetParticlePosition(SOURCE_POSITION);
    }

    // G4double theta = 1.65 * 0.0933353;
    G4double theta = 0.0933353;

    // Generate two random numbers between 0 and 1
    G4double r1 = CLHEP::RandFlat::shoot(0., 1.);
    G4double r2 = CLHEP::RandFlat::shoot(0., 1.);

    // Calculate spherical coordinates
    G4double phi_r = 2 * CLHEP::pi * r1;  // Azimuthal angle
    G4double theta_r =
        std::acos((1 - std::cos(theta)) * r2 + std::cos(theta));  // Polar angle

    // Convert spherical coordinates to Cartesian
    G4double x = std::sin(theta_r) * std::cos(phi_r);
    G4double y = std::cos(theta_r);  // +y direction is the polar axis
    G4double z = std::sin(theta_r) * std::sin(phi_r);

    // Set the particle gun's direction
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x, y, z));

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

// if (ion) { fParticleSource->SetParticleDefinition(ion);
// fParticleSource->SetParticleCharge(ionCharge);
// fParticleSource->SetParticleTime(0.);

// fParticleSource->GetCurrentSource()
//     ->GetAngDist()
//     // ->SetParticleMomentumDirection(G4RandomDirection());
//     ->SetParticleMomentumDirection(G4ThreeVector(0, 0, 0));
// fParticleSource->SetParticlePosition(
//     G4ThreeVector(0.2, 0.2, 0.2));  // Slight offset

// fParticleSource->GeneratePrimaryVertex(anEvent);