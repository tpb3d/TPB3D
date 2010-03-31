//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  CableHingeJoint class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectFactory.h"
#include "../Graphics/TexturedStrip.h"
#include "CableHingeJoint.h"

CableHingeJoint::CableHingeJoint ()
{
    mAngle = 0;
    mWeight = 500;
    mDistance = 5; 
    mLength = 4;
    mpGraphic = ObjectFactory::CreateTexturedStrip (3, "basemetal.png", 0x98b0b0b0);
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
      SetForce((float)dt);
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
   //mpGraphic->Draw();
   glTranslatef( mV2.x, mV2.y, mV2.z );
   RideNode::Draw(); 
   glPopMatrix();
}

void CableHingeJoint::Render()
{
   sf::Vector3f tv = mV1;
   mpGraphic->AddPoint (tv);
   tv.z += 0.1f;
   mpGraphic->AddPoint (tv);
   tv = mV2;
   mpGraphic->AddPoint (tv);
   tv.y += 0.05f;
   tv.z += 0.05f;
   mpGraphic->AddPoint (tv);
   tv = mV3;
   mpGraphic->AddPoint (tv);
   tv.z += 0.1f;
   mpGraphic->AddPoint (tv);
}
