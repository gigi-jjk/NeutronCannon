
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
  
    //Funzioni utili e variabili utili
    void addDetectorEdepL1( G4double Edep)     {fDetectorEnergyDepL1 += Edep;}
    void addDetectorEdepL2( G4double Edep)     {fDetectorEnergyDepL2 += Edep;}
    void addDetectorEdepL3( G4double Edep)     {fDetectorEnergyDepL3 += Edep;}
    void addDetectorEdepL4( G4double Edep)     {fDetectorEnergyDepL4 += Edep;}
    void addDetectorEdeptot( G4double Edep)     {fDetectorEnergyDep += Edep;}
    //void addChcount(int nDetector, G4int fCerenkovCounterL)     {fChcount[nDetector] += fCerenkovCounterL;}
    //void addDetectorNh(int nDetector, G4int fNhcount) {fNh[nDetector] += fNhcount;}
    G4double GetDetectorEnergyDepositL1()  const   {return fDetectorEnergyDepL1;}
    G4double GetDetectorEnergyDepositL2()  const   {return fDetectorEnergyDepL2;}
    G4double GetDetectorEnergyDepositL3()  const   {return fDetectorEnergyDepL3;}
    G4double GetDetectorEnergyDepositL4()  const   {return fDetectorEnergyDepL4;}
    G4double GetDetectorEnergyDeposittot()  const   {return fDetectorEnergyDep;}
    //G4int GetDetectorChcount(int nDetector)  const   {return fChcount[nDetector];}
    //G4int GetDetectorNh(int nDetector)  const   {return fNh[nDetector];}
   // void clearDetectorEdep(int nDetector) {fDetectorEnergyDep[nDetector] = 0.;}
    //void clearChcount(int nDetector) {fChcount[nDetector] = 0;}
    //void clearNh(int nDetector) {fNh[nDetector] = 0;}

    G4int i = 0;
    

  
  void clearDetectorEdepL1() {fDetectorEnergyDepL1 = 0.;}
  void clearDetectorEdepL2() {fDetectorEnergyDepL2 = 0.;}
  void clearDetectorEdepL3() {fDetectorEnergyDepL3 = 0.;}
  void clearDetectorEdepL4() {fDetectorEnergyDepL4 = 0.;}
  void clearDetectorEdeptot() {fDetectorEnergyDep = 0.;}
  private:
    //std::vector<G4double> fDetectorEnergyDep;   // Energy deposited in the detector
    G4double fDetectorEnergyDep;
    G4double fDetectorEnergyDepL1;
    G4double fDetectorEnergyDepL2;
    G4double fDetectorEnergyDepL3;
    G4double fDetectorEnergyDepL4;
    
    //std::vector<G4int> fChcount;   // Energy deposited in the detector
    //std::vector<G4int> fNh;   // Energy deposited in the detector
    


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
