//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  ActuatorBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once
#include "../Graphics/ObjectBase.h"

class ActuatorBase : public ObjectBase
{
   // float mRatio;  // gearing torque
   // float speed;   // loaded speed, too much detail to deal with unloaded speed
public:
   ActuatorBase(int ID ) : ObjectBase(0,ID) {}
   virtual ~ActuatorBase(void) {}
};
