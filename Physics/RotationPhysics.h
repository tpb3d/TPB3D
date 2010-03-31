/*   This file is part of Theme Park Builder 3D The Game.
 *
 *   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef _ROTPHYSICS_H
#define _ROTPHYSICS_H

class RotationPhysics
{
protected:
   bool  mIsMoving;
   float mTime;
   float mTimeTotal;
   float mPosition;
   float mDestinedVelocity;
   float mVelocity;
   float mAcceleration;
   float mMass;
   float mDragRatio;     // this controls speed up and slowdown rates
   float mWeight;        // this amplifies acceleration and deminishes deceleration

public:
   // CTOR
   RotationPhysics (float mDestinedVelocity, float drag, float weight, float mass);

   float Velocity() { return mVelocity; }
   float Acceleration() { return mAcceleration; }
   float Mass() { return mMass; }
   float Position() { return mPosition; }
   void SetMass (float mass) { mMass = mass; }
   void SetAcceleration (float acc) { mAcceleration = acc; }
   void SetWeight (float weight) { mWeight = weight; }
   void SetDestinVelocity (float destvel) { mDestinedVelocity = destvel; }
   void SetPosition (float pos) { mPosition = pos; }

   // Mothods
   void Freeze() { mVelocity = mAcceleration = 0; }  // laws of physics ignored
   void Kill () { mAcceleration = mVelocity / 10; }  // fast stop
   void Stop ();
   
   void DebugPrint ();
   void Integrate (float dt);
};

#endif // _ROTPHYSICS_H
