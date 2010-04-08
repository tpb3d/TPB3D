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
