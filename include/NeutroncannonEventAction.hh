
#ifndef NeutroncannonEventAction_h
#define NeutroncannonEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class NeutroncannonDetectorConstruction;

class NeutroncannonEventAction : public G4UserEventAction
{
  public:
    NeutroncannonEventAction();
   ~NeutroncannonEventAction();

  public:
    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void   EndOfEventAction(const G4Event* anEvent);
  
    //counting

  void addGenNeutrons(){fGenNeutrons+=1;}      
  void addGenGammas(){fGenGammas+=1;}        
  void addInGunNeutrons(){fInGunNeutrons+=1;}    
  void addInGunGammas(){fInGunGammas+=1;}      
  void addOutGunNeutrons(){fOutGunNeutrons+=1;}   
  void addOutGunGammas(){fOutGunGammas+=1;}      
  void addTPCNeutrons(){fTPCNeutrons+=1;}      
  void addTPCGammas(){fTPCGammas+=1;}          
  void addTPCNHits(){fTPCNHits+=1;}         
  void addTPCGHits(){fTPCGHits+=1;}         
  void addBaFEnergy(G4double Edep){fBaFEnergy+=Edep;}      


  G4int getGenNeutrons(){return fGenNeutrons;}      
  G4int getGenGammas(){return fGenGammas;}        
  G4int getInGunNeutrons(){return fInGunNeutrons;}    
  G4int getInGunGammas(){return fInGunGammas;}      
  G4int getOutGunNeutrons(){return fOutGunNeutrons;}   
  G4int getOutGunGammas(){return fOutGunGammas;}      
  G4int getTPCNeutrons(){return fTPCNeutrons;}      
  G4int getTPCGammas(){return fTPCGammas;}          
  G4int getTPCNHits(){return fTPCNHits;}         
  G4int getTPCGHits(){return fTPCGHits;}         
  G4double getBaFEnergy(){return fBaFEnergy;}      
    
  G4int i = 0;
  
  void clearEvent(){   
    fGenNeutrons = 0;     
    fGenGammas = 0;        
    fInGunNeutrons = 0;    
    fInGunGammas = 0;      
    fOutGunNeutrons = 0;   
    fOutGunGammas = 0;      
    fTPCNeutrons = 0;      
    fTPCGammas = 0;          
    fTPCNHits = 0;         
    fTPCGHits = 0;         
    fBaFEnergy = 0.;        
  }

  private:
  G4int fGenNeutrons;      
  G4int fGenGammas;        
  G4int fInGunNeutrons;    
  G4int fInGunGammas;      
  G4int fOutGunNeutrons;   
  G4int fOutGunGammas;      
  G4int fTPCNeutrons;      
  G4int fTPCGammas;          
  G4int fTPCNHits;         
  G4int fTPCGHits;         
  G4int fBaFEnergy;           

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
