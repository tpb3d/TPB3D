//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include "Pathway.h"
#include "Stall.h"
#include "Park.h"
#include "StallCollection.h"

StallCollection::StallCollection ()
{
}

StallCollection::~StallCollection( )
{
}

void StallCollection::Update (float dt, int timeOfDay)
{
   StallIterator iRI;
   for (iRI = this->begin(); iRI != this->end(); iRI++)
   {
      Stall* pStall = *iRI;
      pStall->Update (dt, timeOfDay);
   }
}

void StallCollection::AddStall (Stall* pStall)
{
   this->push_back (pStall);
}

Stall* StallCollection::FindStallByType (StallType st)
{
   StallIterator iSI;
   for (iSI = this->begin(); iSI != this->end(); iSI++)
   {
      Stall* pStall = *iSI;
      if (pStall->IsType (st) )
      {
         return pStall;
      }
   }
   return NULL;
}

void StallCollection::Draw ()
{
   StallIterator iRI;
   for (iRI = this->begin(); iRI != this->end(); iRI++)
   {
      Stall* pStall = *iRI;
      pStall->Draw ();
   }
}

void StallCollection::DrawSelectionTarget (bool bPathwaysOnly)

{
}

