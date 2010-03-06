/*   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BUILDSTRATEGIES_H
#define _BUILDSTRATEGIES_H
#include <string>
#include <map>

class Park;

// these are hard coded now but will be modifiable
class BuildStrategyBase
{
protected:
   std::string mType;  // Building, Apt, Condo
   // subtype maybe, reception, cubes, datacente, boardroom (Buildings) or luxury/studio apt.
   int mWidth;    // in units of 9 pixels
   int mHeight;   // Pathways (1,2 or 3)

public:
   BuildStrategyBase()
   {
   }
   // get/set properties
   int GetWidth() { return mWidth; };
   int GetHeight() { return mHeight; };
public:
   virtual bool PlacingRoom() { return false; }
   virtual bool BuildHere (Park* pPark, int x, int y);
   virtual void ShowGhostBuild (Park* pPark);
};

class BuildStrategyFactory
{
   BuildStrategyFactory();
//   BuildStrategyBase* MakeStrategy (const char* type );
   BuildStrategyBase* MakeStrategy (int type );
};

// Buildings
class BuildBuildingStrategy : public BuildStrategyBase
{
public:
   BuildBuildingStrategy()
   {
      mType = "Building"; // May not always be the class name
      mWidth = 8;       // 72/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Park* pPark, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Park* pPark);
};

// 
class BuildRetailStrategy : public BuildStrategyBase
{
public:
   BuildRetailStrategy()
   {
      mType = "RetailShop"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Park* pPark, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Park* pPark);
};

class BuildRestaurantStrategy : public BuildStrategyBase
{
public:
   BuildRestaurantStrategy()
   {
      mType = "Restaurant"; // May not always be the class name
      mWidth = 12;       // 108/9
      mHeight = 1;      // or 36 pixels
   }
public:
   bool BuildHere (Park* pPark, int x, int y);
   virtual bool PlacingRoom() { return true; }
   virtual void ShowGhostBuild (Park* pPark);
};

// select and drag

#endif // _BUILDSTRATEGIES_H
