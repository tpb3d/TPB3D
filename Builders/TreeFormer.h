//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Tree forming class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
class Tree;
#include "../Graphics/SimpleMeshObject.h"

struct TreeGuide
{
   int iSections;
   int iVerts;
   int iStartVert;
   int YAngle;
   int XAngle;
   sf::Vector3f point;
   double dTubeRadius;
   double dAspect;
   double dShrink; // makes the taper
   double YStep;
   TreeGuide()
   {
      iSections = 1;
      point = sf::Vector3f( 0,0,0 );
      dTubeRadius = 4;
      dAspect = 0.05;
      iVerts = 5;
      iStartVert = 0;
      YAngle = 0;
      XAngle = 0;
      dShrink = 0.9;
      YStep = 1.0;
   }
};


struct metaTrunk
{
   char  Forks; // branches connecting to this if juncton
   char  Index; // to connector node
   short Count;
   short Verts;
   short XAngle;
   short YAngle;
   short ZAngle;
   float Offsetx;
   float Offsetz;
   float RadiusX;
   float RadiusZ;
   float Elevation;
};

struct Leaf
{
   float pVertexes[4][3];
};

// store all the trunk vertex and point data here

struct Face
{
   float Index[2];
   struct UV
   {
      float u;
      float v;
   } UV[2];
};
struct PGroup
{
   int FaceCount;
   StripPair mFaces[20];
//   Face Faces[256];
   PGroup( )
   { FaceCount = 0; };
};

struct Trunk
{
//   int   mFaceCount;
   int   mGroupCount;
   int   mVerticies;
   Vector3f mVertexes[256];
   PGroup mGroups[32];
   Trunk()
   {
      //mFaceCount = 0;
      mGroupCount = 0;
      mVerticies = 0;
   }
   void AddPoint( const sf::Vector3f& pt )
   {
      mVertexes[mVerticies++] = pt;
   }
};

class TreeFormer
{

protected:
   int      mVertices;
   int      mLeafCount;
   float    mHeight;

   Trunk    mTrunk;
//   Trunk    mBranches[16];
   sf::Vector3f mPoint;

   Leaf mLeaves[3*28];
//   void BuildBranch( Trunk& pB, CVPoint& p1, metaTrunk* td, int vert );
//   void BuildBranch( int no, CVPoint& p1, TreeData& td );
//   void BuildTrunk( CVPoint& p1, metaTrunk* mt, int vert );
   void BuildForkedTrunk( sf::Vector3f& point);
   void BuildMonoTrunk( sf::Vector3f& point);

   void BuildBase( TreeGuide& guide );
   void BuildFork( TreeGuide& guide, TreeGuide& branchGuide );
   void BuildReducer( TreeGuide& guide );
   void BuildTrunk( TreeGuide& guide );
   int mBranchCount;

public:
	TreeFormer( sf::Vector3f& point, float Height );
	virtual ~TreeFormer();

   void SetHeight( float newHgt ) { mHeight = newHgt; };
   void Generate( Tree* tree, int style );
};
