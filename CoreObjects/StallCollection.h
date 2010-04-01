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

#include "stall.h"

typedef std::vector<Stall*>::iterator StallIterator;
typedef std::vector<Stall*> StallVector;
enum StallType;

class StallCollection : public StallVector
{
public:
   // ctor dtor
   StallCollection ();
   virtual ~StallCollection ();

protected:
   // local properies

public:
   void   AddStall (Stall* pStall);
   Stall* FindStallByType (StallType st);
   void Update (float dt, int timeOfDay);
   void Draw ();
   void DrawSelectionTarget (bool bPathwaysOnly);
};
