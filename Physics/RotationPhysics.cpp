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

#include <math.h>
#include <iostream>
#include "RotationPhysics.h"

RotationPhysics::RotationPhysics (float mDestinedVelocity, float drag, float weight, float mass)
{
   mAcceleration = 0;
   mPosition = 0;
   mDragRatio = drag;
   mWeight = weight;
   mIsMoving = false;
   mTime = 0;
   mTimeTotal = 0;
   mVelocity = 0;
   this->mMass = 1;   
}

void RotationPhysics::DebugPrint ()
{
   std::cout << "RotationPhysics: Position " << mPosition << std::endl
             << "Velocity " << mVelocity << std::endl
             << "Acceleration " << mAcceleration << std::endl;
}

void RotationPhysics::Integrate (float dt)
{
   float dt_secs = dt / 6;
   mPosition += mVelocity * dt_secs;
   if (mPosition > 360)
   {
      mPosition -=360;
   }
   if( mDestinedVelocity >= 0)
   {
      if( fabs(mVelocity - mDestinedVelocity) < 0.2f)
      {
         mVelocity = mDestinedVelocity;
      }
      else
      {
         if( mVelocity > mDestinedVelocity && mAcceleration > 0)
         {
            mAcceleration = -0.089f;
         }
         else
         {
            mAcceleration = (mDestinedVelocity - mVelocity) * 0.125f;
         }
         mVelocity += mAcceleration * dt_secs;
      }
   }
}
