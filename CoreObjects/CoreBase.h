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

#include "../Types/Vector3.h"

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
   Vector3f mvPosition;
   Vector3f mvAngle;

   static unsigned int NextID;   // all model objects will get one
public:
   // CTOR
   CoreBase ();
   CoreBase (const Vector3f& vPosition);
   CoreBase (const Vector3f& vPosition, const Vector3f& vAngle);
   ~CoreBase ();
   
protected:
   void Initialize();

public:   
   // Properties
   inline float GetX() { return mvPosition.x; }
   inline float GetY() { return mvPosition.y; }
   inline float GetZ() {return mvPosition.z; }
   inline int   GetPathNo() { return mLevel; }
   inline int   GetID () { return mID; }

   inline void SetvPosition(Vector3f& vPosition) { mvPosition = vPosition; }

   // Methods
   virtual void Update (float dt, int tod);
   virtual void Draw ();
   virtual void DrawSelectionTarget () { }
   virtual BaseType GetType () { return BaseEmpty; }
   virtual CoreBase* Clone () = 0;

   virtual void Load(SerializerBase& ser);// iXmlElement* pnParent)
   virtual void Save(SerializerBase& ser);// iXmlElement* pnParent)

   static int GetNextID();
};

#endif
