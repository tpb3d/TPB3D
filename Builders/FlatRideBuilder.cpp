
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

#include "RidePartLoader.h"
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

namespace Builders
{
   const char* kszParts[] =
   {
      "brnstrbase.3ds",
      "brnstrprimary.3ds",
      "brnstrsec.3ds",
      "",
      "brnstrlifter.3ds",
      "",
      "brnstrmcar.3ds",
      "brnstrmdoor.3ds"
   };

   PartGuide::TFlatRideNodeType kParts[] = 
   {
      PartGuide::RideNodeBase,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeRotationHub,
      PartGuide::RideNodeArm,
      PartGuide::RideNodeCableHinge,
      PartGuide::RideNodeCar
   };
}

using namespace Builders;

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
Ride* FlatRideBuilder::CreateRide(int iPattern, Park& park)
{
   Ride* pRide = new Ride(Vector3f(0,0,0), park);
   const int iTest = 12;

   if( iPattern == 0)
   {
      RidePartLoader rpl;
      const char* pPath = "Data/BarnStormers/";
      PartGuide guide;
      guide.Clear();
      // test data, the Barn Stormer ride
      ObjectNode* pHubNode = new ObjectNode (0, 31);
      const char* kszHub = "brnstrprimary.3ds";
      rpl.Load3ds( pPath, kszHub, pHubNode );

      guide.fHeight = 18;
      guide.nCount = 13;
      RideNode* pHub = AddRideNodeHub (NULL, pHubNode, guide);
      pRide->SetNode (pHub);

      // spin up
      guide.fHeight = 12;
      guide.nSpeed = 35;
      guide.fDrop = 12;
      RideNode* pRotHub = AddRideNodeRotationHub (pHub, NULL, guide);

      ObjectNode* pBaseNode = new ObjectNode (0, 33);
      const char* kszBase = "brnstrbase.3ds";
      rpl.Load3ds( pPath, kszBase, pBaseNode );
      // Make a base
      guide.fOffset = 2;
      guide.fWidth = 19.2;
      guide.nCount = 17;
      RideNode* pDeck2 = AddRideNodeDeck (pHub, NULL, guide);
      pDeck2->SetPosition (0,1.1,0);
      pDeck2->Render();
      guide.nCount = iTest;
      RideNode* pDeck = AddRideNodeDeck (pHub, pBaseNode, guide);
      pDeck->SetPosition (0,0,0);

      // test with 8 arms, the laundery ride
      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      STrig trig(0, fDegH, 0, 1.0);
      CVPoint v1(0,0,10);
      CVPoint v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));
      
      guide.fAngle = 0;
      guide.fOffset = 0;
      guide.fHeight = 12;
      guide.fLength = 10.0f;
      guide.fDrop = -10.0f;
      guide.fWidth = vx;
      guide.trig.SetY (fDegH);

      ObjectNode* pCarNode = new ObjectNode (0, 34);
      ObjectNode* pArmNode = new ObjectNode (0, 35);

      const char* pTag1 = "brnstrmcar.3ds";
      rpl.Load3ds( pPath, pTag1, pCarNode );

      const char* kszArm = "brnstrliftr.3ds";
      rpl.Load3ds( pPath, kszArm, pArmNode );

//         guide.fAngle = fAngle;
      AddRideNodeArm (pRotHub, pArmNode, guide); // do the extension arm

      guide.fHeight = 9;
      guide.fLength = 11.0f;
      guide.fDrop = -8.0f;
      guide.fOffset = -vx-2;
      for (int ix = 0; ix < iTest; ++ix)
      {
         // Arm code

         // Building the yoke
         guide.fAngle = fAngle + fDegH;
         RideNode* pWire = AddRideNodeCableHinge (pRotHub, NULL, guide); // do the hanger
         fAngle += fDeg;
         
         AddRideNodeCar (pWire, pCarNode, guide);
      }
   }
   else if( iPattern == 1)
   {

      // test with 8 section carousel
      pRide = new Ride(Vector3f(0,0,0), park);

      // test data, the laundery ride
      int iSides = 14;
      float fRadius = 18.0f;

      // stator hub
      Hub* pHub = new Hub (12, iSides, "DarkWood.png");
      pRide->SetNode(pHub);
      pHub->Render();

      // rotating hub
      RotationHub* pHub2 = new RotationHub (1, 3, iSides, "Chips.png");
      pHub->AddNode(pHub2);
      pHub2->Render();
      pHub2->SetDesiredSpeed(15);
      Deck* pDeck = new Deck(3, fRadius,iSides,"DarkWood.png");
      pDeck->SetPosition(0,-9.5f, 0);
      pDeck->Render();
      pHub2->AddNode (pDeck);

      // prerequisits for the carousel assembly
      float fDeg = 360.0f / iSides;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      STrig trig(0,fDegH,0, 1.0);
      CVPoint v1 (0, 0, fRadius);
      CVPoint v2 (v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));
      // spin out the rows of poles
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

         // radiate the columns of poles
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
      PartGuide guide;
      guide.Clear();

      // test data, the dryer ride
      // base deck
      Deck* pDeck = new Deck(3,15,iTest,"Basemetal.png");
      pDeck->SetPosition(0,0,0);
      pDeck->Render();
      pRide->SetNode (pDeck);
      // lifter arm build
      LiftArm* pLA = new  LiftArm(123, 18, 5, "Basemetal.png");
      pDeck->AddNode(pLA);
      pLA->Render();
      pLA->RideNode::SetPosition(0,0,-15);

      // stator hub on the end of the lifter
      guide.fHeight = 2;
      guide.nCount = 13;
      RideNode* pHubNode = AddRideNodeHub (pLA, NULL, guide);

      // rotating hub mointed on the stator hub
      guide.fHeight = 4;
      guide.nSpeed = 75;
      guide.fDrop = 1.0f;
      RideNode* pRotHub = AddRideNodeRotationHub (pHubNode, NULL, guide);

      // put what ever tub, arm assembly or deck here
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

      // preset our guide to build from.
      // This will come from a data stream once this is all together
      guide.fAngle = 0;
      guide.fOffset = 1.5f;
      guide.fHeight = 2.25f;
      guide.fLength = 10.75f;
      guide.fDrop = -3.0f;
      guide.fWidth = vx;
      guide.trig.SetY (fDegH);

      for (int ix = 0; ix < iTest; ++ix)
      {
         guide.fAngle = fAngle;
         AddRideNodeArm (pRotHub, NULL, guide); // do the extension arm

         guide.fAngle = fAngle + fDegH;
         RideNode* pWire = AddRideNodeCableHinge (pRotHub, NULL, guide); // do the hanger
         fAngle += fDeg;
         
         AddRideNodeHub (pWire, NULL, guide);
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
      
      case PartGuide::RideNodeBase:
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

RideNode* FlatRideBuilder::AddRideNodePlatForm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   return NULL;
}

RideNode* FlatRideBuilder::AddRideNodeBase (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   Deck* pDeck = new Deck (guide.fOffset, guide.fWidth - guide.fOffset, guide.nCount, pGraphicObject);
   pDeck->Render();
   if (pParent != NULL)
   {
      pParent->AddNode (pDeck);
   }
   return pDeck;
}

RideNode* FlatRideBuilder::AddRideNodeHub (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   Hub* pHub = NULL;
   if (pGraphicObject == NULL)
   {
      pHub = new Hub (guide.fHeight, guide.nCount, "foundation.png");
      pHub->Render();
   }
   else
   {
      pHub = new Hub (guide.fHeight, guide.nCount, pGraphicObject);
      pHub->Render();
   }
   if (pParent != NULL)
   {
      pParent->AddNode (pHub);
   }
   return pHub;
}

RideNode* FlatRideBuilder::AddRideNodeStrut (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   return NULL;
}

RideNode* FlatRideBuilder::AddRideNodeArm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   Arm* pArm = NULL;
   if( pGraphicObject == NULL)
   {
      pArm = new Arm(1, guide.fOffset, guide.fHeight, guide.fLength, guide.fAngle);
      pArm->Render();
   }
   else
   {
      pArm = new Arm (1, guide.fOffset, guide.fHeight, guide.fLength, guide.fAngle, pGraphicObject);
   }
   pParent->AddNode (pArm);
   return pArm;
}

RideNode* FlatRideBuilder::AddRideNodeDeck (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   Deck* pDeck = NULL;
   if (pGraphicObject == NULL)
   {
      pDeck = new Deck (guide.fOffset, guide.fWidth - guide.fOffset, guide.nCount, "Basemetal.png");
      pDeck->SetPosition(0,0,0);
      pDeck->Render();
   }
   else
   {
      pDeck = new Deck (guide.fOffset, guide.fWidth - guide.fOffset, guide.nCount, pGraphicObject);
      pDeck->SetPosition(0,0,0);
   }
   if (pParent != NULL)
   {
      pParent->AddNode (pDeck);
   }
   return pDeck;
}

RideNode* FlatRideBuilder::AddRideNodeCar (RideNode* pParent, ObjectNode* pGraphicObject, PartGuide& guide)
{
   Car* pCar = new Car (pGraphicObject);
   pCar->SetPosition(0, guide.fHeight, guide.fOffset);
   pCar->Render();
   pParent->AddNode(pCar);
   return pCar;
}

RideNode* FlatRideBuilder::AddRideNodeDisc (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   return NULL;
}

RideNode* FlatRideBuilder::AddRideNodeCarriage (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   return NULL;
}

RideNode* FlatRideBuilder::AddRideNodeCableHinge (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   CableHingeJoint* pWire = new CableHingeJoint();
   CVPoint v1(0, 0, -(guide.fWidth) * 2);
   CVPoint v2(0, 0, 0);
   CVPoint v3(0, guide.fDrop, -(guide.fWidth));
   pWire->SetPoints (v1.GetVector3f(), v3.GetVector3f(), v2.GetVector3f());
   CVPoint v4(11.0, guide.fHeight, -(guide.fWidth+0.5));
   v4.Rotate (guide.trig);
   pWire->SetYAngle (guide.fAngle);
   pWire->SetPosition (v4.GetVector3f());
   pWire->Render();
   pParent->AddNode (pWire);
   return pWire;
}

RideNode* FlatRideBuilder::AddRideNodeRotationHub (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   RotationHub* pHub2 = new RotationHub (guide.TakeANumber(), guide.fHeight, guide.nCount, "Chips.png");
   pParent->AddNode (pHub2);
 //  pHub2->Render ();
   pHub2->SetDesiredSpeed (guide.nSpeed);
   return pHub2;
}

RideNode* FlatRideBuilder::AddRideNodeLiftArm (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   return NULL;
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