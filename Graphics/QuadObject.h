#pragma once
#include "Texture.h"
#include "ObjectBase.h"

class Material;

class QuadMeshObject : public ObjectBase
{
   Material* mpMaterial;
   unsigned short mVertices;
   unsigned short mIndexes;
   unsigned short mUVCount;
   Gfx::Texture* mpTexture;
   
   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float (*mpVertices)[3];
   //float (*mpNormals)[3];
   //float (*mpUVs)[2];
   //unsigned short (*mpIndexes)[3];
   float mAngle;

public:
   float mfScale;

public:
	QuadMeshObject( int id );
	virtual ~QuadMeshObject();
   virtual ObjectBase* Clone( );

	void Draw();
   void AddMatrix( float Mat16[4][4] );
   void AddMaterials( int iMats, Material* pMats );
   void AddMesh( int mVertices,  sf::Vector3f* ); // add uvs
};
