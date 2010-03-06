//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"

// this is just the tracks not the supports, devices or station
class ObjectBase;
class CVPoint;
struct CamPath;

class Track : public ObjectNode
{
   float m_dHeight; // = 5;
   int   m_PartsCount;
   ObjectBase* m_BaseParts[320]; // temp hardcode
//   CamPath* m_pPoints[168];


public:
   Track(void);
   ~Track(void);

   void AddSection( ObjectBase* pGLBase );
   void Draw();
//   CamPath** GetPath( ) { return m_pPoints; };
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
