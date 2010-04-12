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

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../Storage/SerializerBase.h"

#include"DrinkItem.h"
using namespace std;

DrinkItem::DrinkItem(const string& name, int top, int size)//:  ItemCreation (name, top, size) 
:  ItemBase (name, IC_Drink, size)
{
   if ( top > 100)
   {
      throw "Toppings exceed maximum";
   }
    mTopings = top;
    mTest = size;
    mHasIce = false;
}

void DrinkItem::drawItem()
{
    cout << "This is a test to prove something hapened.";
}

/* void DrinkItem::drawDrink(string top,int size)
{
    name = topings;
    size = test;
}
*/
string DrinkItem::getTopings()
{
    return mTopings;
}

void DrinkItem::displayTopings()
{
   if (this == NULL) throw 5;

   cout << mTopings << endl; // do something
}

DrinkItem* DrinkItem::Create (const char* name, int totalSize, int initialSize)
{
   DrinkItem* test = new DrinkItem(name,totalSize, initialSize);
   //test->DrawItem(name,totalSize,size);
   cout << test->getCategoryName() << " - ";
   cout << test->getName() << ", ";
   cout << test->getCategory() << ", ";
   cout << test->getSize() << endl;
   return test;
}

// this is really test code to show how overloaded functions might be used
DrinkItem* DrinkItem::Create(const char* name, ItemCategory ic)
{
   if ( !(ic == IC_Drink) )
   {
      throw "Drink item used to create a non-Drink item";
   }

   const int kInitialSise = 1;
   const int kTotalSize = 2;
   return Create (name, kTotalSize, kInitialSise);
}

void DrinkItem::Load(SerializerBase& ser)
{
   string strDrink = ser.GetString("class");
   if (strDrink != "Drink")
      return;  // todo throw exception

   mTopings = ser.GetString ("topings");
   ItemBase::Load (ser);
}

void DrinkItem::Save(SerializerBase& ser)
{
   ItemBase::Save (ser);
   ser.Add ("class", "Drink");
   ser.Add ("topings", mTopings.c_str());
}
