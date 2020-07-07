

#include "NeutroncannonEventAction.hh"
#include "NeutroncannonAnalysis.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "NeutroncannonDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4VTrajectory.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonEventAction::NeutroncannonEventAction()
:G4UserEventAction()
{
   

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonEventAction::~NeutroncannonEventAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonEventAction::BeginOfEventAction( const G4Event* anEvent)
{ 
    //initializations
    i++;
    std::cout << "StartEvent " << i << std::endl;

    G4double fEnergyDep = 0;
    
    //inizializzare tutti i verrori evento per evento 
    // for(int i=0; i < fDetectorEnergyDep.size(); i++)
        this->clearDetectorEdepL1();
        this->clearDetectorEdepL2();
        this->clearDetectorEdepL3();
        this->clearDetectorEdepL4();
        this->clearDetectorEdeptot();
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonEventAction::EndOfEventAction( const G4Event* anEvent)
{

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

        if (fDetectorEnergyDepL1 > 0.001){
            analysisManager->FillNtupleDColumn(11,0,fDetectorEnergyDepL1);
            analysisManager->AddNtupleRow(11);
        }
        if (fDetectorEnergyDepL2 > 0.001){
            analysisManager->FillNtupleDColumn(12,0,fDetectorEnergyDepL2);
            analysisManager->AddNtupleRow(12);
        }    
        if (fDetectorEnergyDepL3 > 0.001){
            analysisManager->FillNtupleDColumn(13,0,fDetectorEnergyDepL3);
            analysisManager->AddNtupleRow(13);
        } 
        if (fDetectorEnergyDepL4 > 0.001){
            analysisManager->FillNtupleDColumn(14,0,fDetectorEnergyDepL4);
            analysisManager->AddNtupleRow(14);
        } 
        //totale
        if (fDetectorEnergyDep > 0.001){
            analysisManager->FillNtupleDColumn(15,0,fDetectorEnergyDep);
            analysisManager->AddNtupleRow(15);
        } 
        
        //G4cout << fDetectorEnergyDepL2 << G4endl;
        
        
        
        
    std::cout << "EndEvent " << i << std::endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


