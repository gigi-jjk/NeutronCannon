

#include "NeutroncannonPrimaryGeneratorAction.hh"
//#include "NeutroncannonAnalysis.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "CLHEP/Random/RandBreitWigner.h"
#include "CLHEP/Random/RandPoissonQ.h"
// #include "TString.h"
// #include "TFile.h"
// #include "TTree.h"

#include "NeutroncannonDetectorConstruction.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonPrimaryGeneratorAction::NeutroncannonPrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),fParticleGun(0)
      
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NeutroncannonPrimaryGeneratorAction::~NeutroncannonPrimaryGeneratorAction()
{
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NeutroncannonPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   //debug   
  G4int particleyes = 1;//se generare o meno le particelle per screen
  G4int validationyes = 0;


  if    (particleyes == 1) {
      //leggi file csv
  G4String xstring = "";
  G4String ystring= "";
    
  G4double x=0;
  G4double y=0;
    
  std::vector<double> xcord;
  std::vector<double> ycord;
  G4int i=0;
  G4double yscore =0.0;
	G4double xscore =0.0;
	G4double ynumber =0.0;
	G4double xnumber =0.0;	



std::ifstream ip("gamma distribution dataset.csv");
G4String fileNamecsv = "gamma distribution dataset";
if(!ip.is_open()){
	std::cout << "ERROR File Open" << '\n';
}
while(ip.good()){
		
		getline(ip,xstring,';');	
		getline(ip,ystring,'\n');
		
		std::istringstream buffer(xstring);

		buffer >> x;
		xcord.push_back(x);
		
		std::istringstream buffer1(ystring);
		buffer1 >> y;
		ycord.push_back(y);
		
		i++;
	}   
ip.close();

    
   
///////////////neutroni    
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
    G4int n_particle = CLHEP::RandPoissonQ::shoot(3.76);

  
    //distribution of position
    G4double r = 0.5*cm;
    G4double px = 0*cm,py = 0*cm,pz = 0*cm;

    do 
    {
        px = (G4UniformRand()-0.5)*cm,
        py = (G4UniformRand()-0.5)*cm,
        pz = (G4UniformRand()-0.5)*cm;   
    } 
    while ((px*px)+(py*py) > (r*r));
        
    G4double pzoffset = -3.*cm;//center position of the source
        
    pz += pzoffset;

    
    G4ThreeVector position =  G4ThreeVector(px,py,pz);

  //distribution for neutron direction 
  for (G4int i = 0; i < n_particle; i++){

    
    fParticleGun  = new G4ParticleGun(1);
    fParticleGun->SetParticleDefinition(particle); 
  //distribution uniform in solid angle
    G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi),
             uy = sinTheta*std::sin(phi),
             uz = cosTheta;
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));

  //Watt energy distribution for neutron
    
    n = 0.8*G4UniformRand();
    //std::cout << n << std::endl;
    do
    {
      En = (10* G4UniformRand())*MeV;//from 0 to 10 Mev
      score = (std::exp(-0.88 * En))*(std::sinh(std::sqrt(2*En)));
      //std::cout << score  << std::endl;
      
    } while (score < n );
    


    

    fParticleGun->SetParticlePosition(position); 
    fParticleGun->SetParticleEnergy(En);
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  
  ///GAMMAS
  G4ParticleDefinition* gammaparticle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  g_particle = CLHEP::RandPoissonQ::shoot(8.1);
  //G4cout << " numb of gamma per event " <<  g_particle << G4endl;
  //distribution for gamma direction 
  for (G4int j = 0; j < g_particle; j++){

    
    fgParticleGun  = new G4ParticleGun(1);
    fgParticleGun->SetParticleDefinition(gammaparticle); 

  //distribution uniform in solid angle
    G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi),
             uy = sinTheta*std::sin(phi),
             uz = cosTheta;
    

//////////////////gamma energy distribution from file
  do{
			//generazione random energia
			xnumber =(6*G4UniformRand());
      //std::cout <<" en estratto " <<  xnumber << std::endl;
			//trova valore  prob corrispondente
			for (i=0; i<xcord.size() ;i++){
				if( xcord[i] >xnumber){
          //std::cout <<" en estratto " <<  xnumber <<" valore anticipato " << xcord[i-1] << std::endl;
					//xscore = xcord[i-1];
					yscore = ycord[i-1];//a gradino
          
					break;
				}
			}	
			ynumber = G4UniformRand();
			//std::cout << yscore << "  " << ynumber << std::endl;
		}	
		while(yscore < ynumber);

    




    En = xnumber *MeV;//<--------------------------------------


    
    fgParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
    fgParticleGun->SetParticlePosition(position); 
    fgParticleGun->SetParticleEnergy(En);
    fgParticleGun->GeneratePrimaryVertex(anEvent);
  }

  } 
  
  
 /////////////////////////////////
 //debug validation sphere

 if (validationyes == 1){
  G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("neutron");
  G4int n_particle = 1;

  G4double px = 0*cm;
  G4double py = 0*cm;
  G4double pz = 0*cm;
  G4ThreeVector position =  G4ThreeVector(px,py,pz);
  

    
  fParticleGun  = new G4ParticleGun(1);
  fParticleGun->SetParticleDefinition(particle); 
  //distribution uniform in solid angle
    G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
    G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
    G4double ux = sinTheta*std::cos(phi),
             uy = sinTheta*std::sin(phi),
             uz = cosTheta;
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));

  //Watt energy distribution for neutron
    
    n = 0.8*G4UniformRand();
    //std::cout << n << std::endl;
    do
    {
      En = (10* G4UniformRand())*MeV;//from 0 to 10 Mev
      score = (std::exp(-0.88 * En))*(std::sinh(std::sqrt(2*En)));
      //std::cout << score  << std::endl;
      
    } while (score < n );
    


    

    fParticleGun->SetParticlePosition(position); 
    fParticleGun->SetParticleEnergy(En);
    fParticleGun->GeneratePrimaryVertex(anEvent);
 }














    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

