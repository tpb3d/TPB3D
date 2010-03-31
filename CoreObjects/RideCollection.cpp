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
#include "Ride.h"
#include "Park.h"
#include "RideCollection.h"

RideCollection::RideCollection ()
{
}

RideCollection::~RideCollection( )
{
}

void RideCollection::Update (float dt, int timeOfDay)
{
   RideIterator iRI;
   for (iRI = this->begin(); iRI != this->end(); iRI++)
   {
      Ride* pRide = *iRI;
      pRide->Update ((int)dt);
   }
}

void RideCollection::AddRide (Ride* pRide)
{
   this->push_back (pRide);
}

Ride* RideCollection::FindRideByType (RideType rt)
{
   RideIterator iRI;
   for (iRI = this->begin(); iRI != this->end(); iRI++)
   {
      Ride* pRide = *iRI;
      if (pRide->IsType (rt) )
      {
         return pRide;
      }
   }
   return NULL;
}

Ride* RideCollection::FindRideByName (const char *pszName)
{
   RideIterator iRI;
   for (iRI = this->begin(); iRI != this->end(); iRI++)
   {
      Ride* pRide = *iRI;
      if (_stricmp(pRide->GetRideName(), pszName) == 0)
      {
         return pRide;
      }
   }
   return NULL;
}

void RideCollection::Draw ()
{
   RideIterator iRI;
   for (iRI = this->begin(); iRI != this->end(); iRI++)
   {
      Ride* pRide = *iRI;
      pRide->Draw ();
   }
}

void RideCollection::DrawSelectionTarget (bool bFrameOnly)
{
//   mRoutes.DrawSelectionTarget(); do these later
}

