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
#include "TexturedMesh.h"

class MeshNode : public ObjectBase
{
   unsigned short mAllocatedCount;
   unsigned short mMeshCount;
   TexturedMesh**   mpMeshes;
protected:
   float       mAngle;
   float       mLocation[3];
   float       mRotation[3];

public:
   MeshNode( int MeshCount, int id );
   virtual ~MeshNode(void);
	virtual void Draw();
   virtual void DrawSelectionTarget();

   virtual MeshNode* Clone( );

   void Animate();
   void AddMesh( TexturedMesh* pNode );
   MeshNode* GetNode( int index );
   void Move( float Location[3] );
   //void Rotate( float Rotation[3] );
   void SetRotation( float rotate[3] )
   {
      mRotation[0] = rotate[0]; // this optimizes nicely
      mRotation[1] = rotate[1];
      mRotation[2] = rotate[2];
   };

};
