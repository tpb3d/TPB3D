#pragma once

#include <string>
#include <vector>
#include "ItemBase.h"

using namespace std;

class DrinkItem : public ItemBase // DrinkItem will have access to all public and protected members of SalesObject
                                 // so will any class that derives from DrinkItem
{
   // these are private by default from the class declaration
   string mTopings;
   unsigned int mTest;
   bool  mHasIce;
public:
   enum DrinkType
   {
      DT_Water,
      DT_Soda,
      DT_Tea,
      DT_Milk,
      DT_Shake,
      DT_Coffee
   };

public:
   DrinkItem();
   DrinkItem(const string& name ,int top, int size);
   virtual ~DrinkItem() {};

   static DrinkItem* Create (const char* name, int topings, int initialSize); // mini factory specific to this class
   static DrinkItem* Create (const char* name, ItemCategory ic); // simpler override
   // methods
   virtual void drawItem();

   void DrawDrink(string& name, int& toppings, int& size);
   const char* getCategoryName() { return "Drink"; }
   bool HasIce() { return mHasIce; }
   // properties
   string getTopings();
   void displayTopings();
   // Serialization
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
