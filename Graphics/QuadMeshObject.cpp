//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  QuadMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "QuadMeshObject.h"
#include "Material.h"
#include "ObjectFactory.h"

QuadMeshObject::QuadMeshObject( int id )
:  ObjectBase( 1, id ) // just the mount point
{
   mpTexture = NULL;
   mpVertices = NULL;
   mpFaces = NULL;
   mpDetailFaces = NULL;
   mpName = NULL;
   mVertices = 0;
   mAngle = 0;
   mFaces = 0;
   memset( mMatrix, 0, 4 * 4 * sizeof(float) );        /**< Transformation matrix for mesh data */
   mfScale = 1.0;
}

QuadMeshObject::~QuadMeshObject(void)
{
   delete [] mpVertices;
   delete [] mpFaces;
   delete [] mpDetailFaces;

   if( mpName )
      delete mpName;
   if( mpMaterial )
      delete mpMaterial;
}

void QuadMeshObject::AddMaterials( int iMats, Material* pMats )
{
   mpMaterial = new Material(*pMats);
   mpTexture = mpMaterial->GetTexture( );
}

ObjectBase* QuadMeshObject::Clone( )
{
   int id = ObjectFactory::TakeANumber();
   QuadMeshObject* pNode = new QuadMeshObject( id );
   pNode->AddMaterials( 1, mpMaterial );
//   pNode->AddMesh( mVertices, mpVertices, mpNormals,
//                   mUVCount, mpUVs,
//                   mFaces, mpIndexes );
   pNode->AddMesh( mVertices, mpVertices, mFaces, mpFaces );


   return pNode;
}

void QuadMeshObject::Draw()
{
   if( mpMaterial )
   {
//      mpMaterial->GLSetMaterial();
      glShadeModel( GL_SMOOTH );
   }
//   else
   if( mpTexture != NULL )
   {
      glEnable( GL_TEXTURE_2D );
      mpTexture->Bind( );
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

//   glEnable (GL_COLOR_MATERIAL);
   glBegin(GL_QUADS); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)

   for( int idx = 0; idx < mFaces; ++idx )
   {
        // Coordinates of the first vertex
      QuadPoint& face = mpFaces[idx].mPoints[0];
      glTexCoord2fv( face.mUV );
      glColor4ubv (mpVertices[face.Index].Color);
//      glNormal3fv( mpVertices[face.Index].Normal );
      glVertex3fv( mpVertices[face.Index].Vertices ); //Vertex definition

        // Coordinates of the second vertex
      QuadPoint& face1 = mpFaces[idx].mPoints[1];
      glTexCoord2fv( face1.mUV );
      glColor4ubv (mpVertices[face1.Index].Color);
      glVertex3fv( mpVertices[face1.Index].Vertices ); //Vertex definition
//      glNormal3fv( mpFaces[idx].NormalB );

        // Coordinates of the third vertex
      //glNormal3fv( mpFaces[idx].NormalB );
      QuadPoint& face2 = mpFaces[idx].mPoints[2];
      glTexCoord2fv( face2.mUV );
//      glNormal3fv( mpVertices[face2.Index].Normal );
      glColor4ubv (mpVertices[face2.Index].Color);
      glVertex3fv( mpVertices[face2.Index].Vertices ); //Vertex definition

        // Coordinates of the third vertex
      //glNormal3fv( mpFaces[idx].NormalB );
      QuadPoint& face3 = mpFaces[idx].mPoints[3];
      glTexCoord2fv( face3.mUV );
      glColor4ubv (mpVertices[face3.Index].Color);
      glVertex3fv( mpVertices[face3.Index].Vertices ); //Vertex definition
   }
   glEnd( );
   glDisable( GL_TEXTURE_2D );
}

void QuadMeshObject::DrawSelectionTarget()
{
   glBegin(GL_QUADS); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)

   for( int idx = 0; idx < mFaces; ++idx )
   {
        // Coordinates of the first vertex
      QuadPoint& face = mpFaces[idx].mPoints[0];
      glVertex3fv( mpVertices[face.Index].Vertices ); //Vertex definition

        // Coordinates of the second vertex
      QuadPoint& face1 = mpFaces[idx].mPoints[1];
      glVertex3fv( mpVertices[face1.Index].Vertices ); //Vertex definition

        // Coordinates of the third vertex
      QuadPoint& face2 = mpFaces[idx].mPoints[2];
      glVertex3fv( mpVertices[face2.Index].Vertices ); //Vertex definition

        // Coordinates of the third vertex
      QuadPoint& face3 = mpFaces[idx].mPoints[3];
      glVertex3fv( mpVertices[face3.Index].Vertices ); //Vertex definition
   }
   glEnd( );
}

void QuadMeshObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}


void QuadMeshObject::AddMesh( int VertexCount, float(* pVertexes)[3], float(* pNormals)[3],
                       int UVCount, float(* pUVs)[2],
                        int FaceCount, unsigned short(* pFaces)[3] )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;
   mUVCount = UVCount;

   mpVertices = new QuadVertex[mVertices];
   mpFaces = new QuadFace[FaceCount];

   for( int i = 0; i < mVertices; ++i)
   {
      //lib3ds_vector_copy(p, pMesh->vertices[i]);
      mpVertices[i].Vertices[0] = pVertexes[i][0]*mfScale;
      mpVertices[i].Vertices[1] = pVertexes[i][1]*mfScale;
      mpVertices[i].Vertices[2] = pVertexes[i][2]*mfScale;
   }
   int idxF = 0;
   for( int idx = 0; idx < FaceCount; ++idx )
   {
      QuadFace* pFace = new QuadFace();
      pFace->mPoints[0].Index = pFaces[idx][0];
      pFace->mPoints[0].mUV[0] = pUVs[idxF][0];
      pFace->mPoints[0].mUV[1] = pUVs[idxF][1];
      idxF++;
      pFace->mPoints[1].Index = pFaces[idx][1];
      pFace->mPoints[1].mUV[0] = pUVs[idxF][0];
      pFace->mPoints[1].mUV[1] = pUVs[idxF][1];
      idxF++;
      pFace->mPoints[2].Index = pFaces[idx][1];
      pFace->mPoints[2].mUV[0] = pUVs[idxF][0];
      pFace->mPoints[2].mUV[1] = pUVs[idxF][1];
      idxF++;
      pFace->mPoints[3].Index = pFaces[idx][1];
      pFace->mPoints[3].mUV[0] = pUVs[idxF][0];
      pFace->mPoints[3].mUV[1] = pUVs[idxF][1];
      idxF++;
   }
}

void QuadMeshObject::AddMesh( int VertexCount,  QuadVertex* pVertexes, int FaceCount, QuadFace* pTrigSource )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;
   mUVCount = FaceCount;

   mpVertices = new QuadVertex[mVertices];
   mpFaces = new QuadFace[FaceCount];

   for( int i = 0; i < mVertices; ++i)
   {
      //lib3ds_vector_copy(p, pMesh->vertices[i]);
      memcpy (mpVertices[i].Color, pVertexes[i].Color, 4);
      mpVertices[i].Vertices[0] = pVertexes[i].Vertices[0]*mfScale;
      mpVertices[i].Vertices[1] = pVertexes[i].Vertices[1]*mfScale;
      mpVertices[i].Vertices[2] = pVertexes[i].Vertices[2]*mfScale;
   }

   for( int idx = 0; idx < FaceCount; ++idx )
   {
      QuadFace& Face = mpFaces[idx];
      QuadFace& Source = pTrigSource[idx];
      Face.mPoints[0].Index = Source.mPoints[0].Index;
      Face.mPoints[0].mUV[0] = Source.mPoints[0].mUV[0];
      Face.mPoints[0].mUV[1] = Source.mPoints[0].mUV[1];

      Face.mPoints[1].Index = Source.mPoints[1].Index;
      Face.mPoints[1].mUV[0] = Source.mPoints[1].mUV[0];
      Face.mPoints[1].mUV[1] = Source.mPoints[1].mUV[1];

      Face.mPoints[2].Index = Source.mPoints[2].Index;
      Face.mPoints[2].mUV[0] = Source.mPoints[2].mUV[0];
      Face.mPoints[2].mUV[1] = Source.mPoints[2].mUV[1];

      Face.mPoints[3].Index = Source.mPoints[3].Index;
      Face.mPoints[3].mUV[0] = Source.mPoints[3].mUV[0];
      Face.mPoints[3].mUV[1] = Source.mPoints[3].mUV[1];

   }
   for( int idx = 0; idx < FaceCount-1; ++idx )
   {
      QuadFace& Face = mpFaces[idx];
      QuadVertex& VA = mpVertices[Face.mPoints[0].Index];
      QuadVertex& VB = mpVertices[Face.mPoints[1].Index];
      QuadVertex& VC = mpVertices[Face.mPoints[2].Index];
      QuadVertex& VD = mpVertices[Face.mPoints[3].Index];
      VA.SetNormal( VB.Vertices, VC.Vertices );
      VC.SetNormal( VB.Vertices, VD.Vertices );
   }
}

void QuadMeshObject::AddMesh( int VertexCount, QuadVertex verts[], int FaceCount, QuadFace* pFaceSource, int tag )
{
   if( mpName )
   {
      delete mpName;
   }
   mVertices = VertexCount;
   mIndexes = FaceCount;
   mFaces = FaceCount;
   mUVCount = FaceCount;

   mpVertices = new QuadVertex[VertexCount];
   mpFaces = new QuadFace[FaceCount];

   for( int i = 0; i < mVertices; ++i)
   {
      memcpy (mpVertices[i].Color, verts[i].Color, 4);
      mpVertices[i].Vertices[0] = verts[i].Vertices[0] * mfScale;
      mpVertices[i].Vertices[1] = verts[i].Vertices[1] * mfScale;
      mpVertices[i].Vertices[2] = verts[i].Vertices[2] * mfScale;
   }
   for( int idx = 0; idx < FaceCount; ++idx )
   {
      QuadFace& Face = mpFaces[idx];
      QuadFace& FaceSource = pFaceSource[idx];
      Face.mPoints[0].Index = FaceSource.mPoints[0].Index;
      Face.mPoints[0].mUV[0] = FaceSource.mPoints[0].mUV[0];
      Face.mPoints[0].mUV[1] = FaceSource.mPoints[0].mUV[1];

      Face.mPoints[1].Index = FaceSource.mPoints[1].Index;
      Face.mPoints[1].mUV[0] = FaceSource.mPoints[1].mUV[0];
      Face.mPoints[1].mUV[1] = FaceSource.mPoints[1].mUV[1];

      Face.mPoints[2].Index = FaceSource.mPoints[2].Index;
      Face.mPoints[2].mUV[0] = FaceSource.mPoints[2].mUV[0];
      Face.mPoints[2].mUV[1] = FaceSource.mPoints[2].mUV[1];

      Face.mPoints[3].Index = FaceSource.mPoints[3].Index;
      Face.mPoints[3].mUV[0] = FaceSource.mPoints[3].mUV[0];
      Face.mPoints[3].mUV[1] = FaceSource.mPoints[3].mUV[1];
   }
   for( int idx = 0; idx < FaceCount-1; ++idx )
   {
      QuadFace& Face = mpFaces[idx];
      QuadVertex& VA = mpVertices[Face.mPoints[0].Index];
      QuadVertex& VB = mpVertices[Face.mPoints[1].Index];
      QuadVertex& VC = mpVertices[Face.mPoints[2].Index];
      QuadVertex& VD = mpVertices[Face.mPoints[3].Index];
      VA.SetNormal( VB.Vertices, VC.Vertices );
      VC.SetNormal( VB.Vertices, VD.Vertices );
   }
}

void QuadVertex::SetNormal( float v1[3], float v2[3] )
{
   float x= 1*v2[2] - v1[2]* 1;//v2[1];
   float y= v1[2]*v2[0] - v1[0]*v2[2];
   float z= v1[0]*1 - 1*v2[0];

   float len = (float)(1.0/sqrt( x*x + y*y + z*z ));
   Normal[0] = x * len;
   Normal[1] = y * len;
   Normal[2] = z * len;
}
