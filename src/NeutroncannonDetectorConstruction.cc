
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


// ----------------MATERIALS  ------------------//

   // NIST Materials
   G4Material* air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
   G4Material* californium = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cf");
   G4Material* Pb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
   G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
   G4Material* Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    //------------------------------------------//
    
    //5% boron loaded HDPE   (c2h4)     polietilene ad alta densità 940 kg/m3
    G4Element* H = G4NistManager::Instance()->FindOrBuildElement("H");
    G4Element* C = G4NistManager::Instance()->FindOrBuildElement("C");
    G4Element* B = G4NistManager::Instance()->FindOrBuildElement("B");

    G4Element* O = G4NistManager::Instance()->FindOrBuildElement("O");
    G4Element* Si = G4NistManager::Instance()->FindOrBuildElement("Si");
    G4Element* Ca = G4NistManager::Instance()->FindOrBuildElement("Ca");
    G4Element* Na = G4NistManager::Instance()->FindOrBuildElement("Na");
    G4Element* Fe = G4NistManager::Instance()->FindOrBuildElement("Fe");


    G4Material* hdpe = new G4Material("hdpe", 1.04 * g/cm3, 3 /* components */);
    hdpe -> AddElement(H, 13.5 * perCent);
    hdpe -> AddElement(C, 81.5 * perCent);
    hdpe -> AddElement(B, 5 * perCent);
   //------------------------------------------//
   //BaF2//    <-----------------------------
   
   G4Material* BaF2 = G4NistManager::Instance()->FindOrBuildMaterial("G4_BARIUM_FLUORIDE");  

   //Liquid Argon (as defined DS geant4)
  	G4String  name,
            symbol;
  	G4int     z,
            ncomponents,
            natoms;
  	G4double  a,
            fractionmass,
            pressure;

  	G4Element* Ar = new G4Element(name="Argon", symbol="Ar", z=18, a=39.948*g/mole);
  	G4double density      = 1.40*g/cm3;
  	G4double temperature  = 87*kelvin;
  	G4Material *LiquidArgon = new G4Material(name="LiquidArgon",density,ncomponents=1,kStateLiquid, temperature);
  	LiquidArgon->AddElement(Ar,1.0);  


    //Concrete
     G4Material* Concrete = new G4Material("Concrete",2.5*g/cm3,5);
     Concrete->AddElement(O, fractionmass = 0.52);
     Concrete->AddElement(Si, fractionmass = 0.325);
     Concrete->AddElement(Ca, fractionmass = 0.08);
     Concrete->AddElement(Na, fractionmass = 0.015);
     Concrete->AddElement(Fe, fractionmass = 0.06);


// ----------  SIZES AND POSITIONS---------------------------//
  	G4double worldX = 400.0 *cm;
  	G4double worldY = 400.0 *cm;
  	G4double worldZ = 400.0 *cm;

  	//Cf source
  	G4double innerRadiusOfTheTube_source = 0.;
  	G4double outerRadiusOfTheTube_source = 0.5*cm;
  	G4double hightOfTheTube_source = 0.5*cm;

  	G4double source_x , source_y = 0*cm;
  	G4double source_z = -3*cm;

  	//Lead source collimator
  	G4double lc_dim_x = 25*cm;
  	G4double lc_dim_y = 25*cm;
  	G4double lc_dim_z = 8*cm;
	  G4double lc_hole_x = 15*cm;
  	G4double lc_hole_y = 15*cm;
  	G4double lc_hole_z = 8.1*cm;



  	G4double lc_x , lc_y = 0*cm;
  	G4double lc_z = -4*cm;
    //Surrounding HDPe
    G4double pc_dim_x = 14.98*cm;
    G4double pc_dim_y = 14.98*cm;
    G4double pc_dim_z = 8*cm;
    G4double pc_hole_x = 5*cm;
    G4double pc_hole_y = 5*cm;
    G4double pc_hole_z = 8.1*cm;  


	//cone hole
  	G4double Rmin1Coll_fixed = 0*mm;
  	G4double Rmax1Coll_fixed = 5.*mm;
  	G4double Rmin2Coll_fixed = 0*mm;
  	G4double Rmax2Coll_fixed = 5.*cm;
  	G4double hightColl_fixed = 32.5*cm;

  	G4double cone_x, cone_y = 0*cm;
  	G4double cone_z = 30*cm;

  	//detector
    G4double det_Rmin = 12.5*mm;
    G4double det_Rmax = 19.*mm;
    G4double det_h = 30*mm;

    G4double det_x, det_y = 0*cm;
    G4double det_z = -lc_hole_z-lc_z/2;    


  	//hdpe and lead
  	G4double hdpe_dim_z = 50.*mm;
  	G4double Pb_dim_z = 4.*mm;

  	//nose covering  (d)
  	G4int n_d = 4; //number of stacked PE layers
  	G4double d_dim_x = 25.*cm;
  	G4double d_dim_y = 25.*cm;
  	G4double nose_offset = 15.*cm;

  	//front/ back covering (c)
  	G4double c_back_offset = -30.*cm;
  	G4double c_front_offset =  0.*cm;

    G4double c0_dim_x = 25.*cm;
  	G4double c1_dim_x = 35.*cm;
  	G4double c2_dim_x = 45.*cm;
  	G4double c3_dim_x = 55.*cm;
  	G4double c4_dim_x = 55.8*cm;
    G4double c0_dim_y = 25.*cm;
	  G4double c1_dim_y = 35.*cm;
  	G4double c2_dim_y = 45.*cm;
  	G4double c3_dim_y = 55.*cm;
  	G4double c4_dim_y = 55.8*cm;

  	//left/right - top/bottom covering (a,b)
  	G4double ab1_dim_x = 35.*cm;
  	G4double ab2_dim_x = 45.*cm;
  	G4double ab3_dim_x = 55.*cm;
  	G4double ab4_dim_x = 55.8*cm;

  	G4double ab1_dim_y = 30.*cm;
  	G4double ab2_dim_y = 40.*cm;
  	G4double ab3_dim_y = 50.*cm;
  	G4double ab4_dim_y = 60.*cm;

  	//LAr TPC
    G4double d_tpc = 5.*cm;   //diameter
	  G4double h_tpc = 5.*cm;    //h
	  G4double z_tpc = 50.*cm;

    //Concrete floor 
    G4double floor_dim_x = worldX;
    G4double floor_dim_y = worldY;
    G4double floor_dim_z = 5*cm;

    G4double floor_pos_y = -70*cm - c4_dim_y/2;


    //VIS ATTRIBUTES
  // Visualisation attributes of all elements colours 

  G4VisAttributes * blueCobalt = new G4VisAttributes(G4Colour(0. ,0. ,0.7));
  blueCobalt -> SetVisibility(true);
  blueCobalt -> SetForceSolid(true);


  G4VisAttributes * redtrans = new G4VisAttributes(G4Colour(0.8 ,0. ,0.));
  redtrans -> SetVisibility(true);

  G4VisAttributes * lightblue = new G4VisAttributes(G4Colour(0.0 ,0.7 ,1.));
  lightblue -> SetVisibility(true);
  lightblue -> SetForceSolid(true);

  G4VisAttributes * lightyellow = new G4VisAttributes(G4Colour(0.9 ,0.9 ,0.3));
  lightyellow -> SetVisibility(true);
  lightyellow -> SetForceSolid(true);


  G4VisAttributes * graytrans = new G4VisAttributes(G4Colour(0.3 ,0.3 ,0.3));
  graytrans -> SetVisibility(true);

  G4VisAttributes * concretegray = new G4VisAttributes(G4Colour(0.6 ,0.6 ,0.6));
  graytrans -> SetVisibility(true);




    G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
    rotationMatrix->rotateY(90.*deg);
    rotationMatrix->rotateZ(90.*deg);

    G4RotationMatrix* rotationMatrix2 = new G4RotationMatrix();
    rotationMatrix2->rotateX(90.*deg);

    G4RotationMatrix* rotationMatrix3 = new G4RotationMatrix();
    rotationMatrix3->rotateX(180.*deg);




//World
  G4Box* Room = new G4Box("Room",worldX,worldY,worldZ);
	G4LogicalVolume* logicRoom = new G4LogicalVolume(Room, vacuum,"logicRoom", 0,0,0);  //now set to vacuum
	physicalRoom = new G4PVPlacement(0,G4ThreeVector(),"physicalRoom", logicRoom,0,false,0);

	logicRoom -> SetVisAttributes (G4VisAttributes::GetInvisible());

//Concrete floor
  G4Box* Floor = new G4Box("Floor",floor_dim_x,floor_dim_y,floor_dim_z);
  G4LogicalVolume* logicFloor = new G4LogicalVolume(Floor, Concrete,"logicFloor", 0,0,0); 
  G4PVPlacement* physicalFloor = new G4PVPlacement(rotationMatrix2,G4ThreeVector(0,floor_pos_y,0),"floor",logicFloor,physicalRoom,0,false,0);

  logicFloor -> SetVisAttributes(concretegray);


// Cf cylindrical source
	G4ThreeVector positionTube_source = G4ThreeVector(source_x,source_y,source_z);
  	solidTube_source = new G4Tubs("solidTube_source",innerRadiusOfTheTube_source,outerRadiusOfTheTube_source,hightOfTheTube_source,0*deg,360*deg);          
  	logicTube_source = new G4LogicalVolume(solidTube_source,vacuum,"logicTube_source",0,0,0);//californium< ---------------------------------------------
  	physiTube_source = new G4PVPlacement(0,positionTube_source,logicTube_source,"Tube_source",logicRoom,false,0);

  	logicTube_source -> SetVisAttributes(blueCobalt);

//Lead source collimator w/ hole
	G4ThreeVector positionColl_Pb = G4ThreeVector(lc_x,lc_y,lc_z);  
  	collimator_Pb = new G4Box("collimator_Pb",lc_dim_x/2., lc_dim_y/2., lc_dim_z/2.);
    hole_square_air = new G4Box("foro quadrato",lc_hole_x/2, lc_hole_y/2, lc_hole_z/2);
  	G4VSolid*collimator= new G4SubtractionSolid("piombo-buco", collimator_Pb, hole_square_air,0, G4ThreeVector(0.,0.,0.*cm));
  
  	logiccollimator = new G4LogicalVolume(collimator,hdpe,"collimator",0,0,0);
  	physicollimator = new G4PVPlacement(0,positionColl_Pb,logiccollimator,"collimator",logicRoom,false,0);

  	logiccollimator -> SetVisAttributes(graytrans);
//Surrounding HDPe
    G4ThreeVector positionColl_Pe = G4ThreeVector(lc_x,lc_y,lc_z);  
    G4Box* collimator_Pe = new G4Box("collimator_Pe",pc_dim_x/2., pc_dim_y/2., pc_dim_z/2.);
    G4Box* hole_square_Pe = new G4Box("foro quadrato Pe",pc_hole_x/2, pc_hole_y/2, pc_hole_z/2);
    G4VSolid* collimatorPe= new G4SubtractionSolid("piombo-buco Pe", collimator_Pe, hole_square_Pe,0, G4ThreeVector(0.,0.,0.*cm));
  
    G4LogicalVolume* logiccollimatorPe = new G4LogicalVolume(collimatorPe,Pb,"collimatorPe",0,0,0);
    G4PVPlacement* physicollimatorPe = new G4PVPlacement(0,positionColl_Pe,"coll_Pe",logiccollimatorPe,physicalRoom,false,0);

    logiccollimatorPe -> SetVisAttributes(redtrans);


//conic hole
	G4ThreeVector hole_position = G4ThreeVector(cone_x,cone_y,cone_z);//30.6
	G4Cons* cone_hole = new G4Cons("buco conico",Rmin1Coll_fixed,Rmax1Coll_fixed,Rmin2Coll_fixed,Rmax2Coll_fixed,hightColl_fixed,0*deg,360*deg);

  G4LogicalVolume *conelogic = new G4LogicalVolume(cone_hole,vacuum,"conelogic",0,0,0);
  G4PVPlacement *conePhysical = new G4PVPlacement(new G4RotationMatrix(),hole_position,"conehole",conelogic,physicalRoom,false,0);
  conelogic -> SetVisAttributes(lightyellow); 


//detector
  G4Cons* detectorCone = new G4Cons("detectorCone",0,det_Rmin,0,det_Rmax,det_h/2,0*deg,360*deg);
  detectorLogicalVolume = new G4LogicalVolume(detectorCone,BaF2,"detector logical", 0, 0, 0);
  detectorPhysicalVolume = new G4PVPlacement(rotationMatrix3,G4ThreeVector(det_x,det_y,det_z),"detector",detectorLogicalVolume,physicalRoom,false,0);
  detectorLogicalVolume -> SetVisAttributes(lightblue); 
 

//nose covering
    G4Box* d = new G4Box("d1",d_dim_x/2, d_dim_y/2, hdpe_dim_z/2);

	//d1

      G4VSolid * d1= new G4SubtractionSolid("d1", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -(10*cm+1*hdpe_dim_z)));

      d1LogicalVolume = new G4LogicalVolume(d1,hdpe,"d1 logical", 0, 0, 0);
      d1PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, nose_offset+1*hdpe_dim_z/2),"d1 ",d1LogicalVolume,physicalRoom,false,0);//-0.6
    
      d1LogicalVolume -> SetVisAttributes(graytrans); 

   //d2

      G4VSolid * d2= new G4SubtractionSolid("d2", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -(10*cm+2*hdpe_dim_z) ));

      d2LogicalVolume = new G4LogicalVolume(d2,hdpe,"d2 logical", 0, 0, 0);
      d2PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, nose_offset+3*hdpe_dim_z/2),"d2 ",d2LogicalVolume,physicalRoom,false,0);
    
      d2LogicalVolume -> SetVisAttributes(graytrans);


   //d3

      G4VSolid * d3= new G4SubtractionSolid("d3", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -(10*cm+3*hdpe_dim_z) ));

      d3LogicalVolume = new G4LogicalVolume(d3,hdpe,"d3 logical", 0, 0, 0);
      d3PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, nose_offset+5*hdpe_dim_z/2),"d3 ",d3LogicalVolume,physicalRoom,false,0);
    
      d3LogicalVolume -> SetVisAttributes(graytrans);

   //d4

      G4VSolid * d4= new G4SubtractionSolid("d4", d, cone_hole,0, hole_position + G4ThreeVector(0., 0., -(10*cm+4*hdpe_dim_z) ));

      d4LogicalVolume = new G4LogicalVolume(d4,hdpe,"d4 logical", 0, 0, 0);
      d4PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0.*cm, 0*cm, nose_offset+7*hdpe_dim_z/2),"d4 ",d4LogicalVolume,physicalRoom,false,0);
    
      d4LogicalVolume -> SetVisAttributes(graytrans);

//nose lead shielding (e,f)
	//e,f
    G4Box* e1 = new G4Box("e1",d_dim_x/2, (n_d*hdpe_dim_z)/2-Pb_dim_z, Pb_dim_z/2);
	G4Box* f1 = new G4Box("f1",d_dim_x/2, (n_d*hdpe_dim_z)/2-Pb_dim_z, Pb_dim_z/2);

	G4double ef_x_offset = (d_dim_x+Pb_dim_z)/2;
	G4double ef_y_offset = hdpe_dim_z*(n_d/2+3)+Pb_dim_z; //???

	e1LogicalVolume = new G4LogicalVolume(e1,Pb,"e1logical", 0, 0, 0);
	e1DownPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -ef_x_offset, ef_y_offset),"e1Down",e1LogicalVolume,physicalRoom,false,0);
	e1UpPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, ef_x_offset, ef_y_offset),"e1Up",e1LogicalVolume,physicalRoom,false,0);

	f1LogicalVolume = new G4LogicalVolume(f1,Pb,"f1logical", 0, 0, 0);
	f1LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(ef_x_offset, 0*cm, ef_y_offset),"f1Left",f1LogicalVolume,physicalRoom,false,0);
	f1RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-ef_x_offset, 0*cm, ef_y_offset),"f1Right",f1LogicalVolume,physicalRoom,false,0);
    
	e1LogicalVolume -> SetVisAttributes(redtrans);
	f1LogicalVolume -> SetVisAttributes(redtrans);
	
	//Pb front cover
	G4Box* cover = new G4Box("nosecover",(d_dim_x+Pb_dim_z)/2, (d_dim_x+Pb_dim_z)/2, Pb_dim_z/2);
	//hole_air = new G4Tubs("buco",0.*cm, 5*cm, 3/2*cm,0*deg,360*deg);

	G4VSolid*nosecover= new G4SubtractionSolid("tappo-buco", cover, cone_hole,0, G4ThreeVector(0.,0.,0.));

	nosecoverLogicalVolume = new G4LogicalVolume(nosecover,Pb,"nosecover", 0, 0, 0);
	nosecoverPhysicalVolume = new G4PVPlacement( 0,G4ThreeVector(0.*cm, 0*cm, hdpe_dim_z*(n_d+3)+Pb_dim_z),"nosecover",nosecoverLogicalVolume,physicalRoom,false,0);

	nosecoverLogicalVolume -> SetVisAttributes(redtrans);


//front / rear covering (from inner to outer c1,c2,c3,c4) front with holes
    //innermost back c0
    G4Box* c0 = new G4Box("c0",c0_dim_x/2, c0_dim_y/2, hdpe_dim_z/2);

    G4LogicalVolume* c0LogicalVolume = new G4LogicalVolume(c0,hdpe,"c0 back", 0, 0, 0);
    G4PVPlacement* c0PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_back_offset+1*hdpe_dim_z/2),"c0 back",c0LogicalVolume,physicalRoom,false,0);//-100.6*cm

    c0LogicalVolume -> SetVisAttributes(graytrans); 
    
	  //c1
 	  G4Box* c1 = new G4Box("c1",c1_dim_x/2, c1_dim_y/2, hdpe_dim_z/2);

    c1LogicalVolume = new G4LogicalVolume(c1,hdpe,"c1 back", 0, 0, 0);
    c1PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_back_offset-1*hdpe_dim_z/2),"c1 back",c1LogicalVolume,physicalRoom,false,0);//-100.6*cm

    G4VSolid*c1_hole= new G4SubtractionSolid("c1 Front", c1, cone_hole,0, hole_position );
    c1_holeLogicalVolume = new G4LogicalVolume(c1_hole,hdpe,"c1 front", 0, 0, 0);
    c1_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_front_offset+1*hdpe_dim_z/2),"c1 front",c1_holeLogicalVolume,physicalRoom,false,0);//-30.6*cm
  
    c1LogicalVolume -> SetVisAttributes(graytrans); 
    c1_holeLogicalVolume -> SetVisAttributes(graytrans);
    
    //c2
    G4Box* c2 = new G4Box("c2",c2_dim_x/2, c2_dim_y/2, hdpe_dim_z/2);

    c2LogicalVolume = new G4LogicalVolume(c2,hdpe,"c2 back", 0, 0, 0);
    c2PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_back_offset-3*hdpe_dim_z/2),"c2 back",c2LogicalVolume,physicalRoom,false,0);//-101.0*cm

    G4VSolid*c2_hole= new G4SubtractionSolid("c2 Front", c2, cone_hole,0, hole_position +G4ThreeVector(0., 0., -5*cm) );
    c2_holeLogicalVolume = new G4LogicalVolume(c2_hole,hdpe,"c2 front", 0, 0, 0);
    c2_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_front_offset+3*hdpe_dim_z/2),"c2 front",c2_holeLogicalVolume,physicalRoom,false,0);//-20.6*cm
  
    c2LogicalVolume -> SetVisAttributes(graytrans); 
    c2_holeLogicalVolume -> SetVisAttributes(graytrans);

	  //c3 
    G4Box* c3 = new G4Box("c3",c3_dim_x/2, c3_dim_y/2, hdpe_dim_z/2);

    c3LogicalVolume = new G4LogicalVolume(c3,hdpe,"c3 back", 0, 0, 0);
    c3PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_back_offset-5*hdpe_dim_z/2),"c3 back",c3LogicalVolume,physicalRoom,false,0);//-101.0*cm

    G4VSolid*c3_hole= new G4SubtractionSolid("c3 Front", c3, cone_hole,0, hole_position + G4ThreeVector(0., 0., -10*cm));
    c3_holeLogicalVolume = new G4LogicalVolume(c3_hole,hdpe,"c3 front", 0, 0, 0);
    c3_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_front_offset+5*hdpe_dim_z/2),"c3 front",c3_holeLogicalVolume,physicalRoom,false,0);//-30.6*cm
  
    c3LogicalVolume -> SetVisAttributes(graytrans); 
    c3_holeLogicalVolume -> SetVisAttributes(graytrans);

	  //c4  <-- lead one
    G4Box* c4 = new G4Box("c4",c4_dim_x/2, c4_dim_y/2, Pb_dim_z/2);/////10.*mm

    c4LogicalVolume = new G4LogicalVolume(c4,Pb,"c4back", 0, 0, 0);
    c4PhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_back_offset-3*hdpe_dim_z-Pb_dim_z),"c4back",c4LogicalVolume,physicalRoom,false,0);//-101.0*cm

    G4VSolid * c4_hole = new G4SubtractionSolid("c4 Front", c4, d,0,G4ThreeVector(0,0,0));//buco quadrato
    c4_holeLogicalVolume = new G4LogicalVolume(c4_hole,Pb,"c4front", 0, 0, 0);
    c4_holePhysicalVolume = new G4PVPlacement( new G4RotationMatrix(),G4ThreeVector(0., 0., c_front_offset+3*hdpe_dim_z+Pb_dim_z),"c4front",c4_holeLogicalVolume,physicalRoom,false,0);//-30.6*cm
  
    c4LogicalVolume -> SetVisAttributes(redtrans); 
    c4_holeLogicalVolume -> SetVisAttributes(redtrans);


//left/right (a1...a4) - top/bottom (b1...b4) NB: many sizes are not absolute!

    //a1
    G4Box* a1 = new G4Box("a1",25./2*cm, ab1_dim_y/2, hdpe_dim_z/2);

    a1LogicalVolume = new G4LogicalVolume(a1,hdpe,"a1 logical", 0, 0, 0);
    a1LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(15.*cm, 0.*cm, -15*cm),"a1 left",a1LogicalVolume,physicalRoom,false,0);//30.*cm, 0.*cm, -65.5*cm
    a1RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-15.*cm, 0.*cm, -15*cm),"a1 right",a1LogicalVolume,physicalRoom,false,0);    
    
    a1LogicalVolume -> SetVisAttributes(graytrans); 
    
    //b1
    G4Box* b1 = new G4Box("b1",17.5*cm, ab1_dim_y/2, hdpe_dim_z/2);

    b1LogicalVolume = new G4LogicalVolume(b1,hdpe,"b1 logical", 0, 0, 0);
    b1bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -15.*cm, -15*cm),"b1 bottom",b1LogicalVolume,physicalRoom,false,0);
    b1upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 15.*cm, -15*cm),"b1 up",b1LogicalVolume,physicalRoom,false,0);
    
    b1LogicalVolume -> SetVisAttributes(graytrans); 
    
    //a2
    G4Box* a2 = new G4Box("a2",35./2*cm, ab2_dim_y/2, hdpe_dim_z/2);

    a2LogicalVolume = new G4LogicalVolume(a2,hdpe,"a2 logical", 0, 0, 0);
    a2LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(20*cm, 0.*cm, -15*cm),"a2 left",a2LogicalVolume,physicalRoom,false,0);
    a2RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-20*cm, 0.*cm, -15*cm),"a2 right",a2LogicalVolume,physicalRoom,false,0);
    
    a2LogicalVolume -> SetVisAttributes(graytrans); 
    
    //b2
    G4Box* b2 = new G4Box("b2",45./2*cm, ab2_dim_y/2, hdpe_dim_z/2);

    b2LogicalVolume = new G4LogicalVolume(b2,hdpe,"b2 logical", 0, 0, 0);
    b2bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -20*cm, -15*cm),"b2 bottom",b2LogicalVolume,physicalRoom,false,0);
    b2upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 20*cm, -15*cm),"b2 up",b2LogicalVolume,physicalRoom,false,0);
    
    b2LogicalVolume -> SetVisAttributes(graytrans); 
 
 	//a3
    G4Box* a3 = new G4Box("a3",45./2*cm, ab3_dim_y/2, hdpe_dim_z/2);

	a3LogicalVolume = new G4LogicalVolume(a3,hdpe,"a3 logical", 0, 0, 0);
    a3LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(25*cm, 0.*cm, -15*cm),"a3 left",a3LogicalVolume,physicalRoom,false,0);
    a3RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-25*cm, 0.*cm, -15*cm),"a3 right",a3LogicalVolume,physicalRoom,false,0);
    
    a3LogicalVolume -> SetVisAttributes(graytrans); 
  
  	//b3    
  	G4Box* b3 = new G4Box("b3",55./2*cm, ab3_dim_y/2, hdpe_dim_z/2);

    b3LogicalVolume = new G4LogicalVolume(b3,hdpe,"b3 logical", 0, 0, 0);
    b3bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -25*cm, -15*cm),"b3 bottom",b3LogicalVolume,physicalRoom,false,0);
    b3upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 25*cm, -15*cm),"b3 up",b3LogicalVolume,physicalRoom,false,0);
    
    b3LogicalVolume -> SetVisAttributes(graytrans); 
  
  	//a4
    G4Box* a4 = new G4Box("a4",55./2*cm, ab4_dim_y/2, Pb_dim_z/2);

    a4LogicalVolume = new G4LogicalVolume(a4,Pb,"a4logical", 0, 0, 0);
    a4LeftPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(27.7*cm, 0.*cm, -15*cm),"a4left",a4LogicalVolume,physicalRoom,false,0);
    a4RightPhysicalVolume = new G4PVPlacement( rotationMatrix,G4ThreeVector(-27.7*cm, 0.*cm, -15*cm),"a4right",a4LogicalVolume,physicalRoom,false,0);
    
    a4LogicalVolume -> SetVisAttributes(redtrans); 
 
 	//b4
 	G4Box* b4 = new G4Box("b4",55.8/2*cm, ab4_dim_y/2, Pb_dim_z/2);

    b4LogicalVolume = new G4LogicalVolume(b4,Pb,"b4logical", 0, 0, 0);
    b4bottomPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, -27.7*cm, -15*cm),"b4bottom",b4LogicalVolume,physicalRoom,false,0);
    b4upPhysicalVolume = new G4PVPlacement( rotationMatrix2,G4ThreeVector(0.*cm, 27.7*cm, -15*cm),"b4up",b4LogicalVolume,physicalRoom,false,0);
    
    b4LogicalVolume -> SetVisAttributes(redtrans); 


//LAr TPC
	G4Tubs* TPC_Fill = new G4Tubs("TPC_Fill", 0, 0.5*d_tpc, h_tpc*0.5, 0, 2*M_PI);  
	G4LogicalVolume *TPC_FillLogicalVolume = new G4LogicalVolume(TPC_Fill,LiquidArgon,"TPC_Fill", 0, 0, 0);
	G4PVPlacement *TPC_FillPhysicalVolume = new G4PVPlacement(rotationMatrix2,G4ThreeVector(0.*cm, 0*cm, z_tpc),"TPC_Fill",TPC_FillLogicalVolume,physicalRoom,false,0);

	TPC_FillLogicalVolume -> SetVisAttributes(lightblue);





    return physicalRoom;
}



