//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Object Node class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#pragma once
#include "ObjectBase.h"
#include "SimpleMeshObject.h"
class SimpleMeshObject;

class ObjectNode : public ObjectBase
{
   unsigned short mAllocatedCount;
   unsigned short mAllocatedNodes;
   unsigned short mMeshCount;
   unsigned short mNodeCount;
   ObjectBase** mpMeshes;
   ObjectNode** mpNodes;
protected:
   float       mAngle;
   float       mLocation[3];
   float       mRotation[3];

public:
   ObjectNode( int MeshCount, int id );
   virtual ~ObjectNode(void);
	virtual void Draw();
   virtual void DrawSelectionTarget();
   virtual void Update(int dt) {};

   virtual ObjectNode* Clone( );

   void Animate();
   void AddMesh( ObjectBase* pNode );
   void AddNode( ObjectNode* pChild );
   ObjectNode* GetNode( int index );
   void Move( float Location[3] );
   //void Rotate( float Rotation[3] );
   void SetRotation( float rotate[3] )
   {
      mRotation[0] = rotate[0]; // this optimizes nicely
      mRotation[1] = rotate[1];
      mRotation[2] = rotate[2];
   };

};
