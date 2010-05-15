//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terrain tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"


// this is just the tracks not the supports, devices or station
class ObjectBase;

class Terrain : public ObjectNode
{
   float mDepth; // = 5;
   float mWidth; // = 5;
   float mBaseElevation;
   float mWaterTable;
   typedef std::vector<ObjectBase*>::iterator TypeTerrainIt;
   std::vector<ObjectBase*> mTerrainSections;

public:
   Terrain(void);
   ~Terrain(void);

   void AddSection (ObjectBase* pGLBase);
   void Draw();
};
