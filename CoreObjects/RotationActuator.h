//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RotationActuator class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideActuater   Linear Motion Power Device.
      RideMotor      Rotation Motion Power Device.
*/

#pragma once
#include "ActuatorBase.h"

class RotationActuator : public ActuatorBase
{

public:
   RotationActuator(int ID );
   ~RotationActuator(void);
};
