//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Skybowl class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#define kBowlFacets 18
namespace Gfx
{
   class Texture;
}

class SkyBowl
{
   Gfx::Texture* mTexture[2];
   double mdWorldSize;
   float mfTop[5];
   float mfUpperSkyRing[kBowlFacets][5];
   //float m_fMiddleSkyRing[kBowlFacets][5];
   float mfHorizonSkyRing[kBowlFacets][5];
   float mfOuterLandRing[kBowlFacets][5];
   float mfInnerLandRing[kBowlFacets][5];
public:
   SkyBowl(void );
   ~SkyBowl(void);
   void Init( double dWorldSize );
   void Draw();
};
