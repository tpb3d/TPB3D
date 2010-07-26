//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  SimpleMatMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "SimpleMatMeshObject.h"
#include "Material.h"
#include "ObjectFactory.h"

using namespace Gfx;

SimpleMatMeshObject::SimpleMatMeshObject( int id )
:  ObjectBase( 1, id ) // just the mount point
{
   mVertices = 0;
   mAngle = 0;
   mFaces = 0;
   mpName = NULL;
   memset( mMatrix, 0, 4 * 4 * sizeof(float) );        /**< Transformation matrix for mesh data */
   mpVertices = NULL;
   mpFaces = NULL;
   mfScale = 1.0;
   mpMaterials = NULL;
   mIndexes = 0;
}

SimpleMatMeshObject::~SimpleMatMeshObject(void)
{
   delete [] mpVertices;
   delete [] mpFaces;

   if( mpName )
      delete mpName;
   try
   {
      if( mpMaterials )
         delete /*[]*/ mpMaterials;
   }
   catch ( ...)
   {
      int t = 0; // debug spot
   }
}

void SimpleMatMeshObject::SetMaterials( Gfx::MaterialsList* pMats )
{
   mpMaterials = pMats;
}

ObjectBase* SimpleMatMeshObject::Clone( )
{
   int id = ObjectFactory::TakeANumber();
   SimpleMatMeshObject* pNode = new SimpleMatMeshObject( id );
   pNode->SetMaterials (mpMaterials);
//   pNode->AddMesh( mVertices, mpVertices, mpNormals,
//                   mUVCount, mpUVs,
//                   mFaces, mpIndexes );
   pNode->AddMesh( mVertices, mpVertices, mFaces, mpFaces );


   return pNode;
}

void SimpleMatMeshObject::Draw()
{
   if( mpMaterials )
   {
//      mpMaterial->GLSetMaterial();
      glShadeModel( GL_SMOOTH );
   }
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

   glEnable( GL_BLEND );
   glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
   for( int idx = 0; idx < mFaces; ++idx )
   {
        // Coordinates of the first vertex

//      Material **mpM = mpMaterials->GetMats();
//      mpM[mpFaces[idx]->Mat]->GLSetMaterial();
      TrigPoint2& face = mpFaces[idx]->mPoints[0];
      //glNormal3fv( face.Normal );
      glVertex3fv( mpVertices[face.Index] ); //Vertex definition

        // Coordinates of the second vertex
      TrigPoint2& face1 = mpFaces[idx]->mPoints[1];
      //glNormal3fv( face1.Normal );
      glVertex3fv( mpVertices[face1.Index] ); //Vertex definition

        // Coordinates of the third vertex
      TrigPoint2& face2 = mpFaces[idx]->mPoints[2];
      //glNormal3fv( face2.Normal );
      glVertex3fv( mpVertices[face2.Index] ); //Vertex definition
   }
   glEnd( );
   glDisable( GL_TEXTURE_2D );
   glDisable( GL_BLEND );
}

void SimpleMatMeshObject::DrawSelectionTarget()
{
   glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
   for( int idx = 0; idx < mFaces; ++idx )
   {
        // Coordinates of the first vertex
      TrigPoint2& face = mpFaces[idx]->mPoints[0];
//      glNormal3fv( face.Normal );
      glVertex3fv( mpVertices[face.Index] ); //Vertex definition

        // Coordinates of the second vertex
      TrigPoint2& face1 = mpFaces[idx]->mPoints[1];
//      glNormal3fv( face1.Normal );
      glVertex3fv( mpVertices[face1.Index] ); //Vertex definition

        // Coordinates of the third vertex
      TrigPoint2& face2 = mpFaces[idx]->mPoints[2];
 //     glNormal3fv( face2.Normal );
      glVertex3fv( mpVertices[face2.Index] ); //Vertex definition
   }
   glEnd( );
 }

void SimpleMatMeshObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}

void SimpleMatMeshObject::AddStripFace( int Face, const SimpleFace2* pTrigSource )
{
   SimpleFace2* pFace = new SimpleFace2();
   memcpy( pFace, &pTrigSource[Face], sizeof( SimpleFace2 ) );
}

void SimpleMatMeshObject::AddStripFaces( int FaceCount, const SimpleFace2 pTrigSource[] )
{
   for( int Pair  = 0; Pair < FaceCount; ++Pair )
   {
      SimpleFace2* pFace = new SimpleFace2();
      memcpy( pFace, &pTrigSource[Pair], sizeof( SimpleFace2 ) );
      this->mpFaces[Pair] = pFace;
   }
}

void SimpleMatMeshObject::AddMesh( int VertexCount, float(* pVertexes)[3], float(* pNormals)[3],
                        int FaceCount, unsigned short(* pFaces)[3], unsigned int(*pMats) )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;

   mpVertices = new float[mVertices][3];
   mpFaces = new SimpleFace2*[FaceCount];

   for( int i = 0; i < mVertices; ++i)
   {
      mpVertices[i][0] = pVertexes[i][0]*mfScale;
      if( mfScale > 2.0 || mfScale < 1.0)
      {
         mpVertices[i][1] = pVertexes[i][2]*mfScale;
         mpVertices[i][2] = -pVertexes[i][1]*mfScale;
      }
      else
      {
         mpVertices[i][1] = pVertexes[i][1]*mfScale;
         mpVertices[i][2] = pVertexes[i][2]*mfScale;
      }
   }
   int idxF = 0;
   for( int idx = 0; idx < FaceCount; ++idx )
   {
      SimpleFace2* pFace = new SimpleFace2();
      pFace->mPoints[0].Index = pFaces[idx][0];
      pFace->mPoints[0].Normal[0] = pNormals[idx][0];
      pFace->mPoints[0].Normal[1] = pNormals[idx][1];
      pFace->mPoints[0].Normal[2] = pNormals[idx][2];
      idxF++;
      pFace->mPoints[1].Index = pFaces[idx][1];
      pFace->mPoints[1].Normal[0] = pNormals[idx][0];
      pFace->mPoints[1].Normal[1] = pNormals[idx][1];
      pFace->mPoints[1].Normal[2] = pNormals[idx][2];
      idxF++;
      pFace->mPoints[2].Index = pFaces[idx][2];
      pFace->mPoints[2].Normal[0] = pNormals[idx][0];
      pFace->mPoints[2].Normal[1] = pNormals[idx][1];
      pFace->mPoints[2].Normal[2] = pNormals[idx][2];
      idxF++;
      mpFaces[idx] = pFace;
      mpFaces[idx]->Mat = pMats[idx];
   }
}

void SimpleMatMeshObject::AddMesh( int VertexCount,  float (* pVertexes)[3], int FaceCount, SimpleFace2** pTrigSource )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;

   mpVertices = new float[mVertices][3];
   mpFaces = new SimpleFace2*[FaceCount];

   for( int i = 0; i < mVertices; ++i)
   {
      //lib3ds_vector_copy(p, pMesh->vertices[i]);
      mpVertices[i][0] = pVertexes[i][0]*mfScale;
      mpVertices[i][1] = pVertexes[i][1]*mfScale;
      mpVertices[i][2] = pVertexes[i][2]*mfScale;
   }
   for( int idx = 0; idx < FaceCount; ++idx )
   {
      SimpleFace2* pFace = new SimpleFace2();
      SimpleFace2* pSource = pTrigSource[idx];
      pFace->mPoints[0].Index = pSource->mPoints[0].Index;
      pFace->mPoints[0].Normal[0] = pSource->mPoints[0].Normal[0];
      pFace->mPoints[0].Normal[1] = pSource->mPoints[0].Normal[1];
      pFace->mPoints[0].Normal[2] = pSource->mPoints[0].Normal[2];

      pFace->mPoints[1].Index = pSource->mPoints[1].Index;
      pFace->mPoints[1].Normal[0] = pSource->mPoints[1].Normal[0];
      pFace->mPoints[1].Normal[1] = pSource->mPoints[1].Normal[1];
      pFace->mPoints[1].Normal[2] = pSource->mPoints[1].Normal[2];

      pFace->mPoints[2].Index = pSource->mPoints[2].Index;
      pFace->mPoints[2].Normal[0] = pSource->mPoints[2].Normal[0];
      pFace->mPoints[2].Normal[1] = pSource->mPoints[2].Normal[1];
      pFace->mPoints[2].Normal[2] = pSource->mPoints[2].Normal[2];

   }
}
