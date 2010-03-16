//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  LiftArm class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

// motor drive 
#include <string>
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
#include "../Graphics/TexturedMesh.h"
#include "LiftArm.h"


#define _USE_MATH_DEFINES
#include <math.h>
namespace CoreObjects
{
   struct pair { float x; float z; };
   pair LiftPairs[] =
   {
      { 0, -0.5f },
      { 0, -0.4f },
      { 0.75f, -0.5f },
      { 0.75f, -0.4f },
      { 1.0f, -0.1f },
      { 0.8f, 0 },
      { 1.0, 0.1f },
      { 0.8f, 0 },
      { 0.75f, 0.5f },
      { 0.75f, 0.4f },
      { 0, 0.5f },
      { 0, 0.4f }
   };
}

using namespace CoreObjects;

// physics, create a pneumatic verion that ocsilates.
// simple ocs with mapped sin values 16 element array, diminishing amplitube one step at a time. IE (6,-5, 4,-3,2,-1,0)
// this will make the Jump and Tagada look cool
// linear physics will also need this for the drop tower.

LiftArm::LiftArm (int ID, float length, float width, const char* TexName)
:  ServoPhysics (0, 2000.0f, 1000.0f)
{
   mIdle = 10;
   mRun = 0;
   mSides = 7;
   mDesiredAngle = 0;
   mvPosition.x = 0;
   mvPosition.y = 0;
   mvPosition.z = 0;
   mWidth = width;
   mLength = length;
   mpGraphic = new TexturedMesh (7,4,Gfx::ImageManager::GetInstance()->GetTexture(TexName, 3), 0x98b0b0b8, ObjectFactory::TakeANumber());
}

LiftArm::~LiftArm(void)
{
   if(mpGraphic != NULL)
   {
      delete mpGraphic;
   }
}

void LiftArm::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, 0, mvPosition.z );										// Move to the arc end of the arm 
	glRotatef(mPosition, 1.0f, 0.0f, 0.0f);
   mpGraphic->Draw();
   glTranslatef( 0, 0, mLength );										// Move to the arc end of the arm 
   RideNode::Draw();
   glPopMatrix();
}

void LiftArm::Render()
{
//   using namespace CoreObjects;
   int index = 0;
   for( int ix = 0; ix < mSides; ++ix )  // 7 x 4
   {
      CVPoint pt (LiftPairs[index].z*mWidth, -0.5f, LiftPairs[index].x*mLength);
      mpGraphic->AddPoint (pt.GetVector3f());
      pt = CVPoint  (LiftPairs[index].z*mWidth, 0.5f, LiftPairs[index].x*mLength);
      mpGraphic->AddPoint (pt.GetVector3f());
      index++;

      pt = CVPoint  (LiftPairs[index].z*mWidth, 0.5f, LiftPairs[index].x*mLength);
      mpGraphic->AddPoint (pt.GetVector3f());
      pt = CVPoint (LiftPairs[index].z*mWidth, -0.5f, LiftPairs[index].x*mLength);
      mpGraphic->AddPoint (pt.GetVector3f());
      index++;
   }
}


void LiftArm::Update(int dt)
{
   static int mode = 0;
   if( mRun > 0)
   {
      mRun--;
      Integrate (1);//(float)dt);
   }
   else if( mRun < 0)
   {
      mRun++;
      Integrate (1);//(float)dt);
   }
   else if( mIdle > 0)
   {
      mIdle--;
      Integrate (1);//(float)dt);
   }
   else
   {
      switch (mode)
      {
      case 0:
         SetDesiredAngle( -90 );
         // raise the assembly
         mode = 1;
         mIdle = 0;
         mRun = 90*dt;
         break;
      case 1:
         mode = 2;
         mIdle = 60*dt;
      case 2:
         // lower the assembly
         SetDesiredAngle( 0 );
         mode = 3;
         mIdle = 0;
         mRun = -90*dt;
         break;
      default:
         // go idle
         mode = 0;
         mIdle = 32*dt;
      }
   }
   RideNode::Update (int (dt));
}
