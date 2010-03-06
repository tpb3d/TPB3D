/*   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vector>
#include "../Types/Vector2.h"
#include "FireAnimation.h"

#include "../Utility/GameException.h"

const unsigned char FireAnimation::kFlameColor[16][4] =
{
   { 255,240,49,255 }, //
   { 255,230,48,255 }, //
   { 244,222,47,245 }, //
   { 233,212,46,245 }, //
   { 222,200,45,235 }, //
   { 202,185,44,235 }, //
   { 198,176,43,225 }, //
   { 188,162,62,225 }, //
   { 178,124,81,215 }, //
   { 158,114,90,215 }, //
   { 132,104,91,205 }, //
   { 118,108,90,205 }, //
   { 96, 88, 85,195 }, //
   { 86, 74, 74,195 }, //
   { 68, 62, 63,185 }, // dark flame
   { 42, 38, 38,185 } // dark flame
};
const unsigned char FireAnimation::kSmokeColor[16][4] =
{
   { 205,205,205,255 }, //
   { 195,195,195,245 }, //
   { 185,185,185,235 }, //
   { 172,172,172,225 }, //
   { 160,160,160,215 }, //
   { 149,149,149,205 }, //
   { 138,138,138,195 }, //
   { 122,122,122,185 }, //
   { 108,108,108,175 }, //
   {  92, 92, 92,165 }, //
   {  82, 82, 82,155 }, //
   {  76, 76, 76,145 }, //
   {  66, 66, 66,135 }, //
   {  52, 52, 52,125 }, // dark smoke
   {  42, 42, 42,115 } // dark smoke
};

const float FireAnimation::kUVs[16][4][2] =
{
   {{0.75f, 1.00f}, {0.75f, 0.75f}, {1.00f, 0.75f}, {1.00f, 1.00f}},
   {{0.50f, 1.00f}, {0.50f, 0.75f}, {0.75f, 0.75f}, {0.75f, 1.00f}},
   {{0.25f, 1.00f}, {0.25f, 0.75f}, {0.50f, 0.75f}, {0.50f, 1.00f}},
   {{0.00f, 1.00f}, {0.00f, 0.75f}, {0.25f, 0.75f}, {0.25f, 1.00f}},

   {{0.75f, 0.75f}, {0.75f, 0.50f}, {1.00f, 0.50f}, {1.00f, 0.75f}},
   {{0.50f, 0.75f}, {0.50f, 0.50f}, {0.75f, 0.50f}, {0.75f, 0.75f}},
   {{0.25f, 0.75f}, {0.25f, 0.50f}, {0.50f, 0.50f}, {0.50f, 0.75f}},
   {{0.00f, 0.75f}, {0.00f, 0.50f}, {0.25f, 0.50f}, {0.25f, 0.75f}},

   {{0.75f, 0.50f}, {0.75f, 0.25f}, {1.00f, 0.25f}, {1.00f, 0.50f}},
   {{0.50f, 0.50f}, {0.50f, 0.25f}, {0.75f, 0.25f}, {0.75f, 0.50f}},
   {{0.25f, 0.50f}, {0.25f, 0.25f}, {0.50f, 0.25f}, {0.50f, 0.50f}},
   {{0.00f, 0.50f}, {0.00f, 0.25f}, {0.25f, 0.25f}, {0.25f, 0.50f}},

   {{0.75f, 0.25f}, {0.75f, 0.00f}, {1.00f, 0.00f}, {1.00f, 0.25f}},
   {{0.50f, 0.25f}, {0.50f, 0.00f}, {0.75f, 0.00f}, {0.75f, 0.25f}},
   {{0.25f, 0.25f}, {0.25f, 0.00f}, {0.50f, 0.00f}, {0.50f, 0.25f}},
   {{0.00f, 0.25f}, {0.00f, 0.00f}, {0.25f, 0.00f}, {0.25f, 0.25f}}
};

const float FireAnimation::kVertecies[16][4][3] =
{
   {{-1.00f, 0.00f, 0.10f}, {-1.00f, 2.00f, 0.10f}, {1.00f, 2.00f, 0.10f}, {1.00f, 0.00f, 0.10f}},
   {{-2.00f, 0.00f, 0.10f}, {-2.00f, 3.00f, 0.10f}, {2.00f, 3.00f, 0.10f}, {2.00f, 0.00f, 0.10f}},
   {{-3.00f, 0.50f, 0.10f}, {-3.00f, 4.50f, 0.10f}, {3.00f, 4.50f, 0.10f}, {3.00f, 0.50f, 0.10f}},
   {{-4.00f, 0.75f, 0.10f}, {-4.00f, 7.00f, 0.10f}, {4.00f, 7.00f, 0.10f}, {4.00f, 0.75f, 0.10f}},

   {{-5.00f, 1.00f, 0.10f}, {-5.00f, 8.75f, 0.10f}, {5.00f, 8.75f, 0.10f}, {5.00f, 1.00f, 0.10f}},
   {{-6.00f, 1.25f, 0.10f}, {-6.00f, 10.50f, 0.10f}, {6.00f, 10.50f, 0.10f}, {6.00f, 1.25f, 0.10f}},
   {{-7.00f, 1.50f, 0.10f}, {-7.00f, 13.00f, 0.10f}, {7.00f, 13.00f, 0.10f}, {7.00f, 1.50f, 0.10f}},
   {{-8.00f, 1.75f, 0.10f}, {-8.00f, 17.00f, 0.10f}, {8.00f, 17.00f, 0.10f}, {8.00f, 1.75f, 0.10f}},

   {{-9.00f, 1.85f, 0.10f}, {-9.00f, 22.25f, 0.10f}, {9.00f, 22.25f, 0.10f}, {9.00f, 1.85f, 0.10f}},
   {{-10.00f, 2.50f, 0.10f}, {-10.00f, 25.50f, 0.10f}, {10.00f, 25.50f, 0.10f}, {10.00f, 2.50f, 0.10f}},
   {{-11.00f, 2.80f, 0.10f}, {-11.00f, 26.00f, 0.10f}, {11.00f, 26.00f, 0.10f}, {11.00f, 2.10f, 0.10f}},
   {{-12.00f, 3.20f, 0.10f}, {-12.00f, 27.00f, 0.10f}, {12.00f, 27.00f, 0.10f}, {12.00f, 3.20f, 0.10f}},

   {{-13.00f, 3.50f, 0.10f}, {-13.00f, 28.00f, 0.10f}, {13.00f, 28.00f, 0.10f}, {13.00f, 3.50f, 0.10f}},
   {{-13.25f, 3.75f, 0.10f}, {-13.25f, 28.10f, 0.10f}, {13.25f, 28.10f, 0.10f}, {13.25f, 3.75f, 0.10f}},
   {{-13.50f, 4.00f, 0.10f}, {-13.50f, 28.20f, 0.10f}, {13.50f, 28.20f, 0.10f}, {13.50f, 4.00f, 0.10f}},
   {{-13.75f, 4.20f, 0.10f}, {-13.75f, 28.30f, 0.10f}, {13.75f, 28.30f, 0.10f}, {13.75f, 4.20f, 0.10f}}
};

FireAnimation::FireAnimation (int width, int height)
:  AnimationBase (width, height)
{
   mcurrent_frame = 0;
   mtime = 0;
   mPrimaryClock = 0;
   mPlates[0] = 0;
   mPlates[1] = 0;
   mPlates[2] = 0;
   mPlates[3] = 0;
}

void
FireAnimation::AddFrame (Texture* pTex, float duration)
{
   mframes.push_back (std::pair<Texture*, float> (pTex, duration));
}

void
FireAnimation::BindTexture()
{
   return mframes[mcurrent_frame].first->Bind();
}

void
FireAnimation::Update (float dt)
{
#ifdef _DEBUG
   if( mframes.size() < 3 )
   {
      throw new GameException("FileAnimation object needs 3 frames see source Header file");
   }
#endif

   mtime += dt;
   if (mtime > mframes[mcurrent_frame].second)
   {
      mtime = 0;
      //mcurrent_frame++;
      //if (mcurrent_frame >= mframes.size ())
      //   mcurrent_frame = 0;

      mPrimaryClock++;
      if( ++mPlates[0] > 15 ) mPlates[0] = 0;
      if( mPrimaryClock > 2 ) // delay sequencer so plumes rise staggered
      {
         if( ++mPlates[1] > 15 ) mPlates[1] = 0;
      }
      if( mPrimaryClock > 7 )
      {
         if( ++mPlates[2] > 15 ) mPlates[2] = 0;
      }
      if( mPrimaryClock > 11 )
      {
         if( ++mPlates[3] > 15 ) mPlates[3] = 0;
      }
      // add burn out seq linked to PrimaryClock to fade smoke.
   }
}
