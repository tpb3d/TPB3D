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

class Interface;
class EventArgs;
class CheckViewObject;
class RadioButtonViewObject;
class ButtonViewObject;
class WindowViewObject;
class LabelViewObject;
class GUIDelegate;
class GroupViewEvent; // basic group box without the visual element until we need the visual

class SettingsWindow
{
protected:
   WindowViewObject* mpWnd;
   GUIDelegate* mpDelegate;
   CheckViewObject* mpSoundFx;
   CheckViewObject* mpMusic;
   RadioButtonViewObject* mpEnglish;
   RadioButtonViewObject* mpFrench;
   RadioButtonViewObject* mpGerman;
   RadioButtonViewObject* mpItalian;
   RadioButtonViewObject* mpSpanish;
   ButtonViewObject* mpClose;
   LabelViewObject* mpLabel1;
   LabelViewObject* mpLabel2;

   GroupViewEvent* mpLanguageGroup;
   Interface& mInterface;
public:
   SettingsWindow (Interface& rInterface);
   ~SettingsWindow ();

   GUIDelegate* get_Delegate() { return mpDelegate; }
   WindowViewObject::WindowState get_State() { return mpWnd->get_State(); }

public:
   bool Create (float fx, float fy);
   void Destroy ();
   void Draw ();

   virtual int  TestHit (Vector2i& point);
   virtual int  Dispatch (short code, Vector2i& point);

   int OnMusicCheck (const EventArgs& e);
   int OnSoundCheck (const EventArgs& e);
   int OnClose (const EventArgs& e);
   int OnEnglish (const EventArgs& e);
   int OnSpanish (const EventArgs& e);
   int OnFrench (const EventArgs& e);
   int OnDeutsch (const EventArgs& e);
   int OnItalian (const EventArgs& e);
};
