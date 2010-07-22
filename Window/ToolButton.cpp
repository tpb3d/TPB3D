/*   This file is part of Theme Park Builder 3D The Game.
 *
 *   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstring>
#include <map>
#include <string>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "ToolButton.h"
#include "../Scene/Scene.h"

using namespace Gfx;

namespace Gfx
{
   const unsigned char kButtonLights[3][4] =
   {
      { 195,195,195,128 },    // Mormal
      { 195,255,255,255 },    // Lit
      { 151,151,151,255 }     // Hit
   };
   const float kButtonUVs[4][2] =
   {
      { 0, 0.25 },
      { 0, 0 },
      { 1, 0 },
      { 1, 0.25 }
   };
   const float kButtonTextUVs[8] =
   {
      0.0f, 0.125f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 0.125f
   };
}

ToolButton::ToolButton( float x, float y, int ID)
:  ViewObject(Gfx::kButtonUVs)
{
   m_ID = ID;
   m_ButtonState = BS_Normal;
   mSize.x = 96;
   mSize.y = 24;
   m_Geometry.mPoints[0] = Vector3f (x,y,0);
   m_Geometry.mPoints[1] = Vector3f (x + mSize.x, y, 0);
   m_Geometry.mPoints[2] = Vector3f (x + mSize.x, y + mSize.y, 0);
   m_Geometry.mPoints[3] = Vector3f (x, y+ mSize.y, 0);
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("buttons.png", GL_RGBA);
   mpFace = new AnimationSingle (pTex, mSize.x, mSize.y);
   mpFace->SetPosition(x, y, 0);
   mpFace->SetLightingColor (kButtonLights[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kButtonTextUVs);
}

ToolButton::~ToolButton ()
{
}

void ToolButton::Clear ()
{
   // clear all the buttons
}

int ToolButton::TestHit (Vector2i& point)
{
   if ((point.x > m_Geometry.mPoints[0].x && point.x < m_Geometry.mPoints[2].x)
      && (point.y > m_Geometry.mPoints[0].y && point.y < m_Geometry.mPoints[2].y))
      return this->m_ID;
   return 0;
}

void ToolButton::Update (ButtonState state)
{
   SetState(state);
   mpFace->SetLightingColor(kButtonLights[state]);
}

void ToolButton::Draw ()
{
   Render( mpFace );
   RenderText( mpTextTex, m_Geometry.mPoints[0].x+20, m_Geometry.mPoints[0].y+8, m_Text);
}

