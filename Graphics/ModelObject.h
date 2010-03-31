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

#ifndef _MODELOBJECT_H
#define _MODELOBJECT_H

class AnimationBase;    // Main body of physics component
class FireAnimation;
class Tiler;

namespace Gfx
{

   class ModelObject
   {

   public:
      ModelObject ();

      virtual void Draw() = 0;
      virtual void Draw(int vx, int vy) {}
   protected:
      void Render (AnimationBase* pBase, bool bLight = false);  // draw method replacement, drawing now happens on the GPU side for us
      void Render (AnimationBase* pBase, float x, float x2 );  // overload with specified X and X2
      void Render (Tiler* pTiler);  // draw method replacement, drawing now happens on the GPU side for us
      void RenderRectangle (AnimationBase* pBase );
      void RenderParallax (FireAnimation* pBase, float xOffset );  // overload with specified X and X2 for parallax animation
      void DrawSelectionTarget (AnimationBase* pBase, int id); // milk and cookies run just for the basics to test for a hit
      void DrawSelectionTarget (AnimationBase* pBase, float x, float x2, int id );  // overload with specified X and X2 and id
                                                                                 // for empty spaces

   };
}
#endif // _MODELOBJECT_H
