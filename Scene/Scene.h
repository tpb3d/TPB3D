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

// root of the Pathways and subPathways, the building/ Park.
// create an instance of this. The lobby is created empty.
// call newPathway or newSubPathway to add floors or basement Pathways
#ifndef _SCENE_H
#define _SCENE_H

#include <map>
#include "../Hub/Event.h"
#include "../Types/Vector2.h"
#include "../CoreObjects/Routes.h"
#include "../Graphics/ModelObject.h"

class CoreBase; // aggregate of floor spaces for Buildings, condos and hotels
class Park;
class BuildStrategyBase;
class GameManager;
class SkyBowl;
class Terrain;

// Park is a ModelObject along with all the FloorSpace entities
// This renderes the Park in the ModelSpaces with perspective, pan and zoom.
class Scene
{
   friend class ParkAgent;
   friend class GameManager;
 
public:
   typedef std::vector<Park*>::iterator TypeParkIterator;
   typedef std::vector<Park*> TypeParkVector;

private:
   std::vector<Park*> mParks;     // Lobby is at mNo_SubPathways not zero

   typedef std::map<int,CoreBase*>::iterator TypeFloorSpaceIterator;
   typedef std::pair<int,CoreBase*> TypeFloorSpaceMap;
   std::map<int,CoreBase*> mFloorSpaces;

   //Routes mRoutes;
   BuildStrategyBase* mpBuildStrategy;  // Place floor objects
   SkyBowl* mpSky;
   Terrain* mpTerrain;

public:
   // ctor/dtor
   Scene();
   ~Scene();

protected:
   inline std::vector<Park*>& GetParks()
   {
      return mParks;
   }

   // methods
public:
   //Park* NewPark (int x, int y, int z, int z2, int x2);
   void AddPark (Park* pPark);
   Park* GetPark ()
   {
      return mParks[0];
   }
   void SetTerrain( Terrain* pTerra);
   //Park* GetPark (int no); // positive gets you a Pathway above, negative gets you a basement Pathway

   bool SelectTool( int ToolID );
   void RegisterFloorSpace (int id, CoreBase* pFS);
   void UnregisterFloorSpace (int id, CoreBase* pFS);
   CoreBase* FindFloorSpace (int id);

   virtual bool OnToolHit(const HR_Events Event);
   virtual bool OnFRCS();
   virtual bool OnTRCS();

   void Update (float dt, int timeOfDay);
   void Draw ();
   void DrawSelectionTarget (int Pathway); // hit test run
   void HitDown (int hit, Vector2i& point);  // mouse x and y, send it through geometry to see what we hit
   void HitUp (int hit, Vector2i& point);  // mouse x and y, send it through geometry to see what we hit
   void MoveGhostObject (Vector2f& point);

};

#endif //_SCENE_H
