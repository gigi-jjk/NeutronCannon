

#include "NeutroncannonSteppingAction.hh"
#include "NeutroncannonEventAction.hh"
#include "NeutroncannonDetectorConstruction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "NeutroncannonAnalysis.hh"
//#include "G4ELINP_DetectorConstruction_NRSS.hh"
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

	//debug
	G4int recordyes = 1;
	G4int validationyes = 0;

if (recordyes ==1){
//////////////////////// verifica numero di neutroni prodotti ed energie 
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron")){
		if((aStep->GetTrack()->GetCurrentStepNumber() == 1) && (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()== "Tube_source")){
			G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
			analysisManager->FillNtupleDColumn(0,0,energy);
			analysisManager->AddNtupleRow(0);
			//analysisManager->FillH1(0,energy);
		}	
	}
//////////////////////////verifica numero di gamma prodotti ed energie
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){
		if((aStep->GetTrack()->GetCurrentStepNumber() == 1) && (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName()== "Tube_source")){
			G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
			//G4cout << " kin. energy (MeV): " <<  aStep->GetTrack()->GetKineticEnergy() << G4endl;
			analysisManager->FillNtupleDColumn(1,0,energy);
			analysisManager->AddNtupleRow(1);
			//analysisManager->FillH1(1,energy);
		}	
	}	
	
///////////////////////////////////colleziona gamma secondari generati 
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){//screma per particella
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
	
	











//////////////gamma usciti 
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){
		
		if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detector"){
			
				
				G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
				G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition();
				G4ThreeVector direction = aStep->GetPreStepPoint()->GetMomentumDirection();

				 analysisManager->FillNtupleDColumn(4,0,energy);
				
				analysisManager->AddNtupleRow(4);
			
		}
	}	
	


//////////// neutroni usciti
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron"))	{
		
		if	(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detector"){
			
				
				G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
				G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition();
				G4ThreeVector direction = aStep->GetPreStepPoint()->GetMomentumDirection();

				 analysisManager->FillNtupleDColumn(5,0,energy);
				
				analysisManager->AddNtupleRow(5);
				
			
		}
		
	}

//////////////////////////////gamma attraverso il collimatore
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){
		if	(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detectordisc"){
			G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
				G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition();
				G4ThreeVector direction = aStep->GetPreStepPoint()->GetMomentumDirection();

				 analysisManager->FillNtupleDColumn(6,0,energy);
				 analysisManager->FillNtupleDColumn(10,0,energy);
				 analysisManager->AddNtupleRow(10);
				
				analysisManager->AddNtupleRow(6);
				
		}

	}
//////////////////////////////neutroni attraverso il collimatore
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron")){
		if	(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detectordisc"){
			G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
				G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition();
				G4ThreeVector direction = aStep->GetPreStepPoint()->GetMomentumDirection();

				 analysisManager->FillNtupleDColumn(7,0,energy);
				 analysisManager->FillNtupleDColumn(10,1,energy);
				 analysisManager->AddNtupleRow(10);
				
				analysisManager->AddNtupleRow(7);
				
		}

	}
	//////////////////////////////neutroni attraverso il collimatore puri
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron")){
		if ((aStep->GetTrack()->GetMaterial()->GetName() =="G4_AIR") || (aStep->GetTrack()->GetMaterial()->GetName() =="G4_Galactic")){
			if(aStep->GetPreStepPoint()->GetMomentum() == aStep->GetPostStepPoint()->GetMomentum()){//nessun cambio di direzione
				if	(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detectordisc"){
					
						G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
						G4cout << 
						analysisManager->FillNtupleDColumn(8,0,energy);
						analysisManager->AddNtupleRow(8);
						
				}
			}
		}
	}
	/////////////////////////////neutroni attraverso il collimatore puri
	if ((aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma")){
		if ((aStep->GetTrack()->GetMaterial()->GetName() =="G4_AIR") || (aStep->GetTrack()->GetMaterial()->GetName() =="G4_Galactic")){
			if(aStep->GetPreStepPoint()->GetMomentum() == aStep->GetPostStepPoint()->GetMomentum()){//nessun cambio di direzione
				if	(aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detectordisc"){
					
						G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
						analysisManager->FillNtupleDColumn(9,0,energy);
						analysisManager->AddNtupleRow(9);
				
				}
			}
		}
	}

////////////////////////////energia depositata nei rivelatori
	
	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "L1Detector"){//( aStep->GetPreStepPoint()->GetMaterial()->GetName() =="G4_BARIUM_FLUORIDE"){
		G4double Edepstep = (aStep->GetTotalEnergyDeposit()- aStep->GetNonIonizingEnergyDeposit ());
		if (Edepstep > 0.001){
			fEventAction->addDetectorEdepL1(Edepstep);
		}
	}
	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "L2Detector"){//( aStep->GetPreStepPoint()->GetMaterial()->GetName() =="G4_BARIUM_FLUORIDE"){
		G4double Edepstep = (aStep->GetTotalEnergyDeposit()- aStep->GetNonIonizingEnergyDeposit ());
        if (Edepstep > 0.001){
			fEventAction->addDetectorEdepL2(Edepstep);
		}	
	}
	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "L3Detector"){//( aStep->GetPreStepPoint()->GetMaterial()->GetName() =="G4_BARIUM_FLUORIDE"){
		G4double Edepstep = (aStep->GetTotalEnergyDeposit()- aStep->GetNonIonizingEnergyDeposit ());
        if (Edepstep > 0.001){
			fEventAction->addDetectorEdepL3(Edepstep);
		}	
	}
	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "L4Detector"){//( aStep->GetPreStepPoint()->GetMaterial()->GetName() =="G4_BARIUM_FLUORIDE"){
		G4double Edepstep = (aStep->GetTotalEnergyDeposit()- aStep->GetNonIonizingEnergyDeposit ());
        if (Edepstep > 0.001){
			fEventAction->addDetectorEdepL4(Edepstep);
		}	
	}
	if( aStep->GetPreStepPoint()->GetMaterial()->GetName() =="G4_BARIUM_FLUORIDE"){
		G4double Edepstep = (aStep->GetTotalEnergyDeposit()- aStep->GetNonIonizingEnergyDeposit ());
		if (Edepstep > 0.001){
			fEventAction->addDetectorEdeptot(Edepstep);
		}
	}

	////////////////////////////////////////////////////////
	//posizione dei neutroni uscenti frontalmente
	if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron"){
		if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "detectordisc"){

			G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition(); 
			analysisManager->FillNtupleDColumn(16,0,vertexpos.getX());
        	analysisManager->FillNtupleDColumn(16,1,vertexpos.getY());
			analysisManager->FillNtupleDColumn(16,1,vertexpos.getY());
			analysisManager->AddNtupleRow(16);
			

		}
	}
	if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron"){
		if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "nosecover"){

			G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition(); 
			analysisManager->FillNtupleDColumn(17,0,vertexpos.getX());
        	analysisManager->FillNtupleDColumn(17,1,vertexpos.getY());
			analysisManager->FillNtupleDColumn(17,1,vertexpos.getY());
			analysisManager->AddNtupleRow(17);
			

		}
	}
	if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron"){
		if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "c4front"){

			G4ThreeVector vertexpos = aStep->GetPreStepPoint()->GetPosition(); 
			analysisManager->FillNtupleDColumn(18,0,vertexpos.getX());
        	analysisManager->FillNtupleDColumn(18,1,vertexpos.getY());
			analysisManager->FillNtupleDColumn(18,1,vertexpos.getY());
			analysisManager->AddNtupleRow(18);
			

		}
	}

}
/*
if ( validationyes == 1){
///////////////////////////////////////////////////////
//debug validation sphere
if (aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron"){
	if (aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() == "sferadetector"){
		G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
		analysisManager->FillNtupleDColumn(5,0,energy);
		analysisManager->AddNtupleRow(5);
	}	
}


}
*/






}





