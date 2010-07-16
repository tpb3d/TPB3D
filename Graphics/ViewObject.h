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

// This class is a graphics implementation object that all modeled "Park" objects are derived from.

#pragma once

#ifndef _VIEWOBJECT_H
#define _VIEWOBJECT_H
#include "../Types/Vector3.h"
#include "../Types/Vector2.h"

struct SimpleQuad
{
   Vector3f Position;
   unsigned char Colors[4][4];
   Vector3f mPoints[4];
   float    Angle;
};

class SimpleMesh;
class AnimationBase;    // Main body of physics component

namespace Gfx
{

   class ViewObject
   {
   protected:
      float    mUVs[4][2];
      Vector3f mPoints[2];
      Vector2f mSize;

   public:
      ViewObject ();
      ViewObject (const float uvs[4][2]);

      virtual void Draw() {};
      virtual int  TestHit (Vector2i& point) { return 0; }
   protected:
      void Render(AnimationBase* pBase);  // draw method replacement, drawing now happens on the GPU side for us
      void Render(AnimationBase* pBase, const float uvs[4][2]);  // draw method replacement, drawing now happens on the GPU side for us
      void RenderText(AnimationBase* pBase, float x, float y, std::string str); // includes font w&h, string
      void RenderText(AnimationBase* pBase, std::string str);
      void Render(SimpleQuad* pQuad);  // Renders a quad from 4 vectors.
      void Render(SimpleMesh* pQuad);  // Renders a quad from 4 vectors.
      void DrawSelectionTarget(SimpleQuad* pQuad);      // just the basic geometry
   };
}
#endif // _VIEWOBJECT_H
