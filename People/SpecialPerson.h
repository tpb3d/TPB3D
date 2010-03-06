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

// Special Peeps, Inspectors, Body Guards, Secret Service etc.

#pragma once
#ifndef _SPECIALPERSON_H
#define _SPECIALPERSON_H

#include "person.h" // includes other needed resources


class SpecialPerson : public Person
{
public:
   // specialized work enumerations

   enum Special_State
   {
      WS_Observing,   // No really doing anything
      WS_Relaxing,
      WS_Inspecting,
      WS_Writing,
      WS_OnThePhone,
      WS_LunchBreak // be sure the service personell take one
   };

private:
   Special_State     mSpecialState;
   
   int      mWorkID;
public:
   // CTOR/DTOR
   SpecialPerson (Location& loc);    // x is their starting point, usually in the lobby.
   virtual ~SpecialPerson (void);

   // Properties
   Special_State GetSpecialState () // inline for faster access, same isolation, just quicker code.
   {
      return mSpecialState;
   }
   void SetSpecialState (Special_State state )
   {
      mSpecialState = state;
   }
   unsigned int GetWorkID()   // time clock number
   {
      return mWorkID;
   }
   void SetWorkID (unsigned int id)
   {
      mWorkID = id;   // clock number
   }
   // Implementation methods
   void Update (int tod);
   void Draw ();
   void Draw (int vx, int vy);


};

#endif //_SPECIALPERSON_H
