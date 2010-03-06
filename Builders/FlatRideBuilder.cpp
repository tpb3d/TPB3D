
//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../CoreObjects/Ride.h"
#include "../CoreObjects/RideBase.h"
#include "../CoreObjects/RideSection.h"
#include "../CoreObjects/Arm.h"
#include "../CoreObjects/Hub.h"
#include "../CoreObjects/RotationHub.h"
#include "../CoreObjects/SpokeAssembly.h"
#include "../CoreObjects/RotationJoint.h"
#include "../CoreObjects/Carriage.h"
#include "../CoreObjects/Car.h"

#include "FlatRideBuilder.h"


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
Ride* FlatRideBuilder::CreateRide()
{
   Ride* pRide = new Ride();
   // test data
   Hub* pHub = new Hub (12, 13, "Chute.png");
   pRide->SetNode(pHub);
   pHub->Render();
   RotationHub* pHub2 = new RotationHub (1, 3, 13, "Chips.png");
   pHub->AddNode(pHub2);
   pHub2->Render();
   // test with 8 arms
   const int iTest = 8;
   float fDeg = 360.0f / iTest;
   float fAngle = 0;
   for (int ix = 0; ix < iTest; ++ix)
   {
      Arm* pArm = new Arm(1, 1.5f, 2.25f, 12.75f, fAngle);
      pArm->Render();
      pHub2->AddNode(pArm);
      fAngle += fDeg;
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