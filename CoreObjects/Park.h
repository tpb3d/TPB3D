//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Park class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

// root of the Pathways and subPathways, the building/ Park.
// create an instance of this. The lobby is created empty.
// call newPathway or newSubPathway to add floors or basement Pathways

#pragma once
#ifndef _PARK_H
#define _PARK_H

#include "../Graphics/ModelObject.h"
#include "Routes.h"
#include "PathCollection.h"
#include "RideCollection.h"
#include "StallCollection.h"
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
class Stall;
class Ride;
class BuildStairStrategy;
class Car;
class SerializerBase;

#include "../Storage/SerializerBase.h"

#include "../CoreObjects/Stall.h"
#include "../CoreObjects/Ride.h"
//#include "../People/Peeps.h"
//enum StallType; // if this won't compile, comment this line and include stall.h
//enum RideType; // if this won't compile, comment this line and include ride.h

// Park is a ModelObject
// This renderes the Park in the ModelSpaces with perspective, pan and zoom.
class Park// : public Gfx::ModelObject
{
   friend class ParkAgent;
   friend class FloorAgent;
   friend class GameManager;
   friend class BuildStairStrategy;

protected:
   int mParkNo;
   int mPopulation;  // People in the Park currently

   Scene& mScene; // this is where the Park is modeled in OpenGL.
   ObjectTree* mpTheTree;
   Pathway* mpParkEntrance;

   Car* mpCar; // test part in the tree
   int mCurPoint;
   int mPoints;

   GhostObject mGhostObject;  // this object is rendered with the scene.
                              // it may be a bush, a ride, track or even a whole coaster
   PathCollection mPaths;
   RideCollection mRides;
   StallCollection mStalls;

   // Temp until we know where the people need to be logged while in the park
   std::vector<Person*> mPeopleInPark;

public:
   // ctor/dtor
   Park( int ParkNo, int other, Scene& rScene );
   ~Park();

   // properties
   inline int GetPopulation() { return mPopulation; }
   inline Scene& GetScene() { return mScene; }
   inline GhostObject& GetGhostObject() {  return mGhostObject; }
   inline ObjectTree& GetTree() { return *mpTheTree; }
   inline Pathway* GetEntrance() { return mpParkEntrance; }

   // test
   void AddTestPoint( sf::Vector3f pa, sf::Vector3f pb );

protected:
   // methods
   void ClearStalls (); // deletes all the stalls

public:
   void AddPath (Pathway *path);
   Pathway::PathwayVector GetPaths () { return mPaths; }

   void   AddStall (Stall* pStall);
   Stall* FindStallByType (StallType st);

   void  AddRide (Ride* pRide);
   Ride* FindRideByType (RideType rt);
   Ride* FindRideByName (const char *pszName);

   void Update (float dt, int timeOfDay);
   void Draw ();
   void DrawSelectionTarget (bool bPathwaysOnly);

   // AI interface
   void EnterPark (Person* pPerson);
   void LeavePark (Person* pPerson);

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};

#endif //_PARK_H
