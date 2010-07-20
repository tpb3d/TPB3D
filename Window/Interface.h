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

#pragma once
#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "Clock.h"
#include "Stats.h"
#include "../Hub/Event.h"
#include "../Hub/GameManager.h"

class ToolBar;
class EventHandler;
class GUIDelegate;
class SpecialDelegate;
class WindowViewObject;
class SettingsWindow;
class FileDialogWindow;

class Interface : public EventBase
{
private:
   bool mChangedSettings;
   bool mSoundFxOn;
   bool mMusicOn;
   int mLanguageCode;
   int mCurDay;

protected:
   Clock mClock;
   Stats mStats;
   EventHandler& mEVH; // tap the event handler for the app
   ToolBar* mpToolBar;
   GUIDelegate* mpWindowDelegate;
   WindowViewObject* mpWindow;
   SettingsWindow* mpSettings;
   FileDialogWindow* mpFileDialog;
   SpecialDelegate* mpSpecialDelegate;
   GameManager& mGameManager;

   float m_fHeight;

public:
   Interface (EventHandler& revh, GameManager& GM);
   ~Interface ();

   void SetLanguageCode( int code );
   void SetSoundFx (bool bFX);
   void SetMusic ( bool bMusic);
   int GetLanguageCode() { return mLanguageCode; }
   bool GetSoundFx() { return mSoundFxOn; }
   bool GetMusic() { return mMusicOn; }

   void LoadSettings();
   void SaveSettings();

   int GetTimeOfDay() { return mClock.GetTimeOfDay(); }
   int GetDayOfYear() { return mClock.GetDayOfYear(); }

   Stats& GetStats() { return mStats; }

   void CloseChildWindow();

   virtual bool OnMouseDown (sf::Mouse::Button Button, Vector2i point, Vector2i pointb);
   virtual bool OnMouseUp (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb);
   virtual bool OnMouseMove ( Vector2i pointa, Vector2i pointb);
   virtual bool OnKeyDown (sf::Key::Code Key);
   virtual bool OnKeyUp (sf::Key::Code Key);

   virtual bool OnToolHit (const HR_Events tool);
   virtual bool OnTools ();
   virtual bool OnSettings ();

   bool OpenScene (const char* pPath);
   bool SaveScene (const char* pPath);

   void LoadToolbar ();
   void Update (float dt);
   void Draw ();
};

#endif // _INTERFACE_H
