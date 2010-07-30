//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track forming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>
#include "../CoreObjects/TrackBase.h"
#include "../CoreObjects/Track.h"
#include "../CoreObjects/TrackGuide.h"
#include "../CoreObjects/TrackSection.h"
#include "../CoreObjects/WoodTrestle.h"
#include "../CoreObjects/ParabolicCorkSupport.h"
#include "../Graphics/Image.h"
#include "../Graphics/MeshNode.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/TexturedMesh.h"
#include "../Graphics/ObjectFactory.h"
#include "TrackFormer.h"

#include "../CoreObjects/Park.h" // access to the park for the car path (will change)

TrackFormer::TrackFormer( Gfx::Texture* pTexture, Park& park)
:  mPark(park)
{
   mpTexture = pTexture;
}

TrackFormer::~TrackFormer(void)
{
}

Track* TrackFormer::CreateTrack()
{
   return new Track();
}

void TrackFormer::MakeSection( TrackGuide& guide, Track& Track )
{
   if (guide.GetRailShape() == 7 || guide.GetRailShape() == 8)
   {
      MakeWoodSection( guide, Track );
      return;
   }
   int id = 400;
   int iTubeSections = 6;
   int iRailSides = 6;
   float fGauge = (float)(guide.fTrackGauge/2);
   float fYOffset = 0.8f;

   if( guide.fTubeRadius > 1.99/12 )
   {
      iTubeSections = 9;
   }
   TrackSection* pTrackSection = new TrackSection();
   int iNeeded = 4+guide.GetSections()*2;
   pTrackSection->Create(iNeeded);
   Track.AddSection(pTrackSection);

   // Determine rails needed
   TexturedMesh *pMesh = NULL;
   if( guide.GetRailShape() == 3 )
   {
      pMesh = new TexturedMesh( guide.GetSections()+1, iTubeSections, mpTexture, 0xff009090, id++ );
      pTrackSection->AddSection( pMesh );
   }
   else if( guide.GetRailShape() > 2 )
   {
      pMesh = new TexturedMesh( guide.GetSections()+1, iTubeSections, mpTexture, 0xff009090, id++ );
      pTrackSection->AddSection( pMesh );
   }
   else
   {
      fYOffset = 0.2f;
   }
   TexturedMesh *pMeshA = new TexturedMesh( guide.GetSections()+1, iRailSides, mpTexture, 0xfc2d6fef, id++ );
   TexturedMesh *pMeshB = new TexturedMesh( guide.GetSections()+1, iRailSides, mpTexture, 0xfc2d6fef, id++ );
   pTrackSection->AddSection( pMeshA );
   pTrackSection->AddSection( pMeshB );
   // option for one or two more rails

   // Get fractional vector
   Vector3f TrackPoint( guide.point );
   Vector3f centerPT( 0, -guide.fRadius, 0 );
   Vector3f::VectorAngle3<float> trigXYZ ( guide.fTiltX, guide.fTiltY, guide.fTiltZ);
   Vector3f::VectorAngle3<float> trig (guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);

   float fWoodPos = guide.fCurPos;
   float fWoodRailAngle = guide.fCurRailAngle;
   if( guide.GetSections() > 14 )
   {
      int steps = int(guide.GetSections() / 12) + 1;
      guide.fNextMount = (float)(guide.GetSections() / steps + 1.9);
      guide.fStep = 2.0;
   }
   else
   {
      guide.fNextMount = (float)guide.GetSections()-1;
   }

   int iLast = guide.GetSections();
   int iCurSupp = guide.iSupportSection;
   for( int idxz = 0; idxz<= iLast; ++idxz )
   {
      TexturedStrip* pBar;
      pBar = CrossTie( TrackPoint, guide );
      pTrackSection->AddSection( pBar );

      Vector3f::VectorAngle3<float> trigRZ (0, 0, guide.fCurRailAngle);
      Vector3f::VectorAngle3<float> trigPXYZ (guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);
      double dRad = 0.0;
      if ( !(pMesh == NULL || guide.GetRailShape() == 7))
      {
         double dDeg = 360.0/ (iTubeSections-1);
         for( int idx = 0; idx < iTubeSections; ++idx )
         {
            float fTheta = (float)(M_PI/180 * dRad);
            Vector3f pt( cos(fTheta) * guide.fTubeRadius, sin(fTheta)* guide.fTubeRadius, 0 );
            pt.Rotate( trigRZ );
            pt.Transform (trigPXYZ, TrackPoint);
            pMesh->AddPoint (pt);
            dRad += dDeg;
         }
      }
      double dRDeg = 360.0/(iRailSides-1);
      dRad = 0.0;
      for( int idx = 0; idx < iRailSides; ++idx )
      {
         float fTheta = (float)(M_PI/180 * dRad);
         Vector3f ptA( cos(fTheta) * guide.fRailRadius-fGauge, sin(fTheta)* guide.fRailRadius + fYOffset, 0 );
         Vector3f ptB( cos(fTheta) * guide.fRailRadius+fGauge, sin(fTheta)* guide.fRailRadius + fYOffset, 0 );
         ptA.Rotate( trigRZ );
         ptA.Transform( trigPXYZ, TrackPoint ); // Transform, use matrix here
         ptB.Rotate( trigRZ );
         ptB.Transform( trigPXYZ, TrackPoint ); // Transform, use matrix here

         pMeshA->AddPoint( ptA );
         pMeshB->AddPoint( ptB );

         dRad += dRDeg;
      }
      if( idxz < iLast )
      {
         if( guide.fCurPos > guide.fNextMount ) // bSupports == true
         {
            Vector3f ptMount(TrackPoint);
            ptMount.y -= 0.75;
            if (guide.GetRailShape() != 7)
            {
               pTrackSection->AddSection(Support(ptMount, guide, (float)guide.fCurRailAngle, 10, 1 ));
            }
            guide.fCurPos = 0;
         }
         sf::Vector3f pt3f( TrackPoint.x,TrackPoint.y,TrackPoint.z);
         mPark.AddTestPoint( pt3f, sf::Vector3f(-guide.fCurAngleX, guide.fCurAngleY, -guide.fCurRailAngle) ); // path

         guide.fCurAngleX += guide.fTiltX;
         guide.fCurAngleY += guide.fTiltY;
         guide.fCurAngleZ += guide.fTiltZ;
         guide.fCurRailAngle += guide.fRailTiltZ;
         Vector3f::VectorAngle3<float> trigFV( guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);
         Vector3f pFV(guide.ForwardVector);
         pFV.Rotate(trigFV);
         guide.fCurPos += guide.fStep;
         TrackPoint += pFV; // rotate to the current vector
      }
   }

   guide.iSupportSection = iCurSupp;
   guide.point = TrackPoint;
}

void TrackFormer::MakeWoodSection( TrackGuide& guide, Track& Track )
{
   int id = 400;
   int iTubeSections = 6;
   int iRailSides = 6;
   float fGauge = (float)(guide.fTrackGauge/2);
   float fYOffset = 0.8f;

   if( guide.fTubeRadius > 1.99/12 )
   {
      iTubeSections = 9;
   }
   TrackSection* pTrackSection = new TrackSection();
   int iNeeded = 4+guide.GetSections()*2;
   iNeeded += guide.GetSections() * 3;  // for the extra ties
   pTrackSection->Create(iNeeded);
   Track.AddSection(pTrackSection);

   // Determine rails needed
   TexturedMesh *pMesh = NULL;
   iRailSides = 5;
   fYOffset = 0.0f;

   TexturedMesh *pMeshA = new TexturedMesh( guide.GetSections()+1, iRailSides, mpTexture, 0xfc2d6fef, id++ );
   TexturedMesh *pMeshB = new TexturedMesh( guide.GetSections()+1, iRailSides, mpTexture, 0xfc2d6fef, id++ );
   pTrackSection->AddSection( pMeshA );
   pTrackSection->AddSection( pMeshB );

   TexturedStrip* pLeftCatwalk = new TexturedStrip( guide.GetSections()+1, mpTexture, 0xff3faf3f );
   TexturedStrip* pRightCatwalk = new TexturedStrip( guide.GetSections()+1, mpTexture, 0xff3faf3f );
   pTrackSection->AddSection( pLeftCatwalk );
   pTrackSection->AddSection( pRightCatwalk );


   // Get fractional vector
   Vector3f SupportPoint( guide.point );
   Vector3f centerPT( 0, -guide.fRadius, 0 );
   Vector3f::VectorAngle3<float> trigXYZ ( guide.fTiltX, guide.fTiltY, guide.fTiltZ);
   Vector3f::VectorAngle3<float> trig (guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);

   float fWoodPos = guide.fCurPos;
   float fWoodRailAngle = guide.fCurRailAngle;
   if( guide.GetSections() > 14 )
   {
      int steps = int(guide.GetSections() / 12) + 1;
      guide.fNextMount = (float)(guide.GetSections() / steps + 1.9);
      guide.fStep = 2.0;
   }
   else
   {
      guide.fNextMount = (float)guide.GetSections()-1;
   }

   int iLast = guide.GetSections();
   int iCurSupp = guide.iSupportSection;
   for( int idxz = 0; idxz<= iLast; ++idxz )
   {
      Vector3f TrackPoint( SupportPoint );
      TexturedStrip* pBar;
      Vector3f::VectorAngle3<float> trigRZ (0, 0, guide.fCurRailAngle);
      Vector3f::VectorAngle3<float> trigPXYZ (guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);
      float fBankShift = (float)sin( M_PI/180 * guide.fCurRailAngle ) * 1.45f;
      Vector3f MovePoint( -fBankShift, 0, 0 );
      MovePoint.Rotate( trigPXYZ );
      TrackPoint += MovePoint;

      float fTie = (guide.GetRailShape() == 7) ? 3.0f/12 : 6.0f/12;  // woodie or train
      pBar = WoodCrossTie( TrackPoint, trigPXYZ, trigRZ, guide.fTrackGauge, fTie );
      pTrackSection->AddSection( pBar );

      Vector3f ptCreep (guide.ForwardVector); // We are going to drop a tie between the normal set
      Vector3f::VectorAngle3<float> trigZ2 (0,0, guide.fCurRailAngle+guide.fRailTiltZ/2);
      Vector3f::VectorAngle3<float> trigXYZ2 (guide.fCurAngleX+guide.fTiltX/2, guide.fCurAngleY+guide.fTiltY/2, guide.fCurAngleZ+guide.fTiltZ/2);
      ptCreep.x /= 2;   // split the diff
      ptCreep.y /= 2;
      ptCreep.z /= 2;
      ptCreep.Rotate (trigXYZ2);
      Vector3f pt1(TrackPoint);
      pt1 += ptCreep;
      pBar = WoodCrossTie( pt1, trigXYZ2, trigZ2, guide.fTrackGauge, fTie );
      pTrackSection->AddSection( pBar );

      double dAngle = guide.fCurRailAngle;
      if( dAngle < -90 ) dAngle = -90;
      if( dAngle > 90 ) dAngle = 90;
      float fCatwallDiff = (float)sin( M_PI/180 * dAngle ) * 1.25f;
      if( guide.fCurRailAngle < 33)
      {
         Vector3f ptA( -2.5f, 0, 0 );
         Vector3f ptB( -fGauge+0.45f, 0, 0 );
         ptA.Rotate( trigRZ );
         ptB.Rotate( trigRZ );
         ptB.x -= 0.85f;
         ptB.y = ptA.y;
         if(fCatwallDiff < 0)
            ptA.x += fCatwallDiff;
         else
            ptA.x -= fCatwallDiff;
         ptB.x -= fCatwallDiff;
         ptA.Transform( trigPXYZ, SupportPoint ); // Transform, use matrix here
         ptB.Transform( trigPXYZ, SupportPoint ); // Transform, use matrix here

         pLeftCatwalk->AddPoint( ptA );
         pLeftCatwalk->AddPoint( ptB );
      }
      if( guide.fCurRailAngle > -33)
      {
         Vector3f ptA( 2.5f, 0, 0 );
         Vector3f ptB( fGauge-0.45f, 0, 0 );
         ptA.Rotate( trigRZ );
         ptB.Rotate( trigRZ );
         ptB.x += 0.85f;
         ptB.y = ptA.y;
         if(fCatwallDiff > 0)
            ptA.x += fCatwallDiff;
         else
            ptA.x -= fCatwallDiff;
         ptB.x -= fCatwallDiff;
         ptA.Transform( trigPXYZ, SupportPoint ); // Transform, use matrix here
         ptB.Transform( trigPXYZ, SupportPoint ); // Transform, use matrix here

         pRightCatwalk->AddPoint( ptA );
         pRightCatwalk->AddPoint( ptB );
      }

      double dRad = 45.0f;
      double dRDeg = 360.0/(iRailSides-1);
      for( int idx = 0; idx < iRailSides; ++idx )
      {
         float fTheta = (float)(M_PI/180 * dRad);
         Vector3f ptA( cos(fTheta) * guide.fRailRadius-fGauge, sin(fTheta)* guide.fRailRadius + fYOffset, 0 );
         Vector3f ptB( cos(fTheta) * guide.fRailRadius+fGauge, sin(fTheta)* guide.fRailRadius + fYOffset, 0 );
         ptA.Rotate( trigRZ );
         ptA.Transform( trigPXYZ, TrackPoint ); // Transform, use matrix here
         ptB.Rotate( trigRZ );
         ptB.Transform( trigPXYZ, TrackPoint ); // Transform, use matrix here

         pMeshA->AddPoint( ptA );
         pMeshB->AddPoint( ptB );

         dRad += dRDeg;
      }
      if (--iCurSupp < 1)
      {
         pTrackSection->AddSection (WoodSupports (SupportPoint, guide.fCurAngleY, guide.fCurRailAngle ));
         iCurSupp = 3;
      }
      if( idxz < iLast )
      {
         sf::Vector3f pt3f( TrackPoint.x,TrackPoint.y,TrackPoint.z);
         mPark.AddTestPoint( pt3f, sf::Vector3f(-guide.fCurAngleX, guide.fCurAngleY, -guide.fCurRailAngle) ); // path

         guide.fCurAngleX += guide.fTiltX;
         guide.fCurAngleY += guide.fTiltY;
         guide.fCurAngleZ += guide.fTiltZ;
         guide.fCurRailAngle += guide.fRailTiltZ;
         Vector3f::VectorAngle3<float> trigFV( guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);
         Vector3f pFV(guide.ForwardVector);
         pFV.Rotate(trigFV);
         guide.fCurPos += guide.fStep;
         SupportPoint += pFV; // rotate to the current vector
      }
   }

   guide.iSupportSection = iCurSupp;
   guide.point = SupportPoint; // using the support location as the rail moves
}

TexturedStrip* TrackFormer::CrossTie( Vector3f& TrackPoint, TrackGuide& guide )
{
   float fTrackGuage = guide.fTrackGauge;
   struct FPoint
   {
      float X1;
      float Y1;
      float X2;
      float Y2;
   };

   // These can be moved to XML
      // the following looks like this
      //    o---o
      //    |   |
      //    o---o
   FPoint BoxShape[] =
   {
      { -0.45f, 0.45f, -0.40f, 0.40f },
      {  0.45f, 0.45f,  0.40f, 0.40f },
      {  0.45f, 0.05f,  0.40f, 0.05f  },
      { -0.45f, 0.05f, -0.40f, 0.05f  },
      { -0.45f, 0.45f, -0.40f, 0.40f }
   };

      // the following looks like this
      //   o_____o
      //     \ /
      //      O

   FPoint TieShape[] =
   {
      { -0.46f,0.43f,-0.46f, 0.38f },
      { -0.2f, 0.4f,  -0.2f, 0.2f  },
      { 0,     0.4f,  0,     0.1f  },
      { 0.2f,  0.4f,  0.2f,  0.2f  },
      { 0.46f, 0.43f, 0.46f, 0.38f }
   };

      // the following looks like this
      //    o___o
      //     \ /
      //      O

   FPoint TriShape[] =
   {
      { -0.45f,0.45f,-0.3f, 0.40f },
      { 0.45f, 0.45f, 0.3f, 0.40f },
      { 0.0f,  0.0f,  0.0f,  0.1f  },
      { -0.45f,0.45f,-0.3f, 0.40f }
   };

      // the following looks like this
      //   o     o
      //   |_____|
      //      O
   FPoint UShape[] =
   {
      { -0.58f, 0.43f, -0.54f, 0.43f },
      { -0.58f,  0.1f,  -0.54f, 0.2f },
      { 0.58f,   0.1f,   0.54f, 0.2f },
      { 0.58f,  0.43f,  0.54f, 0.43f }
   };

      // the following looks like this
      //   o----o

   FPoint LShape[] = // ladder
   {
      { -0.42f, 0.2f, -0.42f, 0.12f },
      { 0.42f,  0.2f,  0.42f, 0.12f }
   };

      // _I___I_
      
   FPoint IShape[] = // Railroad or non coaster
   {
      { -1.2f, -0.15f,  1.2f, -0.15f },
      { -1.2f, -0.02f,  1.2f, -0.02f },
      { -1.2f, -0.02f,  1.2f, -0.02f },
      { -1.2f, -0.12f,  1.2f, -0.15f }
   };
   
   const int   TiePoints = 5;
   const int   UPoints = 4;
   const int   IPoints = 2;

   FPoint* pPoints;
   int iCount = 2;
   bool bWood = false;
   switch( guide.GetRailShape() )
   {
   case 6:
      pPoints = BoxShape;
      iCount = 5;
      break;
   case 4:
      pPoints = UShape;
      iCount = 4;
      break;
   case 3:
      pPoints = TriShape;
      iCount = 4;
      break;
   case 2:
      pPoints = LShape;
      iCount = 2;
      break;
   case 5:
      pPoints = TieShape;
      iCount = 5;
      break;
   case 7:
   case 8:
      pPoints = IShape; // railroad
      iCount = 4;
      bWood = true;
      break;
   };

   TexturedStrip* pTBar = new TexturedStrip( iCount, mpTexture, 0x00505750 );
   Vector3f::VectorAngle3<float> trigZ (0, 0, guide.fCurRailAngle);
   Vector3f::VectorAngle3<float> trig2 (guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ);
   //if (bWood)
   //{
   //   float Z1 = 0;
   //   for( int ix = 0; ix < iCount; ++ix )
   //   {
   //      Vector3f pt1( pPoints[ix].X1, pPoints[ix].Y1, Z1 );
   //      Vector3f pt2( pPoints[ix].X2, pPoints[ix].Y2, Z1 );

   //      pt1.Rotate( trigZ );
   //      pt1.Rotate( trig2 );
   //      pt1 *= fTrackGuage;
   //      pt1 += TrackPoint;

   //      pt2.Rotate( trigZ );
   //      pt2.Rotate( trig2 );
   //      pt2 *= fTrackGuage;
   //      pt2 += TrackPoint;

   //      pTBar->AddPoint( pt1 );
   //      pTBar->AddPoint( pt2 );
   //      if (ix == 2)
   //      {
   //         Z1 += 0.1f;
   //      }
   //   }
   //}
   //else
   //{
      for( int ix = 0; ix < iCount; ++ix )
      {
         Vector3f pt1( pPoints[ix].X1, pPoints[ix].Y1, 0 );
         Vector3f pt2( pPoints[ix].X2, pPoints[ix].Y2, 0 );

         pt1.Rotate( trigZ );
         pt1.Rotate( trig2 );
         pt1 *= fTrackGuage;
         pt1 += TrackPoint;

         pt2.Rotate( trigZ );
         pt2.Rotate( trig2 );
         pt2 *= fTrackGuage;
         pt2 += TrackPoint;

         pTBar->AddPoint( pt1 );
         pTBar->AddPoint( pt2 );
      }
   //}
   return pTBar;
}

TexturedStrip* TrackFormer::WoodCrossTie( Vector3f& TrackPoint,
                                          Vector3f::VectorAngle3<float>& trigXYZ, Vector3f::VectorAngle3<float>& trigZ,
                                          float fGauge, float fThick)
{
   TexturedStrip* pTBar = new TexturedStrip( 5, mpTexture, 0xfc2d6fef );
   Vector3f::VectorAngle3<float> trigTie (90.0f, 0, 0);

   Vector3f ptDims( 0, fThick/2, fThick/2);
   Vector3f pt1;
   Vector3f pt2;
   Vector3f ptAdjust (0, -0.325f, 0); // move the tie down below the rail
   float fHTG = fGauge/2 + 1;

   for (int ic = 0; ic < 5; ++ic)
   {
      pt1 = ptDims;     // just the end points
      pt1 += ptAdjust;
      pt2 = pt1;
      pt1.x -= fHTG;    // dimension to width
      pt2.x += fHTG;
      pt1.Rotate(trigZ);   // fix the tilt
      pt2.Rotate(trigZ);
      pt1.Rotate(trigXYZ); // convert to world angle
      pt2.Rotate(trigXYZ);
      pt1 += TrackPoint;   // position in world
      pt2 += TrackPoint;   // position in world
      pTBar->AddPoint (pt1);
      pTBar->AddPoint (pt2);
      ptDims.Rotate(trigTie); //
   }
   return pTBar;
}


// this is experimental and subject to replacement
ObjectBase* TrackFormer::Support( Vector3f ptMount, TrackGuide& guide, float fMountAngle, float Load, float fBaseHeight )
{
   int id = 500;  // local mesh numbering
   double dSuppRadius = 0.5;
   float fYOffset = 0.8f;
   Vector3f ptH(0, ptMount.y, 0);
   Vector3f ptSupport(ptMount);
   MeshNode* pSupp = ObjectFactory::CreateMeshNode(4);
   //if( fMountAngle < -10 || fMountAngle > 10 )
   //{
   //   Vector3f::VectorAngle3<float> trigRZ( 0, 0, fMountAngle-90, 1.0 );
   //   Vector3f ptVec( 0, -1.0, 0);

   //   ptVec *= 3.0;
   //   ptVec.Rotate( trigRZ);
   //   TexturedMesh *pMesh = new TexturedMesh( 2, 6, mpTexture, 0xff3f3f3f, id++ );
   //   Vector3f::VectorAngle3<float> trigPXYZ( guide.dCurAngleX, guide.dCurAngleY, guide.dCurAngleZ, 1.0 );
   //   double dRad = 0.0;
   //   double dDeg = 360.0/ 6;
   //   for( int idx = 0; idx < 7; ++idx )
   //   {
   //      double dTheta = M_PI/180 * dRad;
   //      Vector3f pt( cos(dTheta) * dSuppRadius, sin(dTheta)* dSuppRadius, 0 );
   //      pt.Transform( trigPXYZ, ptMount );
   //      pMesh->AddPoint( pt.GetVector3f() );
   //      dRad += dDeg;
   //   }
   //   Vector3f ptJoint(ptMount);
   //   ptJoint += ptVec;
   //   for( int idx = 0; idx < 7; ++idx )
   //   {
   //      double dTheta = M_PI/180 * dRad;
   //      Vector3f pt( cos(dTheta) * dSuppRadius, sin(dTheta)* dSuppRadius, 0 );
   //      pt.Rotate( trigRZ );
   //      pt.Transform( trigPXYZ, ptJoint );
   //      pMesh->AddPoint( pt.GetVector3f() );
   //      dRad += dDeg;
   //   }
   //   ptJoint *= 0.9; // move back a little
   //   ptSupport = ptJoint;
   //   pSupp->AddMesh( pMesh );
   //}
   TexturedMesh *pMeshA = new TexturedMesh( 2, 7, mpTexture, 0xff5f5f5f, id++ );
   pSupp->AddMesh( pMeshA );
   if( pMeshA )
   {
      Vector3f::VectorAngle3<float> trigRZ (0, 0, fMountAngle);
      Vector3f::VectorAngle3<float> trigPXYZ (0, guide.fCurAngleY, 0);
      double dRad = 0.0;
      double dDeg = 360.0/ 6;
      for( int idx = 0; idx < 7; ++idx )
      {
         float fTheta = (float)(M_PI/180 * dRad);
         Vector3f pt( cos(fTheta) * (float)dSuppRadius, 0, sin(fTheta)* (float)dSuppRadius );
         pt.Rotate( trigRZ );
         pt.Transform( trigPXYZ, ptSupport );
         pMeshA->AddPoint( pt );
         dRad += dDeg;
      }
      ptSupport.y = fBaseHeight;
      for( int idx = 0; idx < 7; ++idx )
      {
         float fTheta = (float)(M_PI/180 * dRad);
         Vector3f pt( cos(fTheta) * (float)dSuppRadius, 0, sin(fTheta)* (float)dSuppRadius );
         pt.Rotate( trigRZ );
         pt.Transform( trigPXYZ, ptSupport );
         pMeshA->AddPoint( pt );
         dRad += dDeg;
      }
   }
//   TexturedMesh *pMeshB = new TexturedMesh( 2, 7, mpTexture, 0xff3f3f3f, id++ );
//   pSupp->AddMesh( pMeshB );
   return pSupp;
}

ObjectBase* TrackFormer::WoodSupports( Vector3f ptMount, float fCurAngleY, float fCurRailAngle )
{
   Vector3f ptH (ptMount);
   ptH.y = 0; // ground + 1
   WoodTrestle* pSupp = new WoodTrestle (mpTexture, ptH);
   pSupp->Preset (WoodTrestle::TF_Standard, fCurAngleY, ptMount.y, 6.0f, fCurRailAngle); // guide.fCurAngleY, 6.0f, guide.fCurRailAngle
   Vector3f HRA(0,0,0);
   Vector3f HRB(0,0,0);
   pSupp->Render (HRA, HRB);
   return pSupp;
}

// Example call
//   pTrackSection->AddSection (AddCorkSupport( TrackPoint, guide.fCurAngleY, 24 ));

ObjectBase* TrackFormer::AddCorkSupport( Vector3f ptMount, float fCurAngleY, float fCorkLength )
{
   ParabolicCorkSupport* pSupp = new ParabolicCorkSupport(mpTexture, ptMount);
   Vector3f cet(0,8.0f,0);
   pSupp->Preset (ParabolicCorkSupport::CSF_Standard, 20, 18, 26);
   pSupp->Render (ptMount, 15.0f);
   return pSupp;
}