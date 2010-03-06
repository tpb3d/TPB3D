//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  ride Arm class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideArm        Assembly that is a feature support that extends out and usually supports a carriage.
      RideTelescopeArm Arm that has an extenstion that slides out to extend the arm up to 1.8 times its collapsed length.
*/

#pragma once
#include "RideNode.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedMesh.h"

class Arm : public RideNode, public TexturedMesh
{
   int   mArmID;
   float mOffset;  // from center axis
   float mDepth;   // depth of the arm web (height at hub)
   float mLength;  // Projection from hub
   float mAngle;
public:
   Arm (int ArmID, float offset, float depth, float length, float angle);
   ~Arm (void);

   virtual void Render();
   virtual void Draw();
   virtual void DrawSelectionTarget(); // base can't draw
   virtual ObjectBase* Clone( );
};
