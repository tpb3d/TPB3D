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
// Is there a way to avoid this include?
#include <vector>
#include "../Types/Vector2.h"
#include "../Types/Vector3.h"

struct Spline
{
   Vector3f mVPoint;
   Vector3f mVAngle;
   Vector3f MotionDelta;
   Vector3f AngleDelta;
   float    TotalDistance;
   float    DeltasPerQuarter;
   Spline()
   {
      TotalDistance = 0;
   }
   void CalcFinalDelta(Vector3f& endPoint, Vector3f& endAngle);
};

typedef std::vector<Spline*> T_Spline;
namespace Test
{
   T_Spline& GetSpline();
}

class LinearPhysics
{
protected:
   bool mIsMoving;
   float mTime;
   float mTimeTotal;
   float mCurrentDelta;
   float mAngleDelta;
   int   mSplineIndex;

public:  // protect these memvars and add gets
   Spline   mCurrentSpline;
   Vector3f mPosition;
   Vector3f mDirection;
   Vector3f mRotation;
   Vector3f mVAngle;
   float mVelocity;
   float mAcceleration; // based on Z angle and inertial forces
public:
   // CTOR
   LinearPhysics (float x, float y, float z);
   LinearPhysics (Vector3f Pos);

   //Properties
   float GetPositionX () { return mPosition.x; }
   float GetPositionY () { return mPosition.y; }
   float GetPositionZ () { return mPosition.z; }
   Vector3f GetPosition() { return mPosition; }
   float GetVelocity () { return mVelocity; }
   float GetAcceleration () { return mAcceleration; }

   // Mothods
   void DebugPrint ();
   // Depreciated!
   void SetPosition (float x, float y, float z);
   void SetRotation (float x, float y, float z);
   void SetVelocity (float x, float y, float z);
   void SetAcceleration (float x, float y, float z);

   void SetPosition (const Vector3f& NewPos) { mPosition = NewPos; }
   void SetRotation (const Vector3f& NewRot) { mRotation = NewRot; }
   void SetVelocity (const float NewV) { mVelocity = NewV; }
   void SetAcceleration (const float NewA) { mAcceleration = NewA; }

   void Start ();
   void Integrate (float dt);
   void MoveTo (float time);
   void Motion();
};
