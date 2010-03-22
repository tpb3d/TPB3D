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


#include <iostream>
#include "../Physics/MotionPhysics.h"
#include "Routes.h"
#include "Park.h"
#include "../Scene/Scene.h" // registation into the scene
#include "CoreBase.h"
#include "../Storage/SerializerBase.h"
#include "../xml/tinyxml/tinyxml.h"
#include "../Types/String.h"

//using namespace Gfx;
unsigned int CoreBase::NextID = 1;
CoreBase::CoreBase ()
:  mvPosition (0,0,0)
,  mvAngle (0,0,0)
{
}

CoreBase::CoreBase (const Vector3f& vPosition)
:  mvPosition (vPosition)
,  mvAngle (0,0,0)
{
}

CoreBase::CoreBase (const Vector3f& vPosition, const Vector3f& vAngle)
:  mvPosition (vPosition)
,  mvAngle (vAngle)
{
}

CoreBase::~CoreBase ()
{
}

void CoreBase::Initialize() // private, only call from CTOR
{
   mID = CoreBase::GetNextID();
   mOccupants = 0;
}

int CoreBase::GetNextID() // static
{
   return NextID++;
}

void CoreBase::Update (float dt, int tod)
{
   std::cout << "Floor base class: update function called" << std::endl;
}

void CoreBase::Draw ()
{
   std::cout << "Floor base class: Draw function called" << std::endl;
}

void CoreBase::Load(SerializerBase& ser)
{
   mID = ser.GetInt("ID");   // first tag
   mvPosition.x = ser.GetFloat("PositionX");   // Position
   mvPosition.y = ser.GetFloat("PositionY");
   mvPosition.z = ser.GetFloat("PositionZ");
}
void CoreBase::Save(SerializerBase& ser)
{
   ser.Add("ID", mID);   // first tag
   ser.Add("PositionX", mvPosition.x);   // Position
   ser.Add("PositionY", mvPosition.y);
   ser.Add("PositionZ", mvPosition.z);
}
