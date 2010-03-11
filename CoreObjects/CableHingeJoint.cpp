//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  CableHingeJoint class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/VPoint.h"
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "CableHingeJoint.h"

CableHingeJoint::CableHingeJoint ()
:  TexturedStrip (3,Gfx::ImageManager::GetInstance()->GetTexture("basemetal.png",4), 0x98b0b0b0) //, ObjectFactory::TakeANumber())
{
    mAngle = 0;
    mWeight = 500;
    mDistance = 5; 
    mLength = 4;
}

CableHingeJoint::~CableHingeJoint (void)
{
}

void CableHingeJoint::SetForce(float Velocity)
{
   mAngle = Velocity * (mWeight/100) / mDistance;  // Fc = sm2/r
   mAngle -= mAngle * (mLength * mLength) / mWeight;
}

void CableHingeJoint::Update(int dt)  // add the other physics beside centrifugal
{
   if(dt > 0)
   {
      SetForce(dt);
   }
   else
   {
      mAngle = 0;
   }
}

void CableHingeJoint::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
	glRotatef(mYAngle,0.0f,1.0f,0.0f);
   glTranslatef( mvPosition.x, mvPosition.y, mvPosition.z );
	glRotatef(mAngle,0.0f,0.0f,1.0f);
   TexturedStrip::Draw();
   RideNode::Draw(); 
   glPopMatrix();
}

void CableHingeJoint::Render()
{
   sf::Vector3f tv = mV1;
   AddPoint (tv);
   tv.z += 0.1f;
   AddPoint (tv);
   tv = mV2;
   AddPoint (tv);
   tv.y += 0.05f;
   tv.z += 0.05f;
   AddPoint (tv);
   tv = mV3;
   AddPoint (tv);
   tv.z += 0.1f;
   AddPoint (tv);
}
