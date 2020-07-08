

#include "NeutroncannonSteppingAction.hh"
#include "NeutroncannonEventAction.hh"
#include "NeutroncannonDetectorConstruction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "NeutroncannonAnalysis.hh"
#include "NeutroncannonPrimaryGeneratorAction.hh"
#include "G4OpticalPhoton.hh"
#include "G4UImanager.hh"
#include "G4LogicalVolume.hh"

#include <cmath>


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonSteppingAction::NeutroncannonSteppingAction(NeutroncannonEventAction* EvAct, NeutroncannonPrimaryGeneratorAction * primGen)
    :G4UserSteppingAction(),fEventAction(EvAct),fPrimaryGeneratorAction(primGen)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonSteppingAction::~NeutroncannonSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

//////////////////////// Info about neutrons 
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron")){
		//generated neutron
		if((aStep->GetTrack()->GetCurrentStepNumber() == 1) && (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()== "Tube_source")){
			fEventAction->addGenNeutrons();
			}
		//neutrons entering the TPC
		if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()== "TPC_Fill"){
			if(aStep->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)
					fEventAction->addTPCNeutrons();
			else
					fEventAction->addTPCNHits();		//scattering inside tpc
			}
	}
//////////////////////// Info about gammas
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){
		if((aStep->GetTrack()->GetCurrentStepNumber() == 1) && (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()== "Tube_source")){
				fEventAction->addGenGammas();
				}	
		if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()== "TPC_Fill" ){
			if(aStep->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)
					fEventAction->addTPCGammas();
			else
					fEventAction->addTPCGHits();		//scattering inside tpc
			}

	}	
	
///////////////////////////////////colleziona gamma secondari generati 
/*	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){//screma per particella
		if(aStep->GetTrack()->GetCurrentStepNumber() == 1){//condizione di prima generazione
				
			if(aStep->GetPreStepPoint()->GetMaterial()->GetName() =="hdpe"){
				if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()!= "Tube_source"){
					if((aStep->GetTrack()->GetCreatorProcess()->GetProcessName() != "compt") && (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() != "phot")){//condizione evita processi compton e fotoelettrico
								
						G4double energy = (aStep->GetPreStepPoint()->GetKineticEnergy());	
							if (aStep->GetPreStepPoint()->GetKineticEnergy() > 0.1) {//taglia energie <--------------------------------------------------------------
								analysisManager->FillNtupleDColumn(2,0,energy);
								analysisManager->AddNtupleRow(2);
							}	
					}
				}
			}
		    
			else{//nel resto dei materiali
				if ( aStep->GetPreStepPoint()->GetMaterial()->GetName() =="G4_Pb"){
					if(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()!= "Tube_source"){
						if((aStep->GetTrack()->GetCreatorProcess()->GetProcessName() != "compt") && (aStep->GetTrack()->GetCreatorProcess()->GetProcessName() != "phot")){//per neutron inelastic
							G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
								analysisManager->FillNtupleDColumn(3,0,energy);
								analysisManager->AddNtupleRow(3);
						}		
					}
				}	
			}	
		}	
	}
	
*/	

}





