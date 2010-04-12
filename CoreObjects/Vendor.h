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
#include "../SalesObjects/ItemBase.h"
#include "../Graphics/ObjectNode.h"

class ItemBase;
class SpecialPerson;

// Derive from ObjectNode so we can place one in the park as a fixture

class Vendor// : public ObjectNode
{
   float mTotalSales; // Income
   float mTotalCost;  // Expenses simple balance sheet
   char  mCurrencySymbol;
   char  mDecimal;

protected:
   static const char* mHeader1[4];
   ItemBase::ItemVector mItems;

public:
   // ctor dtor
   Vendor() { }   //: ObjectNode (0,ID) {}
   virtual ~Vendor(void) {}

   // properties
   size_t ItemCount() { return mItems.size(); }
   void SetCurrency( char symbol, char decimal)
   {
      mCurrencySymbol = symbol;
      mDecimal = decimal;
   }

protected:
   // local methods
   inline void ClearBalance()
   {
      mTotalSales = 0;
      mTotalCost = 0;
   }

public:
   // UI interface methods
   inline void AddItem (ItemBase* pItem)
   {
      mItems.push_back (pItem);
   }
   inline ItemBase* GetItem (size_t index)
   {
      ItemBase* pItem = NULL;
      if(index < mItems.size())
      {
         pItem = mItems[index];
      }
      // else throw exception
      return pItem;
   }
   void ClearItems ()
   {
      while (mItems.end() != mItems.begin())
      {
         ItemBase* pBase = *(mItems.end()-1);
         delete pBase;
         mItems.pop_back();
      }
   }
   void drawHeader()
   {
//       cout << mHeader1[0] << setw(20) << mHeader1[1] << setw(20) << mHeader1[2] << setw(20) << mHeader1[3];
//       cout << endl;
//       cout << setw(45) << mCurrencySymbol;
   }

   void drawFooter() //string, double,string,int);
   {
   }

   void drawFooter2() //string,double,int);
   {
   }

   // TODO
   //  Sell item deduct cost of item and cost of condements
   //  Add cost to mTotalCost and sale price to mTotalSales.
   //  in a real business there would be a lot more expenses but this is a game

public:
   void Tally (SpecialPerson* pComp);  // Comptroll visitor collect sales
};
