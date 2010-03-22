//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Deck class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
//
// Section or sections that make up a surface that can stood or leaned on in rides
// See platform for stations and ramps

#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/Vector3.h"
#include "../Graphics/VPoint.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/ObjectFactory.h"
#include "Deck.h"

#define _USE_MATH_DEFINES
#include <math.h>

Deck::Deck (float innerRadius, float outerRadius, short sides, const char* TexName)
{
   mTexName = TexName;
   mSides = sides;
   mSections = 2; // some rides may have more
   mRadii[0] = innerRadius;
   mRadii[1] = outerRadius;
   mpGraphic = ObjectFactory::CreateTexturedStrip (sides, TexName, 0x98b0b0b8);
}

Deck::Deck (float innerRadius, float outerRadius, short sides, ObjectBase* pGfx)
:  mpGraphic (pGfx)
{
   mTexName = "";
   mSides = sides;
   mSections = 2; // some rides may have more
   mRadii[0] = innerRadius;
   mRadii[1] = outerRadius;
}

Deck::~Deck(void)
{
   if (mpGraphic != NULL)
   {
      delete mpGraphic;
   }
}

void Deck::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y, mvPosition.z );
   mpGraphic->Draw();
   RideNode::Draw();
   glPopMatrix();
}

void Deck::Render()
{
//   using namespace CoreObjects;
   double dRad = 0.0;
   double dDeg = 360.0/ (mSides-1);
   for( int idx = 0; idx < mSides; ++idx )
   {
      double dTheta = M_PI/180 * dRad;
      CVPoint pt (cos(dTheta) * this->mRadii[0], 0, sin(dTheta)* this->mRadii[0]);
      sf::Vector3f temp = pt.GetVector3f();
      mpGraphic->AddPoint (temp);
      dRad += dDeg;
      pt.Set(cos(dTheta) * this->mRadii[1], 0, sin(dTheta)* this->mRadii[1]);
      temp = sf::Vector3f (pt.GetVector3f());
      mpGraphic->AddPoint (temp);
   }
}

void Deck::DrawSelectionTarget()
{
}

void Deck::Update(int dt)
{
   RideNode::Update (dt);
}


//ObjectBase* Deck::Clone( )
//{
//   Deck* pHub = new Deck(mRadii[0], mRadii[1], mSides, mTexName.c_str());
//   return pHub;
//}

namespace CoreObjects
{
   short MinSides;
   short MaxSides;
   int   kVertCount;
}

void Deck::IncreseSides()
{
   if (mSides < CoreObjects::MaxSides)
   {
      mSides++;
      Render();
   }
}

void Deck::DecreseSides()
{
   if (mSides > CoreObjects::MinSides)
   {
      mSides--;
      Render();
   }
}

void Deck::Load(SerializerBase& ser)
{
   // need to build a factory for this
   //RideNodeSection* pRideNodeSection = new RideNodeSection();
   //pRideNodeSection->Load(ser);
}

void Deck::Save(SerializerBase& ser)
{
   ser.Add("type", "Deck");
   RideNode::Save(ser);
}
