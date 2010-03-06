#pragma once
#include "ObjectNode.h"
class Material;

class LeavesObject : public ObjectNode
{
   Material* mpMaterial;
   unsigned short mLeaves;
   Gfx::Texture* mpTexture;

   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float  mVertices[4][3];
   float  mpNormals[4][3];
//   float (*mPoints)[3];
   float  mRotation[3];
   float  mAngle;

public:
   LeavesObject( int id, int LeafCount, float angle );
   virtual ~LeavesObject(void);

	void Draw();
   ObjectNode* Clone() { return new LeavesObject( 1, mLeaves, mAngle ); };
   void AddMatrix( float Mat16[4][4] );
   void AddMaterials( int iMats, Material* pMats );
   void AddLeaf( sf::Vector3f& point );
};
