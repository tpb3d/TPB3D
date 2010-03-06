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

#ifndef _PeepsAGENT_H
#define _PeepsAGENT_H

struct Location; // from person
class Person;
class Park;

class PeepsAgent
{
protected:
   Park& mPark; // must have one or more

public:
   void Update (float dt, int tod);

   PeepsAgent (Park& mPark); // use a Park agent for multiple Parks
   virtual ~PeepsAgent (void);
};

#endif //_PeepsAGENT_H
