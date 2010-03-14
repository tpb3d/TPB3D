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

// root of the Pathways and subPathways, the building/ Park.
// create an instance of this. The lobby is created empty.
// call newPathway or newSubPathway to add floors or basement Pathways
#pragma once

class Ride;
class RideNode;
class Scene;

// Park is a ModelObject along with all the FloorSpace entities
// This renderes the Park in the ModelSpaces with perspective, pan and zoom.
class RideManager
{
   Scene& mScene;
private:

public:
   RideManager( Scene& scene);
   ~RideManager() {}
   void InitialSetup();

   bool Settings();
   bool FRCS();
};
