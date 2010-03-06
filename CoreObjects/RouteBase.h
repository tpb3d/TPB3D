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

#ifndef _ROUTEBASE_H
#define _ROUTEBASE_H
class SerializerBase; // visitor;
class Person;
class PersonQueue;

struct RoutingRequest
{
   int OriginPath;
   int DestinPath;
};

class RouteBase // Abstract, does not even have a CPP file at this point.
{

public:
   RouteBase() {};
   virtual bool SetCallButton( RoutingRequest& req ) = 0;    // call the elevator
   virtual void SetFloorButton( RoutingRequest& req ) = 0;   // once inside, select a floor
   virtual int  LoadPerson(Person* person, RoutingRequest& req) = 0; // pack them in
   virtual void Update (float dt) = 0;
   virtual void Draw () = 0;
   virtual void Save( SerializerBase& ser ) = 0;
   virtual PersonQueue* FindQueue (int Path) = 0;
};

#endif //_ROUTEBASE_H
