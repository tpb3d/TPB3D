//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RotationHub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
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
#include "RotationHub.h"


#define _USE_MATH_DEFINES
#include <math.h>

RotationHub::RotationHub (int ID, float height, short sides, const char* TexName)
:  Hub (height, sides, TexName)
,  RotationPhysics (0, 0.1f, 2000.0f, 1000.0f)
{
   mIdle = 10;
   mRun = 0;
   mDesiredSpeed = 5;
   mvPosition.x = 0;
   mvPosition.y = height;
   mvPosition.z = 0;
   mRadii[0] = 2.75f;
   mRadii[1] = 2.75f;
}

RotationHub::~RotationHub(void)
{
}

void RotationHub::Draw()
{
   //Integrate(22);
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);

   mpGraphic->Draw();
   RideNode::Draw();
   glPopMatrix();
}

void RotationHub::Render()
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


void RotationHub::Update(int dt)
{
   if( mRun > 0)
   {
      mRun--;
      mIdle = 0;
      Integrate (1);//(float)dt);
      mvAngle.y = mPosition;
   }
   else if( mIdle > 0)
   {
      mIdle--;
      Integrate (1);//(float)dt);
      mvAngle.y = mPosition;
   }
   else
   {
      if(this->mVelocity > 0)
      {
         SetDestinVelocity( 0 );
         mIdle = 32*dt;
      }
      else if(dt > 0) // temporary fix to stop ride
      {
         SetDestinVelocity (mDesiredSpeed);
         mRun = 60*dt;
      }
   }
   if(this->mVelocity > 0)
   {
      RideNode::Update (int (mVelocity));
   }
}
