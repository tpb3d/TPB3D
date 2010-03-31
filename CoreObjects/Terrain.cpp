//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terrain tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/ObjectFactory.h"
#include "Terrain.h"


Terrain::Terrain(void)
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
{
   mDepth = 100;
   mWidth = 100;
   mBaseElevation = 10;
   mWaterTable = 0;

}

Terrain::~Terrain(void)
{
   try
   {
      TypeTerrainIt it;
      for( it = mTerrainSections.begin(); it != mTerrainSections.end(); it++)
      {
         ObjectBase* pBase = (*it);
         delete pBase;
      }
   }
   catch( ... )
   {
   }
}

void Terrain::AddSection( ObjectBase* pBase )
{
   mTerrainSections.push_back (pBase);
}

void Terrain::Draw()
{
//   glColor4f( 0.9, 1.0, 0.9, 0.65);
   TypeTerrainIt it;
   for( it = mTerrainSections.begin(); it != mTerrainSections.end(); it++)
   {
      ObjectBase* pBase = (*it);
      pBase->Draw();
   }
}
