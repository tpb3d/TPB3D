//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  WheelDrive class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "ActuatorBase.h"

class WheelDrive : public ActuatorBase
{
   ObjectBase* mpGraphic;
// float fWheelDiameter;
public:
   WheelDrive(int ID );
   ~WheelDrive(void);
};
