//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RotationHub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

// motor drive 
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
#include "RotationHub.h"

RotationHub::RotationHub (int ID, float height, short sides, const char* TexName)
:  Hub (height, sides, TexName)
,  RotationPhysics (0, 0.1f, 2000.0f, 1000.0f)
{
   mIdle = 10;
   mRun = 0;
   mvPosition.x = 0;
   mvPosition.y = 12;
   mvPosition.z = 0;
}

RotationHub::~RotationHub(void)
{
}

void RotationHub::Update(int dt)
{
   if( mRun > 0)
   {
      mRun--;
      mIdle = 0;
      Integrate ((float)dt);
      mvAngle.y = mPosition;
   }
   else if( mIdle > 0)
   {
      mIdle--;
      Integrate ((float)dt);
      mvAngle.y = mPosition;
   }
   else
   {
      if(this->mVelocity > 0)
      {
         SetDestinVelocity( 0 );
         mIdle = 300;
      }
      else
      {
         SetDestinVelocity (90);
         mIdle = 600;
      }
   }
}
