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
#include "../Graphics/ObjectNode.h"

class RideNode;

class Ride : public ObjectNode
{
   sf::Vector3f  mvDim;
   sf::Vector3f  mvPosition;
   sf::Vector3f  mvAngle;
   RideNode* mpBaseNode;   // only child
public:
   Ride();
   virtual ~Ride(void);
   void SetNode (RideNode* pRideNode)
   {
      // be sure to delete the old one if present
      mpBaseNode = pRideNode;
   }

   void DrawSelectionTarget();

   ObjectNode* Clone( );
   void AddSection( ObjectBase* pGLBase );
   void Update(int dt);
   void Draw();
   void Render() { Render(0); };
   int Render( int lod ); // render returning the poly count
//   int GetPathCount() { return m_PointsCount; };
   void Position(sf::Vector3f& vPosition, sf::Vector3f& vAngle) // ah ha, we can move this thing
   {
      mvPosition = vPosition;
      mvAngle = vAngle;
   };
   void Default();

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
