//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track forming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../CoreObjects/TrackBase.h"
#include "../CoreObjects/Track.h"
#include "../CoreObjects/TrackGuide.h"
#include "../CoreObjects/TrackSection.h"
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
   bool bWood = (guide.iRailShape == 8);
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
   pTrackSection->Create(4+guide.iSections*2);
   Track.AddSection(pTrackSection);

   // Determine rails needed
   TexturedMesh *pMesh = NULL;
   if (bWood)
   {
      iRailSides = 5;
      fYOffset = 0.0f;
   }
   else
   {
      if( guide.iRailShape == 3 )
      {
         pMesh = new TexturedMesh( guide.iSections+1, iTubeSections, mpTexture, 0xff009090, id++ );
         pTrackSection->AddSection( pMesh );
      }
      else if( guide.iRailShape > 2 )
      {
         pMesh = new TexturedMesh( guide.iSections+1, iTubeSections, mpTexture, 0xff009090, id++ );
         pTrackSection->AddSection( pMesh );
      }
      else
      {
         fYOffset = 0.2f;
      }
   }
   TexturedMesh *pMeshA = new TexturedMesh( guide.iSections+1, iRailSides, mpTexture, 0xfc2d6fef, id++ );
   TexturedMesh *pMeshB = new TexturedMesh( guide.iSections+1, iRailSides, mpTexture, 0xfc2d6fef, id++ );
   pTrackSection->AddSection( pMeshA );
   pTrackSection->AddSection( pMeshB );
   // option for one or two more rails

   // Get fractional vector
   CVPoint TrackPoint( guide.point );
   CVPoint centerPT( 0, -guide.fRadius, 0 );
   STrig trigXYZ( guide.fTiltX, guide.fTiltY, guide.fTiltZ, 1.0 );
   STrig trig( guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ, 1.0 );
   if( guide.iSections > 14 )
   {
      int steps = int(guide.iSections / 12) + 1;
      guide.fNextMount = (float)(guide.iSections / steps + 1.9);
      guide.fStep = 2.0;
   }

   int iLast = guide.iSections;
   for( int idxz = 0; idxz<= iLast; ++idxz )
   {
      TexturedStrip* pBar = CrossTie( TrackPoint, guide );
      pTrackSection->AddSection( pBar );

      STrig trigRZ( 0, 0, guide.fCurRailAngle, 1.0 );
      STrig trigPXYZ( guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ, 1.0 );
      double dRad = 0.0;
      if (pMesh != NULL)
      {
         double dDeg = 360.0/ (iTubeSections-1);
         for( int idx = 0; idx < iTubeSections; ++idx )
         {
            double dTheta = M_PI/180 * dRad;
            CVPoint pt( cos(dTheta) * guide.fTubeRadius, sin(dTheta)* guide.fTubeRadius, 0 );
            pt.Rotate( trigRZ );
            pt.Transform( trigPXYZ, TrackPoint );
            sf::Vector3f temp = pt.GetVector3f();
            pMesh->AddPoint( temp );
            dRad += dDeg;
         }
      }
      double dRDeg = 360.0/(iRailSides-1);
      dRad = (bWood) ? 45.0f : 0.0;
      for( int idx = 0; idx < iRailSides; ++idx )
      {
         double dTheta = M_PI/180 * dRad;
         CVPoint ptA( cos(dTheta) * guide.fRailRadius-fGauge, sin(dTheta)* guide.fRailRadius + fYOffset, 0 );
         CVPoint ptB( cos(dTheta) * guide.fRailRadius+fGauge, sin(dTheta)* guide.fRailRadius + fYOffset, 0 );
         ptA.Rotate( trigRZ );
         ptA.Transform( trigPXYZ, TrackPoint ); // Transform, use matrix here
         ptB.Rotate( trigRZ );
         ptB.Transform( trigPXYZ, TrackPoint ); // Transform, use matrix here

         sf::Vector3f tempA = ptA.GetVector3f();
         sf::Vector3f tempB = ptB.GetVector3f();
         pMeshA->AddPoint( tempA );
         pMeshB->AddPoint( tempB );

         dRad += dRDeg;
      }
      if( idxz < iLast )
      {
         if( guide.fCurPos > guide.fNextMount ) // bSupports == true
         {
            CVPoint ptMount(TrackPoint);
            ptMount.y -= 0.75;
            pTrackSection->AddSection(Support(ptMount, guide, (float)guide.fCurRailAngle, 10, 1 ));
            guide.fCurPos = 0;
         }
         sf::Vector3f pt3f( TrackPoint.x,TrackPoint.y,TrackPoint.z);
         mPark.AddTestPoint( pt3f, sf::Vector3f(-guide.fCurAngleX, guide.fCurAngleY, -guide.fCurRailAngle) ); // path

         guide.fCurAngleX += guide.fTiltX;
         guide.fCurAngleY += guide.fTiltY;
         guide.fCurAngleZ += guide.fTiltZ;
         guide.fCurRailAngle += guide.fRailTiltZ;
         STrig trigFV( guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ, 1.0 );
         CVPoint pFV(guide.ForwardVector);
         pFV.Rotate(trigFV);
         guide.fCurPos += guide.fStep;
         TrackPoint += pFV; // rotate to the current vector
      }
   }
   guide.point = TrackPoint;
}

TexturedStrip* TrackFormer::CrossTie( CVPoint& TrackPoint, TrackGuide& guide )
{
   double dTrackGuage = guide.fTrackGauge;
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
   switch( guide.iRailShape )
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
   STrig trigZ( 0, 0, guide.fCurRailAngle, 1.0 );
   STrig trig2( guide.fCurAngleX, guide.fCurAngleY, guide.fCurAngleZ, 1.0 );
   if (bWood)
   {
      float Z1 = 0;
      for( int ix = 0; ix < iCount; ++ix )
      {
         CVPoint pt1( pPoints[ix].X1, pPoints[ix].Y1, Z1 );
         CVPoint pt2( pPoints[ix].X2, pPoints[ix].Y2, Z1 );

         pt1.Rotate( trigZ );
         pt1.Rotate( trig2 );
         pt1 *= dTrackGuage;
         pt1 += TrackPoint;

         pt2.Rotate( trigZ );
         pt2.Rotate( trig2 );
         pt2 *= dTrackGuage;
         pt2 += TrackPoint;

         sf::Vector3f temp1 = pt1.GetVector3f();
         sf::Vector3f temp2 = pt2.GetVector3f();
         pTBar->AddPoint( temp1 );
         pTBar->AddPoint( temp2 );
         if (ix == 2)
         {
            Z1 += 0.1f;
         }
      }
   }
   else
   {
      for( int ix = 0; ix < iCount; ++ix )
      {
         CVPoint pt1( pPoints[ix].X1, pPoints[ix].Y1, 0 );
         CVPoint pt2( pPoints[ix].X2, pPoints[ix].Y2, 0 );

         pt1.Rotate( trigZ );
         pt1.Rotate( trig2 );
         pt1 *= dTrackGuage;
         pt1 += TrackPoint;

         pt2.Rotate( trigZ );
         pt2.Rotate( trig2 );
         pt2 *= dTrackGuage;
         pt2 += TrackPoint;

         sf::Vector3f temp1 = pt1.GetVector3f();
         sf::Vector3f temp2 = pt2.GetVector3f();
         pTBar->AddPoint( temp1 );
         pTBar->AddPoint( temp2 );
      }
   }
   return pTBar;
}

// this is experimental and subject to replacement
ObjectBase* TrackFormer::Support( CVPoint ptMount, TrackGuide& guide, float fMountAngle, float Load, float fBaseHeight )
{
   int id = 500;  // local mesh numbering
   double dSuppRadius = 0.5;
   float fYOffset = 0.8f;
   CVPoint ptH(0, ptMount.y, 0);
   CVPoint ptSupport(ptMount);
   MeshNode* pSupp = ObjectFactory::CreateMeshNode(4);
   //if( fMountAngle < -10 || fMountAngle > 10 )
   //{
   //   STrig trigRZ( 0, 0, fMountAngle-90, 1.0 );
   //   CVPoint ptVec( 0, -1.0, 0);

   //   ptVec *= 3.0;
   //   ptVec.Rotate( trigRZ);
   //   TexturedMesh *pMesh = new TexturedMesh( 2, 6, mpTexture, 0xff3f3f3f, id++ );
   //   STrig trigPXYZ( guide.dCurAngleX, guide.dCurAngleY, guide.dCurAngleZ, 1.0 );
   //   double dRad = 0.0;
   //   double dDeg = 360.0/ 6;
   //   for( int idx = 0; idx < 7; ++idx )
   //   {
   //      double dTheta = M_PI/180 * dRad;
   //      CVPoint pt( cos(dTheta) * dSuppRadius, sin(dTheta)* dSuppRadius, 0 );
   //      pt.Transform( trigPXYZ, ptMount );
   //      pMesh->AddPoint( pt.GetVector3f() );
   //      dRad += dDeg;
   //   }
   //   CVPoint ptJoint(ptMount);
   //   ptJoint += ptVec;
   //   for( int idx = 0; idx < 7; ++idx )
   //   {
   //      double dTheta = M_PI/180 * dRad;
   //      CVPoint pt( cos(dTheta) * dSuppRadius, sin(dTheta)* dSuppRadius, 0 );
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
      STrig trigRZ( 0, 0, fMountAngle, 1.0 );
      STrig trigPXYZ( 0, guide.fCurAngleY, 0, 1.0 );
      double dRad = 0.0;
      double dDeg = 360.0/ 6;
      for( int idx = 0; idx < 7; ++idx )
      {
         double dTheta = M_PI/180 * dRad;
         CVPoint pt( cos(dTheta) * dSuppRadius, 0, sin(dTheta)* dSuppRadius );
         pt.Rotate( trigRZ );
         pt.Transform( trigPXYZ, ptSupport );
         sf::Vector3f temp = pt.GetVector3f();
         pMeshA->AddPoint( temp );
         dRad += dDeg;
      }
      ptSupport.y = fBaseHeight;
      for( int idx = 0; idx < 7; ++idx )
      {
         double dTheta = M_PI/180 * dRad;
         CVPoint pt( cos(dTheta) * dSuppRadius, 0, sin(dTheta)* dSuppRadius );
         pt.Rotate( trigRZ );
         pt.Transform( trigPXYZ, ptSupport );
         sf::Vector3f temp = pt.GetVector3f();
         pMeshA->AddPoint( temp );
         dRad += dDeg;
      }
   }
//   TexturedMesh *pMeshB = new TexturedMesh( 2, 7, mpTexture, 0xff3f3f3f, id++ );
//   pSupp->AddMesh( pMeshB );
   return pSupp;
}
