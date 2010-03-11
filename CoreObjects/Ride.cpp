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

Ride::Ride(void)
:  ObjectNode( 1, ObjectFactory::TakeANumber() )
{
   mLocation[0] = 0;
   mLocation[1] = 0;
   mLocation[2] = 0;
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

ObjectNode* Ride::Clone( )
{
   Ride* pRide = new Ride();
   return pRide;
}


void Ride::Load(SerializerBase& ser)
{
   RideSection* pRideSection = new RideSection();
   pRideSection->Load(ser);
}

void Ride::Save(SerializerBase& ser)
{
   ser.Add("type", "Ride");
   ser.Add("angle",mAngle);
   ser.Add("ID", mID);
//   delete pSer;
}