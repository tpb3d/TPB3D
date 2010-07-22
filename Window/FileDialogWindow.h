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

class Interface;
class EventArgs;
class ListViewObject;
class ScrollViewObject;
class ButtonViewObject;
class WindowViewObject;
class LabelViewObject;
class GUIDelegate;

class FileDialogWindow
{
public:
   enum FileDialogType
   {
      FDT_OpenFile,
      FDT_SaveFile
   };
protected:
   WindowViewObject* mpWnd;
   GUIDelegate* mpDelegate;
   ButtonViewObject* mpClose;
   ButtonViewObject* mpOpen;
   ButtonViewObject* mpSave;
   LabelViewObject*  mpLabel1;
   LabelViewObject*  mpLabel2;
   ScrollViewObject* mpScroll;
   ListViewObject* mpList;

   Interface& mInterface;
   FileDialogType mDialogType;
public:
   FileDialogWindow (Interface& rInterface, FileDialogType fdt);
   ~FileDialogWindow ();

   GUIDelegate* get_Delegate() { return mpDelegate; }
   WindowViewObject::WindowState get_State() { return mpWnd->get_State(); }

public:
   bool Create (float fx, float fy);
   void Destroy ();
   void Draw ();

   // based on event types
   int OnScroll (const EventArgs& e);
   int OnSelect (const EventArgs& e);
   int OnOpen (const EventArgs& e);
   int OnSave (const EventArgs& e);
   int OnClose (const EventArgs& e);
};
