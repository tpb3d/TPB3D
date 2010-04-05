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

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <map>
#include "../Types/String.h"
#include "../Settings/Settings.h"
#include "../Physics/MotionPhysics.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Camera.h"
#include "../Hub/Event.h"
#include "ToolButton.h"
#include "ToolBar.h"
#include "Interface.h"

using namespace Gfx;

Interface::Interface (EventHandler& revh)
:  mEVH(revh)
{
   mpToolBar = new ToolBar(6, HR_MainMenu);
   LoadToolbar();
   mLanguageCode = 0;
   mSoundFxOn = false;
   mMusicOn = false;
   LoadSettings();
   mChangedSettings = false;
   mCurDay = 0;
}

Interface::~Interface ()
{
   if (mChangedSettings)
   {
      SaveSettings();
   }
}

void Interface::LoadSettings()
{
   Settings::SettingsIni theSettings;
   theSettings.Load();
   bool bHasSettings = false;
   if( theSettings.SettingsAreLoaded() )
   {
      int iCode = FromString<int>(theSettings.Get("Language.Code"));
      if( iCode >0 && iCode < 5 )
      {
         SetLanguageCode (iCode);
         bHasSettings = true;
      }
      mSoundFxOn = (theSettings.Get ("Sound.FX")[0] == '1' ? true : false ); // its a string, at the least it will have a null terminator
      mMusicOn = (theSettings.Get ("Sound.Music")[0] == '1' ? true : false );
   }
   if (!bHasSettings)
   {
      SetLanguageCode (1);
      theSettings.Set ("Sound.FX", (mSoundFxOn)? "1":"0", false );
      theSettings.Set ("Sound.Music", (mMusicOn)? "1":"0", false );
      theSettings.Set ("Language.Code", "1", true);
   }
}

void Interface::SaveSettings()
{
   Settings::SettingsIni theSettings;
   theSettings.Load();
   bool bHasSettings = false;
   //char buf[8];
   if( theSettings.SettingsAreLoaded() )
   {

      theSettings.Set ("Sound.FX", (mSoundFxOn)? "1":"0", false );
      theSettings.Set ("Sound.Music", (mMusicOn)? "1":"0", false );
      theSettings.Set ("Language.Code", ToString(mLanguageCode), true);
   }
}

void Interface::LoadToolbar ()
{
   // Hardcode plug
   Camera* pCam = Camera::GetInstance ();
   m_fHeight = pCam->GetHeight();
   ToolButton* pB = new ToolButton(0, m_fHeight-32, HR_Settings);
   pB->SetText("Options");
   mpToolBar->AddButton (pB);
   pB = new ToolButton(0, m_fHeight-64, HR_Tools);
   pB->SetText("FRCS");
   mpToolBar->AddButton (pB);
   pB = new ToolButton(0, m_fHeight-96, HR_PlacePath);
   pB->SetText("Paths");
   mpToolBar->AddButton (pB);
   pB = new ToolButton(0, m_fHeight-128, HR_OpenScene);
   pB->SetText("Load");
   mpToolBar->AddButton (pB);
   pB = new ToolButton(0, m_fHeight-160, HR_SaveScene);
   pB->SetText("Save");
   mpToolBar->AddButton (pB);
   pB = new ToolButton(0, m_fHeight-192, HR_Close);
   pB->SetText("Exit");
   mpToolBar->AddButton (pB);
}

void Interface::Update (float dt)
{
   static float count = 0;
   mClock.Update(1); // 1 minute update
   if( count < 1)
   {
      count = dt;
      if( mClock.GetDayOfYear() != mCurDay )
      {
         mStats.SetDayOfWeek (mClock.DayOfWeekToString());
         mStats.SetDate (mClock.DateString());
         mCurDay = mClock.GetDayOfYear();
      }
      mStats.Update();
   }
   count--;
}

void Interface::Draw ()
{
   
   mpToolBar->Draw ();
   mClock.Draw ();
   mStats.Draw ();
}

void Interface::SetLanguageCode (int code)
{
   mLanguageCode = code;
   mClock.SetLanguage (code);
   mChangedSettings = true;
   mCurDay = 0;
}

void Interface::SetSoundFx (bool bFX)
{
   mSoundFxOn = bFX;
   // toddle the sound fx
   mChangedSettings = true;
   mCurDay = 0;
}

void Interface::SetMusic ( bool bMusic)
{
   mMusicOn = bMusic;
   // toggle the music player
   mChangedSettings = true;
   mCurDay = 0;
}

bool Interface::OnMouseDown (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb)
{
   Vector2i pt(pointa.x, (int)m_fHeight - pointa.y);
   int hit = mpToolBar->TestHit (pt);
   if( hit )
   {
      int t = hit;
      //hit
   }
   return false; // leave the message in for the pointer
}

bool Interface::OnMouseUp (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb)
{
   Vector2i pt(pointa.x, (int)m_fHeight - pointa.y);
   int hit = mpToolBar->TestHit (pt);
   if( hit )
   {
      return mEVH.HandleEvents ((HR_Events)hit);
   }
   return false; // leave the message in for the pointer
}

bool Interface::OnMouseMove ( Vector2i pointa, Vector2i pointb)
{
   Vector2i pt(pointa.x, (int)m_fHeight - pointa.y);
   int hit = mpToolBar->TestHit (pt);
   if( hit )
   {
   }
   return true;
}

