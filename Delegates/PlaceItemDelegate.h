/*   This file is part of Theme Park Builder 3D The Game.
 *
 *   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "DelegateBase.h" // includes map and string

template <class T> class PlaceItemDelegate : public DelegateBase
{
protected:
   std::string mToolPlacePathItemed;
   T* mpGhostItem;

public:
   PlaceItemDelegate (const char* pszName, Scene* pScene)
   :  DelegateBase (pszName, pScene)
  // :  mPlacePathItem (PlacePathItem)
   {
      mpScene = pScene;
      mToolPlacePathItemed = pszName;
      mpGhostItem = new T(1,1);
      mpGhostItem->SetGraphic (LoadGraphic());
   }

public:
   void OnHitDown (short ID)
   {
      Park* pPark = mpScene->GetPark();
      T* pT = static_cast<T*>(mpGhostItem->Clone());
      pT->SetGraphic (LoadGraphic());
      pT->SetvPosition( Vector3f(20,1, 20));
      pPark->AddStall (pT);
   }

   void OnHitUp (short ID)
   {
//      mpGhostItem->Onhit();
   }
};
/*
template <class T>
class BuildRoomStrategy : public BuildStrategyBase
{
public:
   BuildRoomStrategy(BuildData& rBuildData)
   :  BuildStrategyBase (rBuildData)
   {
      mType = T::GetBaseType();
   }
   bool BuildHere (Tower* pTower, int x, int y)
   {
     // we don't have multi tower support yet but this will eventually deal with that
     Level* pLevel = pTower->GetLevel(y);
     double dCash = pTower->GetAvailableFunds();
     if( dCash < mBuildData.BuildCost)
        return false;

     int xx = x * Level::mUnitSize;
     bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mBuildData.UnitsWide * Level::mUnitSize);
     if (bAvail)
     {
        FloorBase* pRoom = new T(xx, y, pTower); //OnToolHit is going to set this up, when we hit the floor
        pRoom->SetRent (mBuildData.RentalCost);
        pRoom->SetSalePrice (mBuildData.PurchasePrice);
        pLevel->AddFloorSpace (pRoom);
        pTower->AdjustFunds( -mBuildData.BuildCost );
     }
     return true;
  }
  virtual bool PlacingRoom() { return true; }
  virtual void ShowGhostBuild (Tower* pTower)
  {
     GhostRoom& GR = pTower->GetGhostRoom();
     GR.SetShownType(mType);
     GR.SetWidth(mBuildData.UnitsWide);
  }
};
*/