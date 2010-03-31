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

// Stafe that make the Park run, pay them well.
// Annoy them and they will quit!
#ifndef _STAFFPERSON_H
#define _STAFFPERSON_H

#include "Person.h" // includes other needed resources


class StaffPerson : public Person
{
public:
   // specialized work enumerations

   enum Work_State
   {
      WS_Sleeping,   // first four are done at home (mostly).
      WS_Relaxing,
      WS_Playing,
      WS_Reading,
      WS_Repairing,
      WS_Sweeping,
      WS_LunchBreak, // be sure the service personell take one
      WS_GoingToCall // destination set and going there now
   };

private:
   Health_State   mHealth;
   Mood_State     mWorkMood;
   Work_State     mWorkState;
   
   int      mWorkID;
public:
   // CTOR/DTOR
   StaffPerson (Location& loc);    // x is their starting point, usually in the lobby.
   virtual ~StaffPerson (void);

   // Properties
   Work_State GetWorkState () // inline for faster access, same isolation, just quicker code.
   {
      return mWorkState;
   }
   void SetWorkState (Work_State state )
   {
      mWorkState = state;
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

#endif //_STAFFPERSON_H
