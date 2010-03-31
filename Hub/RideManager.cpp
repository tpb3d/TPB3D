
//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle, Russ Frank and crazy2be.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Skybowl class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "../Types/String.h"

#include "../xml/tinyxml/tinyxml.h"
#include "../Physics/MotionPhysics.h"
#include "../Storage/XMLSerializer.h"
#include "../Graphics/Texture.h"

#include "../CoreObjects/Routes.h"
#include "../CoreObjects/Routes.h"
#include "../CoreObjects/CoreBase.h"
#include "../CoreObjects/Park.h"
#include "../CoreObjects/Pathway.h"
#include "../CoreObjects/RouteBase.h"  // (Pathways).
#include "../Builders/TerrainFormer.h"
#include "../Scene/Scene.h"
#include "Event.h"

#include "RideManager.h"
//test
#include "../Graphics/StripMeshObject.h"
#include "../Graphics/ObjectTree.h"
#include "../Graphics/Tree.h"
#include "../Graphics/Image.h"
#include "../Builders/TreeFormer.h"
#include "../Builders/TrackFormer.h"
#include "../Builders/FlatRideBuilder.h"
#include "../CoreObjects/TrackBase.h"
#include "../CoreObjects/Track.h"
#include "../CoreObjects/TrackGuide.h"
#include "../CoreObjects/TrackSection.h"
#include "../CoreObjects/Car.h"
#include "../CoreObjects/Ride.h"
// endtest

RideManager::RideManager (Scene& scene)
:  mScene(scene)
{

}

void RideManager::InitialSetup()
{
}

bool RideManager::Settings()
{
   return true;
}

bool RideManager::FRCS()
{
   return true;
}

