//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  WobbleHub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideActuater   Linear Motion Power Device.
      RideMotor      Rotation Motion Power Device.
*/

#pragma once
#ifndef _WobbleHub
#define _WobbleHub

#include "Hub.h"
#include "../Physics/RotationPhysics.h"

class RideController;
class ObjectBase;

class WobbleHub : public Hub, public RotationPhysics
{
   int mIdle;
   int mRun;
   float mDesiredSpeed;
protected:
   RideController* mpRCUnit;
   ObjectBase* mpGraphic;

public:
   WobbleHub(RideController* pRCU, int ID, float height, short sides, const char* TexName );
   WobbleHub(RideController* pRCU, int ID, float height, short sides, ObjectBase* pGfx );
   ~WobbleHub(void);

   void SetYPosition(float y) { mvPosition.y = y; }
   void SetDesiredSpeed (float ds) { mDesiredSpeed = ds; }
   void Render();
   void Update(int dt);
   void Draw ();
};
#endif // _WobbleHub
