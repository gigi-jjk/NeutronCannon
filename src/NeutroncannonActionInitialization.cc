
//
// $Id: ActionInitialization.cc 76340 2013-11-08 15:21:09Z gcosmo $
//
/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "NeutroncannonActionInitialization.hh"
#include "NeutroncannonPrimaryGeneratorAction.hh"
#include "NeutroncannonRunAction.hh"
#include "NeutroncannonEventAction.hh"
#include "NeutroncannonSteppingAction.hh"
#include "NeutroncannonSteppingVerbose.hh"
#include "NeutroncannonTrackingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonActionInitialization::NeutroncannonActionInitialization()
 : G4VUserActionInitialization()
{


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonActionInitialization::~NeutroncannonActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonActionInitialization::BuildForMaster() const
{
  NeutroncannonRunAction* runAction = new NeutroncannonRunAction;
  SetUserAction(new NeutroncannonRunAction);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonActionInitialization::Build() const
{
  
  NeutroncannonPrimaryGeneratorAction *primGen = new NeutroncannonPrimaryGeneratorAction;
  SetUserAction(primGen);
  NeutroncannonRunAction* runAction = new NeutroncannonRunAction;
  SetUserAction(new NeutroncannonRunAction);
  NeutroncannonEventAction* eventAction = new NeutroncannonEventAction();
  SetUserAction(eventAction);
  SetUserAction(new NeutroncannonSteppingAction(eventAction,primGen));
  SetUserAction( new NeutroncannonTrackingAction );//<---------------------------
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose* NeutroncannonActionInitialization::InitializeSteppingVerbose() const
{
   return new NeutroncannonSteppingVerbose();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
