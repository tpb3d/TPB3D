//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RidePart Class class - base of parts objects to build rides from
//
//  You should have received a copy of the GNU General Public License
//  along with Extreme Park Developer.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"

class RidePart : public ObjectNode
{
   int m_BaseTexture;
   int m_SeatTexture;
   int m_SideTexture;
   sf::Vector3f  m_vDim;
   sf::Vector3f  m_vPosition;
   sf::Vector3f  m_vAngle;
   int      m_PartsCount;
   ObjectBase* m_BaseParts[16]; // temp hardcode

public:
   RidePart(sf::Vector3f& vDim, sf::Vector3f& vPosition, sf::Vector3f& vAngle, int meshcount, int id );
   virtual ~RidePart(void);

   void Draw();
   void Render() { Render(0); };
   int Render( int lod ); // render returning the poly count
//   int GetPathCount() { return m_PointsCount; };
   void Position(sf::Vector3f& vPosition, sf::Vector3f& vAngle) // ah ha, we can move this thing
   {
      m_vPosition = vPosition;
      m_vAngle = vAngle;
   };
   void AddSection( ObjectBase* pGLBase );
   void RidePart::Default();
};
