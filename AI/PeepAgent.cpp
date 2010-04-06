/*   This file is part of Theme Park Builder 3D The Game.
*
*   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.

*   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "../People/Person.h"
#include "../CoreObjects/Routes.h"
#include "../CoreObjects/PersonQueue.h"
#include "../CoreObjects/RouteBase.h"
#include "../CoreObjects/Building.h"
#include "../CoreObjects/Park.h"
#include "../Utility/GameException.h"
#include "../People/Peeps.h"
#include "RideAgent.h"

#include "PathAgent.h"
#include "PeepAgent.h"

PeepsAgent::PeepsAgent (Park& Park) // use a Park agent for multiple Parks
      :  mPark (Park)
{

}

PeepsAgent::~PeepsAgent ()
{
}

void PeepsAgent::Update (float dt, int tod)
{
   // Shouldn't Peeps be a member within each Park? Supposedly you would want this seperate.
   Peeps* Peeps = Peeps::get_Instance(); // the Peeps object that holds the people collection

   if( Peeps->GetPopulation() < 1)
   {
      Person* peep = Peeps->NewPerson();
      mPark.EnterPark (peep);

      Peeps->Update( dt, (float)tod);
   }

//   if ( (rand() % 4) == 3 )  // TODO: need a better spawn mechanism, raised to 100
//   {
//      //Location loc; // all zeros
//   {
//      Person* peep = Peeps->NewPerson();
//   }

   std::list<Person *>::iterator i;
   std::list<Person *>& persons = Peeps->get_Persons(); // get the persons collection.

   // TODO: Need to create a better interface that provides a clear persons iteration.
   for (i = persons.begin (); i != persons.end (); i++)
   {
      Person* peep = (*i);
      peep->Update( tod );
      Path& workPath = peep->get_WorkPath(); // for now just doing work
      //  TODO: case statement from hell, on the refactor list
      // use a state engine to replace this
        switch ( peep->GetActivity() )
        {
            case Person::AS_LookingForFood:

               cout << "Peep is looking for food" << endl;

               Stall *stall;
               stall = mPark.FindStallByType (ST_Food);
               if(stall)
               {
                  stall->AddPerson(peep);
                  stall->Update (dt, tod);
               } else {
                  cout << "Couldn't find a food stall " << endl;
               }

            break;

            case Person::AS_LookingForDrink:
            break;

            case Person::AS_LookingForRide:
               cout << "Peep is looking for a ride" << endl;

               Ride* pRide;
               pRide = mPark.FindRideByName("Barn Stormers");
               if (pRide != NULL)
               {
                  pRide->AddPerson (peep);
               } else {
                  peep->SetActivity(Person::AS_None);
               }
            break;

            case Person::AS_LookingForATM:
            break;

            case Person::AS_GoingHome:
               Peeps->DestroyPerson(peep); // Peep is going home, just kill the peep for now.
            break;


            default:
            // do something
            break;   // microsoft requires this break
        }
   }
}
