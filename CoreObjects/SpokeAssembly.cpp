//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  SpokeAssembly class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <string>
#include "SpokeAssembly.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include "Arm.h"

class Arm;

namespace CoreObjects
{
   const short MinSides = 3;
   const short MaxSides = 36;
}

SpokeAssembly::SpokeAssembly (float height, short spokes)
{
   mHeight = height;
   mSpokes = spokes;
   Render();
}

SpokeAssembly::~SpokeAssembly(void)
{
}

void SpokeAssembly::Render()
{
   // use a factory to build the required parts time the number needed
   Clear();
   for (int ix = 0; ix < mSpokes; ++ix)
   {
      Arm* pArm = new Arm(ix, 1, 1, 10, 360.0f/mSpokes * ix);
      AddNode (pArm);
   }
}

void SpokeAssembly::IncreseSpokes()
{
   if (mSpokes < CoreObjects::MaxSides)
   {
      mSpokes++;
      Render();
   }
}

void SpokeAssembly::DecreseSpokes()
{
   if (mSpokes > CoreObjects::MinSides)
   {
      mSpokes--;
      Render();
   }
}

void SpokeAssembly::Load(SerializerBase& ser)
{
   // need to build a factory for this
   //RideNodeSection* pRideNodeSection = new RideNodeSection();
   //pRideNodeSection->Load(ser);
}

void SpokeAssembly::Save(SerializerBase& ser)
{
   ser.Add("type", "RideNode");
   RideNode::Save(ser);
}
