#ifndef PRIMARYGENERATORACTION_H
#define PRIMARYGENERATORACTION_H

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
   public:
    // Constructor
    PrimaryGeneratorAction();

    // Destructor
    virtual ~PrimaryGeneratorAction();

    // Method to generate primary particles
    virtual void GeneratePrimaries(G4Event* anEvent) override;

   private:
    // Particle source
    G4GeneralParticleSource* fParticleSource;
};

#endif  // PRIMARYGENERATORACTION_H
