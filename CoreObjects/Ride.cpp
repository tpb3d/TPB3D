//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "CamPath.h"
#include "Ride.h"
#include "RideSection.h"
#include "RideNode.h"
#include "RideController.h"
#include "../People/Person.h"
#include "PersonQueue.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"

Ride::Ride(const Vector3f& vPosition, const Park& ParkParent)
:  CoreBase ( vPosition, Vector3f(0,0,0))
,  mParkParent (ParkParent)
{
   mpRCU = NULL;
   mSeats = 2;
   mRunTime = 0;
   mMaxRunTime = 3000;
   mpQueue = new PersonQueue(this);
   const float fLoc[] = {45,1,0};
   mpQueue->Move (fLoc);
   mvPosition = sf::Vector3f(0,0,0);
   mRideType = RT_Empty;
   mRideIntensity = RI_Gentle;
   mRun = false;
}

Ride::~Ride(void)
{
   delete mpQueue;
}

RideController* Ride::GetController()
{
   if ( mpRCU == NULL)
   {
      mpRCU = new RideController(1);
   }
   return mpRCU;
}

void Ride::Update(int dt)
{
   if (mRun)
   {
      mpBaseNode->Update(dt);
      if (mpRCU->IsRunning())
      {
         mRunTime += dt;
         if (mRunTime > this->mMaxRunTime)
         {
            mpRCU->Stop();
         }
      }
      else
      {
         if (mpRCU->IsStopped())
         {
            mpRCU->UnlockRestraints();
            UnloadPeople();
         }
      }
   }
   else
   {
      mpBaseNode->Update(0);  // temporary
      if (mpQueue->Count() > 0 && mRiders.size() < mSeats)
      {
         ServeNextPerson();
      }
      else
      {
         if (mRiders.size() > 0)
         {
            mpRCU->Start();
            mRun = true;
         }
      }
   }
}

void Ride::DrawSelectionTarget()
{
}

void Ride::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);

   mpBaseNode->Draw();
   glPopMatrix();
}

CoreBase* Ride::Clone( )
{
   Ride* pRide = new Ride (Vector3f(mvPosition.x,mvPosition.y,mvPosition.z), this->mParkParent);
   return pRide;
}

void Ride::AddPerson (Person* pPeep)
{
   mpQueue->AddPerson(pPeep);
}

void Ride::RemovePerson (Person* pPeep)
{

   mpQueue->RemovePerson(pPeep);
}

void Ride::ServeNextPerson (void)
{
   Person* pPeep = mpQueue->TakeNextPerson();
   if (pPeep != NULL)
   {
      // TakeOrder;
      // Serve or Reject
      pPeep->SetActivity (Person::AS_Riding);   // this is just some interaction
      pPeep->SetCurrentState (Person::CS_Riding);
      mRiders.push (pPeep);
   }
}

void Ride::UnloadPeople()
{
   while (mRiders.size() > 0)
   {
      Person* pPeep = mRiders.back();
      mRiders.pop();
      pPeep->SetActivity (Person::AS_None);
      pPeep->SetCurrentState (Person::CS_Disembarking);
   }
}

void Ride::Load(SerializerBase& ser)
{
   RideSection* pRideSection = new RideSection();
   pRideSection->Load(ser);
}

void Ride::Save(SerializerBase& ser)
{
   ser.Add ("type", "Ride");
   ser.Add ("positionX",mvPosition.x);
   ser.Add ("positionY",mvPosition.y);
   ser.Add ("positionZ",mvPosition.z);
   ser.Add ("angleX",mvAngle.x);
   ser.Add ("angleY",mvAngle.y);
   ser.Add ("angleZ",mvAngle.z);
   ser.Add ("ID", mID);
//   delete pSer;
}
