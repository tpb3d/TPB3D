//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
// Ride node, this part can host other parts

#pragma once
#include <vector>
#include "../Types/Vector3.h"
struct PartGuide;
class SerializerBase;

class RideNode
{
protected:
   typedef std::vector<RideNode*> RideNodeVector;
   typedef std::vector<RideNode*>::iterator RideNodeIterator;
//   typedef std::vector<ObjectBase*> SectionVector;
//   typedef std::vector<ObjectBase*>::iterator SectionIterator;

   RideNodeVector mBaseParts; // temp hardcode
//   SectionVector mMeshes;
protected:
   sf::Vector3f  mvDim;
   sf::Vector3f  mvPosition;
   sf::Vector3f  mvAngle;

public:
   // ctor/dtor
   RideNode();
   ~RideNode(void);

   // methods
   void Clear();
   void Create (int Count);
   void SetupGuide (PartGuide& guide);
   void Preset (float fDefPitch, float fLength, float fDegRotation);
   void AddNode( RideNode* pNodeBase );
   void SetPosition (float x, float y, float z) { mvPosition.x = x; mvPosition.y = y; mvPosition.z = z; }
//   void AddSection( ObjectBase* pGLBase );
   virtual void Update (int dt);
   virtual void Render() = 0;   // force each derivative to 
   virtual void Draw();
   virtual void DrawSelectionTarget(int mode) = 0;
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
