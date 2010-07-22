 /***********************************************************************
 filename:   Theme Park application
 *   Thanks to Paul D Turner & The CEGUI Development Team for samples
 *
 *   This file is part of Theme Park Builder 3D The Game.
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
#include "../Delegates/KeyNavDelegate.h"
#include "../Hub/Event.h"
#include "LabelViewObject.h"
#include "CheckViewObject.h"
#include "ButtonViewObject.h"
#include "RadioButtonViewObject.h"
#include "WindowViewObject.h"
#include "SettingsWindow.h"
#include "Interface.h"

SettingsWindow::SettingsWindow(Interface& rInterface)
:  mInterface(rInterface)
{
   mpWnd = NULL;
   mpLanguageGroup = new GroupViewEvent("Group");
   mpDelegate = NULL;
}

SettingsWindow::~SettingsWindow()
{
   if (mpWnd != NULL)
   {
      Destroy();
   }
   delete mpLanguageGroup;
}

bool SettingsWindow::Create (float fx, float fy)
{
   // create the window frame
   mpWnd = new WindowViewObject (fx, fy, 1, NULL);
   mpWnd->Resize (250, 300);
   mpWnd->SubscribeEvent (ViewEvent::ParentClose, new EventSubscriber(1, &SettingsWindow::OnClose, this));
   mpDelegate = new KeyNavDelegate ("Settings", mpWnd);

   // add the title blocks followed by teh controls.
   // subscribe the events so Settings window can get notice.
   LabelViewObject* mpLabel1 =  new LabelViewObject (10, 10, 2, *mpWnd);
   mpLabel1->set_Text ("Sound and Music Options");
   LabelViewObject* mpLabel2 =  new LabelViewObject (10, 90, 2, *mpWnd);
   mpLabel2->set_Text ("Language Options");
   mpWnd->AddChild (mpLabel1);
   mpWnd->AddChild (mpLabel2);

   // Sound and Music options
   mpSoundFx = new CheckViewObject(10, 30, 2, *mpWnd);
   mpSoundFx->Visible (true);
   mpSoundFx->set_Text ("Sound On");
   mpSoundFx->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(2, &SettingsWindow::OnSoundCheck, this));

   mpMusic = new CheckViewObject(10, 60, 3, *mpWnd);
   mpMusic->Visible (true);
   mpMusic->set_Text ("Music On");
   mpMusic->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(3, &SettingsWindow::OnMusicCheck, this));
   mpMusic->Select(true);

   // Language group all subscribe to an event ring mpLanguageGroup.
   mpEnglish = new RadioButtonViewObject (10, 110, 4, *mpWnd, *mpLanguageGroup);
   mpEnglish->Visible (true);
   mpEnglish->set_Text ("English");
   mpEnglish->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(4, &SettingsWindow::OnEnglish, this));

   mpFrench = new RadioButtonViewObject (10, 140, 5, *mpWnd, *mpLanguageGroup);
   mpFrench->Visible (true);
   mpFrench->set_Text ("French");
   mpFrench->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(5, &SettingsWindow::OnFrench, this));

   mpGerman = new RadioButtonViewObject (10, 170, 6, *mpWnd, *mpLanguageGroup);
   mpGerman->Visible (true);
   mpGerman->set_Text ("Deutsch");
   mpGerman->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(6, &SettingsWindow::OnDeutsch, this));

   mpItalian = new RadioButtonViewObject (10, 200, 7, *mpWnd, *mpLanguageGroup);
   mpItalian->Visible (true);
   mpItalian->set_Text ("Italian");
   mpItalian->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(7, &SettingsWindow::OnItalian, this));

   mpSpanish = new RadioButtonViewObject (10, 230, 7, *mpWnd, *mpLanguageGroup);
   mpSpanish->Visible (true);
   mpSpanish->set_Text ("Espaniol");
   mpSpanish->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(8, &SettingsWindow::OnSpanish, this));

   mpEnglish->Select(true);

   mpClose = new ButtonViewObject(100, 270,8, *mpWnd);
   mpClose->Resize (64, 24);
   mpClose->Visible (true);
   mpClose->set_Text ("Close");
   mpClose->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(9, &SettingsWindow::OnClose, this));

   mpWnd->AddChild (mpSoundFx);
   mpWnd->AddChild (mpMusic);
   mpWnd->AddChild (mpEnglish);
   mpWnd->AddChild (mpFrench);
   mpWnd->AddChild (mpGerman);
   mpWnd->AddChild (mpItalian);
   mpWnd->AddChild (mpSpanish);
   mpWnd->AddChild (mpClose);
   mpSpanish->Hit (true);
   return true;
}

void SettingsWindow::Draw ()
{
   if (mpWnd != NULL)
   {
      mpWnd->Draw();
   }
}

int  SettingsWindow::TestHit (Vector2i& point)
{
   return mpWnd->TestHit (point);
}

int  SettingsWindow::Dispatch (short code, Vector2i& point)
{
   int iResult = mpWnd->Dispatch (code, point);
   return iResult;
}

int SettingsWindow::OnClose(const EventArgs& e)
{
   mpWnd->Close(); // set the window to close state
   return ViewEvent::ParentClose;
}

int SettingsWindow::OnSoundCheck(const EventArgs& e)
{
   mInterface.SetSoundFx( (mpSoundFx->isChecked()) );
   return ViewEvent::None;
}

int SettingsWindow::OnMusicCheck(const EventArgs& e)
{
   mInterface.SetMusic( (mpMusic->isChecked()) );
   return ViewEvent::None;
}

int SettingsWindow::OnEnglish(const EventArgs& e)
{
   mInterface.SetLanguageCode(1);
   return ViewEvent::None;
}

int SettingsWindow::OnSpanish(const EventArgs& e)
{
   mInterface.SetLanguageCode(2);
   return ViewEvent::None;
}

int SettingsWindow::OnDeutsch(const EventArgs& e)
{
   mInterface.SetLanguageCode(3);
   return ViewEvent::None;
}

int SettingsWindow::OnFrench(const EventArgs& e)
{
   mInterface.SetLanguageCode(4);
   return ViewEvent::None;
}

int SettingsWindow::OnItalian (const EventArgs& e)
{
   mInterface.SetLanguageCode(5);
   return ViewEvent::None;
}

/*************************************************************************
Cleans up resources allocated in the initialiseSample call.
*************************************************************************/
void SettingsWindow::Destroy()
{
   if (mpWnd != NULL)
   {
      // destroy window
      delete mpWnd;
      mpWnd = NULL;
   }
}
