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
#include <CEGUI.h>
#include "SettingsWindow.h"
#define LOOK "WindowsLook"

SettingsWindow::SettingsWindow()
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
bool SettingsWindow::Create (CEGUI::Window* pRoot)
{
   using namespace CEGUI;

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

   Window* pLabel = winMgr.createWindow( LOOK "/StaticText", "Demo6/ControlPanel/Label1");
   mpWnd->addChildWindow(pLabel);
   pLabel->setProperty("FrameEnabled", "false");
   pLabel->setProperty("BackgroundEnabled", "false");
   pLabel->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim( 0.2f)));
   pLabel->setSize(UVector2(cegui_reldim(0.26f), cegui_reldim( 0.2f)));
   pLabel->setText("Enable Sound:");

   CEGUI::Checkbox* pBox = static_cast<CEGUI::Checkbox*>(winMgr.createWindow(LOOK "/Checkbox", "Settings/SoundChechBox"));
   mpWnd->addChildWindow(pBox);
   pBox->setPosition(UVector2(cegui_reldim(0.28f), cegui_reldim( 0.2f)));
   pBox->setSize(UVector2(cegui_reldim(0.2f), cegui_reldim( 0.2f)));
   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&SettingsWindow::OnClose, this));

   // subscribe handler that quits the application
   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&SettingsWindow::OnSoundCheck, this));

   // return true so that the samples framework knows that initialisation was a
   // success, and that it should now run the sample.
   return true;
}

bool SettingsWindow::OnClose(const CEGUI::EventArgs& e)
{
   Destroy();
   return true;
}

bool SettingsWindow::OnSoundCheck(const CEGUI::EventArgs& e)
{
   return true;
}

/*************************************************************************
Cleans up resources allocated in the initialiseSample call.
*************************************************************************/
void SettingsWindow::Destroy()
{
   using namespace CEGUI;
   if (mpWnd != NULL)
   {
      CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
      winMgr.destroyWindow(mpWnd);
      mpWnd = NULL;
   }
}
