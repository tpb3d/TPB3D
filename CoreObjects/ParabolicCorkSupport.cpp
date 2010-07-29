//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  classic Parabolic Support class for Corkscrew track formations
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include "../Graphics/MeshNode.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/TexturedMesh.h"
#include "../Graphics/ObjectFactory.h"
#include "ParabolicCorkSupport.h"

ParabolicCorkSupport::ParabolicCorkSupport(Gfx::Texture* pTex, Vector3f& loc)
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
,  mLocation (loc)
{
   mpTexture = pTex;
   Clear();
}

ParabolicCorkSupport::~ParabolicCorkSupport()
{
   Clear();
}

void ParabolicCorkSupport::Clear()
{
   mFormat = CSF_Standard;
   mfHeight = 0;
   mfWidth = 0;
   mfYAngle = 0;   // An
   mFootingColor = 0xffafafaf;
   mStructureColor =  0xff7f7f7f;
}

void ParabolicCorkSupport::Create(int Count)
{
}

void ParabolicCorkSupport::SetupGuide(Guide& guide)
{
}

void ParabolicCorkSupport::Preset( CorkSupportFormat format, float mfYAngle, float mfHeight, float mfWidth)
{
}

void ParabolicCorkSupport::AddSection( ObjectBase* pGLBase )
{
}

void ParabolicCorkSupport::Draw()
{
   ObjectNode::Draw();
}

const char codes[] = "SM";
void ParabolicCorkSupport::Load(SerializerBase& ser)
{
}

void ParabolicCorkSupport::Save(SerializerBase& ser)
{
   ser.Add("Type", "ParabolicCorkSupport");
   ser.Add("ID", mID);
   ser.Add("Format", codes[mFormat]);
   ser.Add("YAngle", mAngle);
   ser.Add("Height", mfHeight);
   ser.Add("Width", mfWidth);
}

void ParabolicCorkSupport::Render (Vector3f& RollCenter, float HighPoint)
{
   float fP = HighPoint+1.5;
   float fP2 = HighPoint;
   float fY1 = fP - RollCenter.y;
   float fSX = sqrt(4 * fP * fY1)*2;
   float fSX2 = sqrt(4 * fP2 * fY1)*2;
   int secs = int(fSX) +1; // only half the arch
   float fStep = (fSX*2)/secs;
   float fStep2 =  (fSX2*2)/secs;
   float fAngle = -90;
   float fAngleSec = 180.0f / secs;

   TexturedMesh *pMeshA = new TexturedMesh( secs+1, 6, mpTexture, mStructureColor, 11 );
   TexturedMesh *pMeshB = new TexturedMesh( secs+1, 6, mpTexture, mStructureColor, 12 );
   TexturedMesh *pMeshC = new TexturedMesh( secs+1, 6, mpTexture, mStructureColor, 13);
   AddMesh( pMeshA );
   AddMesh( pMeshB );
   AddMesh( pMeshC );

   // A series of rings start flat on the pad and span 180degs across the parabola to the other pad.
   // Mesh interconnects these rings to for a tube.
   // A slight distortion is formed but should barely be noticeable.
   Vector3f::VectorAngle3<float> trigRail (0, mAngle, 0);
   Vector3f::VectorAngle3<float> trigArch (0, 0,fAngle);
   float fx2 = -fSX2;
   for (float fx = -fSX; fx <= fSX; fx += fStep)   // make up sections of the parabolic arch (3 at a time).
   {
      //float fy = (1/4*(fx*fx)) - 3/2*fx + 1/4;
      float fy = (fx*fx) / (4*fP);
      float fy2 = (fx2*fx2) / (4*fP2);
      float fAnglePipe = 360.0/ (6-1);
      Vector3f Arch (fx,-fy,0);
      Vector3f Arch2 (fx2,-fy2-1, +1.5f);
      Vector3f Arch3 (fx2,-fy2-1, -1.5f);
      Arch.Rotate (trigRail);
      Arch2.Rotate (trigRail);
      Arch3.Rotate (trigRail);
      Arch+= RollCenter;
      Arch2+= RollCenter;
      Arch3+= RollCenter;

      Vector3f::VectorAngle3<float> trigRZ (0, fAnglePipe, 0);
      Vector3f Pipe (2.5f/12,0,0);
      for( int idx = 0; idx < 6; ++idx )
      {
         Vector3f pt( Pipe );    // copy our pipe point so we can move it
         pt.Rotate (trigArch);   // align the segment with the curve of the arch.
         Vector3f pt2(pt);
         Vector3f pt3(pt);
         pt += Arch;             // move it to the position in the arch in the world.
         pt2 += Arch2;
         pt3 += Arch3;
         pMeshA->AddPoint (pt);
         pMeshB->AddPoint (pt2);
         pMeshC->AddPoint (pt3);
         Pipe.Rotate (trigRZ);   // making the pipe points
      }
      fAngle += fAngleSec;
      fx2 += fStep2;
   }
}

