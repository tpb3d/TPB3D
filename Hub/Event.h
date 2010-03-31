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

#ifndef _EVENT_H
#define _EVENT_H

#include "../Types/Vector2.h"

enum HR_Events
{
   HR_MouseInScene = 0,       // Generic
   HR_ClickInScene,           // Left Click
   HR_MenuInScene,            // Right Click
   HR_SelectBuildCursor,      // From tools if BuildOption returns true, set cursor and/or status bar to show active tool.
   HR_SelectBuildOption,      // From tools, include Building, Elevater, Condo etc as option param
   HR_Settings,
   HR_Tools,
   HR_FRCS,
   HR_TRCS,
   HR_OTRCS,
   HR_PlaceBuilding,
   HR_PlaceTrackRide,
   HR_PlaceFlatRide,
   HR_PlaceTerrain,
   HR_PlaceRetail,
   HR_PlaceSecurity,
   HR_PlaceClinic,
   HR_PlaceWasteManagement,
   HR_PlaceElevator,
   HR_PlaceStairs,
   HR_PlaceNone,
   HR_NewScene,
   HR_OpenScene,
   HR_SaveScene,
   HR_CloseScene,
   HR_Close
};

class Camera;

class EventBase
{
public:
   // HELP! The Resize() event can not actually be captured by some classes, since they
   // already define a Resize() member funtion. Maybe we should call prefix theese with
   // "On"? (So OnResize(), OnMouseDown(), etc).
   virtual bool OnResize (Vector2i viewSize) { return false; }
   virtual bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnKeyDown (sf::Key::Code Key) { return false; }
   virtual bool OnKeyUp (sf::Key::Code Key) { return false; }
   virtual bool OnMouseMove (Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnMouseWheel (int Delta) { return false; }
   virtual bool OnClose () { return false; }
   virtual bool OnToolHit (const HR_Events Event) {return false; }
   virtual bool OnOpen (const char* pPath) { return false; }
   virtual bool OnSave (const char* pPath) { return false; }
};

class EventHandler
{
private:
   typedef std::vector<EventBase*> ConType;
   ConType mHandlers;
   Camera* Cam;
   const sf::Input* mpInput;

public:
   EventHandler ();
   void Add (EventBase* Handler);
   bool HandleEvents (const sf::Event& Event);
   bool HandleEvents (const HR_Events& ev );
};

#endif // _EVENT_H
