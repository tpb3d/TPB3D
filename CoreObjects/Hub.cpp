//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Hub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <string>

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/vector3.h"
#include "../Graphics/VPoint.h"
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedMesh.h"
#include "Hub.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace CoreObjects
{
   const short MinSides = 3;
   const short MaxSides = 36;
   const int   kVertCount = 8;
   float kVerts[8][3] =
   {
      {-2,0.5f,-3},
      {-2,0.5f, 3},
      {-2,0.8f,-3},
      {-2,0.8f, 3},
      { 2,0.8f,-3},
      { 2,0.8f, 3},
      { 2,0.5f,-3},
      { 2,0.5f, 3}
   };
}

Hub::Hub (float height, short sides, const char* TexName)
{
   mTexName = TexName;
   mHeight = height;
   mSides = sides;
   mSections = 2; // some rides may have more
   mRadii[0] = 2;
   mRadii[1] = 1.9f;
   mpGraphic = new TexturedMesh (sides,2,Gfx::ImageManager::GetInstance()->GetTexture(TexName, 3), 0x98b0b0b8, ObjectFactory::TakeANumber());
}

Hub::~Hub(void)
{
   if (mpGraphic != NULL)
   {
      delete mpGraphic;
   }
}

void Hub::Draw()
{
   mpGraphic->Draw();
   RideNode::Draw();
}

void Hub::Render()
{
   using namespace CoreObjects;
   double dRad = 0.0;
   double dDeg = 360.0/ (mSides-1);
   for( int idx = 0; idx < mSides; ++idx )
   {
      double dTheta = M_PI/180 * dRad;
      CVPoint pt (cos(dTheta) * this->mRadii[0], 0, sin(dTheta)* this->mRadii[0]);
      sf::Vector3f temp = pt.GetVector3f();
      mpGraphic->AddPoint (temp);
      dRad += dDeg;
      pt = CVPoint (cos(dTheta) * this->mRadii[1], mHeight, sin(dTheta)* this->mRadii[1]);
      temp = sf::Vector3f (pt.GetVector3f());
      mpGraphic->AddPoint (temp);
   }
}

void Hub::DrawSelectionTarget()
{
}

void Hub::Update(int dt)
{
   RideNode::Update (dt);
}


//ObjectBase* Hub::Clone( )
//{
//   Hub* pHub = new Hub(mHeight, mSides, mTexName.c_str());
//   return pHub;
//}

void Hub::IncreseSides()
{
   if (mSides < CoreObjects::MaxSides)
   {
      mSides++;
      Render();
   }
}

void Hub::DecreseSides()
{
   if (mSides > CoreObjects::MinSides)
   {
      mSides--;
      Render();
   }
}

void Hub::Load(SerializerBase& ser)
{
   // need to build a factory for this
   //RideNodeSection* pRideNodeSection = new RideNodeSection();
   //pRideNodeSection->Load(ser);
}

void Hub::Save(SerializerBase& ser)
{
   ser.Add("type", "Hub");
   RideNode::Save(ser);
}