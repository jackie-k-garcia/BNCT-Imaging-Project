//
// The head file in the BNCT Imaging Project simulation.
//

#ifdef G4MULTITHREADED
  #include "G4MTRunManager.hh"
#else
  #include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4ScoringManager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "QGSP_BERT.hh"
#include "ActionInitialization.hh"

#ifdef G4VIS_USE
  #include "G4VisExecutive"
#endif

#ifdef G4UI_USE
  #include "G4UIExecutive.hh"
#endif

// ....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int main(int argc, char** argv)
{
  // Define the default arguments used when you run the executable.
  G4String macroFile = "None";
  G4String startingSeed = "1";

  // Parse the arguments for the executable depending on the number of
  //  arguments passed to the executable.
  if (argc > 1) macroFile = argv[1];
  if (argc > 2) startingSeed = argv[2];

  // Print the arguments used for the executable.
  G4cout << "Starting run with..." << G4endl << G4endl;
  G4cout << "Macro file     :" << G4endl << G4endl;
  G4cout << "Starting seed  :" << G4endl << G4endl;

  // Initialize the multithreaded run manager if Geant4 is run in multithreaded
  //  mode.
  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
  #else
    G4RunManager* runManager = new G4RunManager;
  #endif

  // Initialize the random engine. POSSIBLY UPDATE ???
  G4Random::setTheEngine(new CLHEP::RanecuEngine);

  // Convert the starting seed to an integer and feed it to the random engine.
  unsigned startingSeedInt;
  std::istringstream is(startingSeed);
  is >> startingSeedInt;
  G4Random::setTheSeed(startingSeedInt);

  // Instantiate the scoring manager. NECESSARY ???
  G4ScoringManager::GetScoringManager();

  // Instantiate the geometry.
  DetectorConstruction* det = new DetectorConstruction;
  runManager->SetUserInitialization(det);

  // Instantiate the physics list. POSSIBLY UPDATE TO MORE ACCURATE PHYSICS LIST ???
  runManager->SetUserInitialization(new QGSP_BERT);

  // Set the action initialization.
  runManager->SetUserInitialization(new ActionInitialization(det));

  // Initialize the visual and UI managers with or without the macro file.
  //  If initializaed with the macro file, the simulation is run in interactive
  //  mode.
  #ifdef G4VIS_USE

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

  #endif

  // Open an UI session: It will stay open until the user types "exit" or
  //  simply uses a keyboard interrupt.
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Run the default macro file if no macro file has been specified as an
  //  argument to the executable, the executable is set to use an UI and
  //  visualization is turned on.
  if (argc == 1)
  {
    #ifdef G4UI_USE

      // Create a new UI executive object to start the simulation session if the
      //  executable has been run in interactive mode.
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    #ifdef G4VIS_USE

      // Run the visualization macro.
      UImanager->ApplyCommand('/control/execute vis.mac');

    #endif

      // Start the simulation session.
      ui->SessionStart();

      // Delete the UI executive object after the session is over.
      delete ui;

    #endif
  }

  // Run the executable with the specified macro provided as an argument to the
  //  executable if one or more arguments have been provided by the user.
  else
  {
    #ifdef G4UI_USE

      // Create a new UI executive object to start the simulation session if
      //  the executable has been run in interactive mode.
      G4UIExecutive* ui = new G4UIExecutive(argc, argv);

      // Define command prefix to use to execute the macro file.
      G4String command_prefix = '/control/execute ';

      // Apply the full command, including the macro filename.
      UImanager->ApplyCommand(command_prefix + macroFile);

      // Start the simulation session.
      ui->SessionStart();

      // Delete the UI executive object after the session is over.
      delete ui;

    #endif
  }

  // Terminate the simulation.
  delete runManager;

  // Exit the main function with no errors.
  return 0;

}
