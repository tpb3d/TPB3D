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

#include "../Graphics/Image.h"
#include "../Types/String.h"
#include "CoreBase.h"
#include "Park.h"
#include "Pathway.h"

#include "GhostObject.h"

using namespace Gfx;
//using namespace ParkObjects;

GhostObject::GhostObject (const Vector3f& origin, int level)
   :  mCurrentState (GS_Invalid)
   ,  CoreBase (origin, Vector3f(0,0,0))// no parent
   ,  mBase (1, 1)
{
   mWidthUnits = 1;
   mOffsetUnits = 0;
}

void GhostObject::SetState( Ghost_State gs )
{
   const float cfGreen[] = { 0.0f, 255.0f, 63.0f, 127.0f };
   const float cfGray[] = { 127.0f, 63.0f, 63.0f, 127.0f };
   mBase.SetLightingColor( (gs == GS_Valid) ? cfGreen : cfGray );
}

void GhostObject::SetWidth( int units)
{
   mWidthUnits = units;
   mOffsetUnits = units / 2;
   mBase.SetWidth ((float)(units * 1));
}

void GhostObject::Move (Vector3f& point)
{
   float x = point.x - mOffsetUnits;
   float y = point.y;
   mBase.SetPosition (x, 0, y);
}

void GhostObject::Update (Park* pPark)
{
   SetState (GS_Invalid);
}

void GhostObject::Draw ()
{
   RenderRectangle (&mBase);
}

