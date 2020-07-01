

#ifndef NeutroncannonPrimaryGeneratorAction_h
#define NeutroncannonPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NeutroncannonPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    NeutroncannonPrimaryGeneratorAction();    
   ~NeutroncannonPrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    //G4int getNsegments() const {return nsegments;}

  private:
    G4ParticleGun*  fParticleGun;        //pointer a to G4 service class
    G4ParticleGun*  fgParticleGun;        
    G4int n_particle;
    G4int g_particle;
    G4double score;
    G4double En;
    G4double n;
   //G4int  nsegments;       //number of segments to divide the input file
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


