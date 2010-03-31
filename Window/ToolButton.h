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
// Tick Tock!

#pragma once
#ifndef _TOOLBUTTON_H
#define _TOOLBUTTON_H

#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class ToolButton : public Gfx::ViewObject
{
public:
   // members
   enum ButtonState
   {
      BS_Normal = 0, // up and not highlighted
      BS_Down,       // lit and down
      BS_Highlighted // just lit
   };

protected:
   int m_ID;
   AnimationSingle* mpFace;
   AnimationSingle* mpTextTex;
   std::string m_Text;
   ButtonState m_ButtonState;
   SimpleQuad m_Geometry;

public:
   // CTOR/DTORs
   ToolButton (float x, float y, int ID);
   ~ToolButton ();

public:
   // properties
   void SetText (const char* pText) { m_Text = pText; }
   void SetState( ButtonState bs ) { m_ButtonState = bs; }

   // methods
public:
   void Clear();   // return this button to normal
   int TestHit (Vector2i point); // just render geometry for selection

   void Update (ButtonState state);
   void Draw ();

};

#endif // _TOOLBUTTON_H
