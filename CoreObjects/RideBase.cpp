//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <string>
#include "RideBase.h"
#include "../Storage/SerializerBase.h"

RideBase::RideBase( int ID )
:  ObjectBase( 0, ID)
{
}

RideBase::~RideBase(void)
{
}

void RideBase::Draw()
{
}

void RideBase::Load(SerializerBase& ser)
{
}

void RideBase::Save(SerializerBase& ser)
{
   ser.Add("type", "Track");
   int* pI = (int*)mRGBA[0];
   ser.Add("RGBA", *pI);
   ser.Add("ID", mID);
}