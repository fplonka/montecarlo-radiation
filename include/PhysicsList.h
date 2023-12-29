#ifndef PhysicsList_h
#define PhysicsList_h

#include "G4VUserPhysicsList.hh"

class PhysicsList : public G4VUserPhysicsList {
   public:
    PhysicsList();
    virtual ~PhysicsList();

   protected:
    virtual void ConstructParticle() override;
    virtual void ConstructProcess() override;
    virtual void SetCuts() override;
};

#endif  // PhysicsList_h
