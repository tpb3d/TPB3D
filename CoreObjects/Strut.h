//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Strut class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideStrut      Interconnect or Structural element
      TelscopingStrut
*/

#pragma once
#include "RideNode.h"

class ObjectBase;

class Strut : public RideNode
{
   float  mDistance;
   float  mLength;   // current length of cable (some rides will change this
   sf::Vector3f mV1;
   sf::Vector3f mV2;
   ObjectBase* mpGraphic;

public:
   Strut();
   ~Strut(void);
   void SetPoints (sf::Vector3f v1, sf::Vector3f v2) { mV1 = v1; mV2 = v2; }
   void SetPosition (sf::Vector3f v) { mvPosition = v; }
   void SetDistance (float dis) { mDistance = dis; } // radius of ride is spining
   void SetLength (float len) { mLength = len; }     // current length of cable (some rides will change this

   void Draw();
   void DrawSelectionTarget(int mode);
   void Render();
};
