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

#include <iostream>
#include <map>
#include <vector>
#include "../Physics/MotionPhysics.h"
#include "../Storage/SerializerBase.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "CoreBase.h"
#include "../Types/String.h"

#include "Building.h"

using namespace Gfx;

namespace ParkObjects
{
   static Vector3f VR(0,0,0);
}

using namespace ParkObjects;

Building::Building (Vector3f& origin, Park& ParkParent)
      :  mCurrentState (BS_Operational)
      ,  CoreBase (origin, origin)
      ,  mParkParent (ParkParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New Park Object at " << mvPosition.x << ", " << mvPosition.x << std::endl;
   SetImages (0);
}


void Building::BuildingState()
{
   //state management
}

void Building::RemoveImages()
{
}

void Building::SetImages (int set)
{
   ImageManager * image_man = ImageManager::GetInstance ();
}

void Building::Update (float dt, int tod)
{
   // call updates (tod);
}

void Building::Draw ()
{
//   Render (manimations[mCurrentMode]);
}

void Building::DrawSelectionTarget ()
{
//   DrawSelectionTarget( manimations[mCurrentMode], mID);
}

void Building::Save(SerializerBase& ser)
{
   ser.Add("type", "Building");   // first tag
   CoreBase::Save(ser);
   ser.Add("state", ToString((mCurrentState == BS_Operational)?1:0).c_str());
   // if something goes bump, either deal with it or throw it
}

void Building::PeopleInOut( int count )
{
   BuildingState();
}

bool Building::PeopleApply( )
{
   return false;
}
