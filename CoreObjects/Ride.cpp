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
#include "../People/Person.h"
#include "PersonQueue.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"

Ride::Ride(const Vector3f& vPosition, const Park& ParkParent)
:  CoreBase ( vPosition, Vector3f(0,0,0))
,  mParkParent (ParkParent)
{
   mpQueue = new PersonQueue(this);
   mvPosition = sf::Vector3f(0,0,0);
   mRideType = RT_Empty;
   mRideIntensity = RI_Gentle;
   mRun = false;
}

Ride::~Ride(void)
{
   delete mpQueue;
}

void Ride::Update(int dt)
{
   if (mRun)
   {
      mpBaseNode->Update(dt);
   }
   else
   {
      mpBaseNode->Update(0);  // temporary
   }
   if (mpQueue->Count() > 0 )
   {
      ServeNextPerson();
      mRun = true;
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
