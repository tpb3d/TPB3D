//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  LiftArm class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideActuater   Linear Motion Power Device.
      RideMotor      Rotation Motion Power Device.
*/

#pragma once
#include "RideNode.h"
#include "../Physics/ServoPhysics.h"

class ObjectBase;

class LiftArm : public RideNode, public ServoPhysics
{
   int mIdle;
   int mRun;
   int mSides;
   //float mDesiredAngle;
   float mWidth;
   float mLength;
   ObjectBase* mpGraphic;

public:
   LiftArm(int ID, float length, float width, const char* TexName );
   ~LiftArm(void);
   void SetDesiredAngle (float ang) { mDesiredAngle = ang; }
   void Render();
   void Update(int dt);
   void Draw ();
};
