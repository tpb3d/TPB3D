//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  QuadMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "Texture.h"
#include "ObjectBase.h"

class Material;

struct QuadPoint
{
   unsigned short Index;
   short Other;
   float mUV[2];
};

struct QuadFace
{
   struct QuadPoint mPoints[4];
};

struct QuadVertex
{
   unsigned char Color[4];
   float Vertices[3];
   float Normal[3];
   void  SetNormal( float v1[3], float v2[3] );
};

class QuadMeshObject : public ObjectBase
{
   Gfx::Texture* mpTexture;
   Material* mpMaterial;
   unsigned short mVertices;
   unsigned short mIndexes;
   unsigned short mFaces;
   unsigned short mUVCount;
   QuadVertex* mpVertices;
   QuadFace* mpFaces;
   QuadFace* mpDetailFaces;
   
   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float mAngle;

public:
   float mfScale;

public:
	QuadMeshObject( int id );
	virtual ~QuadMeshObject();
   virtual ObjectBase* Clone( );

   void Normal(QuadFace& face);

	void Draw();
   void DrawSelectionTarget();

   void AddMatrix( float Mat16[4][4] );
   void AddMaterials( int iMats, Material* pMats );
   void AddStripFace( int Face, const QuadFace* pTrigrSource );
   void AddStripFaces( int FaceCount, const QuadFace pTrigrSource[] );
   void SetTexture ( Gfx::Texture* pTex) { mpTexture = pTex; }

   void AddMesh( int VertexCount, float (* pVertexes)[3], float(* pNormals)[3], int UVCount, float(* pUVs)[2],
                 int FaceCount, unsigned short(* pFaces)[3] );//, int TFaceCount, unsigned short* pTFaces );
   void AddMesh( int mVertices,  QuadVertex* pVerts, int mFaces, QuadFace* pTrigSource );
   void AddMesh( int mVertices,  QuadVertex* pVerts, int mFaces, QuadFace* pTrigSource, int tag );
   void CalcNormans();
   
};
