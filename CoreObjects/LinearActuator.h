//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RidePlatform   The Base that sits on the ground or
      RideChassis    Deck or Central base as in a carousel
      RideStrut      Interconnect or Structural element
      RideHub        Stationay Structural element such as the pylon for the yoyo and carousel.
      RideAxes       Base class for connections
      RideFixedMount This connection is fixed.
      RideAxle
      RideGimble
      RidePivot
      RideCable
      RideArm        Assembly that is a feature support that extends out and usually supports a carriage.
      RideTelescopeArm Arm that has an extenstion that slides out to extend the arm up to 1.8 times its collapsed length.
      RideRestraint
      RideActuater   Linear Motion Power Device.
      RideMotor      Rotation Motion Power Device.
                     Arms may be moveable or fixed
      RideDisc       Full or Partial circle, base or roof part
      RideCarriage   Assembly that supports one or more cars
      RideCar        Inclosure, Bucket or platform that holds the seats and may include (a cage or rollbars) and restraints.
*/

#pragma once

class RideBase
{

public:
   RideBase(int ID );
   ~RideBase(void);
};
