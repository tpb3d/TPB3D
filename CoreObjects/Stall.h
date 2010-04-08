//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Vendor class, sales base class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideVendor        Assembly that is a feature support that extends out and usually supports a carriage.
      RideTelescopeVendor Vendor that has an extenstion that slides out to extend the Vendor up to 1.8 times its collapsed length.
*/

#pragma once   // An battle is brweing over pragma once but the VS is slow with out them, Guards are not as effective with VS.
#ifndef _Stall
#define _Stall

#include "Vendor.h"
#include "PersonQueue.h"
#include "../SalesObjects/ItemBase.h"

class Person;

enum StallType
{
   ST_Empty = 0,
   ST_Food,
   ST_Shop,
   ST_Information
};

class Stall : public Vendor, public CoreBase
{
protected:
   ObjectBase* mpGraphic;
   PersonQueue* mpQueue;
   StallType mStallType;
   std::string mStallName;
   ItemBase::ItemVector mItemList;

public:
   // ctor dtor
   Stall(int StallNo, int ID, StallType st);
   Stall(int StallNo, int ID );
   ~Stall(void);
   // properties
   // get...()
   PersonQueue* GetQueue() { return mpQueue; }

   void AddPerson (Person* pPeep);
   void RemovePerson (Person* pPeep);
   void ServeNextPerson (void);
   void SetGraphic (ObjectBase* pGfx) { mpGraphic = pGfx; }
   virtual const char* GetName () { return mStallName.c_str(); }

   // Time Management Methods
   bool IsType (StallType st) { return (mStallType == st); }
   void Update (float dt, int timeOfDay);
   CoreBase* Clone( );

   // Rendering methods
   void Draw ();
   void DrawSelectionTarget (bool bBaseOnly);

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
#endif // _Stall
