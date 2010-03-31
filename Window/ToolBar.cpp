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

#include <cstring>
#include <map>
#include "../Utility/GameException.h"
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "ToolButton.h"
#include "ToolBar.h"

using namespace Gfx;

ToolBar::ToolBar (int ToolCount, short ID)
{
   mID = ID;
   m_ButtonCount = 0;
   m_ButtonMax = ToolCount;
   try
   {
      m_pButtons = new ToolButton*[ToolCount];
   }
   catch( ... )
   {
      throw new GameException ("Error Creating a Toolbutton!");
   }
}

ToolBar::~ToolBar ()
{
   try
   {
      for(int ix = 0; ix < m_ButtonMax; ++ix)
      {
         ToolButton* pButton = m_pButtons[ix];
         delete [] pButton;
      }
   }
   catch( ... )
   {
      throw new GameException ("Error Removing a Toolbutton from the heap!");
   }
   try
   {
      delete [] m_pButtons;
   }
   catch( ... )
   {
      throw new GameException ("Error Removing a Toolbar from the heap!");
   }
}

void ToolBar::AddButton (ToolButton* pButton)
{
   if(m_ButtonCount < m_ButtonMax)
   {
      m_pButtons[m_ButtonCount++] = pButton;
   }
   else
   {
      throw new GameException ("Error adding buttons to the toolbar, exceeded max preallocation size!");
   }
}

void ToolBar::Clear ()
{
   // clear all the button's states
   for(int ix = 0; ix < m_ButtonMax; ++ix)
   {
      ToolButton* pButton = m_pButtons[ix];
      pButton->Clear();
   }
}

int ToolBar::TestHit (Vector2i point)
{
   int hit = 0;
   for(int ix = 0; hit == 0 && ix < m_ButtonMax; ++ix)
   {
      ToolButton* pButton = m_pButtons[ix];
      hit = pButton->TestHit (point);
   }
   return hit;
}

//void ToolBar::Update (int state)
//{
//   for(int ix = 0; ix < m_ButtonMax; ++ix)
//   {
//      ToolButton* pButton = m_pButtons[ix];
//      pButton->Update (state);
//   }
//}

void ToolBar::Draw ()
{
   Render (&m_Border);
   for(int ix = 0; ix < m_ButtonMax; ++ix)
   {
      ToolButton* pButton = m_pButtons[ix];
      pButton->Draw();
   }
}
