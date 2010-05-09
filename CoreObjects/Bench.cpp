//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Author Level5
//  Licensed according to the GPL v3.0
//
//  ParkBench class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "Bench.h"

#include "../People/Person.h"
#include "../Graphics/ObjectFactory.h"

Bench::Bench(ObjectNode *node, Pathway *path, float alignment, ItemHeading heading, unsigned short seats)
: PathItem(path, alignment, heading)
, mQueue (path)
{
   mpGraphic = NULL;
   if(node)
   {
      mpGraphic = node->Clone();

      float fLoc[] = { loc.x, loc.y, loc.z };
      float fRot[] = { rot.x, rot.y, rot.z };
      mpGraphic->Move (fLoc);
      mpGraphic->SetRotation(fRot);
   }
}

Bench::~Bench()
{
   if (mpGraphic)
   {
      delete mpGraphic;
   }
}

void Bench::Draw()
{
   mpGraphic->Draw();
}

void Bench::AddPerson (Person* pPeep)
{
   if(mPeepList.size() <= mSeats) {
      mPeepList.push_back(pPeep);
      pPeep->SetActivity( Person::AS_Sitting);
   } else {
      pPeep->SetActivity( Person::AS_None);
   }
}

void Bench::RemovePerson (Person* pPeep)
{
   mPeepList.remove(pPeep);
}
