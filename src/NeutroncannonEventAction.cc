
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
    if (i%100==0) std::cout << "StartEvent " << i << std::endl;

        this->clearEvent();
    
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonEventAction::EndOfEventAction( const G4Event* anEvent)
{

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();



        analysisManager->FillNtupleIColumn(0,0,i);     
        analysisManager->FillNtupleIColumn(0,1,this->getGenNeutrons());      
        analysisManager->FillNtupleIColumn(0,2,this->getGenGammas());        
        analysisManager->FillNtupleIColumn(0,3,this->getInGunNeutrons());    
        analysisManager->FillNtupleIColumn(0,4,this->getInGunGammas());      
        analysisManager->FillNtupleIColumn(0,5,this->getOutGunNeutrons());   
        analysisManager->FillNtupleIColumn(0,6,this->getOutGunGammas());      
        analysisManager->FillNtupleIColumn(0,7,this->getTPCNeutrons());      
        analysisManager->FillNtupleIColumn(0,8,this->getTPCGammas());          
        analysisManager->FillNtupleIColumn(0,9,this->getTPCNHits());         
        analysisManager->FillNtupleIColumn(0,10,this->getTPCGHits());         
        analysisManager->FillNtupleIColumn(0,11,this->getBaFEnergy());      

        analysisManager->AddNtupleRow(0);
        
        
    //std::cout << "EndEvent " << i << std::endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


