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
#ifndef _CoreBase_H
#define _CoreBase_H

#include "../Types/vector3.h"

class Park;
class Person;
class Level;
class TiXmlElement;
class SerializerBase;

enum BaseType
{
   BaseEmpty = 0,
   BaseGhostObject,
   BaseFlatRide,
   BaseTrackRide,
   BaseOtherTrackRide,
   BaseBuilding,
   BaseRetail,
   BaseRestaurant,
   BaseVenue,
   BaseService,
   BaseSecurity,
   BaseClinic,
   BaseRestroom,
   BaseWasteManagement,
   BaseStair,
   BaseElevator,
   BaseTicketBooth
};

class CoreBase
{
   friend class Level;  // allows level to own these spaces by being able to set protected variables.

protected:
   int mLevel;
   int mID;
   int mOccupants;
   Vector3f mOrigin;
   Park* mpParkParent;

   static unsigned int NextID;   // all model objects will get one
public:
   // CTOR
   CoreBase (Vector3f& origin, Park* ParkParent);

   // Properties
   inline float GetX() { return mOrigin.x; }
   inline float GetY() { return mOrigin.y; }
   inline float GetZ() {return mOrigin.z; }
   inline int   GetPathNo() { return mLevel; }
   inline Park* GetParent() { return mpParkParent; }
   inline int   GetID () { return mID; }

   inline void SetOrigin(Vector3f& origin) { mOrigin = origin; }

   // Methods
   virtual void Update (float dt, int tod);
   virtual void Draw ();
   virtual void DrawSelectionTarget () { }
   virtual BaseType GetType () { return BaseEmpty; }

   virtual void Load(SerializerBase& ser);// iXmlElement* pnParent)
   virtual void Save(SerializerBase& ser);// iXmlElement* pnParent)

   static int GetNextID();
};

#endif
