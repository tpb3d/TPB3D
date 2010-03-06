#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "LeavesObject.h"
#include "Material.h"
#include "ObjectFactory.h"

LeavesObject::LeavesObject( int id, int LeafCount, float angle )
:  ObjectNode( LeafCount, id ) // just the mount point
,  mAngle( angle )
{
   mLeaves = LeafCount;
   mpMaterial = 0;
   memset( mMatrix, 0, 4 * 4 * sizeof(float) );        /**< Transformation matrix for mesh data */
   memset( mRotation, 0, 3* sizeof(float) );
   mVertices[0][0] = -1;
   mVertices[0][1] = -1;
   mVertices[0][2] = 0;
   mVertices[1][0] = -1;
   mVertices[1][1] = 1;
   mVertices[1][2] = 0;
   mVertices[2][0] = 1;
   mVertices[2][1] = 1;
   mVertices[2][2] = 0;
   mVertices[3][0] = 1;
   mVertices[3][1] = -1;
   mVertices[3][2] = 0;
//   mfScale = 1.0;
}

LeavesObject::~LeavesObject(void)
{
   if( mpMaterial )
      delete mpMaterial;
}

void LeavesObject::Draw()
{

   glEnable( GL_TEXTURE_2D );
   mpTexture->Bind( );

   glEnable( GL_BLEND );
   glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
//	   glRotatef(mpAngles[0],1.0f,0.0f,0.0f);
   glRotatef(mAngle,0.0f,1.0f,0.0f);
//	   glRotatef(mpAngles[2],0.0f,0.0f,1.0f);
   for( int idx = 0; idx < mLeaves; ++idx )
   {
	   glTranslatef( mpPoints[idx].x, mpPoints[idx].y, mpPoints[idx].z );

      glBegin(GL_QUADS); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
           // Coordinates of the first vertex
         glTexCoord2f( 0,0 );
   //      glNormal3fv( mpNormals[mpIndexes[idx][0]] );
         glVertex3fv( &mVertices[0][0] ); //Vertex definition

           // Coordinates of the second vertex
         glTexCoord2f( 0,1 );
   //      glNormal3fv( mpNormals[mpIndexes[idx][1]] );
         glVertex3fv( &mVertices[1][0] ); //Vertex definition

           // Coordinates of the third vertex
         glTexCoord2f( 1,1 );
   //      glNormal3fv( mpNormals[mpIndexes[idx][2]] );
         glVertex3fv( &mVertices[2][0] ); //Vertex definition

         glTexCoord2f( 1,0 );
   //      glNormal3fv( mpNormals[mpIndexes[idx][2]] );
         glVertex3fv( &mVertices[3][0] ); //Vertex definition

      glEnd( );
   }
   glDisable( GL_BLEND );
   glDisable( GL_TEXTURE_2D );

}

void LeavesObject::AddMaterials( int iMats, Material* pMats )
{
   mpMaterial = new Material(*pMats);
   mpTexture = mpMaterial->GetTexture( );
}


void LeavesObject::AddMatrix( float Mat16[4][4] )
{
   memcpy( mMatrix, Mat16, sizeof( mMatrix ) );
}

void LeavesObject::AddLeaf( sf::Vector3f& point )
{
   if( mPointCount < mMaxPointCount )
   {
      AddPoint( point );
   }
}
