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
class WindowDelegate;
class GroupViewEvent; // basic group box without the visual element until we need the visual

class SettingsWindow
{
protected:
   WindowViewObject* mpWnd;
   WindowDelegate* mpDelegate;
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

public:
   bool Create ();
   void Destroy ();
   void Draw ();

   bool OnMusicCheck (const EventArgs& e);
   bool OnSoundCheck (const EventArgs& e);
   bool OnClose (const EventArgs& e);
   bool OnEnglish (const EventArgs& e);
   bool OnSpanish (const EventArgs& e);
   bool OnFrench (const EventArgs& e);
   bool OnDeutsch (const EventArgs& e);
   bool OnItalian (const EventArgs& e);
};
