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

#pragma once
#ifndef _GHOSTOBJECT_H
#define _GHOSTOBJECT_H

#include "../Physics/MotionPhysics.h"
#include "../Graphics/Animation.h"
#include "../Graphics/ModelObject.h"
#include "CoreBase.h"

class AnimationSingle;
class SerializerBase;
class Park;

// simple room outline used to track the mouse and assist with placment

enum Ghost_State
{
   GS_Invalid,
   GS_Valid
};

class GhostObject : public CoreBase, public Gfx::ModelObject
{
   Ghost_State    mCurrentState;// vacant /occupied/ day / night
   AnimationShape mBase;
   BaseType       mShownType;

   int   mWidthUnits;
   int   mOffsetUnits;

public:
   GhostObject (Vector3f& origin, int level);

   void Update (Park* pPark);
   void Draw ();
   void DrawSelectionTarget () {};
   virtual BaseType GetType () { return BaseGhostObject; }
   void SetShownType (BaseType bt) { mShownType = bt; }
   void SetState( Ghost_State gs );
   void Move (Vector3f& point);
   void SetWidth( int units);

private:
   void GhostState(int tod);
};

#endif //_GHOSTOBJECT_H
