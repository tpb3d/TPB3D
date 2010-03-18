//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  CarouselAssembly class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  Structural Elemant that extends from a ride hub or axis with a carriage, car or other ride part at the other end.
//  Movable or Stationary. Think Biplanes, Octopus, monster

#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/vector3.h"
#include "../Graphics/VPoint.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/ObjectFactory.h"
#include "CarouselAssembly.h"

// Crank code
#define _USE_MATH_DEFINES
#include <math.h>

void CarouselAssembly::PresetCrank()
{
   mCrankPos1 = 0;
   mCrankPos2 = 18;
   double dRad = 0.0;
   double dDeg = 360.0/ 36;
   for( int ix = 0; ix <36; ++ix)
   {
      double dTheta = M_PI/180 * dRad;
      CVPoint pt (cos(dTheta) * 1.0, 0, sin(dTheta)* 1.0);
      dRad += dDeg;
      mRockAngle[ix] = pt.x * 2;
      mHeights[ix] = pt.z*0.5f;
   }
}
// end crank code

CarouselAssembly::CarouselAssembly (int ID, float offset, float depth, float length, float angle)
:  RideNode()
{
   mCarouselAssemblyID = ID;
   mOffset = offset;
   mDepth = depth;
   mLength = length;
   mAngle = angle;
   PresetCrank();
   mpGraphic = ObjectFactory::CreateTexturedStrip (12, "Chips.png", 0x98b0b0b8);
}

CarouselAssembly::~CarouselAssembly (void)
{
}

void CarouselAssembly::Update(int dt)
{
   mCrankPos1+=1;
   if( mCrankPos1 > 35) mCrankPos1 -= 36;
   mCrankPos2+=1;
   if( mCrankPos2 > 35) mCrankPos2 -= 36;
}

void CarouselAssembly::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y+1.25f, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);
   mpGraphic->Draw();
   RideNode::RideNodeIterator ir;
   float pos = 0;
   float ang = 0;
   int cc = 0;
   glTranslatef( 0, -13.125, 0 );										// Move Left 1.5 Units And Into The Screen 6.0
   for (ir = mBaseParts.begin(); ir != mBaseParts.end(); ir++)
   {
      int cp = (cc & 0x01) ? mCrankPos1 : mCrankPos2;
      cc++;
      ang = mRockAngle[cp];
      pos = mHeights[cp];
    	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
      glTranslatef( 0, pos, 0 );										// Move Left 1.5 Units And Into The Screen 6.0
   	glRotatef(ang,0.0f,0.0f,1.0f);
      RideNode* pB = *(ir);
      pB->Draw ();
      glPopMatrix();
   }
//   RideNode::Draw();
   glPopMatrix();
}

void CarouselAssembly::DrawSelectionTarget()
{
}

void CarouselAssembly::Render()
{
   float ep = 1.0f * 0.125f;
   STrig trig(0, mAngle, 0, 1.0);
   CVPoint pt (mOffset, -0.125, 0);
   CVPoint ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr.GetVector3f());
   pt.y += mDepth;
   ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr.GetVector3f());
   pt.x += mLength;
   ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr.GetVector3f());
   pt.y -= ep;
   ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr.GetVector3f());
}

//ObjectBase* CarouselAssembly::Clone()
//{
//   CarouselAssembly* pCarouselAssembly = new CarouselAssembly(mCarouselAssemblyID, mOffset, mDepth, mLength, mAngle);
//   return pCarouselAssembly;
//}
