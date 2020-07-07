
#include "NeutroncannonTrackingAction.hh"
#include "NeutroncannonAnalysis.hh"
#include "NeutroncannonRunAction.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4Trajectory.hh"

#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"

NeutroncannonTrackingAction::NeutroncannonTrackingAction()
    : G4UserTrackingAction()
{ }

void NeutroncannonTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
    
    fpTrackingManager->SetStoreTrajectory(true);
    fpTrackingManager->SetTrajectory(new G4Trajectory(aTrack));
    /*
    //debug gamma in uscita
    if(aTrack->GetVolume()->GetName()== "physicaTreatmentRoom" && aTrack->GetParentID() == 0 && aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() == "neutron"){
        G4cout << " particle:  " << aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;
        G4cout << " kin. energy (MeV): " << aTrack->GetKineticEnergy() << G4endl;
        G4cout << " Track ID " << aTrack->GetTrackID() << G4endl;
    }
    */



    //debug generazione particelle
    //  if(aTrack->GetVolume()->GetName()== "Tube_source" && aTrack->GetParentID() == 0 && aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma"){
    //      //G4cout << " particle:  " << aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;
    //      G4cout << " kin. energy (MeV): " << aTrack->GetKineticEnergy() << G4endl;
    //  }
/*
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    


    if(aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma" && (aTrack->GetVolume()->GetName() == "physicalTreatmentRoom" )){
    //||aTrack->GetVolume()->GetName()== "detectorFront" ||aTrack->GetVolume()->GetName()== "detectorLeft" ||aTrack->GetVolume()->GetName()== "detectorRight" 
   // ||aTrack->GetVolume()->GetName()== "detectorDown" ||aTrack->GetVolume()->GetName()== "detectorUp")){//
       
       analysisManager->FillNtupleDColumn(1,0,aTrack->GetKineticEnergy());
       analysisManager->AddNtupleRow(1);
       
        // G4cout << "[PreTrackingAction::DEBUG]" << G4endl;
         G4cout << " Track ID:          " << aTrack->GetTrackID() << G4endl;
         G4cout << " particle:          " << aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;
         G4cout << " kin. energy (MeV): " << aTrack->GetKineticEnergy() / MeV << G4endl;
        // G4cout << " volume:            " << aTrack->GetVolume()->GetName() << G4endl;
    }
    /*
    G4cout << "[PreTrackingAction::DEBUG]" << G4endl;
    G4cout << " Track ID:          " << aTrack->GetTrackID() << G4endl;
    G4cout << " particle:          " << aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;

    if( aTrack->GetParentID() >= 1 ){
        G4cout << " Parent ID:         " << aTrack->GetParentID() << G4endl;
        G4cout << " created by:        " << aTrack->GetCreatorProcess()->GetProcessName() << G4endl;
    }

    G4cout << " kin. energy (MeV): " << aTrack->GetKineticEnergy() / MeV << G4endl;
    G4cout << " volume:            " << aTrack->GetVolume()->GetName() << G4endl;
    G4cout << " global time:       " << aTrack->GetGlobalTime() << G4endl;
    */



}

void NeutroncannonTrackingAction::PostUserTrackingAction(const G4Track *aTrack)
{   
    /*
    if(aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() == "gamma" && (aTrack->GetVolume()->GetName() == "physicalTreatmentRoom" )){
    //||aTrack->GetVolume()->GetName()== "detectorFront" ||aTrack->GetVolume()->GetName()== "detectorLeft" ||aTrack->GetVolume()->GetName()== "detectorRight" 
   // ||aTrack->GetVolume()->GetName()== "detectorDown" ||aTrack->GetVolume()->GetName()== "detectorUp")){//
       G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
       analysisManager->FillNtupleDColumn(1,0,aTrack->GetKineticEnergy());
       analysisManager->AddNtupleRow(1);
       
        // G4cout << "[PreTrackingAction::DEBUG]" << G4endl;
         G4cout << " Track ID:          " << aTrack->GetTrackID() << G4endl;
         G4cout << " particle:          " << aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;
         G4cout << " kin. energy (MeV): " << aTrack->GetKineticEnergy() / MeV << G4endl;
        // G4cout << " volume:            " << aTrack->GetVolume()->GetName() << G4endl;
    }
    
    
    
    
    /*
    G4cout << "[POSTTrackingAction::DEBUG]" << G4endl;
    G4cout << " Track ID:          " << aTrack->GetTrackID() << G4endl;
    G4cout << " particle:          " << aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName() << G4endl;
    if( aTrack->GetParentID() >= 1 ){
        G4cout << " Parent ID:         " << aTrack->GetParentID() << G4endl;
        G4cout << " created by:        " << aTrack->GetCreatorProcess()->GetProcessName() << G4endl;
    }

    G4cout << " kin. energy (MeV): " << aTrack->GetKineticEnergy() / MeV << G4endl;
    G4cout << " volume:            " << aTrack->GetVolume()->GetName() << G4endl;
    G4cout << " global time:       " << aTrack->GetGlobalTime() << G4endl;
    */
}
