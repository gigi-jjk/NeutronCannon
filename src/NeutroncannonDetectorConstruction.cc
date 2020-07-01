
#include "NeutroncannonDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4NistMessenger.hh"
#include "G4NistElementBuilder.hh"
#include "G4NistMaterialBuilder.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
# include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Polyhedra.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"

//#include "HadCaloSensitiveDetector.hh"

//constructor
NeutroncannonDetectorConstruction::NeutroncannonDetectorConstruction()
    : physicalRoom(0)
{
}

NeutroncannonDetectorConstruction::~NeutroncannonDetectorConstruction()
{ }

G4VPhysicalVolume* NeutroncannonDetectorConstruction::Construct()
{
    //debug
   G4int geometryyes = 1 ;
   G4int validationyes = 0 ;
    
    
    
    
    
    
    
    
    
    
    
    	// NIST Materials
   G4Material* air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
   G4Material* californium = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cf");
   G4Material* Pb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
   G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
   G4Material* Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    //------------------------------------------//
    //5% boron loaded HDPE   (c2h4)     polietilene ad alta densità 940 kg/m3     <-----------------------------

    G4Element* elH = G4NistManager::Instance()->FindOrBuildElement("H");
    G4Element* elC = G4NistManager::Instance()->FindOrBuildElement("C");
    G4Element* elB = G4NistManager::Instance()->FindOrBuildElement("B");

    G4Material* hdpe = new G4Material("hdpe", 1.04 * g/cm3, 3 /* components */);
    hdpe -> AddElement(elH, 13.5 * perCent);
    hdpe -> AddElement(elC, 81.5 * perCent);
    hdpe -> AddElement(elB, 5 * perCent);
   //------------------------------------------//
   //BaF2//    <-----------------------------
   
   G4Material* BaF2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_BARIUM_FLUORIDE");     
   /* 
   //-------------------------------sorgente californio 252
   G4Isotope * Cf_252 = new G4Isotope("Cf-252", 98, 252., 251*g/mole);
   G4Element* Cf252 = new G4Element("californio","cf",1);
   Cf252 -> AddIsotope( Cf_252,100);
   G4Material* californium252 = new G4Material("Cf-252", 15.12 * g/cm3, 1);
   californium252 -> AddElement(Cf252,100*perCent);*/




  // -----------------------------
  // room - World volume
  // -----------------------------

  // room sizes
  const G4double worldX = 400.0 *cm;
  const G4double worldY = 400.0 *cm;
  const G4double worldZ = 400.0 *cm;

  G4Box* Room = new G4Box("Room",worldX,worldY,worldZ);

  G4LogicalVolume* logicRoom = new G4LogicalVolume(Room, air,"logicRoom", 0,0,0);

  physicalRoom = new G4PVPlacement(0,G4ThreeVector(),"physicalRoom", logicRoom,0,false,0);


  // The room is invisible in the Visualisation
  logicRoom -> SetVisAttributes (G4VisAttributes::GetInvisible());


  // Visualisation attributes of all elements colours 
  G4VisAttributes * grayFe = new G4VisAttributes(G4Colour(0.5 ,0.5 ,0.5));
  grayFe -> SetVisibility(true);
  grayFe -> SetForceSolid(true);

  G4VisAttributes * blueCobalt = new G4VisAttributes(G4Colour(0. ,0. ,0.7));
  blueCobalt -> SetVisibility(true);
  blueCobalt -> SetForceSolid(true);

  G4VisAttributes * bluewire = new G4VisAttributes(G4Colour(0. ,0. ,0.7));
  bluewire -> SetVisibility(true);
  //blueCobalt -> SetForceSolid(true);


  G4VisAttributes * graySS = new G4VisAttributes(G4Colour(0.9 ,0.9 ,0.9));
  graySS -> SetVisibility(true);
  //graySS -> SetForceSolid(true);

  G4VisAttributes * grayAl = new G4VisAttributes(G4Colour(0.7 ,0.7 ,0.7));
  grayAl -> SetVisibility(true);
  grayAl -> SetForceSolid(true);

  G4VisAttributes * blackLead = new G4VisAttributes(G4Colour(0.2 ,0.2 ,0.2));
  blackLead -> SetVisibility(true);
  blackLead -> SetForceSolid(true);
 

  G4VisAttributes * colorTungsten = new G4VisAttributes(G4Colour(0.3 ,0.3 ,0.3));
  colorTungsten -> SetVisibility(true);
  colorTungsten -> SetForceSolid(true);
 
  G4VisAttributes * redWire = new G4VisAttributes(G4Colour(0.8 ,0. ,0.));
  redWire -> SetVisibility(true);
  redWire -> SetForceSolid(true);

  G4VisAttributes * redtrans = new G4VisAttributes(G4Colour(0.8 ,0. ,0.));
  redtrans -> SetVisibility(true);
  //redWire -> SetForceSolid(true);



   G4VisAttributes * yellow = new G4VisAttributes(G4Colour(0.9 ,0.9 ,0.));
  yellow -> SetVisibility(true);
  //yellow -> SetForceSolid(true);

   G4VisAttributes * azzurro = new G4VisAttributes(G4Colour(0.0 ,0.7 ,1.));
   azzurro -> SetVisibility(true);
   azzurro -> SetForceSolid(true);

   G4VisAttributes * graytrans = new G4VisAttributes(G4Colour(0.5 ,0.5 ,0.5));
  graytrans -> SetVisibility(true);
  //grayFe -> SetForceSolid(true);








if (geometryyes ==1){
  //--------------------------------------------
  // Sorgente cilindrica Californio
  //--------------------------------------------
  G4double innerRadiusOfTheTube_source = 0.;
  G4double outerRadiusOfTheTube_source = 0.5*cm;
  G4double hightOfTheTube_source = 0.5*cm;
  G4double startAngleOfTheTube = 0.*deg;
  G4double spanningAngleOfTheTube = 360.*deg;

  //G4ThreeVector positionTube_source = G4ThreeVector(0,0,-40.1*cm);
  G4ThreeVector positionTube_source = G4ThreeVector(0,0,-3*cm);

  solidTube_source = new G4Tubs("solidTube_source",innerRadiusOfTheTube_source,outerRadiusOfTheTube_source,hightOfTheTube_source,startAngleOfTheTube,spanningAngleOfTheTube);          
  logicTube_source = new G4LogicalVolume(solidTube_source,vacuum,"logicTube_source",0,0,0);//californium< ---------------------------------------------
  physiTube_source = new G4PVPlacement(0,positionTube_source,logicTube_source,"Tube_source",logicRoom,false,0);

  logicTube_source -> SetVisAttributes(blueCobalt);

  //----------------------------------------------
  // collimatore di piombo forato
  //----------------------------------------------


  //G4ThreeVector positionColl_Pb = G4ThreeVector(0,0,-39.1*cm);
  G4ThreeVector positionColl_Pb = G4ThreeVector(0,0,-4.*cm);
  
  collimator_Pb = new G4Box("collimator_Pb",20/2.*cm, 20/2.*cm, 8/2.*cm);
    
  //hole_air = new G4Tubs("buco",0.*cm, 0.55*cm, 62.1*cm,startAngleOfTheTube,spanningAngleOfTheTube);
  hole_square_air = new G4Box("foro quadrato",9.5/2*cm, 9.5/2*cm, 10/2*cm);

  G4VSolid*collimator= new G4SubtractionSolid("piombo-buco", collimator_Pb, hole_square_air,0, G4ThreeVector(0.,0.,0.*cm));
  
  logiccollimator = new G4LogicalVolume(collimator,Pb,"collimator",0,0,0);
  physicollimator = new G4PVPlacement(0,positionColl_Pb,logiccollimator,"collimator",logicRoom,false,0);

  logiccollimator -> SetVisAttributes(blackLead);
 

  ///////////////////////buco conico
  G4double Rmin1Coll_fixed = 0*mm;
  G4double Rmax1Coll_fixed = 5.*mm;
  G4double Rmin2Coll_fixed = 0*mm;
  G4double Rmax2Coll_fixed = 5.*cm;
  G4double hightColl_fixed = 32.5*cm;//66*cm
 

  G4ThreeVector hole_position = G4ThreeVector(0,0,30*cm);//30.6

  G4Cons* cone_hole = new G4Cons("buco conico",Rmin1Coll_fixed,Rmax1Coll_fixed,Rmin2Coll_fixed,Rmax2Coll_fixed,hightColl_fixed,startAngleOfTheTube,spanningAngleOfTheTube);
   //------------------------------------------------
   // rivelatore                     
   //------------------------------------------------

    G4Box * rivelatore = new G4Box("rivelatore",1.5*cm,1.5*cm,6*cm);
   //debug
   hole_square_air = new G4Box("foro quadrato",4.75*cm, 4.75*cm, 3*cm);
   G4Box * cavity = new G4Box("cavity",1.1*cm,1.1*cm,15/2*cm);
   
   //  cavityLogic = new G4LogicalVolume(cavity,vacuum,"cavityDetector",0,0,0);
   //  cavityPhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0.*cm, 0.*cm, -3*cm),"L4Detector ",cavityLogic,physicalRoom,false,0);
   //  cavityLogic -> SetVisAttributes(redtrans);

   ///alluminium cover
   G4VSolid * coverAl= new G4SubtractionSolid("coverAl", hole_square_air, cavity,0, G4ThreeVector(0,0,-3.*cm));
   coverAl= new G4SubtractionSolid("coverAl", coverAl, rivelatore,0, G4ThreeVector(-0.5*cm, -2.5*cm, 0.*cm));
   coverAl= new G4SubtractionSolid("coverAl", coverAl, rivelatore,0, G4ThreeVector(0.5*cm, 2.5*cm, 0.*cm));
   coverAl= new G4SubtractionSolid("coverAl", coverAl, rivelatore,0, G4ThreeVector(-2.5*cm, 0.5*cm, 0.*cm));
   coverAl= new G4SubtractionSolid("coverAl", coverAl, rivelatore,0, G4ThreeVector(2.5*cm, -0.5*cm, 0.*cm));
   G4LogicalVolume * coverAlLogic = new G4LogicalVolume(coverAl,Al,"ceverAllogic",0,0,0);
   G4VPhysicalVolume* coverAlPhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0,0,-3.* cm),"coverAl ",coverAlLogic,physicalRoom,false,0);
   coverAlLogic -> SetVisAttributes(grayAl);

   
   rivelatore = new G4Box("rivelatore",1.5*cm,1.5*cm,3*cm);
   L1Logic = new G4LogicalVolume(rivelatore,BaF2,"L1Detector",0,0,0);
   L2Logic = new G4LogicalVolume(rivelatore, BaF2, "L2Detector",0,0,0);
   L3Logic = new G4LogicalVolume(rivelatore, BaF2, "L3Detector",0,0,0);
   L4Logic = new G4LogicalVolume(rivelatore, BaF2, "L4Detector",0,0,0);

   L1PhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(-0.5*cm, -2.5*cm, -3*cm),"L1Detector",L1Logic,physicalRoom,false,0);
   L2PhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0.5*cm, 2.5*cm, -3*cm),"L2Detector",L2Logic,physicalRoom,false,0);
   L3PhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(-2.5*cm, 0.5*cm, -3*cm),"L3Detector",L3Logic,physicalRoom,false,0);
   L4PhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(2.5*cm, -0.5*cm, -3*cm),"L4Detector",L4Logic,physicalRoom,false,0);
   
   ///sensitive detector
   // G4MultiFunctionalDetector* myScorer = new G4MultiFunctionalDetector("myCellScorer");
   // G4SDManager::GetSDMpointer()->AddNewDetector(myScorer);
   // L1Logic->SetSensitiveDetector(myScorer);
   // G4VPrimitiveSensitivity* totalEdep = new G4PSEnergyDepsit("TotalEdep");
   // myScorer->Register(totalEdep); 




   L1Logic -> SetVisAttributes(azzurro);
   L2Logic -> SetVisAttributes(azzurro);
   L3Logic -> SetVisAttributes(azzurro);
   L4Logic -> SetVisAttributes(azzurro);
   

  
   //------------------------------------------------
   // copertura d1                      
   //------------------------------------------------

      G4Box* d = new G4Box("d1",25./2*cm, 25./2*cm, 50./2*mm);
      G4VSolid * d1= new G4SubtractionSolid("d1", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -15*cm));

      d1LogicalVolume = new G4LogicalVolume(d1,hdpe,"d1 logical", 0, 0, 0);
      d1PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 17.5*cm),"d1 ",d1LogicalVolume,physicalRoom,false,0);//-0.6
    
      d1LogicalVolume -> SetVisAttributes(yellow); 
   //------------------------------------------------
   // copertura d2                      
   //------------------------------------------------

      G4VSolid * d2= new G4SubtractionSolid("d2", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -20*cm));

      d2LogicalVolume = new G4LogicalVolume(d2,hdpe,"d2 logical", 0, 0, 0);
      d2PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 22.5*cm),"d2 ",d2LogicalVolume,physicalRoom,false,0);
    
      d2LogicalVolume -> SetVisAttributes(yellow);


   //------------------------------------------------
   // copertura d3                      
   //------------------------------------------------
      G4VSolid * d3= new G4SubtractionSolid("d3", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -25*cm));

      d3LogicalVolume = new G4LogicalVolume(d3,hdpe,"d3 logical", 0, 0, 0);
      d3PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 27.5*cm),"d3 ",d3LogicalVolume,physicalRoom,false,0);
    
      d3LogicalVolume -> SetVisAttributes(yellow);
   //------------------------------------------------
   // copertura d4                      
   //------------------------------------------------
      G4VSolid * d4= new G4SubtractionSolid("d4", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -30*cm));

      d4LogicalVolume = new G4LogicalVolume(d4,hdpe,"d4 logical", 0, 0, 0);
      d4PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 32.5*cm),"d4 ",d4LogicalVolume,physicalRoom,false,0);
    
      d4LogicalVolume -> SetVisAttributes(yellow);
   //------------------------------------------------
   // copertura d5                      
   //------------------------------------------------
      G4VSolid * d5= new G4SubtractionSolid("d5", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -35*cm));

      d5LogicalVolume = new G4LogicalVolume(d5,hdpe,"d5 logical", 0, 0, 0);
      d5PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 37.5*cm),"d5 ",d5LogicalVolume,physicalRoom,false,0);
    
      d5LogicalVolume -> SetVisAttributes(yellow);
   //------------------------------------------------
   // copertura d6                      
   //------------------------------------------------
      G4VSolid * d6= new G4SubtractionSolid("d6", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -40*cm));

      d6LogicalVolume = new G4LogicalVolume(d6,hdpe,"d6 logical", 0, 0, 0);
      d6PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 42.5*cm),"d6 ",d6LogicalVolume,physicalRoom,false,0);
    
      d6LogicalVolume -> SetVisAttributes(yellow);
   //------------------------------------------------
   // copertura d7                      
   //------------------------------------------------
      G4VSolid * d7= new G4SubtractionSolid("d7", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -45*cm));

      d7LogicalVolume = new G4LogicalVolume(d7,hdpe,"d7 logical", 0, 0, 0);
      d7PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 47.5*cm),"d7 ",d7LogicalVolume,physicalRoom,false,0);
    
      d7LogicalVolume -> SetVisAttributes(yellow);
   //------------------------------------------------
   // copertura d8                      
   //------------------------------------------------
      G4VSolid * d8= new G4SubtractionSolid("d8", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -50*cm));

      d8LogicalVolume = new G4LogicalVolume(d8,hdpe,"d8 logical", 0, 0, 0);
      d8PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 52.5*cm),"d8 ",d8LogicalVolume,physicalRoom,false,0);
    
      d8LogicalVolume -> SetVisAttributes(yellow);

   //------------------------------------------------
   // copertura d9                      
   //------------------------------------------------
      G4VSolid * d9= new G4SubtractionSolid("d9", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -55*cm));

      d9LogicalVolume = new G4LogicalVolume(d9,hdpe,"d9 logical", 0, 0, 0);
      d9PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 57.5*cm),"d9 ",d9LogicalVolume,physicalRoom,false,0);
    
      d9LogicalVolume -> SetVisAttributes(yellow);
    
   //------------------------------------------------
   // copertura d10                      
   //------------------------------------------------
      G4VSolid * d10= new G4SubtractionSolid("d10", d, cone_hole,0, hole_position + G4ThreeVector(0., 0.,-60*cm));

      d10LogicalVolume = new G4LogicalVolume(d10,hdpe,"d10 logical", 0, 0, 0);
      d10PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, 62.5*cm),"d10 ",d10LogicalVolume,physicalRoom,false,0);
    
      d10LogicalVolume -> SetVisAttributes(yellow);

   //------------------------------------------------
    // copertura posteriore c1                      
    //------------------------------------------------
     G4Box* c1 = new G4Box("c1",35./2*cm, 35./2*cm, 50./2*mm);

     c1LogicalVolume = new G4LogicalVolume(c1,hdpe,"c1 back", 0, 0, 0);
     c1PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., -32.5*cm),"c1 back",c1LogicalVolume,physicalRoom,false,0);//-100.6*cm

     G4VSolid*c1_hole= new G4SubtractionSolid("c1 Front", c1, cone_hole,0, hole_position );

      c1_holeLogicalVolume = new G4LogicalVolume(c1_hole,hdpe,"c1 front", 0, 0, 0);
      c1_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., 2.5*cm),"c1 front",c1_holeLogicalVolume,physicalRoom,false,0);//-30.6*cm
  
    c1LogicalVolume -> SetVisAttributes(redtrans); 
      c1_holeLogicalVolume -> SetVisAttributes(redtrans);
    
    //------------------------------------------------
    // copertura posteriore c2                      
    //------------------------------------------------
     G4Box* c2 = new G4Box("c2",45./2*cm, 45./2*cm, 50./2*mm);

     c2LogicalVolume = new G4LogicalVolume(c2,hdpe,"c2 back", 0, 0, 0);
     c2PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., -37.5*cm),"c2 back",c2LogicalVolume,physicalRoom,false,0);//-101.0*cm

     G4VSolid*c2_hole= new G4SubtractionSolid("c2 Front", c2, cone_hole,0, hole_position +G4ThreeVector(0., 0., -5*cm) );

      c2_holeLogicalVolume = new G4LogicalVolume(c2_hole,hdpe,"c2 front", 0, 0, 0);
      c2_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., 7.5*cm),"c2 front",c2_holeLogicalVolume,physicalRoom,false,0);//-20.6*cm
  
      c2LogicalVolume -> SetVisAttributes(bluewire); 
      c2_holeLogicalVolume -> SetVisAttributes(bluewire);

//      //------------------------------------------------
//    // copertura posteriore/anteriore c3                      
//    //------------------------------------------------
     G4Box* c3 = new G4Box("c3",55./2*cm, 55./2*cm, 50./2*mm);

     c3LogicalVolume = new G4LogicalVolume(c3,hdpe,"c3 back", 0, 0, 0);
     c3PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., -42.5*cm),"c3 back",c3LogicalVolume,physicalRoom,false,0);//-101.0*cm

     G4VSolid*c3_hole= new G4SubtractionSolid("c3 Front", c3, cone_hole,0, hole_position + G4ThreeVector(0., 0., -10*cm));

      c3_holeLogicalVolume = new G4LogicalVolume(c3_hole,hdpe,"c3 front", 0, 0, 0);
      c3_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., 12.5*cm),"c3 front",c3_holeLogicalVolume,physicalRoom,false,0);//-30.6*cm
  
     c3LogicalVolume -> SetVisAttributes(redtrans); 
     c3_holeLogicalVolume -> SetVisAttributes(redtrans);

//  //------------------------------------------------
//  // copertura posteriore/anteriore con foro conico c4                      
//  //------------------------------------------------
     G4Box* c4 = new G4Box("c4",55.8/2*cm, 55.8/2*cm, 4./2*mm);/////10.*mm

     c4LogicalVolume = new G4LogicalVolume(c4,Pb,"c4back", 0, 0, 0);
     c4PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., -45.2*cm),"c4back",c4LogicalVolume,physicalRoom,false,0);//-101.0*cm

     //G4VSolid * c4_hole = new G4SubtractionSolid("c4Front", c4, cone_hole,0, hole_position + G4ThreeVector(0., 0., -24*cm));//buco conico
     G4VSolid * c4_hole = new G4SubtractionSolid("c4 Front", c4, d,0,G4ThreeVector(0,0,0));//buco quadrato

     c4_holeLogicalVolume = new G4LogicalVolume(c4_hole,Pb,"c4front", 0, 0, 0);
     c4_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., 15.2*cm),"c4front",c4_holeLogicalVolume,physicalRoom,false,0);//-30.6*cm
  
   c4LogicalVolume -> SetVisAttributes(graytrans); 
   c4_holeLogicalVolume -> SetVisAttributes(grayFe);

 
    


    

  //------------------------------------------------
 // copertura a1                      
 //------------------------------------------------

    G4Box* a1 = new G4Box("a1",25./2*cm, 30./2*cm, 50./2*mm);

    G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
    rotationMatrix->rotateY(90.*deg);
    rotationMatrix->rotateZ(90.*deg);

    a1LogicalVolume = new G4LogicalVolume(a1,hdpe,"a1 logical", 0, 0, 0);
   a1LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(15.*cm, 0.*cm, -15*cm),"a1 left",a1LogicalVolume,physicalRoom,false,0);//30.*cm, 0.*cm, -65.5*cm
   a1RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-15.*cm, 0.*cm, -15*cm),"a1 right",a1LogicalVolume,physicalRoom,false,0);
    
    a1LogicalVolume -> SetVisAttributes(redtrans); 
    //------------------------------------------------
 // copertura b1                      
 //------------------------------------------------

    G4Box* b1 = new G4Box("b1",17.5*cm, 15*cm, 25*mm);

    G4RotationMatrix* rotationMatrix2 = new G4RotationMatrix();
    rotationMatrix2->rotateX(90.*deg);
    //rotationMatrix2->rotateZ(90.*deg);

   b1LogicalVolume = new G4LogicalVolume(b1,hdpe,"b1 logical", 0, 0, 0);
   b1bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -15.*cm, -15*cm),"b1 bottom",b1LogicalVolume,physicalRoom,false,0);
   b1upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 15.*cm, -15*cm),"b1 up",b1LogicalVolume,physicalRoom,false,0);
    
   b1LogicalVolume -> SetVisAttributes(blueCobalt); 
    //------------------------------------------------
 // copertura a2                      
 //------------------------------------------------

    G4Box* a2 = new G4Box("a2",35./2*cm, 40./2*cm, 50./2*mm);

   a2LogicalVolume = new G4LogicalVolume(a2,hdpe,"a2 logical", 0, 0, 0);
   a2LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(20*cm, 0.*cm, -15*cm),"a2 left",a2LogicalVolume,physicalRoom,false,0);
   a2RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-20*cm, 0.*cm, -15*cm),"a2 right",a2LogicalVolume,physicalRoom,false,0);
    
    a2LogicalVolume -> SetVisAttributes(bluewire); 
    //------------------------------------------------
 // copertura b2                      
 //------------------------------------------------

    G4Box* b2 = new G4Box("b2",45./2*cm, 40./2*cm, 50./2*mm);

    b2LogicalVolume = new G4LogicalVolume(b2,hdpe,"b2 logical", 0, 0, 0);
   b2bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -20*cm, -15*cm),"b2 bottom",b2LogicalVolume,physicalRoom,false,0);
   b2upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 20*cm, -15*cm),"b2 up",b2LogicalVolume,physicalRoom,false,0);
    
     b2LogicalVolume -> SetVisAttributes(redWire); 
 //------------------------------------------------
 // copertura a3                      
 //------------------------------------------------

    G4Box* a3 = new G4Box("a3",45./2*cm, 50./2*cm, 50./2*mm);

   a3LogicalVolume = new G4LogicalVolume(a3,hdpe,"a3 logical", 0, 0, 0);
   a3LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(25*cm, 0.*cm, -15*cm),"a3 left",a3LogicalVolume,physicalRoom,false,0);
   a3RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-25*cm, 0.*cm, -15*cm),"a3 right",a3LogicalVolume,physicalRoom,false,0);
    
   a3LogicalVolume -> SetVisAttributes(redtrans); 
  //------------------------------------------------
 // copertura b3                      
 //------------------------------------------------

    G4Box* b3 = new G4Box("b3",55./2*cm, 50./2*cm, 50./2*mm);

    b3LogicalVolume = new G4LogicalVolume(b3,hdpe,"b3 logical", 0, 0, 0);
   b3bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -25*cm, -15*cm),"b3 bottom",b3LogicalVolume,physicalRoom,false,0);
   b3upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 25*cm, -15*cm),"b3 up",b3LogicalVolume,physicalRoom,false,0);
    
   b3LogicalVolume -> SetVisAttributes(blueCobalt); 
  //------------------------------------------------
  // copertura a4  laterale in Pb                  
  //------------------------------------------------
    G4Box* a4 = new G4Box("a4",55./2*cm, 60./2*cm, 4./2*mm);

    a4LogicalVolume = new G4LogicalVolume(a4,Pb,"a4logical", 0, 0, 0);
     a4LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(27.7*cm, 0.*cm, -15*cm),"a4left",a4LogicalVolume,physicalRoom,false,0);
     a4RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-27.7*cm, 0.*cm, -15*cm),"a4right",a4LogicalVolume,physicalRoom,false,0);
    
    a4LogicalVolume -> SetVisAttributes(graytrans); 
 //------------------------------------------------
 // copertura b4     in Pb                 
 //------------------------------------------------

    G4Box* b4 = new G4Box("b4",55.8/2*cm, 60./2*cm, 4./2*mm);

    b4LogicalVolume = new G4LogicalVolume(b4,Pb,"b4logical", 0, 0, 0);
   b4bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -27.7*cm, -15*cm),"b4bottom",b4LogicalVolume,physicalRoom,false,0);
   b4upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 27.7*cm, -15*cm),"b4up",b4LogicalVolume,physicalRoom,false,0);
    
   b4LogicalVolume -> SetVisAttributes(grayFe); 

//------------------------------------------------
 // copertura e1     in Pb   per naso              
 //------------------------------------------------
G4Box* e1 = new G4Box("e1",12.5*cm, 24.8*cm, 2*mm);
G4Box* f1 = new G4Box("f1",12.5*cm, 24.8*cm, 2*mm);

e1LogicalVolume = new G4LogicalVolume(e1,Pb,"e1logical", 0, 0, 0);
e1DownPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -12.7*cm, 40.2*cm),"e1Down",e1LogicalVolume,physicalRoom,false,0);
e1UpPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 12.7*cm, 40.2*cm),"e1Up",e1LogicalVolume,physicalRoom,false,0);

f1LogicalVolume = new G4LogicalVolume(f1,Pb,"f1logical", 0, 0, 0);
f1LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(12.7*cm, 0*cm, 40.2*cm),"f1Left",f1LogicalVolume,physicalRoom,false,0);
f1RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-12.7*cm, 0*cm, 40.2*cm),"f1Right",f1LogicalVolume,physicalRoom,false,0);
    
e1LogicalVolume -> SetVisAttributes(grayFe);
f1LogicalVolume -> SetVisAttributes(graytrans);
//------------------------------------------------
 // copertura frontale     in Pb   per naso              
 //------------------------------------------------
G4Box* cover = new G4Box("nosecover",25.8/2*cm, 25.8/2*cm, 4/2*mm);
hole_air = new G4Tubs("buco",0.*cm, 5*cm, 3/2*cm,startAngleOfTheTube,spanningAngleOfTheTube);

G4VSolid*nosecover= new G4SubtractionSolid("tappo-buco", cover, hole_air,0, G4ThreeVector(0.,0.,0.));

nosecoverLogicalVolume = new G4LogicalVolume(nosecover,Pb,"nosecover", 0, 0, 0);
nosecoverPhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0.*cm, 0*cm, 65.3*cm),"nosecover",nosecoverLogicalVolume,physicalRoom,false,0);

nosecoverLogicalVolume -> SetVisAttributes(grayFe);






///////////////////////////////////////////
   //Detector Box
///////////////////////////////////////////

   G4Box* detectorUD = new G4Box("detectorUD",27.9*cm, 30.5*cm, 0.5*mm);
   //detectorUDLogicalVolume = new G4LogicalVolume(detectorUD,vacuum,"detectorUD logical", 0, 0, 0);

   // detectorUpPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, +57.1*cm, -65.5*cm),"detectorUp",detectorUDLogicalVolume,physicalRoom,false,0);
   // detectorDownPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -57.1*cm, -65.5*cm),"detectorDown",detectorUDLogicalVolume,physicalRoom,false,0);
    
   //detectorUDLogicalVolume -> SetVisAttributes(yellow);

   


   G4Box* detectorLR = new G4Box("detectorLR",28*cm, 30.5*cm, 0.5*mm);
   //detectorLRLogicalVolume = new G4LogicalVolume(detectorLR,vacuum,"detectorLR logical", 0, 0, 0);

   // detectorLeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(57.1*cm, 0.*cm, -65.5*cm),"detectorLeft",detectorLRLogicalVolume,physicalRoom,false,0);
   // detectorRightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-57.1*cm, 0.*cm, -65.5*cm),"detectorRight",detectorLRLogicalVolume,physicalRoom,false,0);
    
   //detectorLRLogicalVolume -> SetVisAttributes(yellow);

   G4Box* detectorFB = new G4Box("detectorFB",28*cm, 28*cm,  0.5*mm);
   //detectorFBLogicalVolume = new G4LogicalVolume(detectorFB,vacuum,"detectorFB logical", 0, 0, 0);

   // detectorFrontPhysicalVolume = new G4PVPlacement(0,G4ThreeVector(0., 0., -3.5*cm),"detectorFront",detectorFBLogicalVolume,physicalRoom,false,0);
   // detectorBackPhysicalVolume = new G4PVPlacement(0,G4ThreeVector(0., 0., -126.7*cm),"detectorBack",detectorFBLogicalVolume,physicalRoom,false,0);
    
   //detectorFBLogicalVolume -> SetVisAttributes(yellow);
   d = new G4Box("d",25.8/2*cm, 25.8/2*cm, 50./2*mm);
   G4VSolid*detectorfronthole= new G4SubtractionSolid("tappo-buco", detectorFB, d,0, G4ThreeVector(0.,0.,0.));
  
   e1 = new G4Box("e1",13*cm, 50./2*cm, 1./2*mm);
   f1 = new G4Box("f1",13*cm, 49.8/2*cm, 1./2*mm);
   cover = new G4Box("nosecover",13.*cm, 10.5*cm, 0.5*mm);
   //nosecover= new G4SubtractionSolid("tappo-buco", cover, hole_air,0, G4ThreeVector(0.,0.,0.));


   G4VSolid*detector= new G4UnionSolid("detector", detectorFB, detectorLR,rotationMatrix, G4ThreeVector(-28*cm,0.*cm,30.4*cm));
   detector= new G4UnionSolid("detector", detector, detectorLR,rotationMatrix, G4ThreeVector(28.05*cm,0.*cm,30.4*cm));
   detector= new G4UnionSolid("detector", detector, detectorUD,rotationMatrix2, G4ThreeVector(0*cm,-28.1*cm,30.4*cm));
   detector= new G4UnionSolid("detector", detector, detectorUD,rotationMatrix2, G4ThreeVector(0*cm,28*cm,30.4*cm));
   detector= new G4UnionSolid("detector", detector, detectorfronthole,0, G4ThreeVector(0*cm,0.*cm,61*cm));
   detector= new G4UnionSolid("detector", detector, e1,rotationMatrix2, G4ThreeVector(0.*cm, 13*cm, 86*cm));
   detector= new G4UnionSolid("detector", detector, e1,rotationMatrix2, G4ThreeVector(0.*cm, -13*cm, 86*cm));
   detector= new G4UnionSolid("detector", detector, f1,rotationMatrix, G4ThreeVector(13*cm, 0.*cm, 86*cm));
   detector= new G4UnionSolid("detector", detector, f1,rotationMatrix, G4ThreeVector(-13.*cm, 0.*cm, 86*cm));
   detector= new G4UnionSolid("detector", detector, nosecover,0, G4ThreeVector(0*cm, 0.*cm, 111.2*cm));

   detectorLogicalVolume = new G4LogicalVolume(detector,vacuum,"detectorlogical", 0, 0, 0);
      

   detectorPhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0.*cm, 0*cm, -45.5*cm),"detector",detectorLogicalVolume,physicalRoom,false,0);
   detectorLogicalVolume -> SetVisAttributes (G4VisAttributes::GetInvisible());
//// detector disco bersaglio
   hole_air = new G4Tubs("detectordisc",0.*cm, 5*cm, 0.5*mm,startAngleOfTheTube,spanningAngleOfTheTube);

   
   detectordiscLogicalVolume = new G4LogicalVolume(hole_air,vacuum,"detectordisc", 0, 0, 0);

   detectordiscPhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0.*cm, 0*cm, 65.7*cm),"detectordisc",detectordiscLogicalVolume,physicalRoom,false,0);
   //detectordiscLogicalVolume -> SetVisAttributes(redWire);
   detectordiscLogicalVolume -> SetVisAttributes (G4VisAttributes::GetInvisible());
////////////////////////////////////////////////
}


/*
if (validationyes ==1){
////////////////////////////////////////////////
//DEBUG SPHERE

G4Sphere* sfera = new G4Sphere("sfera",0.1*cm, 15.1*cm,0. *deg, 360. *deg,0. *deg, 180. *deg);

G4LogicalVolume* sferLogicalVolume = new G4LogicalVolume(sfera,hdpe,"sfera", 0, 0, 0);
G4PVPlacement* sferaPhysicalVolume = new G4PVPlacement(0,G4ThreeVector(0.*cm, 0*cm, 0*cm),"sfera",sferLogicalVolume,physicalRoom,false,0);


sferLogicalVolume -> SetVisAttributes(redtrans);


G4Sphere* sferadetector = new G4Sphere("sferadetector",15.1*cm, 15.2*cm,0. *deg, 360. *deg,0. *deg, 180. *deg);

G4LogicalVolume* sferdetectorLogicalVolume = new G4LogicalVolume(sferadetector,vacuum,"sferadetector", 0, 0, 0);
G4PVPlacement* sferadetectorPhysicalVolume = new G4PVPlacement(0,G4ThreeVector(0.*cm, 0*cm, 0*cm),"sferadetector",sferdetectorLogicalVolume,physicalRoom,false,0);


sferdetectorLogicalVolume -> SetVisAttributes (G4VisAttributes::GetInvisible());
}
*/








    return physicalRoom;
}
