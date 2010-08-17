//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Strut class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/ObjectFactory.h"
#include "Strut.h"

Strut::Strut (float fAngle)
{
   mDistance = 5; 
   mLength = 4;
   mAngle = fAngle;
   mpGraphic = ObjectFactory::CreateTexturedStrip (3, "basemetal.png", 0x98b0b0b0);
}

Strut::Strut (float fAngle, ObjectBase* pBase)
{
   mDistance = 5; 
   mLength = 4;
   mAngle = fAngle;
   mpGraphic = pBase;
}

Strut::~Strut (void)
{
}

void Strut::Draw()
{
   mpGraphic->Draw();
}

void Strut::DrawSelectionTarget(int mode)
{
   mpGraphic->DrawSelectionTarget();
}

void Strut::Render()
{
   sf::Vector3f tv1 = mV1;
   sf::Vector3f tv2 = mV2;
   mpGraphic->AddPoint (tv1);
   mpGraphic->AddPoint (tv2);
   tv1.z += 0.1f;
   tv2.z += 0.1f;
   mpGraphic->AddPoint (tv1);
   mpGraphic->AddPoint (tv2);
   tv1.x += 0.1f;
   tv2.x += 0.1f;
   mpGraphic->AddPoint (tv1);
   mpGraphic->AddPoint (tv2);
}
