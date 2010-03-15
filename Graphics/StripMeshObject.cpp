//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  StripMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Material.h"
#include "StripMeshObject.h"
#include "ObjectFactory.h"

StripMeshObject::StripMeshObject( int id )
:  ObjectNode( 1, id ) // just the mount point
{
   mpName = 0;
   mpVertices = 0;
   mpMaterial = 0;
   mpGroups = 0;
   mGroups = 0;
   mVertices = 0;
   MaterialCount = 0;
}

StripMeshObject::~StripMeshObject(void)
{
   delete [] mpVertices;
   if( mpName )
      delete mpName;
   if( mpMaterial )
   {
      for( int idx = 0; idx < MaterialCount; ++idx )
      {
         delete mpMaterial[idx];
      }
      delete [] mpMaterial;
   }
   if( mpGroups )
   {
      for( int idx = 0; idx < mGroups; ++idx )
      {
         StripGroup* pGroup = this->mpGroups[idx];
         delete pGroup;
      }
      delete mpGroups;
   }
}

StripMeshObject* StripMeshObject::Create()
{
   return ObjectFactory::CreateStrip();
}

void StripMeshObject::Draw()
{
//   else
//   if( mTextures[0] >= 0 )
//   {
//      glEnable( GL_TEXTURE_2D );
//      glBindTexture(GL_TEXTURE_2D, mTextures[0]);
//   }
   //glEnableClientState( GL_NORMAL_ARRAY );
   //glEnableClientState( GL_VERTEX_ARRAY );
   //glEnableClientState( GL_INDEX_ARRAY );
   //glEnableClientState( GL_TEXTURE_COORD_ARRAY );
   //glVertexPointer( 3, GL_FLOAT, 0, mpVertices );
   //glTexCoordPointer( 2, GL_FLOAT, 0, mpUVs );
   //glNormalPointer( GL_FLOAT, 0, mpNormals );

   //glDrawElements( GL_TRIANGLES, mIndexes, GL_UNSIGNED_SHORT, mpIndexes );

   //glDisableClientState( GL_VERTEX_ARRAY );
   //glDisableClientState( GL_INDEX_ARRAY );
   //glDisable( GL_TEXTURE_2D );
	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
	glTranslatef( mLocation[0],mLocation[1],mLocation[2] );
	glRotatef(mRotation[0],1.0f,0.0f,0.0f);
	glRotatef(mRotation[1],0.0f,1.0f,0.0f);
	glRotatef(mRotation[2],0.0f,0.0f,1.0f);
   glEnable( GL_LIGHTING );
   glShadeModel( GL_SMOOTH );												// Enable Smooth Shading
   glEnable( GL_LIGHT1 );

	glColor3f( 0.5f, 0.4f, 0.4f );

   for( int idx = 0; idx < mGroups; ++idx )
   {
      StripGroup* pGroup = this->mpGroups[idx];
      if(  pGroup->mpTexture != NULL )
      {
         glEnable( GL_TEXTURE_2D );
        pGroup->mpTexture->Bind( );
      }
      if( mpMaterial[pGroup->mMat] )
      {
//         glColor4f( 1.0, 1.0, 1.0, 1.0 );
      //mpMaterial->GLSetMaterial();
         mpMaterial[pGroup->mMat]->GLSetBlendMode();
      }
      //Plug
      if( mbHighlighted )
      {
         glColor4f( 0.5, 0.75, 1.0, 1.0 );
      }

      glBegin(GL_TRIANGLE_STRIP);
      for( int idf = 0; idf < pGroup->mPairs; ++idf )
      {
         StripPair* pPair = pGroup->mpPairs[idf];

         glTexCoord2fv( pPair->mPoints[0].mUV );
         glNormal3fv( pPair->mPoints[0].Normal );
         glVertex3fv( mpVertices[pPair->mPoints[0].Index] ); //Vertex definition

         glTexCoord2fv( pPair->mPoints[1].mUV );
         glNormal3fv( pPair->mPoints[1].Normal );
         glVertex3fv( mpVertices[pPair->mPoints[1].Index] ); //Vertex definition

      }
      glEnd( );
      glDisable( GL_TEXTURE_2D );
      //glDisable( GL_BLEND );
   }
   ObjectNode::Draw();
   glDisable( GL_LIGHTING );
	glColor3f( 1.0f, 1.0f, 1.0f );

   glPopMatrix();

}

void StripMeshObject::DrawSelectionTarget()   // just the basic geometry
{
	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
	glTranslatef( mLocation[0],mLocation[1],mLocation[2] );
	glRotatef(mRotation[0],1.0f,0.0f,0.0f);
	glRotatef(mRotation[1],0.0f,1.0f,0.0f);
	glRotatef(mRotation[2],0.0f,0.0f,1.0f);
   for( int idx = 0; idx < mGroups; ++idx )
   {
      StripGroup* pGroup = this->mpGroups[idx];
      glBegin(GL_TRIANGLE_STRIP);
      for( int idf = 0; idf < pGroup->mPairs; ++idf )
      {
         StripPair* pPair = pGroup->mpPairs[idf];

//         glNormal3fv( pPair->mPoints[0].Normal );
         glVertex3fv( mpVertices[pPair->mPoints[0].Index] ); //Vertex definition

//         glNormal3fv( pPair->mPoints[1].Normal );
         glVertex3fv( mpVertices[pPair->mPoints[1].Index] ); //Vertex definition

      }
      glEnd( );
   }
   ObjectNode::Draw();

   glPopMatrix();
}

void StripMeshObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}

void StripMeshObject::AddMaterials( int iMats, Material** pMats )
{
   this->mpMaterial = new Material*[iMats];
   for( int idx = 0; idx < iMats; ++idx )
   {
      mpMaterial[idx] = new Material(*pMats[idx]);
   }
   MaterialCount = iMats;
}

void StripMeshObject::AddMesh( int VertexCount, float (* pVertexes)[3], int GroupCount )
{
   //if( mpName )
   //{
   //   delete mpName;
   //}
   //size_t iStrLen = (strlen( pMesh->name ) + 8) & 0xfffffff8;
   //mpName = new char[ iStrLen ];
   //strcpy_s( mpName, iStrLen, pMesh->name );
   mVertices = VertexCount;
   mGroups = GroupCount;
   //mUVCount = UVCount;

   mpVertices = new float[mVertices][3];
   mpGroups = new StripGroup*[GroupCount];

   for( int i = 0; i < mVertices; ++i)
   {
      //lib3ds_vector_copy(p, pMesh->vertices[i]);
      mpVertices[i][0] = pVertexes[i][0]; // *mfScale;
      mpVertices[i][1] = pVertexes[i][1]; // *mfScale;
      mpVertices[i][2] = pVertexes[i][2]; // *mfScale;
   }
}

void StripMeshObject::AddMesh( int VertexCount, sf::Vector3f* pVertexes, int GroupCount )
{
   mVertices = VertexCount;
   mGroups = GroupCount;

   mpVertices = new float[mVertices][3];
   mpGroups = new StripGroup*[GroupCount];

   for( int i = 0; i < mVertices; ++i)
   {
      mpVertices[i][0] = pVertexes[i].x; // *mfScale;
      mpVertices[i][1] = pVertexes[i].y; // *mfScale;
      mpVertices[i][2] = pVertexes[i].z; // *mfScale;
   }
}

ObjectNode* StripMeshObject::Clone()
{
   StripMeshObject* pNode = ObjectFactory::CreateStrip();
   pNode->AddMaterials( this->MaterialCount, mpMaterial );
   pNode->AddMesh( this->mVertices, mpVertices, this->mGroups );
   for( int idx = 0; idx < mGroups; ++idx )
   {
      StripGroup* pGroupSource = this->mpGroups[idx];
      StripGroup* pGroup = pNode->AddStripGroup( idx, pGroupSource->mPairs, pGroupSource->mMat, pGroupSource->mpTexture );
      for( int idy = 0; idy < pGroupSource->mPairs; ++idy )
      {
         pGroup->AddStripPair( idy, pGroupSource->mpPairs[idy] );
      }
   }
   return pNode;
}

StripGroup* StripMeshObject::AddStripGroup( int Group, int PairCount, int Mat, Gfx::Texture* pTex )
{
   StripGroup* pGroup = new StripGroup();
   mpGroups[Group] = pGroup;
   pGroup->mMat = Mat;
   pGroup->mpPairs = new StripPair*[PairCount];
   pGroup->mPairs = PairCount;
   pGroup->mpTexture = pTex;
   return pGroup;
}

void StripGroup::AddStripPair( int Pairs, const StripPair* pPairSource )
{
   for( int idx = 0; idx < Pairs; ++idx )
   {
      StripPair* pPair = new StripPair();
      memcpy( pPair, &pPairSource[idx], sizeof( StripPair ) );
      this->mpPairs[idx] = pPair;
   }
}

void StripGroup::AddStripPairs( int Paircount, const StripPair pPairSource[] )
{
   for( int Pair  = 0; Pair < Paircount; ++Pair )
   {
      StripPair* pPair = new StripPair();
      memcpy( pPair, &pPairSource[Pair], sizeof( StripPair ) );
      this->mpPairs[Pair] = pPair;
   }
}

void StripGroup::AddStripPair( int Pair, unsigned short index0, float(& pNormals0)[3], float U0, float V0,
                                       unsigned short index1, float(& pNormals1)[3], float U1, float V1 )
{
   StripPair* pPair = new StripPair();
   this->mpPairs[Pair] = pPair;
   pPair->mPoints[0].Index = index0;
   pPair->mPoints[1].Index = index1;
   pPair->mPoints[0].Normal[0] = pNormals0[0];
   pPair->mPoints[0].Normal[1] = pNormals0[1];
   pPair->mPoints[0].Normal[2] = pNormals0[2];
   pPair->mPoints[0].mUV[0] = U0;
   pPair->mPoints[0].mUV[1] = V0;
   pPair->mPoints[1].Normal[0] = pNormals1[0];
   pPair->mPoints[1].Normal[1] = pNormals1[1];
   pPair->mPoints[1].Normal[2] = pNormals1[2];
   pPair->mPoints[1].mUV[0] = U1;
   pPair->mPoints[1].mUV[1] = V1;
   mpPairs[mPairs++] = pPair;
}
