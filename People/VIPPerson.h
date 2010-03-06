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

// Stafe that make the Park run, pay them well.
// Annoy them and they will quit!
#ifndef _VIPPERSON_H
#define _VIPPERSON_H

#include "person.h" // includes other needed resources


class VIPPerson : public Person
{
public:
   // CTOR/DTOR
   VIPPerson (Location& loc);    // x is their starting point, usually in the lobby.
   virtual ~VIPPerson (void);

   // Implementation methods
   void Update (int tod);
   void Draw ();
   void Draw (int vx, int vy);


};

#endif //_VIPPERSON_H
