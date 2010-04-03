//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/Texture.h"
#include "../Graphics/Image.h"
#include "../Graphics/ObjectTree.h"
#include "../People/Person.h"
#include "Stall.h"

Stall::Stall (int StallNo, int ID)
:  Vendor (ID)
{
    mpQueue = new PersonQueue();
   mpGraphic = NULL;
   mpQueue = new PersonQueue();
}

Stall::Stall(int StallNo, int ID, StallType st)
:  Vendor (ID)
{
   mStallType = st;
   mpQueue = new PersonQueue();
   mpGraphic = NULL;
   mpQueue = new PersonQueue();
}

Stall::~Stall( )
{
   delete mpQueue;
}

void Stall::AddPerson (Person* pPeep)
{
   mpQueue->AddPerson(pPeep);
}

void Stall::RemovePerson (Person* pPeep)
{

   mpQueue->RemovePerson(pPeep);
}

void Stall::ServeNextPerson (void)
{
   Person* pPeep = mpQueue->TakeNextPerson();
   if (pPeep != NULL)
   {
      // TakeOrder;
      // Serve or Reject
      pPeep->SetActivity (Person::AS_Eating);   // this is just some interaction
      pPeep->SetCurrentState (Person::CS_Walking);
   }
}

void Stall::Update (float dt, int timeOfDay)
{
   static int delay = 5; // playing physics

   if( --delay > 0 )
   {
      return;
   }
   ServeNextPerson();
   if (mpQueue->Count() > 10)
      delay = 3;
   else
      delay = 5;
}

void Stall::Draw ()
{
   ObjectNode::Draw();
}

void Stall::DrawSelectionTarget (bool bBaseOnly)

{
//   draw select geometry
}
