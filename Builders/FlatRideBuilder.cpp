
//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Graphics/VPoint.h"
#include "../CoreObjects/Ride.h"
#include "../CoreObjects/RideBase.h"
#include "../CoreObjects/RideSection.h"
#include "../CoreObjects/Arm.h"
#include "../CoreObjects/Hub.h"
#include "../CoreObjects/Deck.h"
#include "../CoreObjects/Strut.h"
#include "../CoreObjects/LiftArm.h"
#include "../CoreObjects/CarouselAssembly.h"
#include "../CoreObjects/RotationHub.h"
#include "../CoreObjects/SpokeAssembly.h"
#include "../CoreObjects/RotationJoint.h"
#include "../CoreObjects/CableHingeJoint.h"
#include "../CoreObjects/Carriage.h"
#include "../CoreObjects/Car.h"

#include "FlatRideBuilder.h"

/* Must Have List
Monorail - Large Retro
Monorail ( People Mover with Roof )

Coasters

Steel Twister
Woodie Twister

Flat Rides

Carousel Small
Crazy Bus
Eli Ferris Wheel
Eyerly Loop-O-Plane
Eyerly Octopus
Flying Scooters
Scrambler
*/

FlatRideBuilder::FlatRideBuilder(void)
{
}

FlatRideBuilder::~FlatRideBuilder(void)
{
}

// Game Manager Interaction
//
// The game manger call this then adds the returned ride to the park or attack it to a ghost object for placement.
//
Ride* FlatRideBuilder::CreateRide(int iPattern)
{
   Ride* pRide = new Ride();
   const int iTest = 8;

   if( iPattern == 0)
   {
      // test data, the laundery ride
      Deck* pDeck = new Deck(3,15,iTest,"Basemetal.png");
      pDeck->SetPosition(0,0,0);
      pDeck->Render();
      Hub* pHub = new Hub (12, 13, "foundation.png");
      pRide->SetNode(pHub);
      pHub->Render();
      RotationHub* pHub2 = new RotationHub (1, 4, 13, "Chips.png");
      pHub->AddNode(pHub2);
      pHub2->Render();
      pHub2->SetDesiredSpeed(75);
      pHub->AddNode (pDeck);

      // test with 8 arms, the laundery ride
      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      STrig trig(0,fDegH,0, 1.0);
      CVPoint v1(0,0,13.25);
      CVPoint v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));
      
      for (int ix = 0; ix < iTest; ++ix)
      {
         Arm* pArm = new Arm(1, 1.5f, 2.25f, 12.75f, fAngle);
         pArm->Render();
         pHub2->AddNode(pArm);
         float fAngle2 = fAngle + fDegH;
         fAngle += fDeg;
         
         CableHingeJoint* pWire = new CableHingeJoint();
         CVPoint v1(0,0,-vx*2);
         CVPoint v2(0,0,0);
         CVPoint v3(0,0,-vx);
         v3.y = -10;
         pWire->SetPoints (v1.GetVector3f(), v3.GetVector3f(), v2.GetVector3f());
         pHub2->AddNode (pWire);
         CVPoint v4(13.35,3.15f,0);
         v4.Rotate(trig);
         pWire->SetYAngle(fAngle2);
         pWire->SetPosition(v4.GetVector3f());
         pWire->Render();
         Hub* p2 = new Hub(4,8,"railing.png");
         p2->SetPosition(0,-11,-vx);
         p2->Render();
         pWire->AddNode(p2);
      }
   }
   else if( iPattern == 1)
   {

      // test with 8 section carousel
      pRide = new Ride();

      // test data, the laundery ride
      int iSides = 14;
      float fRadius = 18.0f;
      Hub* pHub = new Hub (12, iSides, "DarkWood.png");
      pRide->SetNode(pHub);
      pHub->Render();
      RotationHub* pHub2 = new RotationHub (1, 3, iSides, "Chips.png");
      pHub->AddNode(pHub2);
      pHub2->Render();
      pHub2->SetDesiredSpeed(15);
      Deck* pDeck = new Deck(3, fRadius,iSides,"DarkWood.png");
      pDeck->SetPosition(0,-9.5f, 0);
      pDeck->Render();
      pHub2->AddNode (pDeck);

      float fDeg = 360.0f / iSides;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      STrig trig(0,fDegH,0, 1.0);
      CVPoint v1 (0, 0, fRadius);
      CVPoint v2 (v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));
      
      for (int ix = 0; ix < iSides; ++ix)
      {
         CarouselAssembly* pArm = new CarouselAssembly(1, 0, -2.25f, fRadius, fAngle);
         pArm->SetPosition(0,2.25,0);
         pArm->Render();
         pHub2->AddNode(pArm);
         
         Strut* pStrut = new Strut();
         trig.SetY (fAngle);
         CVPoint v1( fRadius-1, 1.5, 0);
         v1.Rotate (trig);
         CVPoint v2( fRadius-1, -10.0, 0);
         v2.Rotate (trig);
         pStrut->SetPoints (v1.GetVector3f(), v2.GetVector3f());
         pStrut->Render();
         pHub2->AddNode (pStrut);

         for( int iRad = 3+4; iRad < (int)fRadius-3; iRad+=3 )
         {
            // plug the gallop poles into the arm cranks
            Strut* pStrut = new Strut();
            trig.SetY (fAngle);
            CVPoint v1(iRad, -0.75, 0);
            v1.Rotate (trig);
            CVPoint v2(iRad, 10.75, 0);
            v2.Rotate (trig);
            pStrut->SetPoints (v1.GetVector3f(), v2.GetVector3f());
            pStrut->Render();
            pArm->AddNode (pStrut);
         }
         fAngle += fDeg;
      }
   }
   else
   {
      // test data, the dryer ride
      Deck* pDeck = new Deck(3,15,iTest,"Basemetal.png");
      pDeck->SetPosition(0,0,0);
      pDeck->Render();
      LiftArm* pLA = new  LiftArm(123, 15, 5, "Basemetal.png");
      pRide->SetNode(pLA);
      Hub* pHub = new Hub (2, 3, "foundation.png");
      pLA->AddNode (pHub);
      pHub->Render();
      RotationHub* pHub2 = new RotationHub (1, 4, 13, "Chips.png");
      pHub->AddNode(pHub2);
      pHub2->SetYPosition (3.0f);
      pHub2->Render();
      pHub2->SetDesiredSpeed(75);
      pHub->AddNode (pDeck);

      // test with 8 arms, the laundery ride
      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      STrig trig(0,fDegH,0, 1.0);
      CVPoint v1(0,0,13.25);
      CVPoint v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));
      
      for (int ix = 0; ix < iTest; ++ix)
      {
         Arm* pArm = new Arm(1, 1.5f, 2.25f, 12.75f, fAngle);
         pArm->Render();
         pHub2->AddNode(pArm);
         float fAngle2 = fAngle + fDegH;
         fAngle += fDeg;
         
         CableHingeJoint* pWire = new CableHingeJoint();
         CVPoint v1(0,0,-vx*2);
         CVPoint v2(0,0,0);
         CVPoint v3(0,0,-vx);
         v3.y = -3;
         pWire->SetPoints (v1.GetVector3f(), v3.GetVector3f(), v2.GetVector3f());
         pHub2->AddNode (pWire);
         CVPoint v4(13.35,3.15f,0);
         v4.Rotate(trig);
         pWire->SetYAngle(fAngle2);
         pWire->SetPosition(v4.GetVector3f());
         pWire->Render();
         Hub* p2 = new Hub(4,8,"railing.png");
         p2->SetPosition(0,-2,-vx);
         p2->Render();
         pWire->AddNode(p2);
      }
   }

   return pRide;
}

/*
   Ride Sections or nodes that are built in this function as set in the guide.
   The guide is the UIs extension to the builder giving in build commands
   
      RideNodePlatForm  The Base that sits on the ground or
      RideNodeChassis   Deck or Central base as in a carousel
      RideNodeDisc      Circular Deck or Roof
      RideNodeStrut     Interconnect or Structural element
      RideNodeAxis      Bending, Twisting or Totating element
      RideNodeArm       Assembly that is a feature support that extends out and usually supports a carriage.
                        Arms may be moveable or fixed
      RideNodeCarriage  Assembly that supports one or more cars
      RideNodeCar       Inclosure or platform that holds the seats and may include (a cage or rollbars) and restraints.
*/

// UI Interaction
void FlatRideBuilder::MakeSection( PartGuide& guide, Ride& ride )
{
   switch (guide.mNodeType)
   {
      case PartGuide::RideNodePlatForm:
      break;
      
      case PartGuide::RideNodeArm:
      break;
      
      case PartGuide::RideNodeAxis:
      break;
      
      case PartGuide::RideNodeCar:
      break;
      
      case PartGuide::RideNodeCarriage:
      break;
      
      case PartGuide::RideNodeDisc:
      break;
      
      case PartGuide::RideNodeStrut:
      break;
   }
}

bool FlatRideBuilder::SetParameter( int node, int parameter, int id, float value )
{
   return false;
}

// some rides need supports and legs.
ObjectBase* FlatRideBuilder::Support( Vector3f pt, PartGuide& guide, float MountAngle, float Load, float fBaseHeight )
{
   RideSection* pToDo = new RideSection();
   return pToDo;
}

/* DOC
enum TFlatRideNodeType{RideNodeStrut, RideNodeAxis, RideNodeDisc, RideNodeCarriage};
enum TFlatRideNodeShape{Triangle, Square, Round};

class TFlatRideNode
{
public:
float width, height, length;
int repetitions;
int repCount; // temporary value used by render system for interation
int TextureID;
int Debug;
int gearID;
float gearRatio;
float Orientation[3]; // X, Y, Z
float theta; // angle to rotate along x-axis
float phi; // angle to rotate along y-axis
TFlatRideNodeType Type;
TFlatRideNodeShape Shape;
TFlatRideNode *ptrParent;
TFlatRideNode *ptrChild;
TFlatRideNode *ptrPrevSibling;
TFlatRideNode *ptrNextSibling;

TFlatRideNode(); // constructor
~TFlatRideNode() {}; // destructor
};

enum TBaseType {SquareBase, RoundBase, EllipseBase, HexagonBase, OctagonBase};

struct TFlatRideBase {
TBaseType Shape;
int width, length;
};

class TFlatRide
{
public:
TFlatRideBase Base;
TFlatRideNode Primary;
};


For a scrambler type of ride with 3 main arms and 4 secondary arms, there is only a single entry(node) for the main arms and a single node for the secondary arms. Each node contains the number of repetitions and the render engine was responsible for traversing the tree and performing the repetitions during descent. That worked well for the ride editor but may not be the best way to render it during game play. 
*/