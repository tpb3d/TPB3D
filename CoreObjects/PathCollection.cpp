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
#include "Park.h"
#include "PathCollection.h"

PathCollection::PathCollection ()
{
}

PathCollection::~PathCollection( )
{
}

void PathCollection::Update (float dt, int tod)
{
   Pathway::PathwayIterator iPI;
   for (iPI = this->begin(); iPI != this->end(); iPI++)
   {
      Pathway* pPath = *iPI;
      pPath->Update (dt, tod);
   }
}

void PathCollection::AddPathway (Pathway* pPath)
{
   this->push_back (pPath);
}

void PathCollection::Draw ()
{
   Pathway::PathwayIterator iPI;
   for (iPI = this->begin(); iPI != this->end(); iPI++)
   {
      Pathway* pPath = *iPI;
      pPath->Draw ();
   }
}

void PathCollection::DrawSelectionTarget (bool bPathwaysOnly)

{
}

