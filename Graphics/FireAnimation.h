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

#pragma once
#ifndef _FIREANIMATION_H
#define _FIREANIMATION_H
#include "Animation.h"

using namespace Gfx;

class FireAnimation : public AnimationBase   // flame and smoke partical animation
{
private:
   std::vector <std::pair <Texture*, float> > mframes;
   // frame 0 is an alpha panel of burning or exploisions
   // frame 1 and 2 are particles
   unsigned int mcurrent_frame;
   unsigned int mPrimaryClock;
   unsigned int mPlates[4];

   float mtime;
protected:
   static const unsigned char kFlameColor[16][4];
   static const unsigned char kSmokeColor[16][4];
   static const float kUVs[16][4][2];
   static const float kVertecies[16][4][3];

public:
   const unsigned char* GetFlameColor(int index) { return kFlameColor[mPlates[index]]; }
   const unsigned char* GetSmokeColor(int index) { return kSmokeColor[mPlates[index]]; }
   const float* GetUVs(int index, int rs) { return kUVs[mPlates[index]][rs]; }
   const float* GetVertecies(int index, int pt) { return kVertecies[mPlates[index]][pt]; }

public:
   FireAnimation (int width, int height);
   void AddFrame (Texture* pTex, float duration);
   void Update (float dt);
   void BindTexture();
};

#endif //_FIREANIMATION_H
