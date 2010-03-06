#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "Material.h"
#include "ObjectFactory.h"
#include "ComplexMeshObject.h"

ComplexMeshObject::ComplexMeshObject( int meshcount, int id )
:  ObjectNode( meshcount, id )
{
   mVertices = 0;
   mAngle = 0;
   mGroupCount = 0;
   mpTexture = NULL;
   mpName = NULL;
   memset( mMatrix, 0, 4 * 4 * sizeof(float) );        /**< Transformation matrix for mesh data */
   mpVertices = NULL;
   mpGroups = NULL;
   mpMaterial = NULL;
}

ComplexMeshObject::~ComplexMeshObject(void)
{
   delete [] mpVertices;
   delete [] mpGroups;

   if( mpName )
      delete mpName;
   if( mpMaterial )
      delete mpMaterial;
}

ComplexMeshObject* ComplexMeshObject::Create()
{
   return ObjectFactory::CreateComplex();
}

void ComplexMeshObject::AddMaterials( int iMats, Material** pMats )
{
   if( mpMaterial )
   {
      delete [] mpMaterial;
   }
   mpMaterial = new Material*[iMats];
   mMaterialCount = iMats;
   for( int idx = 0; idx < iMats; ++idx )
   {
      mpMaterial[idx] = new Material(*pMats[idx]);
   }
   mpTexture = mpMaterial[0]->GetTexture( );
}

ObjectNode* ComplexMeshObject::Clone( )
{
   int id = ObjectFactory::TakeANumber();
   ComplexMeshObject* pNode = new ComplexMeshObject( 1, id );
   pNode->AddMaterials( 1, mpMaterial );
//   pNode->AddMesh( mVertices, mpVertices, mpNormals,
//                   mUVCount, mpUVs,
//                   mFaces, mpIndexes );
   pNode->AddMesh( mVertices, mpVertices, mGroupCount );
   for( int idx = 0; idx < mGroupCount; ++idx )
   {
      ComplexGroup* pSG = mpGroups[idx];
      ComplexGroup* pGroup = pNode->AddGroup( idx, pSG->mFaces, pSG->mMat, pSG->mpTexture );
      for( int ids = 0; ids < pSG->mFaces; ++ids )
      {
         pGroup->AddFace( ids, pSG->mpFaces[ids] );
      }
   }

   return pNode;
}

void ComplexMeshObject::Draw()
{
   if( mpMaterial )
   {
//      mpMaterial->GLSetMaterial();
      glShadeModel( GL_SMOOTH );
   }
//   else
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

   for( int idx = 0; idx < mGroupCount; ++idx )
   {
      if( mpGroups[idx]->mpTexture != NULL )
      {
         glEnable( GL_TEXTURE_2D );
         mpGroups[idx]->mpTexture->Bind();
      }

      glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
      for( int idf = 0; idf < mpGroups[idx]->mFaces; ++idf )
      {
         ComplexFace* pFace = mpGroups[idx]->mpFaces[idf];
        // Coordinates of the first vertex
         glTexCoord2fv( pFace->mPoints[0].mUV );
         glNormal3fv( pFace->mPoints[0].Normal );
         glVertex3fv( mpVertices[pFace->mPoints[0].Index] ); //Vertex definition

        // Coordinates of the second vertex
         glTexCoord2fv( pFace->mPoints[0].mUV );
         glNormal3fv( pFace->mPoints[0].Normal );
         glVertex3fv( mpVertices[pFace->mPoints[0].Index] ); //Vertex definition

        // Coordinates of the third vertex
         glTexCoord2fv( pFace->mPoints[0].mUV );
         glNormal3fv( pFace->mPoints[0].Normal );
         glVertex3fv( mpVertices[pFace->mPoints[0].Index] ); //Vertex definition
      }
      glEnd( );
   }
   glDisable( GL_TEXTURE_2D );
}

void ComplexMeshObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}

void ComplexMeshObject::AddMesh( int VertexCount, float (* pVertexes)[3], int GroupCount )
{
   mVertices = VertexCount;
   mGroupCount = GroupCount;

   mpVertices = new float[mVertices][3];
   mpGroups = new ComplexGroup*[GroupCount];

   for( int i = 0; i < mVertices; ++i)
   {
      mpVertices[i][0] = pVertexes[i][0]; // *mfScale;
      mpVertices[i][1] = pVertexes[i][1]; // *mfScale;
      mpVertices[i][2] = pVertexes[i][2]; // *mfScale;
   }
}

void ComplexMeshObject::AddMesh( int VertexCount, sf::Vector3f* pVertexes, int GroupCount )
{
   mVertices = VertexCount;
   mGroupCount = GroupCount;

   mpVertices = new float[mVertices][3];
   mpGroups = new ComplexGroup*[GroupCount];

   for( int i = 0; i < mVertices; ++i)
   {
      mpVertices[i][0] = pVertexes[i].x; // *mfScale;
      mpVertices[i][1] = pVertexes[i].y; // *mfScale;
      mpVertices[i][2] = pVertexes[i].z; // *mfScale;
   }
}

ComplexGroup* ComplexMeshObject::AddGroup( int Group, int FaceCount, int Mat, Gfx::Texture* pTex )
{
   ComplexGroup* pGroup = new ComplexGroup();
   mpGroups[Group] = pGroup;
   pGroup->mMat = Mat;
   pGroup->mpFaces = new ComplexFace*[FaceCount];
   pGroup->mFaces = FaceCount;
   pGroup->mpTexture = pTex;
   return pGroup;
}

void ComplexGroup::AddFace( int FaceCount, const ComplexFace* pFaceSource )
{
   for( int idx = 0; idx < FaceCount; ++idx )
   {
      ComplexFace* pFace = new ComplexFace();
      memcpy( pFace, &pFaceSource[idx], sizeof( ComplexFace ) );
      this->mpFaces[idx] = pFace;
   }
}

void ComplexGroup::AddFace( int Face, unsigned short index0, float(& pNormals0)[3], float U0, float V0,
                                       unsigned short index1, float(& pNormals1)[3], float U1, float V1,
                                       unsigned short index2, float(& pNormals2)[3], float U2, float V2 )
{
   ComplexFace* pFace = new ComplexFace();
   pFace->mPoints[0].Index = index0;
   pFace->mPoints[1].Index = index1;
   pFace->mPoints[2].Index = index2;
   pFace->mPoints[0].Normal[0] = pNormals0[0];
   pFace->mPoints[0].Normal[1] = pNormals0[1];
   pFace->mPoints[0].Normal[2] = pNormals0[2];
   pFace->mPoints[0].mUV[0] = U0;
   pFace->mPoints[0].mUV[1] = V0;
   pFace->mPoints[1].Normal[0] = pNormals1[0];
   pFace->mPoints[1].Normal[1] = pNormals1[1];
   pFace->mPoints[1].Normal[2] = pNormals1[2];
   pFace->mPoints[1].mUV[0] = U1;
   pFace->mPoints[1].mUV[1] = V1;
   pFace->mPoints[2].Normal[0] = pNormals1[0];
   pFace->mPoints[2].Normal[1] = pNormals1[1];
   pFace->mPoints[2].Normal[2] = pNormals1[2];
   pFace->mPoints[2].mUV[0] = U1;
   pFace->mPoints[2].mUV[1] = V1;
   mpFaces[Face] = pFace;
}
