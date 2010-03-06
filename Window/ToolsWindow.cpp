 /***********************************************************************
 *   Ride Toolbox for Theme Park Application
 *   Thanks to Paul D Turner & The CEGUI Development Team for samples
 *
 *   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "CEGUI.h"
#include "CEGUIPropertyHelper.h"
#include "../Graphics/Image.h"

#include "ToolsWindow.h"

using namespace CEGUI;

#define SKIN "WindowsLook"

ToolsWindow::ToolsWindow()
{
   mpWnd = NULL;
}

ToolsWindow::~ToolsWindow()
{
   // win manager does this but we may want to use it later
   //if (mpWnd != NULL)
   //{
   //   Destroy();
   //}
}

bool ToolsWindow::Create(CEGUI::Window* pRoot)
{
   // we will use of the WindowManager.
   WindowManager& winMgr = WindowManager::getSingleton ();

   // load some demo windows and attach to the background 'root'
   // because of the 2nd parameter, all windows get prefixed with "ToolTabs/"
   CEGUI::String prefix = "Frame/";
   mpWnd = winMgr.loadWindowLayout ("ToolTabs.layout");//, prefix);
   mpWnd->setPrefix(prefix);
   pRoot->addChildWindow (mpWnd);
   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&ToolsWindow::OnClose, this));

   TabControl *tc = static_cast<TabControl *>(winMgr.getWindow ("Frame/TabControl"));
   
   // Add some pages to tab control
   tc->addTab (winMgr.loadWindowLayout ("ToolTabFRCS.layout", prefix));
   tc->addTab (winMgr.loadWindowLayout ("ToolTabTRCS.layout", prefix));
   tc->addTab (winMgr.loadWindowLayout ("ToolTabTerrain.layout", prefix));

   // What did it load?
   WindowManager::WindowIterator it =  CEGUI::WindowManager::getSingleton().getIterator();
   for(; !it.isAtEnd() ; ++it)
   {
      const char* windowName = it.getCurrentValue()->getName().c_str();
      printf("Name: %s\n", windowName);
   }

   static_cast<PushButton *> (
      winMgr.getWindow("Frame/frcs/NewRide"))->subscribeEvent (
      PushButton::EventClicked,
      Event::Subscriber (&ToolsWindow::OnNewRide, this));

   static_cast<PushButton *> (
      winMgr.getWindow("Frame/frcs/Place"))->subscribeEvent (
      PushButton::EventClicked,
      Event::Subscriber (&ToolsWindow::OnPlace, this));

   RefreshPartList ();

   // From now on, we don't rely on the exceptions anymore, but perform nice (and recommended) checks
   // ourselves.

   return true;
}

// method to perform any required cleanup operations.
void ToolsWindow::Destroy()
{
   using namespace CEGUI;
   if (mpWnd != NULL)
   {
      CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
      winMgr.destroyWindow(mpWnd);
      mpWnd = NULL;
   }
}

bool ToolsWindow::OnClose(const CEGUI::EventArgs& e)
{
   Destroy();
   return true;
}

void ToolsWindow::RefreshPartList ()
{
   WindowManager& winMgr = WindowManager::getSingleton ();
   // Check if the windows exists
   Listbox *lbox = NULL;
   TabControl *tc = NULL;
   if (winMgr.isWindowPresent("Frame/TabControl"))
   {
      tc = static_cast<TabControl *>(winMgr.getWindow (
         "Frame/TabControl"));
      if (winMgr.isWindowPresent("Frame/frcs/PartList"))
      {
         lbox = static_cast<Listbox *> (winMgr.getWindow(
            "Frame/frcs/PartList"));
      }
      if (lbox && tc)
      {
         lbox->resetList ();
         lbox->addItem (new ListItem ("Dino_Car"));
         lbox->addItem (new ListItem ("Dino_Arm"));
         lbox->addItem (new ListItem ("Dino_Hub"));
         lbox->addItem (new ListItem ("Dino_Base"));
      }
      if (winMgr.isWindowPresent("Frame/terrain/PartList"))
      {
         lbox = static_cast<Listbox *> (winMgr.getWindow(
            "Frame/terrain/PartList"));
      }
      if (lbox && tc)
      {
         lbox->resetList ();
         lbox->addItem (new ListItem ("Southern Pine"));
         lbox->addItem (new ListItem ("Dawn Cypress"));
         lbox->addItem (new ListItem ("Hemlock"));
         lbox->addItem (new ListItem ("Redwood"));
      }
   }
}

bool ToolsWindow::OnNewRide (const EventArgs& e)
{

   return true;
}

bool ToolsWindow::OnPlace (const EventArgs& e)
{
   WindowManager& winMgr = WindowManager::getSingleton ();
   // Check if the windows exists
   Listbox *lbox = NULL;
   TabControl *tc = NULL;
   if (winMgr.isWindowPresent("Frame/frcs/PageList"))
   {
      lbox = static_cast<Listbox *> (winMgr.getWindow(
         "Frame/frcs/PageList"));
   }
   if (winMgr.isWindowPresent("Frame/TabControl"))
   {
      tc = static_cast<TabControl *>(winMgr.getWindow (
         "Frame/TabControl"));
   }
   if (lbox && tc)
   {
      ListboxItem *lbi = lbox->getFirstSelectedItem ();
      if (lbi)
      {
         tc->setSelectedTab (lbi->getText ());
      }
   }

   return true;
}

