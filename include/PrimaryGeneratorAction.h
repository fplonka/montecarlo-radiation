#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
   public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent) override;

   private:
    G4ParticleGun* particleGun;
};

#endif  // PrimaryGeneratorAction_h
