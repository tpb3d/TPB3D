//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
//  Ride Base, this part is single or the end node in a ride assembly

#pragma once
#include "../Graphics/ObjectBase.h"

struct PartGuide;

class RideBase : public ObjectBase
{

public:
   RideBase(int ID );
   ~RideBase(void);
   void SetupGuide(const PartGuide& guide);
   void Preset( float fDefPitch, float fDistance, float fDegRotation, float fRadius, float fPitchRadius, float fRoll);
   void Draw();
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
