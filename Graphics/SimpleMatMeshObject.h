//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  SimpleMatMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "Texture.h"
#include "ObjectBase.h"

class Material;
namespace Gfx
{
   class MaterialsList;
}

struct TrigPoint2 // similar to SimpleMeshObject
{
   float Normal[3];
   short Index;
};

struct SimpleFace2
{
   unsigned int Mat;
   struct TrigPoint2 mPoints[3];
};


class SimpleMatMeshObject : public ObjectBase
{
   Gfx::MaterialsList *mpMaterials;
   unsigned short mVertices;
   unsigned short mIndexes;
   unsigned short mFaces;
   
   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float (*mpVertices)[3];
   //float (*mpNormals)[3];
   //unsigned short (*mpIndexes)[3];
   float mAngle;
   SimpleFace2** mpFaces;

public:
   float mfScale;

public:
	SimpleMatMeshObject( int id );
	virtual ~SimpleMatMeshObject();
   virtual ObjectBase* Clone( );
   void SetScale (float frx) { mfScale = frx; }

	void Draw();
   void DrawSelectionTarget();

   void AddMatrix( float Mat16[4][4] );
   void SetMaterials( Gfx::MaterialsList* pMats );
   void AddStripFace( int Face, const SimpleFace2* pTrigrSource );
   void AddStripFaces( int FaceCount, const SimpleFace2 pTrigrSource[] );

   void AddMesh( int VertexCount, float (* pVertexes)[3], float(* pNormals)[3],
                 int FaceCount, unsigned short(* pFaces)[3], unsigned int(* pMats) );//, int TFaceCount, unsigned short* pTFaces );
   void AddMesh( int mVertices,  float (* pVertexes)[3], int mFaces, SimpleFace2** pTrigSource );
   void AddMesh( int mVertices,  sf::Vector3f*, int mFaces, SimpleFace2** pTrigSource );
};
