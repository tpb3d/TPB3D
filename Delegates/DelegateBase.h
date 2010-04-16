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
#include <string>
#include <map>

class DelegateBase
{
protected:
   std::string mToolSelected;
//   Select& mSelect;

public:
   DelegateBase (const char* pszName)
   {
   }
public:
   virtual void OnHitDown (short ID) = 0;
   virtual void OnHitUp (short ID) = 0;
   virtual void Draw()
   {
   }
};
