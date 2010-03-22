//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "CamPath.h"
#include "Ride.h"
#include "RideSection.h"
#include "RideNode.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"

Ride::Ride(const Vector3f& vPosition, const Park& ParkParent)
:  CoreBase ( vPosition, Vector3f(0,0,0))
,  mParkParent (ParkParent)
{
   mvPosition = sf::Vector3f(0,0,0);
}

Ride::~Ride(void)
{
}

void Ride::Update(int dt)
{
   mpBaseNode->Update(dt);
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
