//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride Class class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once
#pragma once
#include "CoreBase.h"

class ObjectBase;
class RideNode;
class Person;
class PersonQueue;
class RideController; // the ride controller that the operator uses

enum RideType
{
   RT_Empty = 0, // dead ride
   RT_Coaster,
   RT_FlatRide,
   RT_OtherTrackRide,
   RT_Tour,
   RT_Venue       // Movies, Shows, Arenas and other gathering (non-motion attraction).
};
enum RideIntensity
{
   RI_NonMoving = 0,
   RI_Gentle,
   RI_Family,
   RI_Thrill,
   RI_Intense,
   RI_Extreme
   // someday we will have a level beyond extreme but it has not been invented yet
};

class Ride : public CoreBase
{
   const Park& mParkParent;
   int   mSeats;
   int   mRunTime;      // how long the ride has been running
   int   mMaxRunTime;   // how long is the ride going to run
   std::string mRideName;
   RideNode* mpBaseNode;   // only child
   PersonQueue* mpQueue;
   std::queue<Person*> mRiders;
   RideController* mpRCU;
   //    PersonQueue* mpQueueFastPass;   if we can do this

protected:
   RideType mRideType;
   RideIntensity mRideIntensity;
   bool  mRun;

public:
   Ride(const Vector3f& vPosition, const Park& ParkParent);
   virtual ~Ride();
   void SetNode (RideNode* pRideNode)
   {
      // be sure to delete the old one if present
      mpBaseNode = pRideNode;
   }
   const char* GetRideName () { return mRideName.c_str(); }
   void SetRideName (const char* szName) { mRideName = szName; }
   bool IsType (RideType rt) { return (mRideType == rt); }
   RideType GetRideType () { return mRideType; }
   void SetRideType (RideType rt) { mRideType = rt; }
   RideIntensity GetRideIntensity () { return mRideIntensity; }
   void SetRideIntensity (RideIntensity ri) { mRideIntensity = ri; }
   PersonQueue* GetQueue() { return mpQueue; }
   virtual const char* GetName () { return mRideName.c_str(); }
   RideController* GetController();

   void AddPerson (Person* pPeep);
   void RemovePerson (Person* pPeep);
   void ServeNextPerson (void);
   void UnloadPeople(void);

   void Start() { mRun = true; }
   void Stop() { mRun = false; }

   void DrawSelectionTarget();

   CoreBase* Clone( );
   void AddSection( ObjectBase* pGLBase );
   void Update(int dt);
   void Draw();
   void Render() { Render(0); };
   int Render( int lod ); // render returning the poly count
//   int GetPathCount() { return m_PointsCount; };
   void SetPosition (float x, float y, float z) { mvPosition.x = x; mvPosition.y = y; mvPosition.z = z; }
   void Position(sf::Vector3f& vPosition, sf::Vector3f& vAngle) // ah ha, we can move this thing
   {
      mvPosition = vPosition;
//      mvAngle = vAngle;
   };
   void Default();

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};

// Plug
#include "../Graphics/ObjectNode.h"
class RidePack : public ObjectNode
{
   Ride* mpRide;
   public:
   RidePack(Ride* pRide) : mpRide(pRide), ObjectNode(1,1) {}
   void Update(int dt) { mpRide->Update(dt); }
   void Draw() { mpRide->Draw(); }
   ObjectNode* Clone( ) { return NULL; }
   void DrawSelectionTarget() { mpRide->DrawSelectionTarget(); }
};
// End Plug
