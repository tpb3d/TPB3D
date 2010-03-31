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

#ifndef _ROUTES_H
#define _ROUTES_H
#include <vector>

class RouteBase; // aggregate of paths, elevators and stairs

class Routes
{
private:
   std::vector<RouteBase*> mRoutes;
//   static Routes* minstance; no longer static as each Park.has it's own routes

public:
   typedef std::vector<RouteBase*>::iterator RouteIterator;
   typedef std::vector<RouteBase*> RoutesVector;

   Routes(); // not part of Park.
   ~Routes();
//   static Routes* GetInstance ();
   RoutesVector& GetRoutes()
   {
      return mRoutes;
   }
   void AddRoute(RouteBase * route);
   void Update (float dt);
   void Draw ();
};

#endif //_ROUTES_H
