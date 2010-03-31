//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Vendor class, sales base class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  Vendor - Base class of all the stalls, shops and restaurants

#pragma once
#include <string>
#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include "Pathway.h"

class PathCollection : public Pathway::PathwayVector
{
public:
   // ctor dtor
   PathCollection ();
   virtual ~PathCollection ();

protected:
   // local properies

public:
   void   AddPathway (Pathway* pPath);
   void Update (float dt, int tod);
   void Draw ();
   void DrawSelectionTarget (bool bPathwaysOnly);
};
