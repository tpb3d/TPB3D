//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Strut class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/VPoint.h"
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "Strut.h"

Strut::Strut ()
:  TexturedStrip (3,Gfx::ImageManager::GetInstance()->GetTexture("basemetal.png",4), 0x98b0b0b0) //, ObjectFactory::TakeANumber())
{
    mDistance = 5; 
    mLength = 4;
}

Strut::~Strut (void)
{
}

void Strut::Draw()
{
   TexturedStrip::Draw();
}

void Strut::Render()
{
   sf::Vector3f tv1 = mV1;
   sf::Vector3f tv2 = mV2;
   AddPoint (tv1);
   AddPoint (tv2);
   tv1.z += 0.1f;
   tv2.z += 0.1f;
   AddPoint (tv1);
   AddPoint (tv2);
   tv1.x += 0.1f;
   tv2.x += 0.1f;
   AddPoint (tv1);
   AddPoint (tv2);
}
