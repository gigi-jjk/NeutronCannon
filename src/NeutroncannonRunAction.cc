

#include "NeutroncannonRunAction.hh"
//#include "G4CsvAnalysisManager.hh"
//#include "G4RootAnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4String.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonRunAction::NeutroncannonRunAction()
 : G4UserRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonRunAction::~NeutroncannonRunAction()
{
  delete G4RootAnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void NeutroncannonRunAction::BeginOfRunAction(const G4Run*)
{
  // save Rndm status
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  G4Random::showEngineStatus();

  
   // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);  
  //analysisManager->SetFirstHistoId(0);

  //Creating NTuple 
  //general event info 
  analysisManager->CreateNtuple("Event", "");               //Ntuple 0
  analysisManager->CreateNtupleIColumn("EventID");          //0 event number
  analysisManager->CreateNtupleIColumn("GenNeutrons");      //1 number of generated neutrons
  analysisManager->CreateNtupleIColumn("GenGammas");        //2 number of generated gammas
  analysisManager->CreateNtupleIColumn("InGunNeutrons");    //3 number of neutrons outside the gun
  analysisManager->CreateNtupleIColumn("InGunGammas");      //4 number of gammas outside the gun
  analysisManager->CreateNtupleIColumn("OutGunNeutrons");   //5 number of neutrons escaping the system
  analysisManager->CreateNtupleIColumn("OutGunGammas");     //6 number of gammas escaping the system 
  //TPC info
  analysisManager->CreateNtupleIColumn("TPCNeutrons");      //7 number of neutrons at TPC per event
  analysisManager->CreateNtupleIColumn("TPCGammas");        //8 number of gammas at TPC per event  
  analysisManager->CreateNtupleIColumn("TPCNHits");         //9 number of neutron Hits inside TPC
  analysisManager->CreateNtupleIColumn("TPCGHits");         //10number "Gamma Hits" inside TPC
            //add info about energy, time and direction
  //BaF Trigger detector info
  analysisManager->CreateNtupleDColumn("BaFEnergy");      //energy deposited at trigger detector per event
            //add info about energy, time and direction
   

  analysisManager->FinishNtuple();


  // Open an output file
  //
  G4String fileName = analysisManager->GetFileName();
  if(fileName == ""){
       //fileName = "/media/dataDisk/datiTesi/TPC/OutFile.root";
       fileName = "OutFile.root";
  }

  analysisManager->OpenFile(fileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonRunAction::EndOfRunAction(const G4Run*)
{  
  // show Rndm status
   G4Random::showEngineStatus();         

  // //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


  analysisManager->Write();
  analysisManager->CloseFile();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
