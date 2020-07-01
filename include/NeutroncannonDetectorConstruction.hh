#ifndef NeutroncannonDetectorConstruction_h
#define NeutroncannonDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"



#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4NistMessenger.hh"
#include "G4NistElementBuilder.hh"
#include "G4NistMaterialBuilder.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Polyhedra.hh"
#include "G4SubtractionSolid.hh"
#include "G4Cons.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Tubs;
class G4Cons;
class G4Box;

/// Detector construction class to define materials and geometry.

class NeutroncannonDetectorConstruction : public G4VUserDetectorConstruction
{
  public:    
    NeutroncannonDetectorConstruction();
   ~NeutroncannonDetectorConstruction();

   G4VPhysicalVolume* Construct();
    
  private:
    G4VPhysicalVolume* physicalRoom;
    ////////////////////////////
    G4Box * rivelatore;
    G4LogicalVolume *  L1Logic;
    G4LogicalVolume *  L2Logic;
    G4LogicalVolume *  L3Logic;
    G4LogicalVolume *  L4Logic;

    G4VPhysicalVolume* L1PhysicalVolume;
    G4VPhysicalVolume* L2PhysicalVolume;
    G4VPhysicalVolume* L3PhysicalVolume;
    G4VPhysicalVolume* L4PhysicalVolume;

    G4Box * cavity;
    G4LogicalVolume * cavityLogic;
    G4VPhysicalVolume * cavityPhysicalVolume;

    ///////////////////
    G4VSolid*detector;
    G4VSolid* detectorfronthole;
    G4VPhysicalVolume* detectorPhysicalVolume;
    G4LogicalVolume* detectorLogicalVolume;

    G4VSolid*detectordisc;
    G4VPhysicalVolume* detectordiscPhysicalVolume;
    G4LogicalVolume* detectordiscLogicalVolume;

    //////////////////////////////////
    G4Box*             c1;
    G4VPhysicalVolume* c1PhysicalVolume;
    G4LogicalVolume* c1LogicalVolume;
    G4VPhysicalVolume* c1_holePhysicalVolume;
    G4LogicalVolume* c1_holeLogicalVolume;
    ///////////////////
    G4Box*             c2;
    G4VPhysicalVolume* c2PhysicalVolume;
    G4LogicalVolume* c2LogicalVolume;
    G4VPhysicalVolume* c2_holePhysicalVolume;
    G4LogicalVolume* c2_holeLogicalVolume;
    ///////////////////
    G4Box*             c3;
    G4VPhysicalVolume* c3PhysicalVolume;
    G4LogicalVolume* c3LogicalVolume;
    G4VPhysicalVolume* c3_holePhysicalVolume;
    G4LogicalVolume* c3_holeLogicalVolume;
    /////////////////
    G4Box*             d;
    G4VPhysicalVolume* d1PhysicalVolume;
    G4LogicalVolume*   d1LogicalVolume;
    G4VPhysicalVolume* d2PhysicalVolume;
    G4LogicalVolume*   d2LogicalVolume;
    G4VPhysicalVolume* d3PhysicalVolume;
    G4LogicalVolume*   d3LogicalVolume;
    G4VPhysicalVolume* d4PhysicalVolume;
    G4LogicalVolume*   d4LogicalVolume;
    G4VPhysicalVolume* d5PhysicalVolume;
    G4LogicalVolume*   d5LogicalVolume;
    G4VPhysicalVolume* d6PhysicalVolume;
    G4LogicalVolume*   d6LogicalVolume;
    G4VPhysicalVolume* d7PhysicalVolume;
    G4LogicalVolume*   d7LogicalVolume;
    G4VPhysicalVolume* d8PhysicalVolume;
    G4LogicalVolume*   d8LogicalVolume;
    G4VPhysicalVolume* d9PhysicalVolume;
    G4LogicalVolume*   d9LogicalVolume;
    G4VPhysicalVolume* d10PhysicalVolume;
    G4LogicalVolume*   d10LogicalVolume;
    //////
    G4Box* e1;
    G4LogicalVolume* e1LogicalVolume;
    G4VPhysicalVolume* e1DownPhysicalVolume;
    G4VPhysicalVolume* e1UpPhysicalVolume;

    G4Box* f1;
    G4LogicalVolume* f1LogicalVolume;
    G4VPhysicalVolume* f1LeftPhysicalVolume;
    G4VPhysicalVolume* f1RightPhysicalVolume;

    //////////////////
    G4Box* cover;
    G4LogicalVolume* nosecoverLogicalVolume;
    G4VPhysicalVolume* nosecoverPhysicalVolume;
    G4VSolid*nosecover;
  /////////////////////////////////////////////
    G4Box*             a1;
    G4VPhysicalVolume* a1LeftPhysicalVolume;
    G4VPhysicalVolume* a1RightPhysicalVolume;
    G4LogicalVolume* a1LogicalVolume;
    //////////////
    G4Box*             b1;
    G4VPhysicalVolume* b1bottomPhysicalVolume;
    G4VPhysicalVolume* b1upPhysicalVolume;
    G4LogicalVolume* b1LogicalVolume;
    ///////////////
    G4Box*             a2;
    G4VPhysicalVolume* a2LeftPhysicalVolume;
    G4VPhysicalVolume* a2RightPhysicalVolume;
    G4LogicalVolume* a2LogicalVolume;
    //////////////
    G4Box*             b2;
    G4VPhysicalVolume* b2bottomPhysicalVolume;
    G4VPhysicalVolume* b2upPhysicalVolume;
    G4LogicalVolume* b2LogicalVolume;
    //////////////////////////
    ///////////////
    G4Box*             a3;
    G4VPhysicalVolume* a3LeftPhysicalVolume;
    G4VPhysicalVolume* a3RightPhysicalVolume;
    G4LogicalVolume* a3LogicalVolume;
    //////////////
    G4Box*             b3;
    G4VPhysicalVolume* b3bottomPhysicalVolume;
    G4VPhysicalVolume* b3upPhysicalVolume;
    G4LogicalVolume* b3LogicalVolume;
    //////////////////////////
    G4Box*             a4;
    G4VPhysicalVolume* a4LeftPhysicalVolume;
    G4VPhysicalVolume* a4RightPhysicalVolume;
    G4LogicalVolume* a4LogicalVolume;
    //////////////
    G4Box*             b4;
    G4VPhysicalVolume* b4bottomPhysicalVolume;
    G4VPhysicalVolume* b4upPhysicalVolume;
    G4LogicalVolume* b4LogicalVolume;
    ///////////////////
    G4Box*             c4;
    G4VPhysicalVolume* c4PhysicalVolume;
    G4LogicalVolume* c4LogicalVolume;
    G4VPhysicalVolume* c4_holePhysicalVolume;
    G4LogicalVolume* c4_holeLogicalVolume;
    ///////////////////
    G4Cons* cone_hole;

    /////////////
    G4Tubs*            hole_air;
    G4Box*             hole_square_air;
    G4LogicalVolume*   logichole_air;    
    G4VPhysicalVolume* physihole_air;
    /////////////
    G4Box*            collimator_Pb;
    G4LogicalVolume*   logiccollimator;    
    G4VPhysicalVolume* physicollimator;
    //G4VSolid*subtract;
    //////////////
    G4Tubs*            solidTube_source;    
    G4LogicalVolume*   logicTube_source;     
    G4VPhysicalVolume* physiTube_source;
  ////////////////////detector
    G4Box*             detectorLR;
    G4VPhysicalVolume* detectorLeftPhysicalVolume;
    G4VPhysicalVolume* detectorRightPhysicalVolume;
    G4LogicalVolume* detectorLRLogicalVolume;
    G4Box*             detectorUD;
    G4VPhysicalVolume* detectorUpPhysicalVolume;
    G4VPhysicalVolume* detectorDownPhysicalVolume;
    G4LogicalVolume* detectorUDLogicalVolume;
    G4Box*             detectorFB;
    G4VPhysicalVolume* detectorFrontPhysicalVolume;
    G4VPhysicalVolume* detectorBackPhysicalVolume;
    G4LogicalVolume* detectorFBLogicalVolume;
};

#endif
   
