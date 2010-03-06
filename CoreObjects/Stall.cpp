//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/Texture.h"
#include "../Graphics/Image.h"
#include "../Graphics/ObjectTree.h"
#include "Stall.h"

Stall::Stall (int StallNo, int ID)
:  Vendor (ID)
{
}

Stall::~Stall( )
{
}

void Stall::Update (float dt, int timeOfDay)
{
   static int delay = 5; // playing physics

   if( --delay > 0 )
   {
      return;
   }
   delay = 3;
}

void Stall::Draw ()
{
//   Draw the graphics
}

void Stall::DrawSelectionTarget (bool bBaseOnly)

{
//   draw select geometry
}
