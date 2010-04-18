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
#include "Stall.h"

#include <iostream> // temporary

Stall::Stall (int StallNo, int ID)
{
   mpGraphic = NULL;
   mpQueue = new PersonQueue(this);
   mStallName = "Stall"; // needs to be more specific
}

Stall::Stall(int StallNo, int ID, StallType st)
{
   mStallType = st;
   mpGraphic = NULL;
   mpQueue = new PersonQueue(this);
   mStallName = "Stall"; // needs to be more specific
}

Stall::~Stall( )
{
   delete mpQueue;
   ClearItems();
}

void Stall::AddPerson (Person* pPeep)
{
   mpQueue->AddPerson(pPeep);
}

void Stall::RemovePerson (Person* pPeep)
{

   mpQueue->RemovePerson(pPeep);
}

void Stall::ServeNextPerson (void)
{
   Person* pPeep = mpQueue->TakeNextPerson();
   if (pPeep != NULL)
   {
      ItemBase *item = mItemList.at( (rand() % mItemList.size()) );
      if( pPeep->GetMoney() >= item->getCost() )
      {
         std::cout << "Peep bought a " << item->getName() << std::endl;
         pPeep->AddItem(item);
         pPeep->SetActivity (Person::AS_Eating);   // this is just some interaction
         pPeep->SetCurrentState (Person::CS_Walking);
      }
      else // Not enough money, go look for an ATM
      {
         pPeep->SetActivity(Person::AS_LookingForATM);
         pPeep->SetCurrentState (Person::CS_Walking);
      }
   }
}

void Stall::Update (float dt, int timeOfDay)
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

CoreBase* Stall::Clone( )
{
   Stall* pStall = new Stall (0, 0);
   return pStall;
}

void Stall::Draw ()
{
   mpGraphic->Draw();
}

void Stall::DrawSelectionTarget (bool bBaseOnly)

{
//   draw select geometry
}

void Stall::Load(SerializerBase& ser)
{
   SerializerBase* pSer = ser.GetFirstChild ("Items");
   int st = ser.GetInt ("stall type");
   mStallType = (st > ST_Empty && st <= ST_Shop) ? StallType(st) : ST_Empty;
   while (pSer != NULL)
   {
      ItemBase* pItem = ItemBase::Create (*pSer); // Factory
      mItems.push_back (pItem);
      pSer = ser.GetNextSibling ("Items");
   }
}

void Stall::Save(SerializerBase& ser)
{
   ser.Add("type", "Stall");
   ser.Add("stall name", mStallName.c_str());
   ser.Add("id", mID);
   SerializerBase* pSer = ser.Spawn("Items"); // create a locale serializer of the type used for Stall
   ItemBase::ItemIterator ii;
   for (ii = mItems.begin(); ii != mItems.end(); ++ii)
   {
      (*ii)->Save(*pSer);
   }
   delete pSer;
}
