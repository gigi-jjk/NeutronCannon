

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

  //Creating Ntuple Id 0
  analysisManager->CreateNtuple("neutron spectrum", "");
  analysisManager->CreateNtupleDColumn("nSpectrum"); //0,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 1
  analysisManager->CreateNtuple("gamma spectrum", "");
  analysisManager->CreateNtupleDColumn("gSpectrum"); //1,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 2
  analysisManager->CreateNtuple("gamma generated in HDPE", "");
  analysisManager->CreateNtupleDColumn("gHDPE"); //4,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 3
  analysisManager->CreateNtuple("gamma generated in Pb", "");
  analysisManager->CreateNtupleDColumn("gPb"); //3,0
  analysisManager->FinishNtuple();

  //Creating Ntuple Id 4
  analysisManager->CreateNtuple("gamma escaped", "");
  analysisManager->CreateNtupleDColumn("gescaped"); //4,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 5
  analysisManager->CreateNtuple("neutron escaped", "");
  analysisManager->CreateNtupleDColumn("nescaped"); //5,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 6
  analysisManager->CreateNtuple("gamma beamed", "");
  analysisManager->CreateNtupleDColumn("gbeamed"); //6,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 7
  analysisManager->CreateNtuple("neutron beamed", "");
  analysisManager->CreateNtupleDColumn("nbeamed"); //7,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 8
  analysisManager->CreateNtuple("direct neutron beamed", "");
  analysisManager->CreateNtupleDColumn("npurebeamed"); //8,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 9
  analysisManager->CreateNtuple("direct gamma beamed", "");
  analysisManager->CreateNtupleDColumn("gpurebeamed"); //9,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 10
  analysisManager->CreateNtuple("direct gamma and neutron beamed", "");
  analysisManager->CreateNtupleDColumn("gbeamed"); //10,0
  analysisManager->CreateNtupleDColumn("nbeamed"); //10,1
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 11
  analysisManager->CreateNtuple("Energy Deposited in BaF2 L1", "");
  analysisManager->CreateNtupleDColumn("eDepL1"); //11,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 12
  analysisManager->CreateNtuple("Energy Deposited in BaF2 L2", "");
  analysisManager->CreateNtupleDColumn("eDepL2"); //12,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 13
  analysisManager->CreateNtuple("Energy Deposited in BaF2 L3", "");
  analysisManager->CreateNtupleDColumn("eDepL3"); //13,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 14
  analysisManager->CreateNtuple("Energy Deposited in BaF2 L4", "");
  analysisManager->CreateNtupleDColumn("eDepL4"); //14,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 15
  analysisManager->CreateNtuple("Energy Deposited in BaF2 total", "");
  analysisManager->CreateNtupleDColumn("eDeptot"); //15,0
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 16
  analysisManager->CreateNtuple("exit position1", "");
  analysisManager->CreateNtupleDColumn("xpos"); //16,0
  analysisManager->CreateNtupleDColumn("ypos"); //16,1
  analysisManager->CreateNtupleDColumn("zpos"); //16,2
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 17
  analysisManager->CreateNtuple("exit position2", "");
  analysisManager->CreateNtupleDColumn("xpos"); //17,0
  analysisManager->CreateNtupleDColumn("ypos"); //17,1
  analysisManager->CreateNtupleDColumn("zpos"); //16,2
  analysisManager->FinishNtuple();
  //Creating Ntuple Id 18
  analysisManager->CreateNtuple("exit position3", "");
  analysisManager->CreateNtupleDColumn("xpos"); //18,0
  analysisManager->CreateNtupleDColumn("ypos"); //18,1
  analysisManager->CreateNtupleDColumn("zpos"); //18,2
  analysisManager->FinishNtuple();
  

  /*
  //Creating Ntuple Histo ID 0
  analysisManager -> CreateH1("neutron spectrum","neutron generated spectrum", 255, 0., 10, "MeV");
  analysisManager -> CreateH1("gamma spectrum","gamma generated spectrum", 255, 0., 10, "MeV");

  //Creating Ntuple Histo ID 1
  analysisManager -> CreateH1("neutron spectrum","neutron generated spectrum", 255, 0., 10, "MeV");
  analysisManager -> CreateH1("gamma spectrum","gamma generated spectrum", 255, 0., 10, "MeV");
  */
  // Open an output file
  //
  G4String fileName = analysisManager->GetFileName();
  if(fileName == ""){
       fileName = "/media/dataDisk/datiTesi/TPC/OutFile.root";
       //fileName = "OutFile.root";
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
