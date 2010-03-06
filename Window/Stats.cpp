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

#include <map>
#include <string>
#include <sstream>
#include <cstdio>
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Camera.h"
#include "Stats.h"

namespace UI
{
   // this defines the coordinates to map the texture image from in pairs
   const float OtherUVs[8] =
   { 0.0f, 0.128f,  0.0f, 0.25f,  1.0f, 0.25f,  1.0f, 0.128f }; // trim the right rounded edge
   const float StatBarUVs[8] =   // stats.png
   { 0.0f, 0.0f,  0.0f, 0.125f,  1.0f, 0.125f,  1.0f, 0.0f };
}

std::string itoa( int n )
{
   std::ostringstream s;
   s << n;
   return s.str();
}

using namespace Gfx;

Stats::Stats ()
{
   mNet = 100000;
   mPopulation = 0;
   mStars = 1;
   mstrDayOfWeek = "Monday";
   mstrDate = "1-1-2010";

   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Stats.png", GL_RGBA);
   mOtherFace = new AnimationSingle (pTex, 256, 16);
   mStatsFace = new AnimationSingle (pTex, 256, 16);

   mOtherFace->SetUVs(UI::OtherUVs);
   mStatsFace->SetUVs(UI::StatBarUVs);
   PosCalc ();

}

Stats::~Stats ()
{
}

void
Stats::PosCalc ()
{
   Camera* pCam = Camera::GetInstance ();
   mOtherFace->SetPosition (( pCam->GetCamSize ().x / 2) - 128, pCam->GetHeight()-16); // relative based on clock
   mStatsFace->SetPosition (( pCam->GetCamSize ().x / 2) - 128, pCam->GetHeight()-32); // relative based on clock
}

void
Stats::Update ()
{
   mstrNet = itoa( mNet );
   mstrPopulation = itoa( mPopulation );
}

void
Stats::Draw ()
{
//   Render (mOtherFace);
//   Render (mStatsFace);
   float x = mStatsFace->GetPositionX();
   float y = mStatsFace->GetPositionY()+2;
   RenderText( mStatsFace, x+40, y, mstrNet);
   RenderText( mStatsFace, x+168, y, mstrPopulation);
   x = mOtherFace->GetPositionX();
   y = mOtherFace->GetPositionY();
   RenderText( mStatsFace, x+40, y, mstrDayOfWeek);
   RenderText( mStatsFace, x+168, y, mstrDate);
}
