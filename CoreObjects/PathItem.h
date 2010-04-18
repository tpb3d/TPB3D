//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Object Node class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#ifndef PATHITEM_H
#define PATHITEM_H

#include "CoreBase.h"
#include "Pathway.h"

class PathItem : public CoreBase
{
   public:
      enum ItemHeading {
         IH_Right = 0,
         IH_Left,
         IH_Up,
         IH_Down
      };

   protected:
      Pathway *mpPath;
      ItemHeading mHeading;
      float mAlignment;

      Vector3f loc;
      Vector3f rot;

   public:
      PathItem(Pathway *parent, float alignment, ItemHeading heading);
      ~PathItem();

      void SetAlignment(float align) { mAlignment = align; }
      void SetHeading( ItemHeading heading );

   private:

};

#endif // PATHITEM_H
