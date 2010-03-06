/*   This file is part of TPB Developer.
 *
 *   TPB Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   TPB Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with TPB Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

/*#include <iostream>
#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include <list>

#include "../Root/Physics.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"
#include "Routes.h"
#include "../Graphics/ObjectBase.h"
#include "Pathway.h"
#include "Building.h"
#include "Park.h"

#include "../Root/TPBException.h"
// This is a debug stub to load a building for early dev

void
Park::DebugLoad (int x, int y, int x2)
{
   try
   {
      // persist these
      Elevator* pElevator = new Elevator( Elevator::LS_Standard, 472, -1, 15, this );
      GetRoutes().AddRoute( pElevator );
      pElevator = new Elevator( Elevator::LS_Standard, 472 + 36 + 9, 0, 15, this );
      GetRoutes().AddRoute( pElevator );
      Level* pLevel = GetLevel(0);
   }
   catch (...)
   {
      throw new TPBException ("Debug Alpha Building failed to create");
   }
}*/

