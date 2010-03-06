/*   This file is part of TPB Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   TPB Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with TPB Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SINGLESTAIRS_H
#define _SINGLESTAIRS_H

// Elevator class, this is the elevator carrige.
// Handles the car movement and operations.
// Elevator is the overhead cable machine.
// LiftShaft is the evelator shaft.
// ListPit is the crash landing pit below in the event of a break failure.
// This three parts build the shaft for the elevator/lift to run in.

// these decls allow inclusion of this header without the need to load these class headers.
//class RouteBase;
struct RoutingRequest;
class AnimationSingle;
class Person;
class PersonQueue;
class Park;
class SerializerBase;

#include "../Root/Physics.h"
#include "../Graphics/ModelObject.h"
#include "RouteBase.h"

// people walk up and down these but will ride the elevators in most cases
namespace ParkObjects
{
   class SingleStair : public Body, public RouteBase, public Gfx::ModelObject // Quad morphic
   {
   public:


   protected:
      static int gElevatorsNumber;
      static const int mStandingPositions[];

      AnimationSingle* mSingleStairImage;

      // Controls this things motion
      int   mX;
      int   mY;
      float mZ;

      int   mNumber;    // number of this stair
      short mTopLevel;
      short mBottomLevel;

      short mWalkersOnStairs;
      short mFloorCount;
      short mMaxCap;

      Park * mParkParent;

   public:
      // CTOR/DTOR  Use create to make on
      SingleStair( int x, short BottLevel, short TopLevel, Park * ParkParent );
      SingleStair( SerializerBase& ser, short TopLevel, Park * ParkParent );
      virtual ~SingleStair();

      // Properties
      inline int  GetNumber() { return mNumber; }

      // Methods
      void Move( int x, int y );
      void Resize( int x, int y );

   protected:
      void LoadImages();
      void PosCalc ();

      int  LoadPerson(Person* person, RoutingRequest& req); // returns space remaining
      void Motion ();
      void SetDestination (int level);
      bool SetCallButton( RoutingRequest& req ) { return false; } // call the elevator
      void SetFloorButton( RoutingRequest& req ) { }      // once inside, select a floor
   public:

      virtual void Update (float dt);
      virtual void Draw ();
      virtual void DrawFramework () { } // geometry test
      
      void Save( SerializerBase& ser );
      PersonQueue* FindQueue (int level);

   };
}

#endif _SINGLESTAIRS_H
