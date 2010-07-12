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
#include "../Types/MathStuff.h"

Terrain::Terrain(void)
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
{
   mDepth = 100;
   mWidth = 100;
   mBaseElevation = 10;
   water = NULL;
   //mWaterTable = 0;
   for(int i=0;i<maxWaterTables;i++)	{	watertables[i]=NULL;	}
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

	for(int i=0;i<nwaterTables;i++)	{
		if(watertables[i]!=NULL)
			delete[]watertables[i];
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
///media/B81D-8323/game projects/tpb3d/source/00-current-svn/tpb3dtg/CoreObjects/Terrain.cpp|59|error: prototype for ‘bool Terrain::AddWaterTables(float, float, float, float, float*, float, short int)’ does not match any in class ‘Terrain’|
bool
Terrain::
	AddWaterTables(float tileWidth,float tileLength,float tileUnitWidth
						,float tileUnitHeight,float*landTiles,float minWaterHeight,float maxWaterHeight,short nnewWaterTables)	{
		bool rv=false;
		for(int i=0;i<nnewWaterTables;i++)	{
			rv=rv||AddWaterTable(tileWidth,tileLength,tileUnitWidth,tileUnitHeight,landTiles,minWaterHeight,maxWaterHeight);
			}
		return rv;
		}
WaterTable&
Terrain::
	wt(short tableI)	{
		return(*(watertables[tableI]));
	}
bool
Terrain::
	AddWaterTable(float tileWidth,float tileLength,float tileUnitWidth
						,float tileUnitHeight,float*landTiles,float minWaterHeight,float maxWaterHeight)	{
		short i=nwaterTables;
		if(nwaterTables>=maxWaterTables)	{	return false;	}
		watertables[i]=new WaterTable[1];
		if(watertables[i]==NULL)	return false;

		float avgWaterHeight=Avg(minWaterHeight,maxWaterHeight);
		wt(i).Init(tileWidth,tileLength,tileUnitWidth,tileUnitWidth,true,avgWaterHeight,landTiles);
		bool done=false;
		short trycount=0;	short tryThreshold=30;
		while(!done)	{
			while(!wt(i).FloodFillRandom(minWaterHeight,maxWaterHeight)&&trycount<tryThreshold)	{	trycount++;	}
			if(i>0)	{
				//test for overlap with previous tables
				for(int ii=0;ii<i&&!done;ii++)	{
					//overlapping? Drain the water table and try again
					if(wt(i).OverlapsWithSameDim(wt(ii)))	{
					//or
					//if(watertables[i]&&watertables[ii])	{
						done=false;
						//watertables[i].WaterDrain();
						//increase try count
						//if try count > try threshold:
						if(++trycount>=tryThreshold)	{
							//give up and exit loop
							done=true;
							}
						}
					//non overlapping?: No further processing needed
					else	{
						done=true;
						}
					}
				}	//if i>0
			else	{
				done=true;
				}	//else
			}	//while not done
		++nwaterTables;
		return true;
		}
Terrain*&
Terrain::
	Water()	{
		return	water;
		}

