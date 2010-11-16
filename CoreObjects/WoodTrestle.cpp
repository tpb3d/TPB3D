//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Wood Support Trestle class
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
#include "WoodTrestle.h"

WoodTrestle::WoodTrestle(Gfx::Texture* pTex, Vector3f& loc)
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
,  mLocation (loc)
{
   mpTexture = pTex;
   mPartsCount = 0;
   mMaxParts = 0;
//   mpBaseParts = NULL;
   Clear();
}

WoodTrestle::~WoodTrestle(void)
{
   Clear();
}

void WoodTrestle::Clear()
{
   try
   {
//      for( int ix = 0; ix < mPartsCount; ++ix )
//      {
//         delete mpBaseParts[ix];
//      }
      mPartsCount = 0;
//      delete [] mpBaseParts;
//      mpBaseParts = NULL;
   }
   catch( ... )
   {
   }
   mFormat = TF_Standard;
   mfHeight = 0;
   mfWidth = 0;
   mfBentAngle = 0;
   mWoodColor = 0xff5e8fbf;
   mFootingColor = 0xffafafaf;
   mHandrailColor = 0xff2f3fef; // red
}

void WoodTrestle::Create(int count)
{
//   mpBaseParts = new ObjectBase*[count];
}

void WoodTrestle::Preset ( TrestleFormat format, float fYAngle, float fHeight, float fWidth, float fBentAngle)
{
   mFormat = format;
   mAngle = fYAngle;
   mfHeight = fHeight;
   mfWidth = fWidth;
   mfBentAngle = fBentAngle;
}


void WoodTrestle::AddSection( ObjectBase* pGLBase )
{
//   mpBaseParts[mPartsCount++] = pGLBase;
}

void WoodTrestle::Draw()
{
//   for( int ix = 0; ix < mPartsCount; ++ix )
//   {
//      mpBaseParts[ix]->Draw();
//   }
   ObjectNode::Draw();
}

const char* WoodTrestle::codes = "SPZCH"; // Std, Pyramid, pyramid with Z, Catherdral or Hybrid steel.

void WoodTrestle::Load(SerializerBase& ser)
{
}

void WoodTrestle::Save(SerializerBase& ser)
{
   ser.Add("Type", "WoodTrestle");
   ser.Add("ID", mID);
   ser.Add("Format", codes[mFormat]);
   ser.Add("YAngle", mAngle);
   ser.Add("Height", mfHeight);
   ser.Add("Width", mfWidth);
   ser.Add("BentAngle", mfBentAngle);
}

void WoodTrestle::Render (Vector3f& HRLeft, Vector3f& HRRight)
{
   Vector3f::VectorAngle3<float> trigY (0, mAngle, 0);
   Vector3f Loc1 (mLocation);
   Vector3f Loc2 (mLocation);
   Vector3f Post1 (-3,0,0);
   Vector3f Post2 (3,0,0);
   Post1.Rotate (trigY);
   Post2.Rotate (trigY);
   Loc1 += Post1;
   Loc2 += Post2;

   int iABH = 0;
   float fPL = 0;
   float fPR = 0;
   float fBHL = 0;   // Height
   float fBHR = 0;
   float fBDL = 0;   // distance
   float fBDR = 0;
   float fBAngle = (float)sin( M_PI/180 * mfBentAngle ) * 1.65f;
   if ( mfBentAngle < -1 )
   {
      fPL = fBAngle;
      fPR = -fBAngle;
      fBHR = mfHeight - 1;  // set right brace to height of bent
   }
   else if ( mfBentAngle > 1)
   {
      fBHL = mfHeight - 1;  // setfBAnglesin(abs(mfBentAngle))*2;
      fPR = -fBAngle;
      fPL = fBAngle;
   }
   WoodPost (Loc1.x, Loc1.y, Loc1.z, 0.5f, mfHeight+fPL, mAngle);
   WoodPost (Loc2.x, Loc2.y, Loc2.z, 0.5f, mfHeight+fPR, mAngle);
   ConcreteFooting (Loc1.x, Loc1.y, Loc1.z, 1.05f, 4.0f);
   ConcreteFooting (Loc2.x, Loc2.y, Loc2.z, 1.05f, 4.0f);

   if (mfHeight > 30)
   {
      iABH = int((mfHeight * 0.75) / 6);
      float fbh = 6.0f * iABH;
      if (fbh > fBHL)
      {
         fBHL = fbh;
      }
      if (fbh > fBHR)
      {
         fBHR = fbh;
      }
   }

   if (fBHL > 0)  // left bracing
   {
      fBDL = fBHL * 0.25f;
      Vector3f Base1 (-fBDL-3,0,0);
      Base1.Rotate (trigY);
      Base1 += mLocation;
      WoodBracePost (Loc1.x, Loc1.y, Loc1.z, 0.5f, fBHL, -fBDL, mAngle);
      ConcreteFooting (Base1.x, Base1.y, Base1.z, 1.25f, 4.0f);
   }
   if (fBHR > 0) // right bracing
   {
      fBDR = fBHR * 0.25f;
      Vector3f Base2 (fBDR+3,0,0);
      Base2.Rotate (trigY);
      Base2 += mLocation;
      WoodBracePost (Loc2.x, Loc2.y, Loc2.z, 0.5f, fBHR, fBDR, mAngle);
      ConcreteFooting (Base2.x, Base2.y, Base2.z, 1.25f, 4.0f);
   }
   int iCount = int((mfHeight - 2) / mfWidth);
   if (mfHeight - 2 - (iCount * mfWidth) < 2)
   {
      iCount--;
   }
   float fy = mLocation.y + 2;
   float fIPBL = 0;
   float fIPBR = 0;
   int iBC = iABH; // only for braced sections
   if( iABH> 0 )
   {
      fIPBL = fBDL / iBC; // setup to use percentage of slope of the post for each beam extended.
      fIPBR = fBDR / iBC; // setup to use percentage of slope of the post for each beam extended.
   }
   for (int ic = 0; ic < iCount; ++ic)
   {
      float fBDL = 0;
      float fBDR = 0;
      if (iBC > 0) // only for braced sections
      {
         fBDL = fIPBL * iBC - 0.5f;
         fBDR = fIPBR * iBC - 0.5f;
         iBC--;
      }
      WoodBeam (mLocation.x, fy, mLocation.z, 0.75f, mfWidth, 0.25f, mAngle, fBDL, fBDR);
      WoodBrace  (mLocation.x, fy, mLocation.z, 0.75f, mfWidth, 0.25f, mfWidth-0.325f, mAngle);
      fy+=mfWidth;
   }
   if( fy < mfHeight - 3)
   {
      WoodBeam (mLocation.x, fy, mLocation.z, 0.75f, mfWidth, 0.25f, mAngle, 0, 0);
   }
   float fBY = mfHeight-1;
   if ( mfBentAngle < -25 || mfBentAngle > 25)
   {
      fBY = mfHeight - sin(fabs(mfBentAngle))*3;
      WoodBeam (mLocation.x, fy, mLocation.z, 1, mfWidth, 0.5f, mAngle, 0, 0);
   }
   WoodBrace  (mLocation.x, fy, mLocation.z, 0.75f, mfWidth, 0.25f, fBY-fy-0.325f, mAngle);
   WoodBent (mLocation.x, mLocation.y + mfHeight - 1, mLocation.z, 1, mfWidth, 0.375f, mAngle, mfBentAngle);
}

void WoodTrestle::WoodPost (float x, float y, float z, float w, float h, float angle)
{
   TexturedMesh *pMeshA = new TexturedMesh (5, 2, mpTexture, mWoodColor, 600 );
   this->AddMesh (pMeshA);

   Vector3f::VectorAngle3<float> trigY (0, angle, 0);
   Vector3f::VectorAngle3<float> trigSY (0, 90.0f, 0);

   Vector3f ptDims( w/2, 0, w/2);
   Vector3f ptL (x, y, z);
   Vector3f ptU (x, y+h+2, z);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptU);
   ptDims.Rotate(trigY);
   pt1 += ptDims;
   pt2 += ptDims;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptDims.Rotate(trigSY);
   pt1 = ptL;
   pt2 = ptU;
   pt1 += ptDims;
   pt2 += ptDims;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptDims.Rotate(trigSY);
   pt1 = ptL;
   pt2 = ptU;
   pt1 += ptDims;
   pt2 += ptDims;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptDims.Rotate(trigSY);
   pt1 = ptL;
   pt2 = ptU;
   pt1 += ptDims;
   pt2 += ptDims;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptDims.Rotate(trigSY);
   pt1 = ptL;
   pt2 = ptU;
   pt1 += ptDims;
   pt2 += ptDims;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);
}

void WoodTrestle::WoodBracePost(float x, float y, float z, float w, float l, float d, float angle)
{
   TexturedMesh *pMeshA = new TexturedMesh (5, 2, mpTexture, mWoodColor, 600 );
   this->AddMesh (pMeshA);

   Vector3f::VectorAngle3<float> trigY (0, angle, 0);
   Vector3f::VectorAngle3<float> trigSY (0, 90.0f, 0);

   Vector3f ptDims( w/2, 0, w/2);
   Vector3f ptBrace( d, 0, 0);
   ptDims.Rotate(trigY);
   ptBrace.Rotate(trigY);
   Vector3f ptL (x+ptBrace.x, y, z+ptBrace.z);
   Vector3f ptU (x, y+l, z);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptU);

   for (int ic = 0; ic < 5; ++ic)
   {
      pt1 = ptL;
      pt2 = ptU;
      pt1 += ptDims;
      pt2 += ptDims;
      pMeshA->AddPoint (pt1);
      pMeshA->AddPoint (pt2);
      ptDims.Rotate(trigSY);
   }
}

void WoodTrestle::WoodBeam (float x, float y, float z, float w, float l, float d, float angle, float leftExt, float rightExt)
{
   TexturedMesh *pMeshA = new TexturedMesh( 5, 2, mpTexture, mWoodColor, 600 );
   AddMesh (pMeshA);

   Vector3f::VectorAngle3<float> trigY (0, angle, 0);
   Vector3f::VectorAngle3<float> trigSY (0, 90.0f, 0);

   float hy = w/2;
   // building a 2x6 the hard way.
   Vector3f ptLoc (x,y,z);
   Vector3f ptL( -l/1.8f-leftExt, -hy, -0.5);
   Vector3f ptR( l/1.8f+rightExt, -hy, -0.5);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptR);
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.y += hy;
   ptR.y += hy;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.z += d;
   ptR.z += d;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.y -= hy;
   ptR.y -= hy;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.z -= d;
   ptR.z -= d;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);
}

void WoodTrestle::WoodBrace (float x, float y, float z, float w, float l, float d, float h, float angle)
{
   TexturedMesh *pMeshA = new TexturedMesh( 2, 5, mpTexture, mWoodColor, 600 );
   AddMesh (pMeshA);
   Vector3f::VectorAngle3<float> trigY (0, angle, 0);

   Vector3f ptLoc (x,y,z);
   Vector3f ptL( l/-1.8f, 0, -0.45f);
   Vector3f ptR( l/1.8f-w, h, -0.45f);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptR);

   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.z += d;
   ptR.z += d;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.x += w;
   ptR.x += w;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.z -= d;
   ptR.z -= d;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.x -= w;
   ptR.x -= w;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);
}

void WoodTrestle::WoodBent (float x, float y, float z, float w, float l, float d, float angle, float tilt)
{
   TexturedMesh *pMeshA = new TexturedMesh( 5, 2, mpTexture, mWoodColor, 600 );
   this->AddMesh (pMeshA);

   Vector3f::VectorAngle3<float> trigY (0, angle, 0);
   Vector3f::VectorAngle3<float> trigSY (0, 90.0f, 0);
   Vector3f::VectorAngle3<float> trigZ (0, 0, tilt);
   float fTilt = tilt;
   float fLeftFactor = (fTilt < 0 && fTilt > -50) ? sin (fTilt)/2 : 0;
   float fRightFactor = (fTilt > 0 && fTilt < 50) ? sin (fTilt)/2 : 0;
   float fXFactor = (fLeftFactor + fRightFactor)/2;

   float hy = w/2;
   float hz = d/2;

   // building a 2x12 the hard way.
   // Note will not work beyond a 45 deg tilt
   Vector3f ptLoc (x,y,z);
   Vector3f ptL( l/-1.75f + (fLeftFactor * l), -hy, -hz);
   Vector3f ptR( l/1.75f + (fRightFactor * l), -hy, -hz);
   //ptL.x -= fXFactor * l;
   //ptR.x -= fXFactor * l;
   ptL.y -= fabs (fXFactor * l);
   ptR.y -= fabs (fXFactor * l);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptR);
   pt1.Rotate (trigZ);
   pt2.Rotate (trigZ);
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.y += hy;
   ptR.y += hy;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigZ);
   pt2.Rotate (trigZ);
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   ptL.z += hz;
   ptR.z += hz;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigZ);
   pt2.Rotate (trigZ);
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   pt1.y -= hy;
   pt2.y -= hy;
   pt1 = ptL;
   pt2 = ptR;
   pt1.Rotate (trigZ);
   pt2.Rotate (trigZ);
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);

   pt1 = ptL;
   pt2 = ptR;
   pt1.z -= hz;
   pt2.z -= hz;
   pt1.Rotate (trigZ);
   pt2.Rotate (trigZ);
   pt1.Rotate (trigY);
   pt2.Rotate (trigY);
   pt1 += ptLoc;
   pt2 += ptLoc;
   pMeshA->AddPoint (pt1);
   pMeshA->AddPoint (pt2);
}

void WoodTrestle::ConcreteFooting (float x, float y, float z, float width, float depth)
{
   TexturedMesh *pMeshA = new TexturedMesh (9, 2, mpTexture, mFootingColor, 600 );
   this->AddMesh (pMeshA);

   Vector3f::VectorAngle3<float> trigSY (0, 360.0f/8, 0);

   Vector3f ptDims( width/2, 0, 0);
   Vector3f ptL (x, y, z);
   Vector3f ptU (x, y-depth, z);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptU);

   for (int ic = 0; ic < 9; ++ic)
   {
      pt1 = ptL;
      pt2 = ptU;
      pt1 += ptDims;
      pt2 += ptDims;
      pMeshA->AddPoint (pt1);
      pMeshA->AddPoint (pt2);
      ptDims.Rotate(trigSY);
   }
}

void WoodTrestle::WondHandrails (Vector3f& HRLeftA, Vector3f& HRRightA, Vector3f& HRLeftB, Vector3f& HRRightB)
{
   TexturedMesh *pMeshA = new TexturedMesh (5, 2, mpTexture, mHandrailColor, 600 );
   this->AddMesh (pMeshA);

   Vector3f::VectorAngle3<float> trigZS (0, 0, -15.0f); // Start
   Vector3f::VectorAngle3<float> trigZA (0, 0, 30.0f);
   Vector3f::VectorAngle3<float> trigZB (0, 0, 150.0f);

   Vector3f ptDims( 0.2f, 0, 0);
   ptDims.Rotate(trigZS);
   Vector3f ptL (ptDims);
   Vector3f ptU (ptDims);
   Vector3f pt1 (ptL);
   Vector3f pt2 (ptU);

   for (int ic = 0; ic < 5; ++ic)
   {
      pt1 = ptL;
      pt2 = ptU;
      pt1 += ptDims;
      pt2 += ptDims;
      pMeshA->AddPoint (pt1);
      pMeshA->AddPoint (pt2);
      if( ic ==0 || ic == 2 || ic == 4)
         ptDims.Rotate(trigZA);
      else
         ptDims.Rotate(trigZB);
   }
}

