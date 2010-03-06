//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track Guide structure
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/System.hpp>
#include "TrackGuide.h"

void TrackGuide::SetupTurn( double dDegRotation, double dRadius, double dRoll )
{
   // Using doubles in calcs for higher presision.
   // In long wide turns a float could cause tracking error outside tolerances.
   double dArcFeet = dDegRotation * ((2 * dRadius * M_PI) / 360); // how many feet per deg into Arc feet.
   iSections = abs((int)(dArcFeet / 2)); // how many degs per 2 feet
   if( dArcFeet/iSections > 2.2 ) iSections++;
   double dFootDegs = dDegRotation / iSections; // steps in approx 2 foot increments
   double dStep = dArcFeet / int(dArcFeet / 2);
   fTiltX = 0;
   fTiltY = (float)(dDegRotation / iSections);
   fTiltZ = 0;
   fRailTiltZ = (float)(dRoll / iSections);
   ForwardVector.Set( 0, 0, fabs(dStep) );
}

void TrackGuide::SetupPitch( double dDegPitch, double dRadius, double dRoll )
{
   double dArcFeet = dDegPitch * ((2 * dDegPitch * M_PI) / 360); // how many feet per deg into Arc feet.
   iSections = abs((int)(dArcFeet / 2)); // how many degs per 2 feet
   if( dArcFeet/iSections > 2.2 ) iSections++;
   double dFootDegs = dDegPitch / iSections; // how many degs per 2 feet
   double dStep = dArcFeet / int(dArcFeet / 2);
   fTiltX = (float)dDegPitch / iSections;
   fTiltY = 0;
   fTiltZ = 0;
   fRailTiltZ = (float)(dRoll / iSections);
   ForwardVector.Set( 0, 0, fabs(dStep) );
}

void TrackGuide::SetupStraight( double dDistance, double dRoll )
{
   iSections = int(dDistance / 2);
   fTiltX = 0;
   fTiltY = 0;
   fTiltZ = 0;
   fRailTiltZ = (float)(dRoll / iSections);
   ForwardVector.Set( 0, 0, 2);
}
void TrackGuide::SetupCompound( double dDegRotation, double dRadius, double dDegPitch, double dPitchRadius, double dRoll )
{
   double dArcFeet = dDegRotation * ((2 * dRadius * M_PI) / 360); // how many feet per deg into Arc feet.
   double dArcFeetPitch = dDegPitch * ((2 * dDegPitch * M_PI) / 360); // how many feet per deg into Arc feet.

   double dFootDegs = (dArcFeet > dArcFeetPitch) ? (dArcFeet / 2) : (dArcFeetPitch / 2); // how many degs per 2 feet
   iSections = (int)(dDegRotation / dFootDegs); // steps in approx 2 foot increments
   fTiltX = (float)(dDegPitch / iSections);
   fTiltY = (float)(dDegRotation / iSections);
   fTiltZ = (float)(dRoll / iSections);
}
