//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Vendor class, sales base class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  Vendor - Base class of all the stalls, shops and restaurants

#pragma once
#include <string>
#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include "../Graphics/ObjectNode.h"

class SaleItemBase;

struct SaleItem
{
   float Cost;    // cost to the park or vendor
   float Price;   // what we sell it for
   std::string Description;
   typedef std::vector<SaleItem*>::iterator ItemIterator;
   typedef std::vector<SaleItem*> ItemVector;
};

// Derive from ObjectNode so we can place one in the park as a fixture

class Vendor// : public ObjectNode
{
   float mTotalSales; // Income
   float mTotalCost;  // Expenses simple balance sheet
   SaleItem::ItemVector mItems;

public:
   // ctor dtor
   Vendor(int ID ) {}   //: ObjectNode (0,ID) {}
   virtual ~Vendor(void) {}
   // properties
   size_t ItemCount() { return mItems.size(); }

protected:
   // local methods
   inline void ClearBalance()
   {
      mTotalSales = 0;
      mTotalCost = 0;
   }

public:
   // UI interface methods
   inline void AddItem (SaleItem* pItem)
   {
      mItems.push_back (pItem);
   }
   inline SaleItem* GetItem (size_t index)
   {
      SaleItem* pItem = NULL;
      if(index < mItems.size())
      {
         pItem = mItems[index];
      }
      // else throw exception
      return pItem;
   }
   // TODO
   //  Sell item deduct cost of item and cost of condements
   //  Add cost to mTotalCost and sale price to mTotalSales.
   //  in a real business there would be a lot more expenses but this is a game
   /*
public:
   inline void Tally (ParkCOO* pComp)  // Comptroll visitor collect sales
   {
      // Lock();  // stop sales until we finish tallying and clearing the till
      pComp->ShopSales(mTotalSales - mTotalCost);  // Park Contribution, park owns this vendor
      ClearBalance();
      // Unlock();
   }
   */
};
