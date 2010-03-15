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
// Tick Tock!

#pragma once

namespace CEGUI
{
   class FrameWindow;
}

class FRCSWindow
{
protected:
   CEGUI::FrameWindow* mpWnd;
public:
   FRCSWindow ();
   ~FRCSWindow ();

public:
   bool Create(CEGUI::Window* pRoot);
   void Destroy ();

   bool OnSoundCheck(const CEGUI::EventArgs& e);
   bool OnClose (const CEGUI::EventArgs& e);
};
