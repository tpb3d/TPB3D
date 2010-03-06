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

// When somone wants to go somewhere, just hand them over to their own personal travel agent.
// "MyPathAgent 2500 will take you to your destination quickly and safely, only 19.95 + S&H"
// The Activities Agent will hand people to this agent when they enter a travel state.
// A location and destination will be set for the person(s) preparing to embark. The path agent will
// then find the best path to that destination. Folks in the Park(s) will be transitioned from
// point to point.

#include <vector>
#include "../People/Person.h"
#include "../CoreObjects/Routes.h"
#include "../CoreObjects/RouteBase.h"
#include "../CoreObjects/Park.h"
#include "../AI/PeepAgent.h"

#include "PathAgent.h"

PathAgent::PathAgent (Person* person )
      :  mPerson( person )
{

}

// functor Pathway PathAgent
// Instiate, get the person to his destination and done
PathAgent::PathAgent (Person* person, int Pathway)   // deposit person on this Pathway;
      :  mPerson( person )
{
   person->get_Location();
}

PathAgent::~PathAgent ()
{

}

bool PathAgent::findPath (Location& origin, Location& dest, Park& Park )
{
   return true;
}

