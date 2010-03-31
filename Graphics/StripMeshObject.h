//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  StripMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Texture.h"
#include "ObjectNode.h"

class Material;

struct StripPair
{
   struct StripPoint
   {
      float Normal[3];
      float mUV[2];
      short Index;
   } mPoints[2];
};

struct StripGroup
{
   unsigned short mPairs;
   short mMat;
   Gfx::Texture* mpTexture;
   StripPair** mpPairs;
   float mAngle;
   ~StripGroup()
   {
      for( int idx = 0; idx < mPairs; ++idx )
      {
         StripPair* pPair = mpPairs[idx];
         delete pPair;
      }
      delete [] mpPairs;
   }
   void AddStripPairs( int Paircount, const StripPair pPairSource[] );
   void AddStripPair( int Pair, const StripPair* pPairSource );
   void AddStripPair( int Pair, unsigned short index0, float(& pNormals0)[3], float U0, float V0,
                               unsigned short index1, float(& pNormals1)[3], float U1, float V1 );
};

class StripMeshObject : public ObjectNode
{
   int MaterialCount;
   Material** mpMaterial;
   StripGroup** mpGroups;
   unsigned short mVertices;
   unsigned short mGroups;
   char*  mpName;
   float  mMatrix[4][4];        /**< Transformation matrix for mesh data */
   float (*mpVertices)[3];
public:
   StripMeshObject(int id );
   virtual ~StripMeshObject(void);
   virtual ObjectNode* Clone();
   static StripMeshObject* Create();

	void Draw();
   void DrawSelectionTarget();
   void AddMatrix( float Mat16[4][4] );
   void AddMaterials( int iMats, Material** pMats );
   void AddMesh( int VertexCount, float (* pVertexes)[3], int GroupCount );
   void AddMesh( int VertexCount, Vector3f* pVertexes, int GroupCount );
   StripGroup* AddStripGroup( int Group, int Pairs, int Mat, Gfx::Texture* pTex );
};
