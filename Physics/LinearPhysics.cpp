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

#include <iostream>
#include "LinearPhysics.h"

namespace Test
{
   T_Spline CoasterSplines;
   T_Spline& GetSpline() { return CoasterSplines; }
}

void Spline::CalcFinalDelta(Vector3f& endPoint, Vector3f& endAngle)
{
   MotionDelta = endPoint;
   MotionDelta -= mVPoint;
   AngleDelta = endAngle;
   AngleDelta -= mVAngle;
   DeltasPerQuarter = TotalDistance * 8;
}

LinearPhysics::LinearPhysics (Vector3f Pos)
{
   mPosition = Pos;
   mVelocity = 80;
   mAcceleration = 1;
   mSplineIndex = 0;
   mCurrentDelta = 0;
   mTime = 0;
}

LinearPhysics::LinearPhysics (float x, float y, float z)
{
   mPosition = Vector3f(x,y,z);
   mVelocity = 60;
   mAcceleration = 1;
   mSplineIndex = 0;
   mCurrentDelta = 0;
   mTime = 0;
}

void LinearPhysics::DebugPrint ()
{
   std::cout << "LinearPhysics: Position " << mPosition.x << " , " << mPosition.y << std::endl
             << "Velocity " << mVelocity << std::endl
             << "Acceleration " << mAcceleration << std::endl;
}

void LinearPhysics::SetPosition (float x, float y, float z)
{
   mPosition.x = x;
   mPosition.y = y;
   mPosition.z = z;
   mSplineIndex = 0;
   Spline* pS = Test::CoasterSplines[mSplineIndex];
   memcpy (&mCurrentSpline, pS, sizeof(mCurrentSpline));
   mDirection = mCurrentSpline.MotionDelta;
   mRotation = mCurrentSpline.AngleDelta;
   mPosition = mCurrentSpline.mVPoint;
   mVAngle = mCurrentSpline.mVAngle;
}

void LinearPhysics::SetRotation (float x, float y, float z)
{
   mRotation.x = x;
   mRotation.y = y;
   mRotation.z = z;
}

void LinearPhysics::MoveTo (float time)
{
   mIsMoving = true;
   mTime = 0.0;
   mTimeTotal += time;
   float fPotential = (mVAngle.z*mVAngle.z) * 0.0125f;
   mVelocity = (2 * fPotential) / time;
   mAcceleration = -(mVelocity * mVelocity) / (2 * fPotential);
}
void LinearPhysics::Start()
{
   Spline* pS = Test::CoasterSplines[mSplineIndex];
   memcpy (&mCurrentSpline, pS, sizeof(mCurrentSpline));
}

void LinearPhysics::Integrate (float dt)
{
   float dt_secs = dt / 100;
   float fVelSec = mVelocity * dt_secs;
   float fPotential = -(mVAngle.x*mVAngle.x) * 0.0125f;
   if (fPotential == 0)
   {
      fPotential = mVelocity * 0.82f;
   }
   mVelocity = (2 * fPotential) / dt;
   mAcceleration = -(mVelocity * mVelocity) / (2 * fPotential);

   if( mCurrentDelta > 1.0f )
   {
      mCurrentDelta -= 1.0f;
      if( ++mSplineIndex >= (int)Test::CoasterSplines.size()) mSplineIndex = 0;
      Spline* pS = Test::CoasterSplines[mSplineIndex];
      memcpy (&mCurrentSpline, pS, sizeof(mCurrentSpline));
   }
   if(mCurrentSpline.TotalDistance>0)
   {
      float fT = (1.0f / mCurrentSpline.DeltasPerQuarter) * dt / 2;
      mTime = (fT>0) ? fT : 0;
   }
   else
   {
      float fT = dt_secs;
      mTime = (fT>0) ? fT : 0;
   }
}

void LinearPhysics::Motion()
{
   mCurrentDelta += mTime;
   mPosition.x = mCurrentSpline.mVPoint.x + mCurrentSpline.MotionDelta.x * mCurrentDelta;
   mPosition.y = mCurrentSpline.mVPoint.y + mCurrentSpline.MotionDelta.y * mCurrentDelta;
   mPosition.z = mCurrentSpline.mVPoint.z + mCurrentSpline.MotionDelta.z * mCurrentDelta;
   mRotation.x = mCurrentSpline.mVAngle.x + mCurrentSpline.AngleDelta.x * mCurrentDelta;
   mRotation.y = mCurrentSpline.mVAngle.y + mCurrentSpline.AngleDelta.y * mCurrentDelta;
   mRotation.z = mCurrentSpline.mVAngle.z + mCurrentSpline.AngleDelta.z * mCurrentDelta;
}