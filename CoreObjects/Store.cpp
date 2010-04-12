//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Storage/SerializerBase.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Image.h"
#include "../Graphics/ObjectTree.h"
#include "../People/Person.h"
#include "Store.h"

Store::Store (int StoreNo, int ID)
{
   mpGraphic = NULL;
   mpQueue = new PersonQueue(this);
   mStoreName = "Store"; // needs to be more specific
}

Store::Store(int StoreNo, int ID, StoreType st)
{
   mStoreType = st;
   mpGraphic = NULL;
   mpQueue = new PersonQueue(this);
   mStoreName = "Store"; // needs to be more specific
}

Store::~Store( )
{
   delete mpQueue;
   ClearItems();
}

void Store::AddPerson (Person* pPeep)
{
   mpQueue->AddPerson(pPeep);
}

void Store::RemovePerson (Person* pPeep)
{

   mpQueue->RemovePerson(pPeep);
}

void Store::ServeNextPerson (void)
{
   Person* pPeep = mpQueue->TakeNextPerson();
   if (pPeep != NULL)
   {
      // TakeOrder;
      // Serve or Reject
      pPeep->SetActivity (Person::AS_Eating);   // this is just some interaction
      pPeep->SetCurrentState (Person::CS_Walking);
   }
}

void Store::Update (float dt, int timeOfDay)
{
   static int delay = 5; // playing physics

   if( --delay > 0 )
   {
      return;
   }
   ServeNextPerson();
   if (mpQueue->Count() > 10)
      delay = 3;
   else
      delay = 5;
}

CoreBase* Store::Clone( )
{
   Store* pStore = new Store (0, 0);
   return pStore;
}

void Store::Draw ()
{
   mpGraphic->Draw();
}

void Store::DrawSelectionTarget (bool bBaseOnly)

{
//   draw select geometry
}

void Store::Load(SerializerBase& ser)
{
   SerializerBase* pSer = ser.GetFirstChild ("Items");
   int st = ser.GetInt ("Store type");
   mStoreType = (st > Store_Empty && st <= Store_Shop) ? StoreType(st) : Store_Empty;
   while (pSer != NULL)
   {
      ItemBase* pItem = ItemBase::Create (*pSer); // Factory
      mItems.push_back (pItem);
      pSer = ser.GetNextSibling ("Items");
   }
}

void Store::Save(SerializerBase& ser)
{
   ser.Add("type", "Store");
   ser.Add("Store name", mStoreName.c_str());
   ser.Add("id", mID);
   SerializerBase* pSer = ser.Spawn("Items"); // create a locale serializer of the type used for Store
   ItemBase::ItemIterator ii;
   for (ii = mItems.begin(); ii != mItems.end(); ++ii)
   {
      (*ii)->Save(*pSer);
   }
   delete pSer;
}
