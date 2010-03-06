/*   This file is part of Theme Park Developer 3D The Game.
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

// People that make the Park thrive.

#include <iostream>
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "GuestPerson.h"

GuestPerson::GuestPerson (Location& loc)
:  Person (loc)
{
}
GuestPerson::~GuestPerson (void)
{
}

void GuestPerson::Update (int tod)   //actual time
{
   // check time of day, what activity should we be doing.
   if (mOccupation < 1) // && age > 16 )
   {
      SetActivity (AS_JobHunting);
      return;
   }
   else if (mHome < 1 && mActivity == AS_Sleeping ) // in general, Guest is sleepping, wake up and go to work.
   {
      SetActivity (AS_GoingToWork);
      return;
   }
// this is just some code thrown in to expose some enums and give ideas on what needs implementing
   switch (mActivity)
   {
   case AS_GoingToWork:
      break;
   case AS_Working:
      break;
   case AS_LunchBreak:
      break;
   case AS_GoingHome:
      break;
   case AS_Sleeping:
      break;
   }
}

void GuestPerson::Draw ()
{
//   Render (parameters );
}

void GuestPerson::Draw (int vx, int vy)
{
//   Render (parameters, vx, vx+8 );
}
