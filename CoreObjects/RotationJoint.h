//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RotationJoint class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "RideNode.h"

class RotationJoint : public RideNode
{
   float  mAngle;
   float  mYAngle;
   float  mWeight;
   float  mDistance; // radius of ride is spining
   float  mLength;   // current length of cable (some rides will change this
   sf::Vector3f mV1;

public:
   RotationJoint ();
   ~RotationJoint (void);

   void SetPoint (sf::Vector3f vp) { mV1 = vp; }
   void SetPosition (sf::Vector3f v) { mvPosition = v; }
   void SetYAngle (float y) { mYAngle = y; }
   void SetWeight (float wgt) { mWeight = wgt; }
   void SetDistance (float dis) { mDistance = dis; } // radius of ride is spining
   void SetLength (float len) { mLength = len; }     // current length of cable (some rides will change this

   void SetForce(float Velocity);

   virtual void Update(int dt);
   virtual void Render();
   virtual void Draw();
   virtual void DrawSelectionTarget(int mode);
//   virtual ObjectBase* Clone( ) { return new CableHingeJoint(); }
};
