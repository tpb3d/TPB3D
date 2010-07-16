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

#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class ToolButton;

class ToolBar : public Gfx::ViewObject
{
   SimpleQuad m_Border;
   short m_ButtonCount;
   short m_ButtonMax;
   short mID;
protected:
   ToolButton** m_pButtons;

public:
   ToolBar (int ButtonsNeeded, short ID);
   ~ToolBar ();

public:
   void Clear();   // return buttons to normal
   void AddButton (ToolButton* pButton);
   short GetID() { return mID; }

   void PosCalc ();
//   void Update (int state);
   void Draw ();
   int TestHit (Vector2i& point);

};

