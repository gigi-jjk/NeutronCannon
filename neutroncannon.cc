//
// ********************************************************************
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "G4PhysListFactory.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "G4ScoringManager.hh"

#include "NeutroncannonDetectorConstruction.hh"
#include "NeutroncannonPhysicsList.hh"
#include "NeutroncannonActionInitialization.hh"
#include "NeutroncannonSteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {
 
  //choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4int seconds =  time(NULL);
  G4Random::setTheSeed(seconds);
  
  // Construct the default run manager
  #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
  #else
    G4VSteppingVerbose::SetInstance(new NeutroncannonSteppingVerbose);  
    G4RunManager* runManager = new G4RunManager;
  #endif


   G4ScoringManager::GetScoringManager(); // This enables scoring
  // set mandatory initialization classes

  NeutroncannonDetectorConstruction *detector = new NeutroncannonDetectorConstruction();
  runManager->SetUserInitialization(detector);

  ///Physics

  // Initialize the physics
  G4PhysListFactory factory;                                  
  G4VModularPhysicsList* phys = 0;                           
  G4String physName = "";                                     




  // Physics List name defined via environment variable
  char* path = std::getenv("PHYSLIST");                       //crea un puntatore a char con  una variabile di ambiente??????
  if (path) { physName = G4String(path); }                    //se da esito positivo  associa all oggeto physName  G4String(path) (sarà una stringa tirata fuori da geant).

  if(physName != "" && factory.IsReferencePhysList(physName)) //se la stringa physName non è vuota e risultato di IsReferencePhysList(physName) dell oggetto factory è vero
    {
      phys = factory.GetReferencePhysList(physName);          //allora associa a phys factory.GetReferencePhysList(physName)
    }

  if(!phys) { phys = new NeutroncannonPhysicsList(); }           //se l assegnazione di phys va a buon fine  sli associa GammaKnifePhysicsList()

  runManager->SetUserInitialization(phys);                    //fa partire la simulazione con le impostazioni date da phys (forse sono le impostazioni della fisica del sistema)





  
    
  // set user action classes
  runManager->SetUserInitialization(new NeutroncannonActionInitialization);
  //Initialize G4 kernel
  runManager->Initialize();
    
  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager -> Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc!=1) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode : define UI session

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

     UImanager->ApplyCommand("/control/execute defaultMacro.mac");/////////////<--------------------------------

    // UImanager->ApplyCommand("/control/execute batch.mac");

    ui->SessionStart();
    delete ui;

  }

  delete visManager;

  delete runManager;
  //delete controller;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

