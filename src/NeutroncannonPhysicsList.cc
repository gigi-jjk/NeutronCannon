
//
/// \file hadronic/Hadr03/src/PhysicsList.cc
/// \brief Implementation of the PhysicsList class
//
// $Id: PhysicsList.cc 70319 2013-05-29 07:53:09Z gcosmo $

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NeutroncannonPhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"
#include <G4PhysListFactory.hh>
//#include <G4EmLivermorePhysics.hh>
#include <G4EmStandardPhysics_option4.hh>
#include <G4EmExtraPhysics.hh>
//#include <G4EmStandardPhysics.hh>
#include <G4HadronPhysicsQGSP_BIC_HP.hh>
#include <G4StoppingPhysics.hh>
#include <G4DecayPhysics.hh>
// particles

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
////////////////
#include "G4HadronElasticProcess.hh"//<----------------------------------------------
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4HadronFissionProcess.hh"//<-------------------- ????
//////
#include "G4LossTableManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonPhysicsList::NeutroncannonPhysicsList()
    :G4VModularPhysicsList()
{
    G4LossTableManager::Instance();
    defaultCutValue = 1.*mm;
    cutForGamma     = defaultCutValue;
    cutForElectron  = defaultCutValue;
    cutForPositron  = defaultCutValue;

        // EM physics
    emPhysicsList = new G4EmStandardPhysics_option3(1);
    //emPhysicsList = new G4EmLivermorePhysics(1);

    emName = G4String("G4EmLivermorePhysics");
    hadronPhys.push_back( new G4HadronElasticPhysics());
    hadronPhys.push_back( new G4DecayPhysics());
    hadronPhys.push_back( new G4RadioactiveDecayPhysics());
    hadronPhys.push_back( new G4IonBinaryCascadePhysics());
    hadronPhys.push_back( new G4EmExtraPhysics());
    hadronPhys.push_back( new G4HadronElasticPhysicsHP());
    hadronPhys.push_back( new G4StoppingPhysics());
    hadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_HP());
    hadronPhys.push_back( new G4NeutronTrackingCut());

    
    // Decay physics and all particles
    decPhysicsList = new G4DecayPhysics();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonPhysicsList::~NeutroncannonPhysicsList()
{
    delete emPhysicsList;
    delete decPhysicsList;
    
    for(size_t i=0; i<hadronPhys.size(); i++) 
        delete hadronPhys[i];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



void NeutroncannonPhysicsList::ConstructParticle()
{
    decPhysicsList->ConstructParticle();
    emPhysicsList->ConstructParticle();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonPhysicsList::ConstructProcess()
{
  // transportation
  AddTransportation();

  // electromagnetic physics list
  emPhysicsList->ConstructProcess();
  
  // decay physics list
  decPhysicsList->ConstructProcess();

  // hadronic physics lists
  for(size_t i=0; i<hadronPhys.size(); i++) {
    hadronPhys[i] -> ConstructProcess();
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// void NeutroncannonPhysicsList::SetCuts()
// {
    
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
