//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved for the TPB3D community.
//  Author Sub Voyage Fan
//  Licensed according to the GPL v3.0
//
//  Deck class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
//
//  Vendors and Sales

#include <string>
#include "../Storage/SerializerBase.h"

#include "ItemBase.h"
#include "FoodItem.h"

using namespace std;


ItemBase::ItemBase (string test, ItemCategory ic, unsigned int size)
{
    mName = test;
    mCategory = ic;
    mSize = size;
    mCost = 1.0f;
    mPrice = 2.0f;
}
void ItemBase::DrawItem(string& itemName, ItemCategory itemCategory, int itemSize)
{
    itemName = mName;
    itemCategory = mCategory;
    itemSize = mSize;
}

ItemBase* ItemBase::Create (SerializerBase& ser)
{
   ItemBase* pItem = NULL;
   int ic = ser.GetInt ("category");
   switch (ic)
   {
   case IC_Food:
      pItem = FoodItem::Create(ser.GetString ("name"), ser.GetInt("topings"), ser.GetInt("size"));
      pItem->Load(ser);
      break;
   }
   return pItem;
}

void ItemBase::Load (SerializerBase& ser)
{
   mName = ser.GetString ("name");
   int ic = ser.GetInt ("category");
   if (ic > IC_None && ic <= IC_PoolAccessories)
   {
      mCategory = ItemCategory(ic);
   }
   mSize = (unsigned int)ser.GetInt("size");
   mCost = ser.GetFloat("cost");
   mPrice = ser.GetFloat("price");

}

void ItemBase::Save(SerializerBase& ser)
{
   ser.Add ("name", mName.c_str());
   ser.Add ("category", mCategory);
   ser.Add ("size", (int)mSize);
   ser.Add ("cost", mCost);
   ser.Add ("price", mPrice);
}
