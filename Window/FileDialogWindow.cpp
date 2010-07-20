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
#include "../Delegates/GUIDelegate.h"
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

bool FileDialogWindow::Create ()
{
   // create the window frame
   mpWnd = new WindowViewObject(0, 0, 1, NULL);
   mpWnd->Resize (400, 300);

   // add the title blocks followed by teh controls.
   // subscribe the events so FileDialog window can get notice.
   LabelViewObject* mpLabel1 =  new LabelViewObject (10, 280, 2, *mpWnd);
   mpLabel1->set_Text ("Open/Save File");
   LabelViewObject* mpLabel2 =  new LabelViewObject (10, 250, 2, *mpWnd);
   mpLabel2->set_Text ("Files");
   mpWnd->AddChild (mpLabel1);
   mpWnd->AddChild (mpLabel2);


   // Scroll List
   mpList = new ListViewObject(10, 320, 2, *mpWnd);
   mpList->Visible (true);
   mpList->Resize (300,300);
   mpList->AddText ("File1");
   mpList->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnSelect, this));

   mpScroll = new ScrollViewObject(350, 48, 3, *mpWnd);
   mpScroll->Resize (20,250);
   mpScroll->Visible (true);
   mpScroll->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnScroll, this));
   mpScroll->Select(true);

   // Buttons Cancel and either Open or Save.

   mpClose = new ButtonViewObject(300,20,4, *mpWnd);
   mpClose->Resize (64, 20);
   mpClose->Visible (true);
   mpClose->set_Text ("Cancel");
   mpClose->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnClose, this));
   mpOpen = new ButtonViewObject(200,20,5, *mpWnd);
   mpOpen->Resize (64, 20);
   mpOpen->Visible (false);
   mpOpen->set_Text ("Open");
   mpOpen->SubscribeEvent (ViewEvent::Changed, new EventSubscriber(1, &FileDialogWindow::OnOpen, this));
   mpSave = new ButtonViewObject(200,20,6, *mpWnd);
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

void FileDialogWindow::Draw ()
{
   if (mpWnd != NULL)
   {
      mpWnd->Draw();
   }
}

bool FileDialogWindow::OnClose(const EventArgs& e)
{
   Destroy();
   return true;
}

bool FileDialogWindow::OnSave(const EventArgs& e)
{
   return true;
}

bool FileDialogWindow::OnOpen(const EventArgs& e)
{
   return true;
}

bool FileDialogWindow::OnSelect(const EventArgs& e)
{
   return true;
}

bool FileDialogWindow::OnScroll(const EventArgs& e)
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
