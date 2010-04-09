//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideController class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
//  Ride Controller Unit, provides up tree support to start, stop and control speed of ride parts

#pragma once
#ifndef _RideController
#define _RideController

#include "../Graphics/ObjectBase.h"

class RotationPhysics;
class ServoPhysics;
class RideController
{
   float mSpeed;
protected:
   RotationPhysics* pPrimaryRotation;
   RotationPhysics* pSecondaryRotation;
   ServoPhysics* pPrimaryServo;
   ServoPhysics* pSecondaryServo;

public:
   RideController(int ID );
   ~RideController(void);

   void Register (RotationPhysics* pRP);
   void Register (ServoPhysics* pSP);
   void Unregister (RotationPhysics* pRP);
   void Unregister (ServoPhysics* pSP);

   void Start ();
   void Stop ();
   void Sequence (int no);
   void SetCycles (int cycles);
   void SetSpeed (float speed);
   void SetPosition ( int pos);
   void LockRestraints ();
   void UnlockRestraints ();

   bool IsStopped();
   bool IsRunning();
   bool IsRestraintsLocked ();
   bool IsRestraintsUnlocked ();
   float CurrentSpeed ();
   int  CurrentPosition ();
};

#endif // _RideController
