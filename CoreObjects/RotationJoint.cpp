//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RotationJoint class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <string>
#include "RotationJoint.h"

RotationJoint::RotationJoint ()
{
   mAngle = 0;
   mWeight = 500;
   mDistance = 5; 
   mLength = 4;
//   mpGraphic = ObjectFactory::CreateTexturedStrip (3, "basemetal.png", 0x98b0b0b0);
}

RotationJoint::~RotationJoint (void)
{
}

void RotationJoint::SetForce(float Velocity)
{
   mAngle = Velocity * (mWeight/100) / mDistance;  // Fc = sm2/r
   mAngle -= mAngle * (mLength * mLength) / mWeight;
}

void RotationJoint::Update(int dt)  // add the other physics beside centrifugal
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

void RotationJoint::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   //mpGraphic->Draw();
   glTranslatef( mV1.x, mV1.y, mV1.z );
	glRotatef(mYAngle,0.0f,1.0f,0.0f);
   RideNode::Draw(); 
   glPopMatrix();
}

void RotationJoint::DrawSelectionTarget(int mode)
{
}

void RotationJoint::Render()
{
//   sf::Vector3f tv = mV1;
//   mpGraphic->AddPoint (tv);
}
