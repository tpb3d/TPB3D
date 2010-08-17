//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  WobbleHub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

// motor drive 
#include <string>
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include "../Types/Vector3.h"
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedMesh.h"
#include "RideController.h"
#include "WobbleHub.h"


#define _USE_MATH_DEFINES
#include <math.h>

WobbleHub::WobbleHub (RideController* pRCU, int ID, float height, short sides, const char* TexName)
:  Hub (height, sides, TexName)
,  RotationPhysics (0, 0.1f, 2000.0f, 1000.0f)
{
   mpRCUnit = pRCU;
   mpRCUnit->Register (this);  // Connect this Wobbleal assembly to the Ride Control Unit (motor physics);
   mIdle = 10;
   mRun = 0;
   mDesiredSpeed = 5;
   mvPosition.x = 0;
   mvPosition.y = 0;
   mvPosition.z = 0;
   mRadii[0] = 2.75f;
   mRadii[1] = 2.75f;
   mpGraphic = ObjectFactory::CreateTexturedMesh (2, 2, TexName, 0x98b0b0b8 );
}

WobbleHub::WobbleHub (RideController* pRCU, int ID, float height, short sides, ObjectBase* pGraphics)
:  Hub (height, sides, "darkwood.png")
,  RotationPhysics (0, 0.1f, 2000.0f, 1000.0f)
,  mpGraphic (pGraphics)
{
   mpRCUnit = pRCU;
   mpRCUnit->Register (this);  // Connect this Wobbleal assembly to the Ride Control Unit (motor physics);
   mIdle = 10;
   mRun = 0;
   mDesiredSpeed = 5;
   mvPosition.x = 0;
   mvPosition.y = 0;
   mvPosition.z = 0;
   mRadii[0] = 2.75f;
   mRadii[1] = 2.75f;
}

WobbleHub::~WobbleHub(void)
{
   mpRCUnit->Unregister(this);
}

void WobbleHub::Draw()
{
   //Integrate(22);
   mvAngle.y = mVelocity;
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);

   mpGraphic->Draw();
   RideNode::Draw();
   glPopMatrix();
}

void WobbleHub::Render()
{
//   using namespace CoreObjects;
   double dRad = 0.0;
   double dDeg = 360.0/ (mSides-1);
   for( int idx = 0; idx < mSides; ++idx )
   {
      float fTheta = (float)(M_PI/180 * dRad);
      Vector3f pt (cos(fTheta) * this->mRadii[0], 0, sin(fTheta)* this->mRadii[0]);
      mpGraphic->AddPoint (pt);
      dRad += dDeg;
      pt = Vector3f (cos(fTheta) * this->mRadii[1], 0 + mHeight, sin(fTheta)* this->mRadii[1]);
      mpGraphic->AddPoint (pt);
   }
}


void WobbleHub::Update(int dt)
{
   if(this->mVelocity > 0)
   {
      Integrate (1);//(float)dt);
   }
}
