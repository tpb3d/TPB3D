//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Storage/SerializerBase.h"
#include "../Physics/MotionPhysics.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Image.h"
#include "../Graphics/ObjectTree.h"
#include "../Scene/Scene.h"
#include "../People/Person.h"
#include "Routes.h"
#include "CoreBase.h"
#include "Pathway.h"
#include "Car.h"
#include "Ride.h"
#include "Stall.h"
#include "Park.h"

// even more test code
namespace Test
{
   sf::Vector3f mVPoints[2048];
   sf::Vector3f mVAngles[2048];
}

Park::Park (int ParkNo, int other, Scene& rScene )
:  mParkNo (ParkNo)
,  mScene(rScene)
,  mGhostObject (Vector3f(0,0,0),0)
{
   mpTheTree = new ObjectTree(1);
   mPopulation = 0;
   mPoints = 0;
   mCurPoint = 0;

   mpParkEntrance = new Pathway(Vector3f(-30.0f, 1.0f, 349.0f), this, "Stone.png");
   mpParkEntrance->Rotate( Vector3f(0, 90, 0) );
}

Park::~Park( )
{
   try
   {
      ClearStalls();
      // ClearRides();
      delete mpParkEntrance;
      //delete mpTheTree;
   }
   catch (...)
   {
      // might want to do something before the whole park is sucked into a black hole.
   }
}

void Park::AddTestPoint( sf::Vector3f pa, sf::Vector3f pb )
{
   Test::mVPoints[mPoints]=pa;
   Test::mVAngles[mPoints++]=pb;
}

void Park::Update (float dt, int timeOfDay)
{
   static int delay = 3; // playing physics

   mpTheTree->Update(dt);
   mGhostObject.GetPathNo();
   mGhostObject.Update (this);

   if( mCurPoint <= mPoints )
   {
      if( mCurPoint < mPoints )
      {
         //m_xcam = m_VPoints[m_CurPoint].x;
         //m_ycam = (m_VPoints[m_CurPoint].y + 4.0 )*-1;
         //m_zcam = m_VPoints[m_CurPoint].z;
         //m_xrot = m_VAngles[m_CurPoint].x;
         //m_yrot = m_VAngles[m_CurPoint].y + 180;
         //m_zrot = m_VAngles[m_CurPoint].z;
         mpCar->Position( Test::mVPoints[mCurPoint], Test::mVAngles[mCurPoint] );
      }
      else
      {
         //m_Camera.x = m_xcam;
         //m_Camera.y = m_ycam;
         //m_Camera.z = m_zcam;
      }
      mCurPoint++;
   }
   else
   {
      mCurPoint = 0;
   }
   mRides.Update(dt, timeOfDay);
   mStalls.Update(dt, timeOfDay);
   //RidesIterator iRI;
   //for (iRI = mRides.begin(); iRI != mRides.end(); iRI++)
   //{
   //   Ride* pRide = *iRI;
   //   pRide->Update ((int)dt);
   //}
}

void Park::AddPath(Pathway *path) {
   mPaths.push_back(path);
}

void Park::AddStall (Stall* pStall)
{
   mStalls.push_back (pStall);
}

Stall* Park::FindStallByType (StallType st)
{
   return mStalls.FindStallByType (st);
   //StallsIterator iSI;
   //for (iSI = mStalls.begin(); iSI != mStalls.end(); iSI++)
   //{
   //   Stall* pStall = *iSI;
   //   if (pStall->IsType (st) )
   //   {
   //      return pStall;
   //   }
   //}
   //return NULL;
}

void Park::ClearStalls()
{
   while (mStalls.end() != mStalls.begin())
   {
      Stall* pBase = *(mStalls.end()-1);
      delete pBase;
      mStalls.pop_back();
   }
}

void Park::AddRide (Ride* pRide)
{
   mRides.AddRide (pRide);
}

Ride* Park::FindRideByType (RideType rt)
{
   return mRides.FindRideByType (rt);
   //RidesIterator iRI;
   //for (iRI = mRides.begin(); iRI != mRides.end(); iRI++)
   //{
   //   Ride* pRide = *iRI;
   //   if (pRide->IsType (rt) )
   //   {
   //      return pRide;
   //   }
   //}
   //return NULL;
}

Ride* Park::FindRideByName (const char *pszName)
{
    return mRides.FindRideByName(pszName);
//   RidesIterator iRI;
//   for (iRI = mRides.begin(); iRI != mRides.end(); iRI++)
//   {
//      Ride* pRide = *iRI;
//      if (_stricmp(pRide->GetRideName(), pszName) == 0)
//      {
//         return pRide;
//      }
//   }
//   return NULL;
}

void Park::Draw ()
{

   mpTheTree->Draw ();
   mpParkEntrance->Draw();
   mStalls.Draw ();
   mRides.Draw ();

   vector<Person*>::iterator peeps;
   for (peeps = mPeopleInPark.begin(); peeps != mPeopleInPark.end(); peeps ++)
   {
      Person* pPeep = *peeps;
      pPeep->Draw();
   }
   //   mGhostObject.Draw();
}

void Park::DrawSelectionTarget (bool bPathwaysOnly)

{
//   mRoutes.DrawSelectionTarget(); do these later
}

// AI interface
void Park::EnterPark (Person* pPerson)
{
   mPopulation++;
   mPeopleInPark.push_back(pPerson);

   // Test code for Ride Operations to put every new park guest onto the BarnStormers
   //Ride* pRide = this->FindRideByName("Barn Stormers");
   //if (pRide != NULL)
   //{
   //   pRide->AddPerson (pPerson);
   //}
}

// AI interface
void Park::LeavePark (Person* pPerson)
{
   // when implemented, this function will take people out of the building, walking, bus, train etc.
   mPopulation--;
   if (mPopulation < 0 )
      mPopulation = 0;
}

// Serialization
void Park::Load(SerializerBase& ser)
{
   SerializerBase* pSer = ser.GetFirstChild ("Stalls");
   while (pSer != NULL)
   {
      int ist = pSer->GetInt ("stall type");
      StallType st = (ist > ST_Empty && ist <= ST_Information) ? StallType(st) : ST_Empty;
      Stall* pStall = new Stall (0, pSer->GetInt("id"), st);
      mStalls.push_back (pStall);
      pSer = ser.GetNextSibling ("Stalls");
   }
}

void Park::Save(SerializerBase& ser)
{
   ser.Add("park name", "First Park");
   SerializerBase* pSer = ser.Spawn("Stalls"); // create a locale serializer of the type used for Stall
   StallCollection::iterator si;
   for (si = mStalls.begin(); si != mStalls.end(); ++si)
   {
      (*si)->Save(*pSer);
   }
   delete pSer;
}
