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
#include "ObjectNode.h"
#include "ObjectFactory.h"

ObjectNode::ObjectNode( int MeshCount, int id )
:  ObjectBase( MeshCount, id )
{
   mAllocatedCount = MeshCount;
   mAllocatedNodes = 0;
   mNodeCount = 0;

   mMeshCount = 0;
   mpMeshes = 0;//= new CSimpleMeshObject*[MeshCount];
   mpNodes = 0;
   mAngle = 0;
   mLocation[0] = 0;
   mLocation[1] = 1;
   mLocation[2] = 0;
   mRotation[0] = 0;
   mRotation[1] = 0;
   mRotation[2] = 0;
   mpNodes = NULL;
   mpMeshes = NULL;
}

ObjectNode::~ObjectNode(void)
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
   if( mpNodes )
   {
      for( int idx = 0; idx < mNodeCount; ++idx )
      {
         ObjectNode* pChild = mpNodes[idx];
         delete pChild;
      }
      delete [] mpNodes;
   }
}

void ObjectNode::Animate()
{
   mAngle+= 1.0;
   if( mAngle > 359 )
      mAngle = 0;
}

ObjectNode* ObjectNode::GetNode( int index )
{
   ObjectNode* pNode = 0;
   if( index < mNodeCount )
   {
      pNode = mpNodes[index];
   }
   return pNode;
}

void ObjectNode::Move(const float Location[])
{
   mLocation[0] = Location[0]; // this optimizes nicely
   mLocation[1] = Location[1];
   mLocation[2] = Location[2];
}

ObjectNode* ObjectNode::Clone( )
{
   int id = ObjectFactory::TakeANumber();
   ObjectNode* pNode = new ObjectNode( mMeshCount, id );
   pNode->SetRotation( mRotation );
   for( int idx = 0; idx < mMeshCount; ++idx )
   {
      SimpleMeshObject* pMesh = reinterpret_cast<SimpleMeshObject*>(mpMeshes[idx]->Clone( ));
   }
   //for( int idx = 0; idx < mNodeCount; ++idx )
   //{
   //   CObjectNode* pChild = mpNodes[idx];
   //   pChild->Draw();
   //}

   for( int idx = 0; idx < mNodeCount; ++idx )
   {
      pNode->AddNode(mpNodes[idx]);
   }

   for( int idx = 0; idx < mMeshCount; ++idx )
   {
      pNode->AddMesh(mpMeshes[idx]);
   }

   return pNode;
}

void ObjectNode::Draw()
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
      ObjectBase* pMesh = mpMeshes[idx];
      pMesh->Draw();
   }
   glPopMatrix();
   for( int idx = 0; idx < mNodeCount; ++idx )
   {
   	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
      ObjectNode* pChild = mpNodes[idx];
      pChild->Draw();
      glPopMatrix();
   }

//   glDisable( GL_BLEND );
}

void ObjectNode::DrawSelectionTarget()
{
	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
	glTranslatef( mLocation[0],mLocation[1],mLocation[2] );
	glRotatef(mRotation[0],1.0f,0.0f,0.0f);
	glRotatef(mRotation[1],0.0f,1.0f,0.0f);
	glRotatef(mRotation[2],0.0f,0.0f,1.0f);
//   glPassThrough((GLfloat)mID );
   glLoadName( mID );
   for( int idx = 0; idx < mMeshCount; ++idx )
   {
      ObjectBase* pMesh = mpMeshes[idx];
      pMesh->DrawSelectionTarget();
   }
   glPopMatrix();
}

void ObjectNode::AddMesh( ObjectBase* pNode )
{
   if( !mpMeshes )
   {
      mAllocatedCount+=4;
      mpMeshes = new ObjectBase*[mAllocatedCount];
   }
   else if( mMeshCount+1 > mAllocatedCount )
   {
      mAllocatedCount+=4;
      ObjectBase** pMeshes = new ObjectBase*[mAllocatedCount];
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

void ObjectNode::AddNode(ObjectNode *pChild)
{
   if( !mpNodes )
   {
      mpNodes = new ObjectNode*[4];
      mAllocatedNodes = 4;
   }
   else if( mNodeCount+1 > mAllocatedNodes )
   {
      mAllocatedNodes+=4;
      ObjectNode** pNodes = new ObjectNode*[mAllocatedNodes];
      if( mAllocatedNodes > 0 )
      {
         for( int idx = 0; idx < mNodeCount; ++idx )
         {
            pNodes[idx] = mpNodes[idx];
         }
         delete [] mpNodes;
      }
      mpNodes = pNodes;
   }
   mpNodes[mNodeCount++] = pChild;
}
