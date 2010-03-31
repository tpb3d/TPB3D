//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  HingeJoint class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once
#include "JointBase.h"

class HingeJoint : public JointBase
{

public:
   HingeJoint(int ID, int points );
   ~HingeJoint(void);
   virtual void Render() {};
   virtual void Draw() {};
   virtual void DrawSelectionTarget() {}; // base can't draw
   //virtual JointBase* Clone( ) {};
};
