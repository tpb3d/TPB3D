//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Arm class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  Structural Elemant that extends from a ride hub or axis with a carriage, car or other ride part at the other end.
//  Movable or Stationary. Think Biplanes, Octopus, monster

#include "../Storage/SerializerBase.h"
#include "../Types/Vector3.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedMesh.h"
#include "../Graphics/ObjectFactory.h"
#include "Arm.h"

// temp
#include "../Graphics/TexturedMesh.h"

Arm::Arm (int ID, float offset, float depth, float length, float angle)
:  RideNode()
{
   mArmID = ID;
   mOffset = offset;
   mDepth = depth;
   mLength = length;
   mAngle = angle;
   mpGraphic = ObjectFactory::CreateTexturedMesh (2, 2, "Arm.png", 0x98b0b0b8 );
}

Arm::Arm (int ID, float offset, float depth, float length, float angle, ObjectBase* pGfx)
:  RideNode()
,  mpGraphic (pGfx)
{
   mArmID = ID;
   mOffset = offset;
   mDepth = depth;
   mLength = length;
   mAngle = angle;
   mvAngle.y = angle;
}

Arm::~Arm (void)
{
   if(mpGraphic != NULL)
   {
      delete mpGraphic;
   }
}

void Arm::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y+1.25f, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);
   mpGraphic->Draw();
   RideNode::Draw();
   glPopMatrix();
}

void Arm::DrawSelectionTarget(int mode)
{
}

void Arm::Render()
{
   float ep = 1.0f * 0.125f;
   Vector3f::VectorAngle3<float> trig(0, mAngle, 0);
   Vector3f pt (mOffset, -0.125f, 0);
   Vector3f ptr (pt);
   ptr.Rotate(trig);
   //mpGraphic->AddPoint (ptr.GetVector3f());
   pt.y += mDepth;
   ptr = pt;
   ptr.Rotate(trig);
   //mpGraphic->AddPoint (ptr.GetVector3f());
   pt.x += mLength;
   ptr = pt;
   ptr.Rotate(trig);
   //mpGraphic->AddPoint (ptr.GetVector3f());
   pt.y -= ep;
   ptr = pt;
   ptr.Rotate(trig);
   //mpGraphic->AddPoint (ptr.GetVector3f());
}

//ObjectBase* Arm::Clone()
//{
//   Arm* pArm = new Arm(mArmID, mOffset, mDepth, mLength, mAngle);
//   return pArm;
//}
