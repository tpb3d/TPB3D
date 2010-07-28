//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TrackSection class
//
//  Generated track sections specified by a pattern and parameters
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#include "../Types/Vector3.h"

#pragma once
struct TrackGuide
{
protected:
   int iSections;
   int iRailShape;
public:
   int yDir;
   int xDir;
   Vector3f point;
   Vector3f ForwardVector;
   float fCurAngleX;
   float fCurAngleY;
   float fCurAngleZ;
   float fCurRailAngle;
   float fTubeRadius;
   float fRailRadius;
   float fRailTiltZ;
   float fTiltX;
   float fTiltY;
   float fTiltZ;
   float fWalkX;
   float fWalkY;
   float fWalkZ;
   float fRadius;
   float fTieWidth;
   float fTrackGauge;
   // supports
   float fNextMount;
   float fCurPos;
   float fStep;   // computed section length
   float fStepLength;

   int   iSupportSection;   // how many sections since the last support
   int   iSupportInterval;  // how many sections between supports
   bool  bStraight;

   TrackGuide()
   {
      iSections = 1;
      iRailShape = 2; // simple mouse track
      point.Set( 0,0,0 );
      fCurAngleX = 0;
      fCurAngleY = 0;
      fCurAngleZ = 0;
      fCurRailAngle = 0;
      fTubeRadius = 0;
      fRailRadius = 0;
      fRailTiltZ = 0;
      fTieWidth = 3;
      fTiltX = 0;
      fTiltY = 0;
      fTiltZ = 0;
      fRadius = 4;
      fTrackGauge = 2.0;
      // supports
      fNextMount = 32;
      fCurPos = 0;
      fStep = 2.0f;
      fStepLength = 2.0f;

      iSupportSection = 0;
      iSupportInterval = 7;

      bStraight = false;
   }
   void SetRailShape (int shape);
   int  GetRailShape () { return iRailShape;}
   int  GetSections () { return iSections; }
   void SetupTurn( double dDegRotation, double dRadius, double dRoll );
   void SetupPitch( double dDegPitch, double dRadius, double dRoll );
   void SetupStraight( double dDistance, double dRoll );
   void SetupCompound( double dDegRotation, double dRadius, double dDegPitch, double dPitchRadius, double dRoll );
};

