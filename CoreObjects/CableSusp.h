//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  CableHinge class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once
#include "RideNode.h"
//#include "../Physics/PendulumPhysics.h"
#include "../Physics/MotionPhysics.h"

class ObjectBase;

class CableSusp : public RideNode, public Body//, public PendulumPhysics
{
   float  mAngle;
   float  mWeight;
   float  mDistance; // radius of ride this is suspended from
   float  mLength;   // current length of cable depending on the winch driving it.
   ObjectBase* mpGraphic;
   sf::Vector3f mV1;
   sf::Vector3f mV2;
   float mMax;

public:
   CableSusp();
   ~CableSusp(void);

   void SetPosition (sf::Vector3f v) { mvPosition = v; }
   void SetWeight (float wgt) { mWeight = wgt; }
   void SetDistance (float dis) { mDistance = dis; } // radius of ride is spining
   void SetLength (float len) { mLength = len; }     // current length of cable (some rides will change this

   void SetDirection(float Velocity);
   void SetMax (float mx) { mMax = mx; }

   virtual void Update(int dt);
   virtual void Render();
   virtual void Draw();
//   virtual ObjectBase* Clone( ) { return new CableSusp(); }
};
