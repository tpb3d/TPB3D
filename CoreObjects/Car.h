//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Flying Camera class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
#include "RideNode.h"

class CVPoint;
class CMainFrame;

class Car : public RideNode
{
   int m_BaseTexture;
   int m_SeatTexture;
   int m_SideTexture;
   sf::Vector3f  m_vDim;
   sf::Vector3f  m_vPosition;
   sf::Vector3f  m_vAngle;
   int      m_PartsCount;
   ObjectNode* m_BaseParts; // temp hardcode

public:
   Car( const sf::Vector3f& vDim, const sf::Vector3f& vPosition, const sf::Vector3f& vAngle, int meshcount, int id );
   Car (ObjectNode* pNode);
   virtual ~Car(void);

   void Draw();
   void Render() { Render(0); };
   int Render( int lod ); // render returning the poly count
//   int GetPathCount() { return m_PointsCount; };
   void Position(const sf::Vector3f& vPosition, const sf::Vector3f& vAngle) // ah ha, we can move this thing
   {
      m_vPosition = vPosition;
      m_vAngle = vAngle;
   };
   void AddSection( ObjectBase* pGLBase );
   void Default();
};
