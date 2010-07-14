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
#include "../Delegates/WindowDelegate.h"
#include "CheckViewObject.h"
#include "WindowViewObject.h"
#include "SettingsWindow.h"
#include "Interface.h"

SettingsWindow::SettingsWindow(Interface& rInterface)
:  mInterface(rInterface)
{
   mpWnd = NULL;
}

SettingsWindow::~SettingsWindow()
{
   if (mpWnd != NULL)
   {
      Destroy();
   }
}

/*************************************************************************
Sample specific initialisation goes here.
*************************************************************************/
bool SettingsWindow::Create ()
{
/*
// Code provided by Paul D Turner (C) 2005
   CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
   // A FrameWindow is a window with a frame and a titlebar which may be moved around
   // and resized.
   //
   // Create a FrameWindow in the TaharezLook style, and name it 'Demo Window'
   mpWnd = (FrameWindow*)winMgr.createWindow( LOOK "/FrameWindow", "Settings");
   // Here we attach the newly created FrameWindow to the previously created
   // DefaultWindow which we will be using as the root of the displayed gui.
   pRoot->addChildWindow(mpWnd);

   // Windows are in Relative metrics mode by default.  This means that we can
   // specify sizes and positions without having to know the exact pixel size
   // of the elements in advance.  The relative metrics mode co-ordinates are
   // relative to the parent of the window where the co-ordinates are being set.
   // This means that if 0.5f is specified as the width for a window, that window
   // will be half as its parent window.
   //
   // Here we set the FrameWindow so that it is half the size of the display,
   // and centered within the display.
   mpWnd->setPosition(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.25f)));
   mpWnd->setSize(UVector2(cegui_reldim(0.5f), cegui_reldim( 0.5f)));

   // now we set the maximum and minum sizes for the new window.  These are
   // specified using relative co-ordinates, but the important thing to note
   // is that these settings are aways relative to the display rather than the
   // parent window.
   //
   // here we set a maximum size for the FrameWindow which is equal to the size
   // of the display, and a minimum size of one tenth of the display.
   mpWnd->setMaxSize(UVector2(cegui_reldim(1.0f), cegui_reldim( 1.0f)));
   mpWnd->setMinSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));

   // As a final step in the initialisation of our sample window, we set the window's
   // text to "Hello World!", so that this text will appear as the caption in the
   // FrameWindow's titlebar.

   mpWnd->setText("Theme Park Builder 3D Developer Preferences");


   // Code by AlabamaCajun
   Window* pLabel1 = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label1");
   Window* pLabel2 = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label2");
   Window* pLabel3 = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label3");
   Window* pLabel3a = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label3a");
   Window* pLabel3b = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label3b");
   Window* pLabel3c = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label3c");
   Window* pLabel3d = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label3d");
   Window* pLabel3e = winMgr.createWindow( LOOK "/StaticText", "TPB3DTG/ControlPanel/Label3s");
   // Sound Label
   pLabel1->setProperty("FrameEnabled", "false");
   pLabel1->setProperty("BackgroundEnabled", "false");
   pLabel1->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim( 0.1f)));
   pLabel1->setSize(UVector2(cegui_reldim(0.26f), cegui_reldim( 0.1f)));
   pLabel1->setText("Enable Sound:");
   // Sound Enable CheckBox
   mpSoundFx = static_cast<CEGUI::Checkbox*>(winMgr.createWindow(LOOK "/Checkbox", "Settings/SoundChechBox"));
   mpSoundFx->setSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));
   mpSoundFx->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.1f)));
   mpSoundFx->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnSoundCheck, this));
   mpSoundFx->setSelected (mInterface.GetSoundFx()); 

   // Music Label
   pLabel2->setProperty("FrameEnabled", "false");
   pLabel2->setProperty("BackgroundEnabled", "false");
   pLabel2->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim( 0.2f)));
   pLabel2->setSize(UVector2(cegui_reldim(0.26f), cegui_reldim( 0.1f)));
   pLabel2->setText("Enable Music:");
   // Music Enable CheckBox
   mpMusic = static_cast<CEGUI::Checkbox*>(winMgr.createWindow(LOOK "/Checkbox", "Settings/MusicCheckBox"));
   mpMusic->setSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));
   mpMusic->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.2f)));
   mpMusic->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnMusicCheck, this));
   mpMusic->setSelected (mInterface.GetMusic());

   // Lanugage Label
   int code = mInterface.GetLanguageCode();
   pLabel3->setProperty("FrameEnabled", "false");
   pLabel3->setProperty("BackgroundEnabled", "false");
   pLabel3->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim( 0.3f)));
   pLabel3->setSize(UVector2(cegui_reldim(0.2f), cegui_reldim( 0.1f)));
   pLabel3->setText("Language:");
   CEGUI::RadioButton* pBox3a = static_cast<CEGUI::RadioButton*>(winMgr.createWindow(LOOK "/RadioButton", "Settings3/EnglishCheckBox"));
   pBox3a->setSize(UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f)));
   pBox3a->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.3f)));
//   pBox3a->addEvent("EnglishChecked");
   if (code==1) pBox3a->setSelected(true);
   pBox3a->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnEnglish, this));

   CEGUI::RadioButton* pBox3b = static_cast<CEGUI::RadioButton*>(winMgr.createWindow(LOOK "/RadioButton", "Settings3/SpanishCheckBox"));
   pBox3b->setSize(UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f)));
   pBox3b->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.375f)));
   if (code==2) pBox3b->setSelected(true);
   pBox3b->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnSpanish,this));

   CEGUI::RadioButton* pBox3c = static_cast<CEGUI::RadioButton*>(winMgr.createWindow(LOOK "/RadioButton", "Settings3/DeutschCheckBox"));
   pBox3c->setSize(UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f)));
   pBox3c->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.525f)));
   if (code==4) pBox3c->setSelected(true);
   pBox3c->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnDeutsch,this));

   CEGUI::RadioButton* pBox3d = static_cast<CEGUI::RadioButton*>(winMgr.createWindow(LOOK "/RadioButton", "Settings3/FrenchCheckBox"));
   pBox3d->setSize(UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f)));
   pBox3d->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.45f)));
   if (code==3) pBox3d->setSelected(true);
   pBox3d->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnFrench,this));

   CEGUI::RadioButton* pBox3e = static_cast<CEGUI::RadioButton*>(winMgr.createWindow(LOOK "/RadioButton", "Settings3/ItalianCheckBox"));
   pBox3e->setSize(UVector2(cegui_reldim(0.05f), cegui_reldim( 0.05f)));
   pBox3e->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.6f)));
   if (code==4) pBox3e->setSelected(true);
   pBox3e->subscribeEvent (RadioButton::EventMouseClick, Event::Subscriber(&SettingsWindow::OnItalian,this));

   // Lanugage Label
   pLabel3a->setProperty("FrameEnabled", "false");
   pLabel3a->setProperty("BackgroundEnabled", "false");
   pLabel3a->setPosition(UVector2(cegui_reldim(0.375f), cegui_reldim( 0.3f)));
   pLabel3a->setSize(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.05f)));
   pLabel3a->setText("English");
   pLabel3b->setProperty("FrameEnabled", "false");
   pLabel3b->setProperty("BackgroundEnabled", "false");
   pLabel3b->setPosition(UVector2(cegui_reldim(0.375f), cegui_reldim( 0.375f)));
   pLabel3b->setSize(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.05f)));
   pLabel3b->setText("Deutsch");
   pLabel3c->setProperty("FrameEnabled", "false");
   pLabel3c->setProperty("BackgroundEnabled", "false");
   pLabel3c->setPosition(UVector2(cegui_reldim(0.375f), cegui_reldim( 0.525f)));
   pLabel3c->setSize(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.05f)));
   pLabel3c->setText("Spanish");
   pLabel3d->setProperty("FrameEnabled", "false");
   pLabel3d->setProperty("BackgroundEnabled", "false");
   pLabel3d->setPosition(UVector2(cegui_reldim(0.375f), cegui_reldim( 0.45f)));
   pLabel3d->setSize(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.05f)));
   pLabel3d->setText("French");
   pLabel3e->setProperty("FrameEnabled", "false");
   pLabel3e->setProperty("BackgroundEnabled", "false");
   pLabel3e->setPosition(UVector2(cegui_reldim(0.375f), cegui_reldim( 0.6f)));
   pLabel3e->setSize(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.05f)));
   pLabel3e->setText("Italian");

   mpWnd->addChildWindow(pLabel1);
   mpWnd->addChildWindow(pLabel2);
   mpWnd->addChildWindow(pLabel3);
   mpWnd->addChildWindow(pLabel3a);
   mpWnd->addChildWindow(pLabel3b);
   mpWnd->addChildWindow(pLabel3c);
   mpWnd->addChildWindow(pLabel3d);
   mpWnd->addChildWindow(pLabel3e);

   mpWnd->addChildWindow(mpSoundFx);
   mpWnd->addChildWindow(mpMusic);
   mpWnd->addChildWindow(pBox3a);
   mpWnd->addChildWindow(pBox3b);
   mpWnd->addChildWindow(pBox3c);
   mpWnd->addChildWindow(pBox3d);
   mpWnd->addChildWindow(pBox3e);
*/
   // subscribe handler that closes the dialog
//   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&SettingsWindow::OnClose, this));

   mpWnd = new WindowViewObject(200, 100, 1, NULL);

   mpSoundFx = new CheckViewObject(10, 30, 1, *mpWnd);
   mpSoundFx->Visible (true);
   mpSoundFx->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &SettingsWindow::OnSoundCheck, this));

   mpMusic = new CheckViewObject(10, 60, 1, *mpWnd);
   mpMusic->Visible (true);
   mpMusic->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &SettingsWindow::OnMusicCheck, this));

   return true;
}

void SettingsWindow::Draw ()
{
   if (mpWnd != NULL)
   {
      mpWnd->Draw();
   }
}

bool SettingsWindow::OnClose(const EventArgs& e)
{
   Destroy();
   return true;
}

bool SettingsWindow::OnSoundCheck(const EventArgs& e)
{
//   mInterface.SetSoundFx( (mpSoundFx->isSelected()) );
   return true;
}

bool SettingsWindow::OnMusicCheck(const EventArgs& e)
{
   mInterface.SetMusic( (mpMusic->isChecked()) );
   return true;
}

bool SettingsWindow::OnEnglish(const EventArgs& e)
{
   mInterface.SetLanguageCode(1);
   return true;
}

bool SettingsWindow::OnSpanish(const EventArgs& e)
{
   mInterface.SetLanguageCode(2);
   return true;
}

bool SettingsWindow::OnDeutsch(const EventArgs& e)
{
   mInterface.SetLanguageCode(3);
   return true;
}

bool SettingsWindow::OnFrench(const EventArgs& e)
{
   mInterface.SetLanguageCode(4);
   return true;
}

bool SettingsWindow::OnItalian (const EventArgs& e)
{
   mInterface.SetLanguageCode(5);
   return true;
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
