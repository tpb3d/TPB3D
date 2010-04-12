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

#pragma once
#ifndef _Store
#define _Store

#include "Vendor.h"
#include "PersonQueue.h"
#include "../SalesObjects/ItemBase.h"

class Person;

enum StoreType
{
   Store_Empty = 0,
   Store_Food,
   Store_Shop,
   Store_GiftShop,
   Store_Specialty
};

class Store : public Vendor, public CoreBase
{
protected:
   ObjectBase* mpGraphic;
   PersonQueue* mpQueue;
   StoreType mStoreType;
   std::string mStoreName;
   ItemBase::ItemVector mItemList;

public:
   // ctor dtor
   Store(int StoreNo, int ID, StoreType st);
   Store(int StoreNo, int ID );
   ~Store(void);
   // properties
   // get...()
   PersonQueue* GetQueue() { return mpQueue; }

   void AddPerson (Person* pPeep);
   void RemovePerson (Person* pPeep);
   void ServeNextPerson (void);
   void SetGraphic (ObjectBase* pGfx) { mpGraphic = pGfx; }
   virtual const char* GetName () { return mStoreName.c_str(); }

   // Time Management Methods
   bool IsType (StoreType st) { return (mStoreType == st); }
   void Update (float dt, int timeOfDay);
   CoreBase* Clone( );

   // Rendering methods
   void Draw ();
   void DrawSelectionTarget (bool bBaseOnly);

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
#endif // _Store
