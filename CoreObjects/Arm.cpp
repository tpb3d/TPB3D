//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Arm class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  Structural Elemant that extends from a ride hub or axis with a carriage, car or other ride part at the other end.
//  Movable or Stationary. Think Biplanes, Octopus, monster

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/vector3.h"
#include "../Graphics/VPoint.h"
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "Arm.h"

Arm::Arm (int ID, float offset, float depth, float length, float angle)
:  RideNode()
,  TexturedMesh (2,2,Gfx::ImageManager::GetInstance()->GetTexture("Arm.png",4), 0x98b0b0b8, ObjectFactory::TakeANumber())
{
   mArmID = ID;
   mOffset = offset;
   mDepth = depth;
   mLength = length;
   mAngle = angle;
}

Arm::~Arm (void)
{
}

void Arm::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y+1.25f, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);
   TexturedMesh::Draw();
   RideNode::Draw();
   glPopMatrix();
}

void Arm::DrawSelectionTarget()
{
}

void Arm::Render()
{
   float ep = 1.0f * 0.125f;
   STrig trig(0, mAngle, 0, 1.0);
   CVPoint pt (mOffset, -0.125, 0);
   CVPoint ptr = pt;
   ptr.Rotate(trig);
   AddPoint (ptr.GetVector3f());
   pt.y += mDepth;
   ptr = pt;
   ptr.Rotate(trig);
   AddPoint (ptr.GetVector3f());
   pt.x += mLength;
   ptr = pt;
   ptr.Rotate(trig);
   AddPoint (ptr.GetVector3f());
   pt.y -= ep;
   ptr = pt;
   ptr.Rotate(trig);
   AddPoint (ptr.GetVector3f());
}

ObjectBase* Arm::Clone()
{
   Arm* pArm = new Arm(mArmID, mOffset, mDepth, mLength, mAngle);
   return pArm;
}
