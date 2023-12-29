#include "PhysicsList.h"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4ParticleTypes.hh"  // This includes the definition for G4Gamma
#include "G4PhotoElectricEffect.hh"
#include "G4PhysicsListHelper.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList() {
    // Constructor implementation, even if it's empty
}

PhysicsList::~PhysicsList() {
    // Destructor implementation, even if it's empty
}

void PhysicsList::ConstructParticle() {
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4Gamma::GammaDefinition();
}

void PhysicsList::ConstructProcess() {
    // Add photoelectric effect, Compton scattering, and pair production
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    ph->RegisterProcess(new G4PhotoElectricEffect, G4Gamma::Gamma());
    ph->RegisterProcess(new G4ComptonScattering, G4Gamma::Gamma());
    ph->RegisterProcess(new G4GammaConversion, G4Gamma::Gamma());
    // ...
}

void PhysicsList::SetCuts() {
    // Set cuts for gamma
    SetCutValue(1 * mm, "gamma");
}
