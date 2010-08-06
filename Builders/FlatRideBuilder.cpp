
//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../CoreObjects/Ride.h"
#include "../CoreObjects/RideBase.h"
#include "../CoreObjects/RideSection.h"
#include "../CoreObjects/RideController.h"
#include "../CoreObjects/Arm.h"
#include "../CoreObjects/Hub.h"
#include "../CoreObjects/Deck.h"
#include "../CoreObjects/Strut.h"
#include "../CoreObjects/Carriage.h"
#include "../CoreObjects/LiftArm.h"
#include "../CoreObjects/CarouselAssembly.h"
#include "../CoreObjects/HorizontalCrankHub.h"
#include "../CoreObjects/RotationHub.h"
#include "../CoreObjects/SpokeAssembly.h"
#include "../CoreObjects/RotationJoint.h"
#include "../CoreObjects/CableHingeJoint.h"
#include "../CoreObjects/Carriage.h"
#include "../CoreObjects/Car.h"

#include "RidePartLoader.h"
#include "PartGuide.h"
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
Tagada
Polyp and Spider
*/
/* wish list Flat Rides
01.) Aviator Ride
02.) Carousel Small
03.) Chance Radar/Turbo
04.) Crazy Bus
05.) Eli Ferris Wheel
06.) Eyerly Loop-O-Plane
07.) Eyerly Octopus
08.) Fabbri Booster
09.) Flying Scooters
10.) Intamin Double Wheel
11.) Paratrooper
12.) Polyp Ride ( Plus add-on Pack Too )
13.) Rotor ( Regular chance ride )
14.) Round-Up
15.) Scrambler
16.) Skywheel
17.) Tagada
18.) Trabant ( Requires textures )
19.) Yo-Yo

OTR:

20.) Chairlift Von-Roll Terminal and Gondolas ( Pending Vodhin nails Gondolas )
21.) Go-Kart 01
22.) Monorail - Large Retro
23.) Monorail ( People Mover with Roof )
24.) Monorail ( Suspended - Small Pirate Ship )
25.) Multi-Mover Dark Ride Cars
26.) Steam Boat - Samuel Clemens ( Pending water optional )

Coaster:

27.) Log Flume Ride ( Pending water optional )
28.) Steel Twister
29.) The Top
30.) Woodie Twister */

namespace Builders
{
   // these are temporary templates for ride assembly
   // Later these will be in XML
   const char* kszBSParts[] =
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
   const char* kszBS = "data/Barn Stormer/";

   PartGuide::TRideNodeType kBSNodes[] =
   {
      PartGuide::RideNodeBase,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeRotationHub,
      PartGuide::RideNodeArm,
      PartGuide::RideNodeCableHinge,
      PartGuide::RideNodeCar
   };

   const char* kszSpida = "data/Spider/";
   const char* kszSpidaParts[] =
   {
      "",
      "sr4_Spyd_EngBox.3ds",
      "sr4_Spyd_DCyl.3ds",
      "",                        // rotation
      "sr4_Spyd_DSphr.3ds",
      "sr4_Spyd_AShaft.3ds",     // crank
      "sr4_Spyd_arm.3ds",
      "sr4_Spyd_DFing.3ds",
      "sr4_Spyd_SFing.3ds",
      "sr4_Spyd_pod.3ds"
   };
   PartGuide::TRideNodeType kSpidaNodes[] =
   {
      PartGuide::RideNodeBase,
      PartGuide::RideNodeDeck,
      PartGuide::RideNodeRotationHub,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeCrankHub,
      PartGuide::RideNodeArm,
      PartGuide::RideNodeArm, // left
      PartGuide::RideNodeArm, // right
      PartGuide::RideNodeCar
   };

   const char* kszPolyp = "data/Polyp/";
   const char* kszPolypParts[] =
   {
      "",
      "polengcvr.3ds",
      "pol5finger.3ds",
      "poltop.3ds",
      "monarm",
      "polarm.3ds",
      "polfing5.3ds",
      "polsleicar.3ds"  // hope Santa has insurance for this thing
   };

   PartGuide::TRideNodeType kPolypNodes[] =
   {
      PartGuide::RideNodeBase,
      PartGuide::RideNodeDeck,
      PartGuide::RideNodeRotationHub,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeArm,
      PartGuide::RideNodeArm, // left
      PartGuide::RideNodeCar
   };

   const char* kszOcto = "data/EyerlyOctopus/";
   const char* kszOctoParts[] =
   {
      "",
      "Central_Unit.3ds",
      "Sweep.3ds",
      "",                        // rotation
      "",                        // crank
      "crosbar.3ds",
      "Tub.3ds"  // hope Santa has insurance for this thing
   };
   PartGuide::TRideNodeType kOctoNodes[] =
   {
      PartGuide::RideNodeBase,
      PartGuide::RideNodeRotationHub,
      PartGuide::RideNodeHub,
      PartGuide::RideNodeCrankHub,
      PartGuide::RideNodeArm,
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

   // this will be replaced by a class factory once time permits and the code looks like it will work.
   if( iPattern == Biplanes)
   {
      pRide->SetRideType (RT_FlatRide);
      pRide->SetRideIntensity (RI_Thrill);
      pRide->SetRideName ("Barn Stormers");
      PartCorrection corr;

      RidePartLoader rpl (corr);
      const char* pPath = kszBS;
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
      RideNode* pRotHub = AddRideNodeRotationHub (pRide->GetController(), pHub, NULL, guide);

      ObjectNode* pBaseNode = new ObjectNode (0, 33);
      const char* kszBase = "brnstrbase.3ds";
      rpl.Load3ds( pPath, kszBase, pBaseNode );
      // Make a base
      guide.fOffset = 2;
      guide.fWidth = 19.2f;
      guide.nCount = 17;
      RideNode* pDeck2 = AddRideNodeDeck (pHub, NULL, guide);
      pDeck2->SetPosition (0, 1.1f, 0);
      pDeck2->Render();
      guide.nCount = iTest;
      RideNode* pDeck = AddRideNodeDeck (pHub, pBaseNode, guide);
      pDeck->SetPosition (0, 0, 0);

      // test with 8 arms, the laundery ride
      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      Vector3f::VectorAngle3<float> trig(0, fDegH, 0);
      Vector3f v1(0,0,10);
      Vector3f v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));

      guide.fAngle = 180;
      guide.fOffset = 0;
      guide.fHeight = 12;
      guide.fLength = 10.0f;
      guide.fDrop = -10.0f;
      guide.fWidth = vx;
      guide.trig.Set (0, fDegH, 0);

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
   else if( iPattern == Spider)
   {
      PartCorrection corr;
      RidePartLoader rpl (corr);
      const char* pPath = kszSpida;
      PartGuide guide;
      guide.Clear();
      // test data, the spider ride
      ObjectNode* pHubNode = new ObjectNode (0, 32);
      const char* kszHub = kszSpidaParts[6];
      rpl.Load3ds( pPath, kszHub, pHubNode );

      guide.fHeight = 1;
      guide.nCount = 13;
      RideNode* pHub = AddRideNodeHub (NULL, pHubNode, guide);
      pRide->SetNode (pHub);

      // spin up
      guide.fHeight = 2;
      guide.nSpeed = 35;
      guide.fDrop = 0;
      RideNode* pRotHub = AddRideNodeRotationHub (pRide->GetController(), pHub, NULL, guide);

      ObjectNode* pBaseNode = new ObjectNode (0, 33);
      const char* kszBase = kszSpidaParts[7];
      rpl.Load3ds( pPath, kszBase, pBaseNode );
      // Make a base
      guide.fOffset = 2;
      guide.fWidth = 2.2f;
      guide.nCount = 8;
      RideNode* pDeck2 = AddRideNodeDeck (pHub, NULL, guide);
      pDeck2->SetPosition (0, 1.1f, 0);
      pDeck2->Render();
      guide.nCount = iTest;
      RideNode* pDeck = AddRideNodeDeck (pHub, NULL, guide);
      pDeck->SetPosition (0, 0, 0);

      // test with 8 arms, the laundery ride
      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      Vector3f::VectorAngle3<float> trig(0, fDegH, 0);
      Vector3f v1(0,0,10);
      Vector3f v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));

      ObjectNode* pCarNode = new ObjectNode (0, 34);
      ObjectNode* pArmNode = new ObjectNode (0, 35);

      const char* kszArm = kszSpidaParts[6];
      const char* kszArmA = kszSpidaParts[7];
      const char* kszArmB = kszSpidaParts[8];
      rpl.Load3ds( pPath, kszArm, pArmNode );
      rpl.Load3ds( pPath, kszArmA, pArmNode );
      rpl.Load3ds( pPath, kszArmB, pArmNode );

      guide.fAngle = 90;//fAngle;
      AddRideNodeArm (pRotHub, pArmNode, guide); // do the extension arm

      //guide.fAngle = 0;
      //guide.fOffset = 0;
      //guide.fHeight = 12;
      //guide.fLength = 10.0f;
      //guide.fDrop = -10.0f;
      //guide.fWidth = vx;
      //guide.trig.SetY (fDegH);
      const char* pTag1 = kszSpidaParts[4];
      rpl.Load3ds( pPath, pTag1, pCarNode );


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
         AddRideNodeSpinCar (pWire, pCarNode, guide);
      }
   }
   else if( iPattern == Carousel)
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
      RotationHub* pHub2 = new RotationHub (pRide->GetController(), 1, 3, iSides, "Chips.png");
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
      Vector3f::VectorAngle3<float> trig(0, fDegH, 0);
      Vector3f v1 (0, 0, fRadius);
      Vector3f v2 (v1);
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
         trig.Set (0, fAngle, 0);
         Vector3f v1( fRadius-1, 1.5, 0);
         v1.Rotate (trig);
         Vector3f v2( fRadius-1, -10.0, 0);
         v2.Rotate (trig);
         pStrut->SetPoints (sf::Vector3f(v1.x, v1.y, v1.z), sf::Vector3f(v2.x, v2.y, v2.z));
         pStrut->Render();
         pHub2->AddNode (pStrut);

         // radiate the columns of poles
         for( int iRad = 3+4; iRad < (int)fRadius-3; iRad+=3 )
         {
            // plug the gallop poles into the arm cranks
            Strut* pStrut = new Strut();
            trig.Set (0, fAngle, 0);
            Vector3f v1((float)iRad, -0.75f, 0);
            v1.Rotate (trig);
            Vector3f v2((float)iRad, 10.75f, 0);
            v2.Rotate (trig);
            pStrut->SetPoints (sf::Vector3f(v1.x, v1.y, v1.z), sf::Vector3f(v2.x, v2.y, v2.z));
            pStrut->Render();
            pArm->AddNode (pStrut);
         }
         fAngle += fDeg;
      }
   }
   else if( iPattern == Polyp)
   {
      PartCorrection corr;
      //corr.Rotation[0] = 270; // x
      //corr.Rotation[1] = -22; // y
      RidePartLoader rpl (corr);
      float fRRLoc[4] = { 0,0,0 };
      float fRot2[4] = { 270,0,0,0 }; // polyp
      corr.SetLocation (fRRLoc);
      corr.SetRotation (fRot2);
      const char* pPath = kszPolyp;
      PartGuide guide;
      guide.Clear();
      // test data, the polyp ride
      ObjectNode* pHubNode = new ObjectNode (0, 32);
      const char* kszHub = kszPolypParts[1];
      rpl.Load3ds( pPath, kszHub, pHubNode );

      guide.fHeight = 1;
      guide.nCount = 13;
      RideNode* pHub = AddRideNodeHub (NULL, pHubNode, guide);
      pRide->SetNode (pHub);

      // spin up
      guide.fHeight = 0;
      guide.nSpeed = 135;
      guide.fDrop = 0;

      ObjectNode* pBaseNode = new ObjectNode (0, 33);
      const char* kszBase = kszPolypParts[2];
      rpl.Load3ds( pPath, kszBase, pBaseNode );
      RideNode* pRotHub = AddRideNodeRotationHub (pRide->GetController(), pHub, pBaseNode, guide);
      // Make a base
      guide.fOffset = 2;
      guide.fWidth = 2.2f;
      guide.nCount = 8;
      RideNode* pDeck2 = AddRideNodeHub (pHub, NULL, guide);
      pDeck2->SetPosition (0, 1.1f, 0);
      pDeck2->Render();
      guide.nCount = iTest;
      RideNode* pDeck = AddRideNodeDeck (pHub, NULL, guide);
      pDeck->SetPosition (0, 0, 0);

      const char* kszBody = kszPolypParts[3];
      rpl.Load3ds( pPath, kszBody, pHubNode);

      // test with 6 arms on the polyp
      const int iTest5 = 5;
      float fDeg = 360.0f / iTest5;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      float fDeg1 = 360.0f / iTest5;
      float fDegH1 = fDeg1 /2; // Half increment
      float fAngle1 = 0;
      Vector3f::VectorAngle3<float> trig(0, fDegH, 0);
      Vector3f v1(0,0,10);
      Vector3f v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));

      ObjectNode* pCarNode = new ObjectNode (0, 35);
      ObjectNode* pArmNode = new ObjectNode (0, 36);
      guide.fOffset=-30;
      const char* kszArm = kszPolypParts[5];
      const char* kszArmA = kszPolypParts[6];
      const char* kszArmB = kszPolypParts[7];
      rpl.Load3ds( pPath, kszArm, pArmNode );
      rpl.Load3ds( pPath, kszArmA, pArmNode );

      guide.fAngle = 90;//fAngle;

//      AddRideNodeArm (pRotHub, pArmNode, guide); // do the extension arm

      //guide.fAngle = 0;
      //guide.fOffset = 0;
      //guide.fHeight = 12;
      //guide.fLength = 10.0f;
      //guide.fDrop = -10.0f;
      //guide.fWidth = vx;
      //guide.trig.SetY (fDegH);
      const char* pTag1 = kszPolypParts[7];
      rpl.Load3ds( pPath, pTag1, pCarNode );


      guide.fHeight = 4;
      guide.fLength = 4.0f;
      guide.fDrop = -8.0f;
      guide.fOffset = -vx-3;
      for (int ix1 = 0; ix1 < iTest5; ++ix1)
      {
         guide.fAngle = fAngle1 + fDegH1;
         RideNode* armNode = AddRideNodeArm (pRotHub, pArmNode, guide); // do the extension arm

         PartGuide g2;
         g2.fHeight = 9;
         g2.fLength = 11.0f;
         g2.fDrop = -8.0f;
         g2.fOffset = 0;//-vx-2;
      
         for (int ix = 0; ix < iTest5; ++ix)
         {
            // Arm code

            // Building the yoke
            g2.fAngle = fAngle + fDegH;
            RideNode* pWire = AddRideNodeRotationJoint(armNode, NULL, g2); // do the hanger
            fAngle += fDeg;
            AddRideNodeCar (pWire, pCarNode, g2);
         }
         fAngle1 += fDeg1;
      }
   }
   else if (iPattern == Scrambler)
   {
      pRide->SetRideType (RT_FlatRide);
      pRide->SetRideIntensity (RI_Thrill);
      pRide->SetRideName ("Scrambler");
      PartGuide guide;
      guide.Clear();

      // base deck
      guide.fHeight = 1;
      guide.fWidth = 1; // radius
      guide.fWidthTop = 0.75f;
      guide.nCount = 8;
      RideNode* pHub = AddRideNodeHub (NULL, NULL, guide);
      pHub->Render();
      pRide->SetNode (pHub);

      // stator hub
      guide.fOffset = 0;
      guide.fWidth = 3; // radius
      guide.nCount = 9;
      RideNode* pDeck = AddRideNodeDeck (pHub, NULL, guide);
      pDeck->SetPosition(0,0,0);
      pDeck->Render();

      // spin up
      // rotating hub
      RotationHub* pHub2 = new RotationHub (pRide->GetController(), 1, 5, 7, "Chips.png");
      pHub->AddNode(pHub2);
      pHub2->SetYPosition (1.0f);
      pHub2->SetRadii (0.75f, 0.5f);
      pHub2->Render();
      pHub2->SetDesiredSpeed(15);

      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      guide.fHeight = 9;
      guide.fLength = 11.0f;
      guide.fDrop = -8.0f;
      for (int ix = 0; ix < 3; ++ix)
      {
         // Arm code

         // Building the yoke
         guide.fAngle = fAngle + fDegH;
         RideNode* pArm = new Arm (ix, 1.5f, 1.5f, 6, fAngle);
         pArm->SetPosition(0,0,0);
         pArm->Render();
         pHub2->AddNode (pArm);
         fAngle += fDeg;
         ObjectNode* pCarNode = new ObjectNode (0, 34);
         AddRideNodeSpinCar (pArm, pCarNode, guide);
      }

   }
   else if( iPattern == Octopus)
   {
      PartCorrection corr;
      float fRRLoc[4] = { 0,0,0 };
      float fRot1[4] = { 270,0,0,0 }; // polyp
      corr.SetLocation (fRRLoc);
      corr.SetRotation (fRot1);
      RidePartLoader rpl (corr);
      const char* pPath = kszOcto;
      PartGuide guide;
      guide.Clear();
      // test data, the Octo ride
      ObjectNode* pHubNode = new ObjectNode (0, 32);
      const char* kszHub = kszOctoParts[1];
      rpl.Load3ds( pPath, kszHub, pHubNode );

      guide.fHeight = 1;
      guide.nCount = 13;
      RideNode* pHub = AddRideNodeHub (NULL, pHubNode, guide);
      pRide->SetNode (pHub);

      // spin up
      guide.fHeight = 2;
      guide.nSpeed = 35;
      guide.fDrop = 0;

      ObjectNode* pBaseNode = new ObjectNode (0, 33);
      const char* kszBase = kszOctoParts[2];
      rpl.Load3ds( pPath, kszBase, pBaseNode );
      RideNode* pRotHub = AddRideNodeRotationHub (pRide->GetController(), pHub, pBaseNode, guide);
      // Make a base
      guide.fOffset = 2;
      guide.fWidth = 2.2f;
      guide.nCount = 8;
      RideNode* pDeck2 = AddRideNodeHub (pHub, NULL, guide);
      pDeck2->SetPosition (0, 1.1f, 0);
      pDeck2->Render();
      guide.nCount = iTest;
      RideNode* pDeck = AddRideNodeDeck (pHub, NULL, guide);
      pDeck->SetPosition (0, 0, 0);

      const char* kszBody = kszOctoParts[3];
      rpl.Load3ds( pPath, kszBody, pHubNode);

      // test with 4 arms on the Octo
      const int iTest5 = 4;
      float fDeg = 360.0f / iTest5;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      Vector3f::VectorAngle3<float> trig(0, fDegH, 0);
      Vector3f v1(0,0,10);
      Vector3f v2(v1);
      v2.Rotate(trig);
      v2 -= v1;
      float vx = sqrt((v2.x*v2.x) + (v2.z*v2.z));

      ObjectNode* pCarNode = new ObjectNode (0, 35);
      ObjectNode* pArmNode = new ObjectNode (0, 36);
      guide.fOffset=-3;
      const char* kszArm = kszOctoParts[4];
      const char* kszArmA = kszOctoParts[5];
      rpl.Load3ds( pPath, kszArm, pArmNode );
      rpl.Load3ds( pPath, kszArmA, pArmNode );

      guide.fAngle = 90;//fAngle;

      const char* pTag1 = kszOctoParts[6];
      float fRot2[4] = { 270,90,-30,0 }; // polyp
      corr.SetRotation (fRot2);
      rpl.Load3ds( pPath, pTag1, pCarNode );

      guide.fOffset = 10;
      for (int ix = 0; ix < iTest5; ++ix)
      {
         // Arm code

         guide.fAngle = fAngle + fDegH;
         AddRideNodeArm (pRotHub, pArmNode, guide); // do the extension arm
         // Building the yoke
         RideNode* pWire = AddRideNodeRotationJoint(pRotHub, NULL, guide); // do the hanger
         pWire->SetPosition (0, 3, 0);
         fAngle += fDeg;
         RideNode* pCar = AddRideNodeCar (pWire, pCarNode, guide);
         pCar->SetPosition (0, 0, 10);
      }
   }
   else if( iPattern == Enterprise)
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
      RideNode* pRotHub = AddRideNodeRotationHub (pRide->GetController(), pHubNode, NULL, guide);

      // put what ever tub, arm assembly or deck here
      // test with 8 arms, the laundery ride
      float fDeg = 360.0f / iTest;
      float fDegH = fDeg /2; // Half increment
      float fAngle = 0;
      Vector3f::VectorAngle3<float> trig(0, fDegH, 0);
      Vector3f v1(0,0,13.25);
      Vector3f v2(v1);
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
      guide.trig.Set (0, fDegH, 0);

      for (int ix = 0; ix < iTest; ++ix)
      {
         guide.fAngle = fAngle;
         fAngle += fDeg;

         AddRideNodeHub (pRotHub, NULL, guide);
      }
   }

   return pRide;
}

void FlatRideBuilder::OnHit (int hit)
{
   // hit delegate [tool selection, select part, navigation]
}

void FlatRideBuilder::OnMove (const Vector3f& vec)
{
   // move delegate
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
      pHub->SetRadii (guide.fWidth, guide.fWidthTop);
      pHub->Render();
   }
   else
   {
      pHub = new Hub (guide.fHeight, guide.nCount, pGraphicObject);
      pHub->SetRadii (guide.fWidth, guide.fWidthTop);
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

RideNode* FlatRideBuilder::AddRideNodeSpinCar (RideNode* pParent, ObjectNode* pGraphicObject, PartGuide& guide)
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
   Carriage* pWire = new Carriage();
   Vector3f v1(0, 0, -(guide.fWidth) * 2);
   Vector3f v2(0, 0, 0);
   Vector3f v3(0, guide.fDrop, -(guide.fWidth));
   Vector3f v4(11.0f, guide.fHeight, -(guide.fWidth+0.5f));
   v4.Rotate (guide.trig);
   pWire->Render();
   pParent->AddNode (pWire);
   return pWire;
}

RideNode* FlatRideBuilder::AddRideNodeCableHinge (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   CableHingeJoint* pWire = new CableHingeJoint();
   Vector3f v1(0, 0, -(guide.fWidth) * 2);
   Vector3f v2(0, 0, 0);
   Vector3f v3(0, guide.fDrop, -(guide.fWidth));
   pWire->SetPoints (sf::Vector3f(v1.x, v1.y, v1.z), sf::Vector3f(v3.x, v3.y, v3.z), sf::Vector3f(v2.x, v2.y, v2.z));
   Vector3f v4(11.0f, guide.fHeight, -(guide.fWidth+0.5f));
   v4.Rotate (guide.trig);
   pWire->SetYAngle (guide.fAngle);
   pWire->SetPosition (sf::Vector3f(v4.x, v4.y, v4.z));
   pWire->Render();
   pParent->AddNode (pWire);
   return pWire;
}

RideNode* FlatRideBuilder::AddRideNodeRotationJoint (RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   RotationJoint* pWire = new RotationJoint();
   Vector3f v2(0, 0, -(guide.fWidth) * 2);
   Vector3f v1(0, 0, 0);
   Vector3f v3(0, guide.fDrop, -(guide.fWidth));
   //pWire->SetPoints (sf::Vector3f(v1.x, v1.y, v1.z), sf::Vector3f(v3.x, v3.y, v3.z), sf::Vector3f(v2.x, v2.y, v2.z));
   Vector3f v4(11.0f, guide.fHeight, -(guide.fWidth+0.5f));
   v4.Rotate (guide.trig);
   pWire->SetYAngle (guide.fAngle);
   pWire->SetPosition (sf::Vector3f(v4.x, v4.y, v4.z));
   pWire->Render();
   pParent->AddNode (pWire);
   return pWire;
}

RideNode* FlatRideBuilder::AddRideNodeRotationHub (RideController* pRCU, RideNode* pParent, ObjectBase* pGraphicObject, PartGuide& guide)
{
   RotationHub* pHub2 = new RotationHub (pRCU, guide.TakeANumber(), guide.fHeight, guide.nCount, "Chips.png");
   pParent->AddNode (pHub2);
   pHub2->SetRadii (guide.fWidth, guide.fWidthTop);
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
