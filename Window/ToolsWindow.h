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

class ViewWindowObject;

/*
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
*/
class ToolsWindow
{
protected:
   ViewWindowObject* mpWnd;
public:
   ToolsWindow ();
   ~ToolsWindow ();

public:
   bool Create();
   void Destroy ();
/*
   bool OnSoundCheck(const EventArgs& e);
   bool OnNewRide (const EventArgs& e);
   bool OnPlace (const EventArgs& e);
   bool OnClose (const CEGUI::EventArgs& e);
   */
   void RefreshPartList ();

};
