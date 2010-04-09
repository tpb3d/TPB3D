//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideController class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Physics/RotationPhysics.h"
#include "../Physics/ServoPhysics.h"
#include "RideController.h"
#include "../Storage/SerializerBase.h"

RideController::RideController( int ID )
{
   mSpeed = 30;
   pPrimaryRotation = NULL;
   pSecondaryRotation = NULL;
   pPrimaryServo = NULL;
   pSecondaryServo = NULL;
}

RideController::~RideController(void)
{
}

void RideController::Register (RotationPhysics* pRP)
{
   if( pPrimaryRotation == NULL)
   {
      pPrimaryRotation = pRP;
   }
   else
   {
      pSecondaryRotation = pRP;  // only two allowed
   }
}

void RideController::Register (ServoPhysics* pSP)
{
   if( pPrimaryServo == NULL)
   {
      pPrimaryServo = pSP;
   }
   else
   {
      pSecondaryServo = pSP;
   }
}

void RideController::Unregister (RotationPhysics* pRP)
{
   if( pPrimaryRotation == pRP)
   {
      pPrimaryRotation = NULL;
   }
   if( pSecondaryRotation == pRP)
   {
      pSecondaryRotation = NULL;
   }
}

void RideController::Unregister (ServoPhysics* pSP)
{
   if (pPrimaryServo == pSP)
   {
      pPrimaryServo = NULL;
   }
   if (pSecondaryServo == pSP)
   {
      pSecondaryServo = NULL;
   }
}

void RideController::Start ()
{
   if (pPrimaryRotation)
   {
      pPrimaryRotation->SetDestinVelocity (mSpeed);
      pPrimaryRotation->Integrate (1.0f);
   }
}

void RideController::Stop ()
{
   if (pPrimaryRotation)
      pPrimaryRotation->SetDestinVelocity (0);
}

void RideController::Sequence (int no)
{
}

void RideController::SetCycles (int cycles)
{
}

void RideController::SetSpeed (float speed)
{
   mSpeed = speed;
}

void RideController::SetPosition ( int pos)
{
}

void RideController::LockRestraints ()
{
}

void RideController::UnlockRestraints ()
{
}

bool RideController::IsStopped()
{
   if (pPrimaryRotation)
      return (pPrimaryRotation->Velocity () == 0);
   return false;
}

bool RideController::IsRunning()
{
   if (pPrimaryRotation)
      return (pPrimaryRotation->Velocity () != 0);
   return false;
}

bool RideController::IsRestraintsLocked ()
{
   return false;
}

bool RideController::IsRestraintsUnlocked ()
{
   return false;
}

float RideController::CurrentSpeed ()
{
   return pPrimaryRotation->Velocity ();
}

int  RideController::CurrentPosition ()
{
   return 0;
}
