//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride Class class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once
#pragma once
#include "CoreBase.h"

class ObjectBase;
class RideNode;

class Ride : public CoreBase
{
   Park& mParkParent;
   RideNode* mpBaseNode;   // only child
public:
   Ride(Vector3f& vPosition, Park& ParkParent);
   virtual ~Ride();
   void SetNode (RideNode* pRideNode)
   {
      // be sure to delete the old one if present
      mpBaseNode = pRideNode;
   }

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
