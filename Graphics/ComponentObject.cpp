#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Material.h"
#include "ComponentObject.h"
#include "ObjectFactory.h"

ComponentObject::ComponentObject( int id )
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

ComponentObject::~ComponentObject(void)
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
         MeshGroup* pGroup = this->mpGroups[idx];
         delete pGroup;
      }
      delete mpGroups;
   }
}

void ComponentObject::Draw()
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

	glColor3f( 1.0f, 1.0f, 1.0f );

   for( int idx = 0; idx < mGroups; ++idx )
   {
      MeshGroup* pGroup = this->mpGroups[idx];
      if(  pGroup->mpTexture != NULL )
      {
         glEnable( GL_TEXTURE_2D );
         pGroup->mpTexture->Bind();
      }
      if( mpMaterial[pGroup->mMat] )
      {
         glColor4f( 1.0, 1.0, 1.0, 1.0 );
      //mpMaterial->GLSetMaterial();
         mpMaterial[pGroup->mMat]->GLSetBlendMode();
      }
      //Plug
      if( mbHighlighted )
      {
         glColor4f( 0.5, 0.75, 1.0, 1.0 );
      }

      glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
      for( int idf = 0; idf < pGroup->mFaces; ++idf )
      {
         MeshFace* pFace = pGroup->mpFaces[idf];

         glTexCoord2fv( pFace->mTriangles[0].mUV );
         glNormal3fv( pFace->mTriangles[0].Normal );
         glVertex3fv( mpVertices[pFace->mTriangles[0].Index] ); //Vertex definition

         glTexCoord2fv( pFace->mTriangles[1].mUV );
         glNormal3fv( pFace->mTriangles[1].Normal );
         glVertex3fv( mpVertices[pFace->mTriangles[1].Index] ); //Vertex definition

         glTexCoord2fv( pFace->mTriangles[2].mUV );
         glNormal3fv( pFace->mTriangles[2].Normal );
         glVertex3fv( mpVertices[pFace->mTriangles[2].Index] ); //Vertex definition
      }
      glEnd( );
      glDisable( GL_TEXTURE_2D );
      glDisable( GL_BLEND );
   }
   glPopMatrix();

}

void ComponentObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}

void ComponentObject::AddMaterials( int iMats, Material** pMats )
{
   this->mpMaterial = new Material*[iMats];
   for( int idx = 0; idx < iMats; ++idx )
   {
      mpMaterial[idx] = new Material(*pMats[idx]);
   }
   MaterialCount = iMats;
}

void ComponentObject::AddMesh( int VertexCount, float (* pVertexes)[3], int GroupCount )
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
   mpGroups = new MeshGroup*[GroupCount];

   for( int i = 0; i < mVertices; ++i)
   {
      //lib3ds_vector_copy(p, pMesh->vertices[i]);
      mpVertices[i][0] = pVertexes[i][0]; // *mfScale;
      mpVertices[i][1] = pVertexes[i][1]; // *mfScale;
      mpVertices[i][2] = pVertexes[i][2]; // *mfScale;
   }
}

void ComponentObject::AddMesh( int VertexCount, sf::Vector3f* pVertexes, int GroupCount )
{
   mVertices = VertexCount;
   mGroups = GroupCount;

   mpVertices = new float[mVertices][3];
   mpGroups = new MeshGroup*[GroupCount];

   for( int i = 0; i < mVertices; ++i)
   {
      mpVertices[i][0] = pVertexes[i].x; // *mfScale;
      mpVertices[i][1] = pVertexes[i].y; // *mfScale;
      mpVertices[i][2] = pVertexes[i].z; // *mfScale;
   }
}

ObjectNode* ComponentObject::Clone()
{
   ComponentObject* pNode = ObjectFactory::CreateComponent();
   pNode->AddMaterials( this->MaterialCount, mpMaterial );
   pNode->AddMesh( this->mVertices, mpVertices, this->mGroups );
   for( int idx = 0; idx < mGroups; ++idx )
   {
      MeshGroup* pGroupSource = this->mpGroups[idx];
      MeshGroup* pGroup = pNode->AddMeshGroup( idx, pGroupSource->mFaces, pGroupSource->mMat, pGroupSource->mpTexture );
      for( int idy = 0; idy < pGroupSource->mFaces; ++idy )
      {
         pGroup->AddMeshFace( idy, pGroupSource->mpFaces[idy] );
      }
   }
   return pNode;
}

MeshGroup*  ComponentObject::AddMeshGroup( int Group, int FaceCount, int Mat, Gfx::Texture* pTex )
{
   MeshGroup* pGroup = new MeshGroup();
   mpGroups[Group] = pGroup;
   pGroup->mMat = Mat;
   pGroup->mpFaces = new MeshFace*[FaceCount];
   pGroup->mFaces = FaceCount;
   pGroup->mpTexture = pTex;
   return pGroup;
}

void MeshGroup::AddMeshFace( int face, const MeshFace* pFaceSource )
{
   MeshFace* pFace = new MeshFace();
   memcpy( pFace, pFaceSource, sizeof( MeshFace ) );
   this->mpFaces[face] = pFace;
}

void MeshGroup::AddMeshFaces( int facecount, const MeshFace pFaceSource[] )
{
   for( int face  = 0; face < facecount; ++face )
   {
      MeshFace* pFace = new MeshFace();
      memcpy( pFace, pFaceSource, sizeof( MeshFace ) );
      this->mpFaces[face] = pFace;
   }
}

void MeshGroup::AddMeshFace( int face, unsigned short index0, float(& pNormals0)[3], float U0, float V0,
                                       unsigned short index1, float(& pNormals1)[3], float U1, float V1,
                                       unsigned short index2, float(& pNormals2)[3], float U2, float V2 )
{
   MeshFace* pFace = new MeshFace();
   this->mpFaces[face] = pFace;
   pFace->mTriangles[0].Index = index0;
   pFace->mTriangles[1].Index = index1;
   pFace->mTriangles[2].Index = index2;
   pFace->mTriangles[0].Normal[0] = pNormals0[0];
   pFace->mTriangles[0].Normal[1] = pNormals0[1];
   pFace->mTriangles[0].Normal[2] = pNormals0[2];
   pFace->mTriangles[0].mUV[0] = U0;
   pFace->mTriangles[0].mUV[1] = V0;
   pFace->mTriangles[1].Normal[0] = pNormals1[0];
   pFace->mTriangles[1].Normal[1] = pNormals1[1];
   pFace->mTriangles[1].Normal[2] = pNormals1[2];
   pFace->mTriangles[1].mUV[0] = U1;
   pFace->mTriangles[1].mUV[1] = V1;
   pFace->mTriangles[2].Normal[0] = pNormals2[0];
   pFace->mTriangles[2].Normal[1] = pNormals2[1];
   pFace->mTriangles[2].Normal[2] = pNormals2[2];
   pFace->mTriangles[2].mUV[0] = U2;
   pFace->mTriangles[2].mUV[1] = V2;
}
   //FILE* fp = fopen( "dat.asc", "a+" );
   //for( int idx = 0; idx < mFaces; ++idx )
   //{
   //   fprintf( fp, "Face: %dA, UVs= %f, %f\r", mpIndexes[idx][0], mpUVs[mpIndexes[idx][0]][0], mpUVs[mpIndexes[idx][0]][1] );
   //   fprintf( fp, "Face: %dB, UVs= %f, %f\r", mpIndexes[idx][1], mpUVs[mpIndexes[idx][1]][0], mpUVs[mpIndexes[idx][1]][1] );
   //   fprintf( fp, "Face: %dC, UVs= %f, %f\r", mpIndexes[idx][2], mpUVs[mpIndexes[idx][2]][0], mpUVs[mpIndexes[idx][2]][1] );
   //}
   //fclose( fp );
