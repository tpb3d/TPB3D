//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  CableSusp class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/VPoint.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectFactory.h"
#include "../Graphics/TexturedStrip.h"
#include "CableSusp.h"

CableSusp::CableSusp ()
:  Body (0, 1)
{
    mAngle = 0;
    mWeight = 500;
    mDistance = 5; 
    mLength = 4;
    mMax = 20;
    mpGraphic = ObjectFactory::CreateTexturedStrip (2, "basemetal.png", 0x98b0b0b0);
    SetVelocity(0,0,0);
    SetAcceleration(0,0,0);
}

CableSusp::~CableSusp (void)
{
}

void CableSusp::SetDirection(float Velocity)
{
   if (mVelocity.y != Velocity)
   {
      SetVelocity (0,Velocity,0);
      if (Velocity < 0)
      {
         this->SetDistance(-mMax);
      }
      else if (Velocity > 0)
      {
         this->SetDistance(mMax);
      }
      else
      {
         this->SetDistance(0);
      }
   }
}

void CableSusp::Update(int dt)  // add the other physics beside centrifugal
{
   static int wait = 10;
   if(wait < 1)
   {
      Integrate(1.0);
      wait = dt;
   }
   else
   {
      wait--;
   }
}

void CableSusp::Draw()
{
   mpGraphic->Draw();
   RideNode::Draw(); 
}

void CableSusp::Render()
{
   sf::Vector3f tv = mV1;
   mpGraphic->AddPoint (tv);
   tv.z += 0.1f;
   mpGraphic->AddPoint (tv);
   tv = mV2;
   mpGraphic->AddPoint (tv);
   tv.y += 0.05f;
   tv.z += 0.05f;
   mpGraphic->AddPoint (tv);
}
