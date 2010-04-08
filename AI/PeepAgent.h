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

#ifndef _PeepsAGENT_H
#define _PeepsAGENT_H

#include <stack>

struct Location; // from person
class Person;
class Park;
class Pathway;

class PathFind
{
   public:
      PathFind(Person *peep, Pathway *distPath);
      ~PathFind() {;}

      bool Update();
      bool Find(Pathway *p);

      bool HasPath() { return mFound; }

      Pathway *GetDestination() { return dest; }

   private:
      Pathway *start;
      Pathway *dest;
      Person *mPeep;

      bool mFound;

      std::vector<Pathway *> path;
      std::stack<Pathway *> stack;

      // Used for interpolation
      std::vector<Vector3f> Interpolation;
      int iter;
};

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
