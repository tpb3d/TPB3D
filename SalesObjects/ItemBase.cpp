#include "ItemBase.h"
#include <string>
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
