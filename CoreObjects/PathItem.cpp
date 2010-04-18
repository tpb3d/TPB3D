//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Author Level5
//  Licensed according to the GPL v3.0
//
//  PathItem class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "PathItem.h"

PathItem::PathItem(Pathway *parent, float alignment, ItemHeading heading)
{
   mpPath = parent;
   mHeading = heading;
   mAlignment = alignment;

   double lz = +sin( -(parent->GetRotation().y / 57.29577851) );
   double lx = -cos( -(parent->GetRotation().y / 57.29577851) );

   if(heading == IH_Right) {
      loc = Vector3f( parent->GetX() + (parent->GetWidth()*(lz)) + (alignment*(-lx)), parent->GetY() + 1, parent->GetZ() + (parent->GetWidth()*lx) + (alignment*lz) );
      rot = Vector3f( 0, parent->GetRotation().y + 180, 0 );
   }

      if(heading == IH_Left) {
      loc = Vector3f( parent->GetX() + (-parent->GetWidth()*(lz)) + (alignment*(-lx)), parent->GetY() + 1, parent->GetZ() + (-parent->GetWidth()*lx) + (alignment*lz) );
      rot = Vector3f( 0, parent->GetRotation().y, 0 );
   }
}

PathItem::~PathItem()
{
   //dtor
}

void PathItem::SetHeading( ItemHeading heading ) {
}
