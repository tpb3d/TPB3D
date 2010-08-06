//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Object Node class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Texture.h"
#include "MeshNode.h"
#include "ObjectFactory.h"

MeshNode::MeshNode( int MeshCount, int id )
:  ObjectBase( MeshCount, id )
{
   mMeshCount = 0;
   mpMeshes = 0;//= new CSimpleMeshObject*[MeshCount];
   mAngle = 0;
   mLocation[0] = 0;
   mLocation[1] = 1;
   mLocation[2] = 0;
   mRotation[0] = 0;
   mRotation[1] = 0;
   mRotation[2] = 0;
}

MeshNode::~MeshNode(void)
{
   if( mpMeshes )
   {
      for( int idx = 0; idx < mMeshCount; ++idx )
      {
         ObjectBase* pMesh = mpMeshes[idx];
         delete pMesh;
      }
      delete [] mpMeshes;

   }
}

void MeshNode::Animate()
{
   mAngle+= 1.0;
   if( mAngle > 359 )
      mAngle = 0;
}


void MeshNode::Move(float Location[])
{
   mLocation[0] = Location[0]; // this optimizes nicely
   mLocation[1] = Location[1];
   mLocation[2] = Location[2];
}

MeshNode* MeshNode::Clone( )
{
   int id = ObjectFactory::TakeANumber();
   MeshNode* pNode = new MeshNode( mMeshCount, id );
   pNode->SetRotation( mRotation );
   for( int idx = 0; idx < mMeshCount; ++idx )
   {
//      TexturedMesh* pMesh = reinterpret_cast<TexturedMesh*>(mpMeshes[idx]->Clone( ));
   }
   return pNode;
}

void MeshNode::Draw()
{
	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
  // glLoadIdentity();													// Reset The Current Modelview Matrix
	glTranslatef( mLocation[0],mLocation[1],mLocation[2] );
	glRotatef(mRotation[0],1.0f,0.0f,0.0f);
	glRotatef(mRotation[1],0.0f,1.0f,0.0f);
	glRotatef(mRotation[2],0.0f,0.0f,1.0f);

	glColor3f( 1.0f, 1.0f, 1.0f );

//   glRotatef(rotation_x,1.0,0.0,0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)
//   glRotatef(mAngle,0.0,1.0,0.0);
//   glRotatef(rotation_z,0.0,0.0,1.0);
//   glEnable( GL_BLEND );
//   glBlendFunc( GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
// //   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );

   for( int idx = 0; idx < mMeshCount; ++idx )
   {
      TexturedMesh* pMesh = mpMeshes[idx];
      pMesh->Draw();
   }
   glPopMatrix();
//   glDisable( GL_BLEND );
}

void MeshNode::DrawSelectionTarget()
{
   glPassThrough((GLfloat)mID );
   glLoadName( mID );
   glBegin(GL_QUADS);
   float fx = mLocation[0];
   float fy = mLocation[1];
   float fz = mLocation[2];
   glVertex3f( fx, fy, fz );  // needs to be a cube
   glVertex3f( fx+5, fy, fz );
   glVertex3f( fx+5, fy+10, fz );
   glVertex3f( fx, fy+10, fz );
   glEnd();
}

void MeshNode::AddMesh( TexturedMesh* pNode )
{
   if( !mpMeshes )
   {
      mpMeshes = new TexturedMesh*[mAllocatedCount];
   }
   else if( mMeshCount+1 > mAllocatedCount )
   {
      mAllocatedCount+=8;
      TexturedMesh** pMeshes = new TexturedMesh*[mAllocatedCount];
      if( mAllocatedCount > 0 )
      {
         for( int idx = 0; idx < mMeshCount; ++idx )
         {
            pMeshes[idx] = mpMeshes[idx];
         }
         delete [] mpMeshes;
      }
      mpMeshes = pMeshes;
   }
   mpMeshes[mMeshCount++] = pNode;
}

