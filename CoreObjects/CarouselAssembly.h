//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  ride CarouselAssembly class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideCarouselAssembly        Assembly that is a feature support that extends out and usually supports a carriage.
      RideTelescopeCarouselAssembly CarouselAssembly that has an extenstion that slides out to extend the CarouselAssembly up to 1.8 times its collapsed length.
*/

#pragma once
#include "RideNode.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedStrip.h"

class CarouselAssembly : public RideNode, public TexturedStrip
{
   int   mCarouselAssemblyID;
   float mOffset;  // from center axis
   float mDepth;   // depth of the CarouselAssembly web (height at hub)
   float mLength;  // Projection from hub
   float mAngle;
   
   // This goes with the crank later
   // this will simulate the crank and gallop of the carousel horse
   float mRockAngle[36];
   float mHeights[36];
   int mCrankPos1;
   int mCrankPos2;
   void PresetCrank();
   // End crank code
   
public:
   CarouselAssembly (int CarouselAssemblyID, float offset, float depth, float length, float angle);
   ~CarouselAssembly (void);

   virtual void Render();
   virtual void Draw();
   virtual void DrawSelectionTarget(); // base can't draw
   virtual ObjectBase* Clone( );
};
