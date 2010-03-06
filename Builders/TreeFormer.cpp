//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Tree forming class
//
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
#include "../Graphics/StripMeshObject.h"
#include "../Graphics/ComplexMeshObject.h"
#include "../Graphics/LeavesObject.h"
#include "../Graphics/Tree.h"
#include "../Graphics/Material.h"

#include "TreeFormer.h"
#include "../Graphics/ObjectFactory.h"
#include "../Graphics/Image.h"
#include "../Graphics/Texture.h"

#include <lib3ds.h>
//#include <libpng12/pngconf.h>


TreeFormer::TreeFormer( sf::Vector3f& point, float fHeight )
:  mHeight( fHeight )
,  mPoint( point )
{
   mLeafCount = 0;
   mVertices = 0;
}

TreeFormer::~TreeFormer()
{
}

void TreeFormer::Generate( Tree* pTree, int style )
{
   Gfx::Texture* texs[2];
   //glGenTextures( 2, tex );
//   LoadTexture( "pineneedles2.png", tex[0] );
//   LoadTexture( "oakbark.png", tex[1] );
   Gfx::ImageManager* pMan = Gfx::ImageManager::GetInstance();
   texs[0] = pMan->GetTexture( "pineneedles2.png", 4);
   texs[1] = pMan->GetTexture( "oakbark.png", 3);

   Material* mat = new Material( 1,1,1.0,0.5f, 0.12f,0,1.0f );
   ObjectNode* pNode = 0;

   //BuildMonoTrunk( mPoint );
   BuildForkedTrunk( mPoint );
   StripMeshObject* pMesh = StripMeshObject::Create();
   //mTrunk.mGroupCount = 1;
   pMesh->AddMaterials( 1, &mat );
   pMesh->AddMesh( mTrunk.mVerticies, mTrunk.mVertexes, mTrunk.mGroupCount );
   for( int idx = 0; idx < mTrunk.mGroupCount; ++idx )
   {
      StripGroup* pMG = pMesh->AddStripGroup( idx, mTrunk.mGroups[idx].FaceCount, 0, texs[1] );
      pMG->AddStripPairs( mTrunk.mGroups[idx].FaceCount, mTrunk.mGroups[idx].mFaces );
   }
   pTree->AddNode( pMesh );
   pNode = pMesh;

   mat->SetTexture( texs[0] );
   float angle = 1;
   float fY = 30; //35
   float fZ = 0.1f;
   int idn = 25;
   for( int idx = 0; idx < 20; ++idx )
   {
      LeavesObject* pLeaves = new LeavesObject( idn++, 10, angle );

      sf::Vector3f pt1( 0, fY, fZ );
      pLeaves->AddMaterials( 1, mat );
      pLeaves->AddLeaf( pt1 );
      pt1.y = -0.15f;
      pt1.z = 0.15f;
      pLeaves->AddLeaf( pt1 );
      pt1.x = 1.0f;
      pLeaves->AddLeaf( pt1 );
      pt1.x = -2.75f;
      pLeaves->AddLeaf( pt1 );
      pt1.y = -0.25f;
      pt1.x = 1.5f;
      pLeaves->AddLeaf( pt1 );
      pt1.x = 1.0f;
      pLeaves->AddLeaf( pt1 );
      pt1.x = -3.5f;
      pLeaves->AddLeaf( pt1 );
      pt1.y = -0.275f;
      pt1.x = 2.65f;
      pLeaves->AddLeaf( pt1 );
      pt1.x = -1.20f;
      pLeaves->AddLeaf( pt1 );
      pt1.x = 2.50f;
      pLeaves->AddLeaf( pt1 );

      pNode->AddNode( pLeaves );
      angle += 135;
      fZ += 0.25;
      fY -= 1.1f;
   }
   delete mat;
}

void TreeFormer::BuildMonoTrunk( sf::Vector3f& point)
{
   sf::Vector3f ptS;
   TreeGuide guide;
   guide.iVerts = 10;
   guide.YStep = 3;
   guide.dTubeRadius = 1.2;
   BuildBase( guide );
   guide.dTubeRadius = 1.0;
   guide.iStartVert = 10;
   guide.point.y += 0.75;
   guide.iSections = 12;
   guide.dShrink = 0.9;
   BuildTrunk( guide );
}

void TreeFormer::BuildForkedTrunk( sf::Vector3f& point)
{
   sf::Vector3f ptS;
   TreeGuide guide;
   guide.iVerts = 9;
   guide.YStep = 3;
   guide.dTubeRadius = 1.3;
   guide.dAspect = 0.5;
   BuildBase( guide );

   guide.dTubeRadius = 1.0;
   guide.iStartVert = mTrunk.mVerticies;
   guide.point.y += 0.75;
   guide.YAngle = 0;
   guide.iSections = 4;
   guide.dShrink = 0.9;
   BuildTrunk( guide );
   TreeGuide guide2;
   guide.iVerts = 9;
   guide.YStep = 1;
   BuildFork( guide, guide2 );

   guide.YAngle = 90;
   guide.iVerts = 5;
   guide.dTubeRadius = 0.5;
   guide.iStartVert = mTrunk.mVerticies;
   guide.point.y += 0.75;
   guide.point.x += 0.45f;
   guide.iSections = 3;
   guide.dShrink = 0.6;
   BuildTrunk( guide );

   //guide.YStep = 3.75;
   //guide.YAngle = -5;
   //guide.XAngle = 5;
   //guide.iVerts = 1;
   //guide.dTubeRadius = 0.5;
   //guide.iStartVert = mTrunk.mVerticies;
   //guide.point.y += 0.95f;
   //guide.point.x += 1.15f;
   //guide.iSections = 4;
   //guide.dShrink = 0.5;
   //BuildTrunk( guide );
}

void TreeFormer::BuildBase( TreeGuide& guide )
{
   double radion = guide.YAngle;
   int VertIndex = mTrunk.mVerticies;
   double rx = 360.0 / guide.iVerts;
   double dRadiusX = guide.dTubeRadius * guide.dAspect;
   double dRadiusZ = guide.dTubeRadius * (1.0 - guide.dAspect);
   for( int idx = 0; idx < guide.iVerts; ++idx )
   {
      sf::Vector3f p2(guide.point);
      double dTheta = PI/180 * radion;
      radion += rx;
      p2.x += float( cos(dTheta)*( dRadiusX ));
      p2.z += float( sin(dTheta)*( dRadiusZ ));
      mTrunk.AddPoint( p2 );
   }
}

void TreeFormer::BuildTrunk( TreeGuide& guide )
{
   double radion = guide.YAngle;
   int VertIndex = guide.iStartVert;
   int vert = mTrunk.mVerticies-guide.iVerts;
   double rx = 360.0 / (guide.iVerts);
   int ics = (guide.iSections > 3) ? 3 : guide.iSections;
   float fVi = 1.0f / ics;
   float fV1 = 0;
   float fV2 = fVi;
   for( int rdx = 0; rdx < guide.iSections; ++rdx )
   {
      double radion = guide.YAngle;
      double dRadiusX = guide.dTubeRadius * guide.dAspect;
      double dRadiusZ = guide.dTubeRadius * (1.0 - guide.dAspect);
      for( int idx = 0; idx < guide.iVerts; ++idx )
      {
         sf::Vector3f p2(guide.point);
         double dTheta = PI/180 * radion;
         radion += rx;
         p2.x += float( cos(dTheta)*( dRadiusX ));
         p2.z += float( sin(dTheta)*( dRadiusZ ));
         mTrunk.AddPoint( p2 );
      }
      PGroup& group = mTrunk.mGroups[rdx];
      float fU = 0;
      for( int idx = 0; idx < guide.iVerts; ++idx )
      {
         sf::Vector3f np;
//this is a problem         np.Normal( mTrunk.mVertexes[vert], mTrunk.mVertexes[vert+1], mTrunk.mVertexes[VertIndex] );

         StripPair& face = group.mFaces[group.FaceCount++];
         face.mPoints[0].Index = vert++;
         face.mPoints[0].mUV[0] = fU;
         face.mPoints[0].mUV[1] = fV1;
         face.mPoints[0].Normal[0] = np.x;
         face.mPoints[0].Normal[1] = np.y;
         face.mPoints[0].Normal[2] = np.z;
         face.mPoints[1].Index = VertIndex++;
//problem         np.Normal( mTrunk.mVertexes[vert], mTrunk.mVertexes[vert+1], mTrunk.mVertexes[VertIndex] );
         face.mPoints[1].mUV[0] = fU;
         face.mPoints[1].mUV[1] = fV2;
         face.mPoints[1].Normal[0] = np.x;
         face.mPoints[1].Normal[1] = np.y;
         face.mPoints[1].Normal[2] = np.z;
         fU += 0.2f;
      }
      sf::Vector3f np;
//problem      np.Normal( mTrunk.mVertexes[vert], mTrunk.mVertexes[vert+1], mTrunk.mVertexes[VertIndex] );
      StripPair& face = group.mFaces[group.FaceCount++];
      face.mPoints[0].Index = vert-guide.iVerts;
      face.mPoints[0].mUV[0] = fU;
      face.mPoints[0].mUV[1] = fV1;
      face.mPoints[0].Normal[0] = np.x;
      face.mPoints[0].Normal[1] = np.y;
      face.mPoints[0].Normal[2] = np.z;
      face.mPoints[1].Index = VertIndex-guide.iVerts;
 // problem     np.Normal( mTrunk.mVertexes[vert], mTrunk.mVertexes[vert+1], mTrunk.mVertexes[VertIndex] );
      face.mPoints[1].mUV[0] = fU;
      face.mPoints[1].mUV[1] = fV2;
      face.mPoints[1].Normal[0] = np.x;
      face.mPoints[1].Normal[1] = np.y;
      face.mPoints[1].Normal[2] = np.z;

      guide.dTubeRadius *= guide.dShrink;
//      vert += guide.iVerts;
      guide.point.y += (float)guide.YStep;
      mTrunk.mGroupCount++;
      fV1 = fV2;
      fV2+= fVi;
   }
}

void TreeFormer::BuildReducer( TreeGuide& guide )
{
}

void TreeFormer::BuildFork( TreeGuide& guide, TreeGuide& branchGuide )
{

   // build the fork layer with two rings connected
   // 2-3-5-9-17

   //  5, 6, 7, 8, 9,
   //  0, 1, 2, 3, 4

   int HVert = mTrunk.mVerticies;
   int LVert = HVert - guide.iVerts+1;

   float fVi = 1.0f / guide.iVerts;
   float fV1 = 0;
   float fV2 = fVi;

   double rx = 360.0 / (guide.iVerts /2 + 1);
   sf::Vector3f p1(guide.point);
   sf::Vector3f p2(guide.point);
   double dForkRadiusX = guide.dTubeRadius * guide.dAspect;
   double dForkRadiusZ = guide.dTubeRadius * (1.0 - guide.dAspect);
   sf::Vector3f pv( float(cos(PI/180 * guide.YAngle+90) * (dForkRadiusX*0.75)), 0,
               float(sin(PI/180 * guide.YAngle+90) * (dForkRadiusZ*0.75)) );


   double radion = guide.YAngle;
   int VertIndex = guide.iStartVert;
   int vert = mTrunk.mVerticies - guide.iVerts;

   double dRadiusX = guide.dTubeRadius * guide.dAspect;
   double dRadiusZ = guide.dTubeRadius * (1.0 - guide.dAspect);

// the fork
   p1 += pv;
   p2 -= pv;
   radion = guide.YAngle + 5;
   for( int idx = 0; idx < guide.iVerts/2+1; ++idx )
   {
      sf::Vector3f p3(p1);
      double dTheta = PI/180* radion;
      radion += rx;
      p3.x += float( cos(dTheta) * dRadiusX );
      p3.z += float( sin(dTheta) * dRadiusZ );
      mTrunk.AddPoint( p3 );
   }
   radion = guide.YAngle+30;
   for( int idx = 0; idx < guide.iVerts/2; ++idx )
   {
      sf::Vector3f p3(p2);
      double dTheta = PI/180 * (radion+180);
      radion += rx;
      p3.x += float( cos(dTheta) * dRadiusX );
      p3.z += float( sin(dTheta) * dRadiusZ );
      mTrunk.AddPoint( p3 );
   }

   PGroup& group = mTrunk.mGroups[mTrunk.mGroupCount++];
   float fU = 0;
   for( int idx = 0; idx < guide.iVerts; ++idx )
   {
      sf::Vector3f np;
//problem      np.Normal( mTrunk.mVertexes[LVert], mTrunk.mVertexes[LVert+1], mTrunk.mVertexes[HVert] );

      StripPair& face = group.mFaces[group.FaceCount++];
      face.mPoints[0].Index = LVert++;
      face.mPoints[0].mUV[0] = fU;
      face.mPoints[0].mUV[1] = fV1;
      face.mPoints[0].Normal[0] = np.x;
      face.mPoints[0].Normal[1] = np.y;
      face.mPoints[0].Normal[2] = np.z;
      face.mPoints[1].Index = HVert++;
//problem      np.Normal( mTrunk.mVertexes[LVert], mTrunk.mVertexes[HVert], mTrunk.mVertexes[HVert] );
      face.mPoints[1].mUV[0] = fU;
      face.mPoints[1].mUV[1] = fV2;
      face.mPoints[1].Normal[0] = np.x;
      face.mPoints[1].Normal[1] = np.y;
      face.mPoints[1].Normal[2] = np.z;
      fU += 0.2f;
   }
   sf::Vector3f np;
//problem   np.Normal( mTrunk.mVertexes[LVert], mTrunk.mVertexes[LVert+1], mTrunk.mVertexes[HVert] );
   HVert -= 4;
   LVert -= 4;

   StripPair& face = group.mFaces[group.FaceCount++];
   face.mPoints[0].Index = LVert;
   face.mPoints[0].mUV[0] = fU;
   face.mPoints[0].mUV[1] = fV1;
   face.mPoints[0].Normal[0] = np.x;
   face.mPoints[0].Normal[1] = np.y;
   face.mPoints[0].Normal[2] = np.z;
   face.mPoints[1].Index = HVert;
//problem   np.Normal( mTrunk.mVertexes[LVert], mTrunk.mVertexes[HVert], mTrunk.mVertexes[HVert] );
   face.mPoints[1].mUV[0] = fU;
   face.mPoints[1].mUV[1] = fV2;
   face.mPoints[1].Normal[0] = np.x;
   face.mPoints[1].Normal[1] = np.y;
   face.mPoints[1].Normal[2] = np.z;
//problem   np.Normal( mTrunk.mVertexes[LVert], mTrunk.mVertexes[LVert+1], mTrunk.mVertexes[HVert] );
   HVert -= 4;
   LVert -= 4;

   //StripPair& face2 = group.mFaces[group.FaceCount++];
   //face2.mPoints[0].Index = LVert;
   //face2.mPoints[0].mUV[0] = fU;
   //face2.mPoints[0].mUV[1] = fV1;
   //face2.mPoints[0].Normal[0] = np.x;
   //face2.mPoints[0].Normal[1] = np.y;
   //face2.mPoints[0].Normal[2] = np.z;
   //face2.mPoints[1].Index = HVert;
   //np.Normal( mTrunk.mVertexes[LVert], mTrunk.mVertexes[HVert], mTrunk.mVertexes[HVert] );
   //face2.mPoints[1].mUV[0] = fU;
   //face2.mPoints[1].mUV[1] = fV2;
   //face2.mPoints[1].Normal[0] = np.x;
   //face2.mPoints[1].Normal[1] = np.y;
   //face2.mPoints[1].Normal[2] = np.z;

   guide.iStartVert = mTrunk.mVerticies;
}

/*
void TreeFormer::BuildBranch( Trunk& pB, CVPoint& p1, TreeData* td )
{
   CGLLeaf* pLeaf = new CGLLeaf( T_MagnoliaGrandLeaf,
                                td.leafStyle,
                                td.leafStyle +2 );
   CGLTexturedMesh* pBranch = new CGLTexturedMesh(  2,5, T_OakBark, RGB(0x90, 0x90, 0x80)  );
   mpLeaves[mLeafCount] = pLeaf;
   mpBranches[mLeafCount++] = pBranch;
   double dTheta = mPI/180*td.radion;
   double dTheta90 = mPI/180*(td.radion+90);

   float fx = float( cos(dTheta90)*(td.length+1)*0.625 );
   float fz = float( sin(dTheta90)*(td.length+1)*0.625 );
   float dxt = float( p1.x + cos(dTheta)*td.length * 0.45 );
   float dzt = float( p1.z + sin(dTheta)*td.length * 0.45 );
   float dxb = float( p1.x + cos(dTheta)*td.length * 1.65 );
   float dzb = float( p1.z + sin(dTheta)*td.length * 1.65 );
   float fy = float( fabs(fx)+fabs(fz)/3.75 );
   float dx = float( p1.x + cos(dTheta)*td.length );
   float dy = float(p1.y + (td.y + mHeight*0.35)); // Branch tip height
   float dz = float( p1.z + sin(dTheta)*td.length );
   CVPoint p2(p1);
   p2.y += td.y * 0.75f; // branch base height
   p2.x -=0.13f;

   pBranch->AddPoint( p2 );
   pBranch->AddPoint( CVPoint(dx,dy,dz ) );
   p2.x +=0.1f;
   pBranch->AddPoint( p2 );
   pBranch->AddPoint( CVPoint(dx,dy,dz ) );
   p2.x +=0.1f;
   pBranch->AddPoint( p2 );
   pBranch->AddPoint( CVPoint(dx+0.1f,dy,dz ) );
   p2.z -=0.1f;
   pBranch->AddPoint( p2 );
   pBranch->AddPoint( CVPoint(dx,dy,dz+0.1f ) );
   p2.z -=0.1f;
   pBranch->AddPoint( p2 );
   pBranch->AddPoint( CVPoint(dx,dy,dz ) );
   p2.z +=0.1f;
//   pLeaf->SetQuadrant2( td.leafStyle );
   pLeaf->AddPoint( dxt, dy+fy, dzt );
   pLeaf->AddPoint( dx-fx,dy-fy,dz-fz );
   pLeaf->AddPoint( dx+fx,dy-fy,dz+fz );
}

*/

