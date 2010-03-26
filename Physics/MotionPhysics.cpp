/*   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "MotionPhysics.h"

Body::Body (int width, int height)
{
   mIsMoving = false;
   mTime = 0;
   mTimeTotal = 0;
   // mMoveDest self initializes in the CTOR
   mPosition = Vector3f(0,0,0);
   mVelocity = Vector3f(0,0,0);
   mAcceleration = Vector3f(0,0,0);
   mWidth = Vector3f ((float)width, 0, 0);
   mHeight = Vector3f (0, (float)height, 0);
   mDepth = Vector3f (0, 0, 1);
   
}

Body::Body (Vector3f Pos, int width, int height)
{
   mPosition = Pos;
   mVelocity = Vector3f(0,0,0);
   mAcceleration = Vector3f(0,0,0);
   mWidth = Vector3f ((float)width, 0, 0);
   mHeight = Vector3f (0, (float)height, 0);
   mDepth = Vector3f (0, 0, 1);
}

Body::Body (float x, float y, int width, int height)
{
   mPosition = Vector3f(x,y,0);
   mVelocity = Vector3f(0,0,0);
   mAcceleration = Vector3f(0,0,0);
   mWidth = Vector3f ((float)width, 0, 0);
   mHeight = Vector3f (0, (float)height, 0);
   mDepth = Vector3f (0, 0, 1);
}

void Body::DebugPrint ()
{
   std::cout << "Body: Position " << mPosition.x << " , " << mPosition.y << std::endl
             << "Velocity " << mVelocity.x << " , " << mVelocity.y << std::endl
             << "Acceleration " << mAcceleration.x << " , " << mAcceleration.y << std::endl;
}

void Body::SetPosition (float x, float y, float z)
{
   mPosition.x = x;
   mPosition.y = y;
   mPosition.z = z;
}

void Body::SetVelocity (float x, float y, float z)
{
   mVelocity.x = x;
   mVelocity.y = y;
   mVelocity.z = z;
}

void Body::MoveTo (float x, float y, float z, float time)
{
   mIsMoving = true;
   mTime = 0.0;
   mTimeTotal += time;
   mMoveDest.x = x;
   mMoveDest.y = y;
   mMoveDest.z = z;
   float dist_x = x - mPosition.x;
   float dist_y = y - mPosition.y;
   float dist_z = z - mPosition.z;
   if (dist_x == 0)
   {
      mVelocity.x = 0;
      mAcceleration.x = 0;
   }
   else
   {
      mVelocity.x = (2 * dist_x) / time;
      mAcceleration.x = -(mVelocity.x * mVelocity.x) / (2 * dist_x);
   }
   if (dist_y == 0)
   {
      mVelocity.y = 0;
      mAcceleration.y = 0;
   }
   else
   {
      mVelocity.y = (2 * dist_y) / time;
      mAcceleration.y = -(mVelocity.y * mVelocity.y) / (2 * dist_y);
   }
   if (dist_z == 0)
   {
      mVelocity.z = 0;
      mAcceleration.z = 0;
   }
   else
   {
      mVelocity.z = (2 * dist_z) / time;
      mAcceleration.z = -(mVelocity.z * mVelocity.z) / (2 * dist_z);
   }
}

void Body::SetAcceleration (float x, float y, float z)
{
   mAcceleration.x = x;
   mAcceleration.y = y;
   mAcceleration.z = z;
}

void Body::Integrate (float dt)
{
   float dt_secs = dt / 1000;
   mPosition.x += mVelocity.x * dt_secs;
   mPosition.y += mVelocity.y * dt_secs;
   mPosition.z += mVelocity.z * dt_secs;
   mVelocity.x += mAcceleration.x * dt_secs;
   mVelocity.y += mAcceleration.y * dt_secs;
   mVelocity.z += mAcceleration.z * dt_secs;
   if ((mVelocity.x > -10) && (mVelocity.x < 10))
   {
      mVelocity.x = 0;
      mAcceleration.x = 0;
   }
   if ((mVelocity.y > -10) && (mVelocity.y < 10))
   {
      mVelocity.y = 0;
      mAcceleration.y = 0;
   }
   if ((mVelocity.z > -10) && (mVelocity.z < 10))
   {
      mVelocity.z = 0;
      mAcceleration.z = 0;
   }
   if (mIsMoving)
   {
      mTime += dt;
      if (mTime >= mTimeTotal)
      {
         mPosition = mMoveDest;
         mIsMoving = false;
         mVelocity.x = 0;
         mVelocity.y = 0;
         mVelocity.z = 0;
         mAcceleration.x = 0;
         mAcceleration.y = 0;
         mAcceleration.z = 0;
      }
   }
}
