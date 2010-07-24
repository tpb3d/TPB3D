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
#include "ListViewObject.h"
#include "ScrollViewObject.h"
#include "ButtonViewObject.h"
#include "WindowViewObject.h"
#include "FileDialogWindow.h"
#include "Interface.h"

FileDialogWindow::FileDialogWindow(Interface& rInterface, FileDialogType fdt)
:  mInterface(rInterface)
,  mDialogType (fdt)
{
   mpWnd = NULL;
   mpClose = NULL;
   mpOpen = NULL;
   mpSave = NULL;
   mpLabel1 = NULL;
   mpLabel2 = NULL;
   mpScroll = NULL;
}

FileDialogWindow::~FileDialogWindow()
{
   if (mpWnd != NULL)
   {
      Destroy();
   }
}

bool FileDialogWindow::Create (float fx, float fy)
{
   // create the window frame
   mpWnd = new WindowViewObject(fx, fy, 1, NULL);
   mpWnd->Resize (360, 300);
   mpWnd->SubscribeEvent (ViewEvent::ParentClose, new EventSubscriber(1, &FileDialogWindow::OnClose, this));
   if (mDialogType == FDT_OpenFile)
   {
      mpWnd->set_Text ("Open File");
   }
   else
   {
      mpWnd->set_Text ("Save File");
   }
   mpDelegate = new KeyNavDelegate ("File", mpWnd);

   // add the title blocks followed by teh controls.
   // subscribe the events so FileDialog window can get notice.
   LabelViewObject* mpLabel1 =  new LabelViewObject (10, 2, 2, *mpWnd);
   mpLabel1->set_Text ("Files");
   mpWnd->AddChild (mpLabel1);


   // Scroll List
   mpList = new ListViewObject(10, 10, 3, *mpWnd);
   mpList->Visible (true);
   mpList->Resize (300,250);

   // PLAY DATA
   mpList->AddText ("A really BIG park");
   mpList->AddText ("Dark Park");
   mpList->AddText ("Diamond Springs Park");
   mpList->AddText ("Diamondback Rattler World");
   mpList->AddText ("Flatrideville");
   mpList->AddText ("Overkill loaded with coasters no flats");
   mpList->AddText ("Peep Slide Fun Park");
   mpList->AddText ("Perrindle Park");
   mpList->AddText ("Rattlesnake infested zoo");
   mpList->AddText ("Small park");
   mpList->AddText ("Test Parks and faked data");
   mpList->AddText ("TORCG wished it had these rides");
   mpList->AddText ("Wishwehadwaterparks");
   mpList->AddText ("Yellow Bolder Screams and Chills");
   mpList->AddText ("Zephyrs and Zoos");
   // END

   mpList->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnSelect, this));

   mpScroll = new ScrollViewObject(320, 20, 4, *mpWnd);
   mpScroll->Resize (20,250);
   mpScroll->Visible (true);
   mpScroll->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnScroll, this));
   mpScroll->Select(true);

   // Buttons Cancel and either Open or Save.

   mpClose = new ButtonViewObject(276, 280, 5, *mpWnd);
   mpClose->Resize (64, 20);
   mpClose->Visible (true);
   mpClose->set_Text ("Cancel");
   mpClose->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnClose, this));
   mpOpen = new ButtonViewObject(200, 280, 6, *mpWnd);
   mpOpen->Resize (64, 20);
   mpOpen->Visible (false);
   mpOpen->set_Text ("Open");
   mpOpen->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnOpen, this));
   mpSave = new ButtonViewObject(200, 280, 7, *mpWnd);
   mpSave->Resize (64, 20);
   mpSave->Visible (false);
   mpSave->set_Text ("Save");
   mpSave->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnSave, this));

   if (mDialogType == FDT_SaveFile)
   {
      mpSave->Visible (true);
   }
   else
   {
      mpOpen->Visible (true);
   }
   mpWnd->AddChild (mpList);
   mpWnd->AddChild (mpScroll);
   mpWnd->AddChild (mpOpen);
   mpWnd->AddChild (mpSave);
   mpWnd->AddChild (mpClose);
   return true;
}

int FileDialogWindow::TestHit (Vector2i& point)
{
   return mpWnd->TestHit (point);
}

void FileDialogWindow::Draw ()
{
   if (mpWnd != NULL)
   {
      mpWnd->Draw();
   }
}

int FileDialogWindow::OnClose(const EventArgs& e)
{
   mpWnd->Close(); // set the window to close state
   return ViewEvent::ParentClose;
}

int FileDialogWindow::OnSave(const EventArgs& e)
{
   return true;
}

int FileDialogWindow::OnOpen(const EventArgs& e)
{
   return true;
}

int FileDialogWindow::OnSelect(const EventArgs& e)
{
   return true;
}

int FileDialogWindow::OnScroll(const EventArgs& e)
{
   return true;
}

/*************************************************************************
Cleans up resources allocated in the initialiseSample call.
*************************************************************************/
void FileDialogWindow::Destroy()
{
   if (mpWnd != NULL)
   {
      // destroy window
      delete mpWnd;
      mpWnd = NULL;
   }
}
