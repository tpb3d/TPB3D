#include "../People/SpecialPerson.h"
#include "Vendor.h"

const char* Vendor::mHeader1[4] =
{
   "Item Number","Item Name", "Price", "Quantity"
};

void Vendor::Tally (SpecialPerson* pComp)  // Comptroll visitor collect sales
{
   // Lock();  // stop sales until we finish tallying and clearing the till
//   pComp->ShopSales(mTotalSales - mTotalCost);  // Park Contribution, park owns this vendor
   ClearBalance();
   // Unlock();
}
