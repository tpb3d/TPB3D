#pragma once   // supercedes define wraps

#include <string>
#include <vector>
using namespace std;

class ItemBase
{
// other declarations
public:
   enum ItemCategory
   {
      IC_None = 0,
      IC_Food,       // 1
      IC_Drink,
      IC_Toy,        // 3
      IC_Clothing,
      IC_Brocure,    // maps and other paper
      IC_PoolAccessories
   };

   // implementation
protected:
   float mCost;    // cost to the park or vendor
   float mPrice;   // what we sell it for
   string Description;
   string mName;  // name of the item being created. Can be any size for now.
   ItemCategory mCategory; // wheitehr its food drink or other
   unsigned int mSize; // tells what size it is in total

public:
   typedef vector<ItemBase*>::iterator ItemIterator;
   typedef vector<ItemBase*> ItemVector;

public:
   ItemBase();
   ItemBase(string name, ItemCategory ic, unsigned int size);
   virtual ~ItemBase() {};
   // inlines properties
   string ItemBase::getName()
   {
      return mName;
   }

   int getCategory()
   {
       return mCategory;
   }

   unsigned int getSize()
   {
       return mSize;
   }
   float getCost () { return mCost; }
   float getPrice () { return mPrice; }
   // methods
   void SetPricing (float Cost, float Price);
   virtual const char* getCategoryName() { return "Nothing"; }
   virtual void DrawItem(string& name,ItemCategory itemCategory, int size);
};
