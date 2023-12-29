#include "PrimaryGeneratorAction.h"

#include "G4Gamma.hh"
#include "G4ParticleGun.hh"
#include "G4Poisson.hh"
#include "G4RandomTools.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : particleGun(new G4ParticleGun(1)) {
    // Constructor implementation
    particleGun->SetParticleDefinition(G4Gamma::GammaDefinition());
    particleGun->SetParticleEnergy(662 *
                                   keV);  // Set energy to 662 keV for Cs-137
    // The direction will be set randomly for each photon below
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete particleGun;
    // Destructor implementation
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    // Assuming you have defined a variable for the activity of the source
    // You can calculate the expected number of decays in the time window of the
    // event Here we assume a time window of 1 second for simplicity
    // this depends on the amount of it?
    double activity = 37000 * becquerel;  // Example activity of 1 Ci
                                          //
    double timeWindow = 0.03 * second;
    G4int numPhotons = G4Poisson(
        activity * timeWindow);  // Number of photons based on the activity
                                 // i

    numPhotons = 100;

    for (G4int i = 0; i < numPhotons; ++i) {
        // G4ThreeVector dir =
        G4RandomDirection();  // Random direction for each photon
        // particleGun->SetParticleMomentumDirection(dir);
        particleGun->GeneratePrimaryVertex(anEvent);
    }

    G4cout << "Generating " << numPhotons << " photons from a Cs-137 source."
           << G4endl;
}
