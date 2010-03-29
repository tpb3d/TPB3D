//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  HorizontalCrankHub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  Structural Elemant thah provides recipital motion.
//  The journal is mounted to the ride hub or base.
//  The bell crank has one or many rod-arms attached.
//  This includes the spiders and octopus.

#include "../Storage/SerializerBase.h"
#include "../Types/Vector3.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/ObjectFactory.h"
#include "HorizontalCrankHub.h"

// Crank code
// TODO: similar code in carousel assembly may be merged.
#define _USE_MATH_DEFINES
#include <math.h>

void HorizontalCrankHub::PresetCrank()
{
   mCrankPos = 0;
   double dRad = 0.0;
   double dDeg = 360.0/ kCrankPositions;
   for( size_t ix = 0; ix <kCrankPositions; ++ix)
   {
      double dTheta = M_PI/180 * dRad;
      Vector3f pt ((float)(cos(dTheta) * 1.25), 0, (float)(sin(dTheta)* 1.25f));
      dRad += dDeg;
      mRockAngle[ix] = pt.x * 2;
      mHeights[ix] = pt.z*0.5f;
   }
}
// end crank code

HorizontalCrankHub::HorizontalCrankHub (int ID, float offset, float depth, float length, float angle)
:  RideNode()
{
   mHorizontalCrankHubID = ID;
   mOffset = offset;
   mDepth = depth;
   mLength = length;
   mAngle = angle;
   PresetCrank();
   mpGraphic = ObjectFactory::CreateTexturedStrip (12, "Chips.png", 0x98b0b0b8);
}

HorizontalCrankHub::~HorizontalCrankHub (void)
{
}

void HorizontalCrankHub::Update(int dt)
{
   if (dt > 0)
   {
      mCrankPos+=1;
      if (mCrankPos >= kCrankPositions) mCrankPos -= kCrankPositions;
   }
   else
   {
      mCrankPos-=1;
      if (mCrankPos < 0) mCrankPos += kCrankPositions;
   }
}

void HorizontalCrankHub::Draw()
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
      int cp = mCrankPos;
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

void HorizontalCrankHub::DrawSelectionTarget()
{
}

void HorizontalCrankHub::Render()
{
   float ep = 1.0f * 0.125f;
   Vector3f::VectorAngle3<float> trig(0, mAngle, 0);
   Vector3f pt (mOffset, -0.125, 0);
   Vector3f ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr);
   pt.y += mDepth;
   ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr);
   pt.x += mLength;
   ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr);
   pt.y -= ep;
   ptr = pt;
   ptr.Rotate(trig);
   mpGraphic->AddPoint (ptr);
}

//ObjectBase* HorizontalCrankHub::Clone()
//{
//   HorizontalCrankHub* pHorizontalCrankHub = new HorizontalCrankHub(mHorizontalCrankHubID, mOffset, mDepth, mLength, mAngle);
//   return pHorizontalCrankHub;
//}
