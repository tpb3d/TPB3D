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
#ifndef _TOOLSWINDOW_H
#define _TOOLSWINDOW_H

#define SKIN "WindowsLook"

namespace CEGUI
{
   class FrameWindow;
}

using namespace CEGUI;

class ListItem : public ListboxTextItem
{
public:
   ListItem (const String& text) : ListboxTextItem(text)
   {
      colour rgbC( 0,0,0);
      setSelectionBrushImage(SKIN, "MultiListSelectionBrush");
      setTextColours (rgbC, rgbC, rgbC, rgbC );
   }
};

class ToolsWindow
{
protected:
   CEGUI::Window* mpWnd;
public:
   ToolsWindow ();
   ~ToolsWindow ();

public:
   bool Create(CEGUI::Window* pRoot);
   void Destroy ();

   bool OnSoundCheck(const CEGUI::EventArgs& e);
   bool OnNewRide (const EventArgs& e);
   bool OnPlace (const EventArgs& e);
   bool OnClose (const CEGUI::EventArgs& e);
   void RefreshPartList ();

};

#endif // _TOOLSWINDOW_H
