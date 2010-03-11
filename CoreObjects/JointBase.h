//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  JointBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once
#include "../Graphics/ObjectBase.h"

class JointBase : public ObjectBase
{
   // float mMaxAngle;
   // float mMinAngle;
public:
   JointBase(int ID, int points ) : ObjectBase(points, ID) {}
   virtual ~JointBase(void) {}
};
