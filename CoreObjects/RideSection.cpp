//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideSection class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "CamPath.h"
#include "RideSection.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"

const char* RideSection::codes = "SPCX";

RideSection::RideSection()
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
{
   mPartsCount = 0;
   mMaxParts = 0;
   mpBaseParts = NULL;
   Clear();
}

RideSection::~RideSection(void)
{
   Clear();
}

void RideSection::Clear()
{
   try
   {
      for( int ix = 0; ix < mPartsCount; ++ix )
      {
         delete mpBaseParts[ix];
      }
      mPartsCount = 0;
      delete [] mpBaseParts;
      mpBaseParts = NULL;
   }
   catch( ... )
   {
   }
   mSectionFormat = SF_Straight;
   mfDegPitch = 0;
   mfDistance = 0;
   mfDegRotation = 0;
   mfRadius = 0;
   mfPitchRadius =0;
   mfRoll = 0;
}
void RideSection::Create(int count)
{
   mpBaseParts = new ObjectBase*[count];
}

void RideSection::Preset( float fDegPitch, float fDistance, float fDegRotation, float fRadius, float fPitchRadius, float fRoll)
{
   mfDegPitch = fDegPitch;
   mfDistance = fDistance;
   mfDegRotation = fDegRotation;
   mfRadius = fRadius;
   mfPitchRadius = fPitchRadius;
   mfRoll = fRoll;
}


void RideSection::AddSection( ObjectBase* pGLBase )
{
   mpBaseParts[mPartsCount++] = pGLBase;
}

void RideSection::Draw()
{
   for( int ix = 0; ix < mPartsCount; ++ix )
   {
      mpBaseParts[ix]->Draw();
   }
}

void RideSection::Load(SerializerBase& ser)
{
}

void RideSection::Save(SerializerBase& ser)
{
   ser.Add("Type", "RideSection");
   ser.Add("ID", mID);
   ser.Add("Format", codes[mSectionFormat]);
   ser.Add("DegPitch", mfDegPitch);
   ser.Add("Distance", mfDistance);
   ser.Add("DegRotation", mfDegRotation);
   ser.Add("Radius", mfRadius);
   ser.Add("PitchRadius", mfPitchRadius);
   ser.Add("Roll", mfRoll);

}
