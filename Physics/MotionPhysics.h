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

#ifndef _PHYSICS_H
#define _PHYSICS_H

// Is there a way to avoid this include?
#include "../Types/Vector2.h"
#include "../Types/Vector3.h"

class Body
{
protected:
   bool mIsMoving;
   float mTime;
   float mTimeTotal;
   Vector3f mMoveDest;

protected:  
   Vector3f mWidth; // these vectors are zero based
   Vector3f mHeight;
   Vector3f mDepth;

public:  // protect these memvars and add gets
   Vector3f mPosition;
   Vector3f mVelocity;
   Vector3f mAcceleration;

public:
   // CTOR
   Body (int width, int height);
   Body (float x, float y, int width, int height);
   Body (Vector3f Pos, int width, int height);

   //Properties
   float GetPositionX () { return mPosition.x; }
   float GetPositionY () { return mPosition.y; }
   float GetPositionZ () { return mPosition.z; }
   Vector3f GetPosition() { return mPosition; }
   float GetVelocityX () { return mVelocity.x; }
   float GetVelocityY () { return mVelocity.y; }
   Vector3f GetVelocity() { return mVelocity; }
   float GetAccelerationX () { return mAcceleration.x; }
   float GetAccelerationY () { return mAcceleration.y; }
   Vector3f GetAcceleration() { return mAcceleration; }

   Vector3f GetWidthVector() { return mWidth; }
   float GetWidth() { return mWidth.x; }
   Vector3f GetHeightVector() { return mHeight; }
   float GetHeight() { return mHeight.y; }
   Vector3f GetDepthVector() { return mDepth; }
   float GetDepth() { return mDepth.z; }

   // Mothods
   void DebugPrint ();
   // Depreciated!
   void SetPosition (float x, float y, float z);
   void SetVelocity (float x, float y, float z);
   void SetAcceleration (float x, float y, float z);

   void SetPosition (const Vector3f& NewPos) { mPosition = NewPos; }
   void SetVelocity (const Vector3f& NewV) { mVelocity = NewV; }
   void SetAcceleration (const Vector3f& NewA) { mAcceleration = NewA; }

   void Integrate (float dt);
   void MoveTo (float x, float y, float z, float time);
};

#endif
