#include "PrimaryGeneratorAction.h"

#include "G4GeneralParticleSource.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4RandomDirection.hh"
#include "G4SystemOfUnits.hh"
#include "SimulationConstants.h"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleSource(new G4GeneralParticleSource()) {}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleSource; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    G4int Z = 55;   // Cesium
    G4int A = 137;  // Mass number 137
    G4double ionCharge = 0. * eplus;
    G4double excitEnergy = 0. * keV;

    G4ParticleDefinition* ion =
        G4IonTable::GetIonTable()->GetIon(Z, A, excitEnergy);
    // if (ion) {
    fParticleSource->SetParticleDefinition(ion);
    fParticleSource->SetParticleCharge(ionCharge);
    fParticleSource->SetParticleTime(0.);

    fParticleSource->GetCurrentSource()
        ->GetAngDist()
        ->SetParticleMomentumDirection(G4RandomDirection());

    fParticleSource->GeneratePrimaryVertex(anEvent);
}
