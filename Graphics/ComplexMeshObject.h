#pragma once
#include "Texture.h"
#include "ObjectNode.h"
#include "SimpleMeshObject.h"

struct ComplexFace
{
   struct ComplexPoint
   {
      float Normal[3];
      float mUV[2];
      short Index;
   } mPoints[3];
};

struct ComplexGroup
{
   unsigned short mFaces;
   short mMat;
   Gfx::Texture* mpTexture;
   ComplexFace** mpFaces;
   float mAngle;
   ComplexGroup()
   {
      mpFaces = 0;
   }
   ~ComplexGroup()
   {
      for( int idx = 0; idx < mFaces; ++idx )
      {
         ComplexFace* pFace = mpFaces[idx];
         delete pFace;
      }
      delete [] mpFaces;
   }
   void AddFaces( int Paircount, const ComplexFace pFaceSource[] );
   void AddFace( int Pair, const ComplexFace* pFaceSource );
   void AddFace( int Pair, unsigned short index0, float(& pNormals0)[3], float U0, float V0,
                           unsigned short index1, float(& pNormals1)[3], float U1, float V1,
                           unsigned short index2, float(& pNormals2)[3], float U2, float V2 );
};


class ComplexMeshObject : public ObjectNode
{
protected:
   Material** mpMaterial;
   unsigned short mVertices;
   unsigned short mGroupCount;
   unsigned short mMaterialCount;
   Gfx::Texture*  mpTexture;

   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float (*mpVertices)[3];
   float mAngle;
   ComplexGroup** mpGroups;
public:
   ComplexMeshObject( int meshcount, int id );
   virtual ~ComplexMeshObject(void);

   virtual ObjectNode* Clone( );
   static ComplexMeshObject* Create();

	void Draw();

   void AddMatrix( float Mat16[4][4] );
   void AddMaterials( int iMats, Material** pMats );

   void AddMesh( int VertexCount, float (* pVertexes)[3], int GroupCount );
   void AddMesh( int VertexCount, sf::Vector3f* pVertexes, int GroupCount );
   ComplexGroup* AddGroup( int Group, int Pairs, int Mat, Gfx::Texture* pTex );
};
