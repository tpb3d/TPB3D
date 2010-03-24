//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Skybowl class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Texture.h"
#include "SkyBowl.h"

#define _USE_MATH_DEFINES 
#include <math.h>

SkyBowl::SkyBowl(void)
{
   Gfx::ImageManager& iMan = *(Gfx::ImageManager::GetInstance());
   mTexture[0] = iMan.GetTexture("sky2.png", 4);
   mTexture[1] = iMan.GetTexture("grass.png", 4);
}

SkyBowl::~SkyBowl(void)
{
}
void SkyBowl::Init( double dWorldSize )
{
   mdWorldSize = dWorldSize;
   double dInnerRad = 280;
   double dMiddleRad = 500;
   double dOuterRad = 510;
   double dTop = 300;

   double lastTheta = PI * 2;
   double bumpTheta = lastTheta/(kBowlFacets-1); 
   double theta = 0.0;
   double dLU = 0;
   double dLInc = 0.25;
   for( int idx = 0; idx < kBowlFacets; ++idx )
   {
      double dTerrainCos = cos(theta);
      double dTerrainSin = sin(theta);
      theta += bumpTheta;
      mfTop[0] = 0;
      mfTop[1] = (float)dTop;
      mfTop[2] = 0;
      mfTop[3] = 0.5f;
      mfTop[4] = 0.5f;
      mfUpperSkyRing[idx][0] = float( dTerrainCos * dInnerRad );
      mfUpperSkyRing[idx][1] = float( dTop * 0.65);
      mfUpperSkyRing[idx][2] = float( dTerrainSin * dInnerRad );
      mfUpperSkyRing[idx][3] = float( 0.5 + 0.3 * dTerrainCos );
      mfUpperSkyRing[idx][4] = float( 0.5 + 0.3 * dTerrainSin );

      //mfMiddleSkyRing[idx][0] = float( dTerrainCos * dInnerRad );
      //mfMiddleSkyRing[idx][1] = float( dTop * 0.5 );
      //mfMiddleSkyRing[idx][2] = float( TerrainSin * dInnerRad );
      //mfMiddleSkyRing[idx][3] = float( dTop * 0.5 + 0.4 * dTerrainCos );
      //mfMiddleSkyRing[idx][4] = float( dTop * 0.5 + 0.4 * dTerrainSin );

      mfHorizonSkyRing[idx][0] = float( dTerrainCos*dOuterRad );
      mfHorizonSkyRing[idx][1] = float( dTop * 0.05 );
      mfHorizonSkyRing[idx][2] = float( dTerrainSin*dOuterRad );
      mfHorizonSkyRing[idx][3] = float( 0.5 + 0.5 * dTerrainCos );
      mfHorizonSkyRing[idx][4] = float( 0.5 + 0.5 * dTerrainSin );

      mfOuterLandRing[idx][0] = mfHorizonSkyRing[idx][0];
      mfOuterLandRing[idx][1] = mfHorizonSkyRing[idx][1];
      mfOuterLandRing[idx][2] = mfHorizonSkyRing[idx][2];
      mfOuterLandRing[idx][3] = 0;
      mfOuterLandRing[idx][4] = (float)dLU;

      mfInnerLandRing[idx][0] = float( dTerrainCos*dMiddleRad );
      mfInnerLandRing[idx][1] = 0;
      mfInnerLandRing[idx][2] = float( dTerrainSin*dMiddleRad );
      mfInnerLandRing[idx][3] = 1;
      mfInnerLandRing[idx][4] = (float)dLU;
      dLU += dLInc;
   }
}

void SkyBowl::Draw ()
{
   glEnable( GL_TEXTURE_2D );
   mTexture[0]->Bind();
   glColor4f( 1.0f, 1.0f, 1.0f, 0.95f);
   glBegin(GL_TRIANGLE_FAN );
   glTexCoord2f( mfTop[3],mfTop[4] );
   glVertex3fv( this->mfTop );
   for( int idx = 0; idx < kBowlFacets; ++idx)
   {
      glTexCoord2f( mfUpperSkyRing[idx][3],mfUpperSkyRing[idx][4] );
      glVertex3fv( mfUpperSkyRing[idx] );
   }
   glEnd();
   glBegin(GL_TRIANGLE_STRIP );
   for( int idx = 0; idx < kBowlFacets; ++idx)
   {
      glTexCoord2f( mfUpperSkyRing[idx][3],mfUpperSkyRing[idx][4] );
      glVertex3fv( mfUpperSkyRing[idx] );
      glTexCoord2f( mfHorizonSkyRing[idx][3],mfHorizonSkyRing[idx][4] );
      glVertex3fv( mfHorizonSkyRing[idx] );
   }
   glEnd();
   mTexture[1]->Bind();
   glBegin(GL_TRIANGLE_STRIP );
   for( int idx = 0; idx < kBowlFacets; ++idx)
   {
      glTexCoord2f( mfOuterLandRing[idx][3],mfOuterLandRing[idx][4] );
      glVertex3fv( mfOuterLandRing[idx] );
      glTexCoord2f( mfInnerLandRing[idx][3],mfInnerLandRing[idx][4] );
      glVertex3fv( mfInnerLandRing[idx] );
   }
   glEnd();
   glDisable( GL_TEXTURE_2D );
}
