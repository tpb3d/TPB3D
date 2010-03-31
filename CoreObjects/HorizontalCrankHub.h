//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  ride HorizontalCrankHub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "RideNode.h"

class ObjectBase;

#define kCrankPositions 72

class HorizontalCrankHub : public RideNode
{
   int   mHorizontalCrankHubID;
   float mOffset;  // from center axis
   float mDepth;   // depth of the HorizontalCrankHub web (height at hub)
   float mLength;  // Projection from hub
   float mAngle;
   ObjectBase* mpGraphic;

   // We may replace this with a crank object
   // this will simulate the crank and connecting rods (Struts)
   float mRockAngle[kCrankPositions];
   float mHeights[kCrankPositions];
   int mCrankPos;
   void PresetCrank();
   // End crank code
   
public:
   HorizontalCrankHub (int HorizontalCrankHubID, float offset, float depth, float length, float angle);
   ~HorizontalCrankHub (void);

   virtual void Update(int dt);
   virtual void Render();
   virtual void Draw();
   virtual void DrawSelectionTarget(); // base can't draw
   //virtual ObjectBase* Clone( );
};
