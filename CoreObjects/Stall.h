//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Vendor class, sales base class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

/*
      RideVendor        Assembly that is a feature support that extends out and usually supports a carriage.
      RideTelescopeVendor Vendor that has an extenstion that slides out to extend the Vendor up to 1.8 times its collapsed length.
*/

#pragma once
#include "Vendor.h"

class Stall : public Vendor
{

public:
   // ctor dtor
   Stall(int StallNo, int ID );
   ~Stall(void);
   // properties
   // get...()

   // Time Management Methods
   void Update (float dt, int timeOfDay);

   // Rendering methods
   void Draw ();
   void DrawSelectionTarget (bool bBaseOnly);

};
