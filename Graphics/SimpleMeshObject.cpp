//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  SimpleMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "SimpleMeshObject.h"
#include "Material.h"
#include "ObjectFactory.h"

using namespace Gfx;

SimpleMeshObject::SimpleMeshObject( int id )
:  ObjectBase( 1, id ) // just the mount point
{
   mVertices = 0;
   mAngle = 0;
   mFaces = 0;
   mpTexture = NULL;
   mpName = NULL;
   memset( mMatrix, 0, 4 * 4 * sizeof(float) );        /**< Transformation matrix for mesh data */
   mpVertices = NULL;
   mpFaces = NULL;
   mfScale = 1.0;
   mpMaterials = NULL;
}

SimpleMeshObject::~SimpleMeshObject(void)
{
   delete [] mpVertices;
   delete [] mpFaces;

   if( mpName )
      delete mpName;
   if( mpMaterials )
      delete [] mpMaterials;
}

void SimpleMeshObject::SetMaterials( Gfx::MaterialsList* pMats )
{
   mpMaterials = pMats;
   mpTexture = pMats->GetMats()[0]->GetTexture();
}

ObjectBase* SimpleMeshObject::Clone( )
{
   int id = ObjectFactory::TakeANumber();
   SimpleMeshObject* pNode = new SimpleMeshObject( id );
   pNode->SetMaterials (mpMaterials);
//   pNode->AddMesh( mVertices, mpVertices, mpNormals,
//                   mUVCount, mpUVs,
//                   mFaces, mpIndexes );
   pNode->AddMesh( mVertices, mpVertices, mFaces, mpFaces );


   return pNode;
}

void SimpleMeshObject::Draw()
{
   if( mpMaterials )
   {
//      mpMaterial->GLSetMaterial();
      glShadeModel( GL_SMOOTH );
   }
//   else
   if( mpTexture != NULL )
   {
      glEnable( GL_TEXTURE_2D );
      mpTexture->Bind( );
      unsigned char ub[] = { 250,250,220,255 };
      glColor3ubv( ub );
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
      TrigPoint& face = mpFaces[idx]->mPoints[0];
      glTexCoord2fv( face.mUV );
      //glNormal3fv( face.Normal );
      glVertex3fv( mpVertices[face.Index] ); //Vertex definition

        // Coordinates of the second vertex
      TrigPoint& face1 = mpFaces[idx]->mPoints[1];
      glTexCoord2fv( face1.mUV );
      //glNormal3fv( face1.Normal );
      glVertex3fv( mpVertices[face1.Index] ); //Vertex definition

        // Coordinates of the third vertex
      TrigPoint& face2 = mpFaces[idx]->mPoints[2];
      glTexCoord2fv( face2.mUV );
      //glNormal3fv( face2.Normal );
      glVertex3fv( mpVertices[face2.Index] ); //Vertex definition
   }
   glEnd( );
   glDisable( GL_TEXTURE_2D );
   glDisable( GL_BLEND );
}

void SimpleMeshObject::DrawSelectionTarget()
{
   glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
   for( int idx = 0; idx < mFaces; ++idx )
   {
        // Coordinates of the first vertex
      TrigPoint& face = mpFaces[idx]->mPoints[0];
//      glNormal3fv( face.Normal );
      glVertex3fv( mpVertices[face.Index] ); //Vertex definition

        // Coordinates of the second vertex
      TrigPoint& face1 = mpFaces[idx]->mPoints[1];
//      glNormal3fv( face1.Normal );
      glVertex3fv( mpVertices[face1.Index] ); //Vertex definition

        // Coordinates of the third vertex
      TrigPoint& face2 = mpFaces[idx]->mPoints[2];
 //     glNormal3fv( face2.Normal );
      glVertex3fv( mpVertices[face2.Index] ); //Vertex definition
   }
   glEnd( );
 }

void SimpleMeshObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}

void SimpleMeshObject::AddStripFace( int Face, const SimpleFace* pTrigSource )
{
   SimpleFace* pFace = new SimpleFace();
   memcpy( pFace, &pTrigSource[Face], sizeof( SimpleFace ) );
}

void SimpleMeshObject::AddStripFaces( int FaceCount, const SimpleFace pTrigSource[] )
{
   for( int Pair  = 0; Pair < FaceCount; ++Pair )
   {
      SimpleFace* pFace = new SimpleFace();
      memcpy( pFace, &pTrigSource[Pair], sizeof( SimpleFace ) );
      this->mpFaces[Pair] = pFace;
   }
}

void SimpleMeshObject::AddMesh( int VertexCount, float(* pVertexes)[3], float(* pNormals)[3],
                       int UVCount, float(* pUVs)[2],
                        int FaceCount, unsigned short(* pFaces)[3], unsigned int(*pMats) )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;
   mUVCount = UVCount;

   mpVertices = new float[mVertices][3];
   mpFaces = new SimpleFace*[FaceCount];

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
      SimpleFace* pFace = new SimpleFace();
      pFace->mPoints[0].Index = pFaces[idx][0];
      pFace->mPoints[0].mUV[0] = pUVs[pFaces[idx][0]][0];
      pFace->mPoints[0].mUV[1] = pUVs[pFaces[idx][0]][1];
      pFace->mPoints[0].Normal[0] = pNormals[idx][0];
      pFace->mPoints[0].Normal[1] = pNormals[idx][1];
      pFace->mPoints[0].Normal[2] = pNormals[idx][2];
      idxF++;
      pFace->mPoints[1].Index = pFaces[idx][1];
      pFace->mPoints[1].mUV[0] = pUVs[pFaces[idx][1]][0];
      pFace->mPoints[1].mUV[1] = pUVs[pFaces[idx][1]][1];
      pFace->mPoints[1].Normal[0] = pNormals[idx][0];
      pFace->mPoints[1].Normal[1] = pNormals[idx][1];
      pFace->mPoints[1].Normal[2] = pNormals[idx][2];
      idxF++;
      pFace->mPoints[2].Index = pFaces[idx][2];
      pFace->mPoints[2].mUV[0] = pUVs[pFaces[idx][2]][0];
      pFace->mPoints[2].mUV[1] = pUVs[pFaces[idx][2]][1];
      pFace->mPoints[2].Normal[0] = pNormals[idx][0];
      pFace->mPoints[2].Normal[1] = pNormals[idx][1];
      pFace->mPoints[2].Normal[2] = pNormals[idx][2];
      idxF++;
      mpFaces[idx] = pFace;
      mpFaces[idx]->Mat = pMats[idx];
   }
}

void SimpleMeshObject::AddMesh( int VertexCount,  float (* pVertexes)[3], int FaceCount, SimpleFace** pTrigSource )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;
   mUVCount = FaceCount;

   mpVertices = new float[mVertices][3];
   mpFaces = new SimpleFace*[FaceCount];

   for( int i = 0; i < mVertices; ++i)
   {
      //lib3ds_vector_copy(p, pMesh->vertices[i]);
      mpVertices[i][0] = pVertexes[i][0]*mfScale;
      mpVertices[i][1] = pVertexes[i][1]*mfScale;
      mpVertices[i][2] = pVertexes[i][2]*mfScale;
   }
   for( int idx = 0; idx < FaceCount; ++idx )
   {
      SimpleFace* pFace = new SimpleFace();
      SimpleFace* pSource = pTrigSource[idx];
      pFace->mPoints[0].Index = pSource->mPoints[0].Index;
      pFace->mPoints[0].mUV[0] = pSource->mPoints[0].mUV[0];
      pFace->mPoints[0].mUV[1] = pSource->mPoints[0].mUV[1];
      pFace->mPoints[0].Normal[0] = pSource->mPoints[0].Normal[0];
      pFace->mPoints[0].Normal[1] = pSource->mPoints[0].Normal[1];
      pFace->mPoints[0].Normal[2] = pSource->mPoints[0].Normal[2];

      pFace->mPoints[1].Index = pSource->mPoints[1].Index;
      pFace->mPoints[1].mUV[0] = pSource->mPoints[1].mUV[0];
      pFace->mPoints[1].mUV[1] = pSource->mPoints[1].mUV[1];
      pFace->mPoints[1].Normal[0] = pSource->mPoints[1].Normal[0];
      pFace->mPoints[1].Normal[1] = pSource->mPoints[1].Normal[1];
      pFace->mPoints[1].Normal[2] = pSource->mPoints[1].Normal[2];

      pFace->mPoints[2].Index = pSource->mPoints[2].Index;
      pFace->mPoints[2].mUV[0] = pSource->mPoints[2].mUV[0];
      pFace->mPoints[2].mUV[1] = pSource->mPoints[2].mUV[1];
      pFace->mPoints[2].Normal[0] = pSource->mPoints[2].Normal[0];
      pFace->mPoints[2].Normal[1] = pSource->mPoints[2].Normal[1];
      pFace->mPoints[2].Normal[2] = pSource->mPoints[2].Normal[2];

   }
}
