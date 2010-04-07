#pragma once

#include <string>
#include <vector>
#include "SalesObject.h"

using namespace std;

class FoodItem : public SalesObject // FoodItem will have access to all public and protected members of SalesObject
                                 // so will any class that derives from FoodItem
{
   // these are private by default from the class declaration
   string mTopings;
   unsigned int mTest;

public:
   FoodItem();
   FoodItem(const string& name ,int top, int size);
   virtual ~FoodItem() {};

   static FoodItem* Create (const char* name, int totalSize, int initialSize); // mini factory specific to this class
   static FoodItem* Create (const char* name, ItemCategory ic); // simpler override
   // methods
   virtual void drawItem();

   void DrawFood(string& name, int& toppings, int& size);
   const char* getCategoryName() { return "Food"; }
   // properties
   string getTopings();
   void displayTopings();

};
