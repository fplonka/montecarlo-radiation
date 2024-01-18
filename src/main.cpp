#include "ActionInitialization.h"
#include "DetectorConstruction.h"
#include "G4PhysListFactory.hh"
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VModularPhysicsList.hh"
#include "G4VisExecutive.hh"
#include "PhysicsList.h"

int main(int argc, char** argv) {
    // Construct the default run manager
    auto runManager = new G4RunManager;

    // Set mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction());

    G4PhysListFactory physListFactory;

    // TODO: change to Shielding list or w/e
    // G4VModularPhysicsList* physicsList =
    // physListFactory.GetReferencePhysList(
    //     "FTFP_BERT");  // or "G4EmStandardPhysics"
    G4VModularPhysicsList* physicsList = physListFactory.GetReferencePhysList(
        "Shielding");  // or "G4EmStandardPhysics"
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    // Set user action initialization
    // This is where PrimaryGeneratorAction is set
    runManager->SetUserInitialization(new ActionInitialization());

    // Initialize the run manager
    runManager->Initialize();

    // Initialize visualization
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager::GetUIpointer()->ApplyCommand("/vis/list");

    // Get the pointer to the User Interface manager and set visualization
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Define UI session for interactive mode
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        // Interactive mode
        ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute init_vis.mac");
    }

    // Process macro or start UI session
    if (ui) {
        ui->SessionStart();
        delete ui;
    } else {
        // Batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // Job termination
    delete visManager;
    delete runManager;

    return 0;
}
