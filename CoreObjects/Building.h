/*   This file is part of Theme Park Builder 3D The Game.
 =   This code originated from Exterme Park Developer.
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

#ifndef _Building_H
#define _Building_H

#include <map>

#include "../Graphics/ModelObject.h"
#include "CoreBase.h"

class SerializerBase;

enum Building_state
{
   BS_Operational,
   BS_Smoking        // equipment inside has failed, not filled with smoke
};

class Building : public CoreBase, public Gfx::ModelObject
{
   Building_state mCurrentState; // metric of building condition

public:
   Building (Vector3f& origin, Park* ParkParent);

   void Update (float dt, int tod);
   void Draw ();
   void DrawSelectionTarget ();
   virtual BaseType GetType () { return BaseBuilding; }

   void RemoveImages();
   void SetImages (int set);
   void Save(SerializerBase& ser);

   void PeopleInOut( int count );
   bool PeopleApply( );    // get a job

private:
   void BuildingState();
};

#endif
