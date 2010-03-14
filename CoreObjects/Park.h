//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Park class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

// root of the Pathways and subPathways, the building/ Park.
// create an instance of this. The lobby is created empty.
// call newPathway or newSubPathway to add floors or basement Pathways
#ifndef _PARK_H
#define _PARK_H

#include "../Graphics/ModelObject.h"
#include "Routes.h"
#include "GhostObject.h" // local for speed

class ObjectBase; // aggregate
class ObjectTree;
class Pathway;
class ParkAgent;
class FloorAgent;
class GameManager;
class Routes;
class Person;
class Scene;
class BuildStairStrategy;
class Car;

// Park is a ModelObject
// This renderes the Park in the ModelSpaces with perspective, pan and zoom.
class Park// : public Gfx::ModelObject
{
   friend class ParkAgent;
   friend class FloorAgent;
   friend class GameManager;
   friend class BuildStairStrategy;

   int mParkNo;
   int mNo_SubPathways;
   int mPopulation;  // People in the Park currently

   Scene& mScene; // this is where the Park is modeled in OpenGL.
   ObjectTree* mpTheTree;

   Car* mpCar; // test part in the tree
   int mCurPoint;
   int mPoints;

   GhostObject mGhostObject;  // this object is rendered with the scene.
                              // it may be a bush, a ride, track or even a whole coaster

public:
   typedef std::vector<Pathway*>::iterator PathwayIterator;
   typedef std::vector<Pathway*> PathwayVector;

   // ctor/dtor
   Park( int ParkNo, int NoSubPathways, Scene& rScene );
   ~Park();

   // properties
   inline int GetPopulation() { return mPopulation; }
   inline Scene& GetScene() { return mScene; }
   inline GhostObject& GetGhostObject() {  return mGhostObject; }
   inline ObjectTree& GetTree() { return *mpTheTree; }

   // test
   void AddTestPoint( sf::Vector3f pa, sf::Vector3f pb );

protected:
   // methods
public:

   void Update (float dt, int timeOfDay);
   void Draw ();
   void DrawSelectionTarget (bool bPathwaysOnly);

   // AI interface
   void EnterPark (Person* pPerson);
   void LeavePark (Person* pPerson);

};

#endif //_PARK_H
