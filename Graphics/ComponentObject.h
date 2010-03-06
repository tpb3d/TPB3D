#pragma once
#include "ObjectNode.h"

class Material;

struct MeshFace
{
   struct Triangle
   {
      float Normal[3];
      float mUV[2];
      short Index;
   } mTriangles[3];
};

struct MeshGroup
{
   unsigned short mFaces;
   short mMat;
   Gfx::Texture* mpTexture;
   MeshFace** mpFaces;
   float mAngle;
   ~MeshGroup()
   {
      for( int idx = 0; idx < mFaces; ++idx )
      {
         MeshFace* pFace = mpFaces[idx];
         delete pFace;
      }
      delete [] mpFaces;
   }
   void AddMeshFaces( int facecount, const MeshFace pFaceSource[] );
   void AddMeshFace( int face, const MeshFace* pFaceSource );
   void AddMeshFace( int face, unsigned short index0, float(& pNormals0)[3], float U0, float V0,
                               unsigned short index1, float(& pNormals1)[3], float U1, float V1,
                               unsigned short index2, float(& pNormals2)[3], float U2, float V2 );
};

class ComponentObject :
   public ObjectNode
{
//   GLuint mTextures[2];
   int MaterialCount;
   Material** mpMaterial;
   MeshGroup** mpGroups;
   unsigned short mVertices;
   unsigned short mGroups;
   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float (*mpVertices)[3];
public:
   ComponentObject( int id );
   virtual ~ComponentObject(void);
   virtual ObjectNode* Clone();

	void Draw();
   void AddMatrix( float Mat16[4][4] );
   void AddMaterials( int iMats, Material** pMats );
   void AddMesh( int VertexCount, float (* pVertexes)[3], int GroupCount );
   void AddMesh( int VertexCount, sf::Vector3f* pVertexes, int GroupCount );
   MeshGroup* AddMeshGroup( int Group, int Faces, int Mat, Gfx::Texture* pTex );
};
