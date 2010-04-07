#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include"FoodItem.h"
using namespace std;

FoodItem::FoodItem(const string& name, int top, int size)//:  ItemCreation (name, top, size) 
:  ItemBase (name, IC_Food, size)
{
   if ( top > 100)
   {
      throw "Toppings exceed maximum";
   }
    mTopings = top;
    mTest = size;
}

void FoodItem::drawItem()
{
    cout << "This is a test to prove something hapened.";
}

/* void FoodItem::drawFood(string top,int size)
{
    name = topings;
    size = test;
}
*/
string FoodItem::getTopings()
{
    return mTopings;
}

void FoodItem::displayTopings()
{
   if (this == NULL) throw 5;

   cout << mTopings << endl; // do something
}

FoodItem* FoodItem::Create (const char* name, int totalSize, int initialSize)
{
   FoodItem* test = new FoodItem(name,totalSize, initialSize);
   //test->DrawItem(name,totalSize,size);
   cout << test->getCategoryName() << " - ";
   cout << test->getName() << ", ";
   cout << test->getCategory() << ", ";
   cout << test->getSize() << endl;
   return test;
}

// this is really test code to show how overloaded functions might be used
FoodItem* FoodItem::Create(const char* name, ItemCategory ic)
{
   if ( !(ic == IC_Food) )
   {
      throw "Food item used to create a non-food item";
   }

   const int kInitialSise = 1;
   const int kTotalSize = 2;
   return Create (name, kTotalSize, kInitialSise);
}
