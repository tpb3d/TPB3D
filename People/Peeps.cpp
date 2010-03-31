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

// Here lies all your people. The purpose of this class it to keep track of people.
// Everyone in your city will be here including non-residents of your Park(s).
// This is stritly the data storage collection of persons and where they are created and destroyed.

#include <list>
#include <iostream>
#include "Person.h"
#include "../Utility/GameException.h"

#include "Peeps.h"

Peeps* Peeps::minstance = NULL;

Peeps* Peeps::get_Instance()
{
   if (minstance == NULL)
   {
      minstance = new Peeps();
   }
   return minstance;
}

void Peeps::destroy() // clear out the city
{
   try
   {
      if (minstance != NULL)
      {
         delete minstance;
      }
      minstance = NULL;
   }
   catch ( GameException* ex )
   {
      minstance = NULL;
      throw ex;            // pass on app generated exception
   }
   catch (...)
   {
      throw new GameException( "Error in cleaning up the Citezens collection" );
   }
}

Peeps::Peeps()
{
}

Peeps::~Peeps()
{
   std::cout << "Cleaning up Peeps";
   try
   {
      std::list<Person *>::iterator i;
      for (i = mPeople.begin (); i != mPeople.end (); i++)
      {
         Person* peep = (*i);
         delete peep;
      }
   }
   catch (...)
   {
      throw new GameException( "Error in Citezens destructor" );
   }
}

// this update only needs to be called about once per second are so.
// no need to call it on every frame
void Peeps::Update (float dt)
{
   // TODO: implement life cycles
/*   std::list<C_Person *>::iterator i;
   for (i = m_People.begin (); i != m_People.end (); i++)
   {
      C_Person* peep = (*i);
   // look for dead people and remove when we get aging in.
   // look for lost people stuck in on rides, elevators etc.
   }*/
}

Person* Peeps::NewPerson()
{
   Location loc;
   Person* person = new Person( loc );
   mPeople.push_back (person);
   return person;
}

void Peeps::DestroyPerson( Person* person )
{
   std::list<Person *>::iterator i;
   for (i = mPeople.begin (); i != mPeople.end (); i++)
   {
      Person* peep = (*i);
      if (peep == person)
      {
         mPeople.remove(peep);
         delete peep;
      }
   }
}

size_t Peeps::GetPopulationForPark( int Park )
{
   int pop = 0;
   std::list<Person *>::iterator i;
   for (i = mPeople.begin (); i != mPeople.end (); i++)
   {
      Person* peep = (*i);
      // if(peep->get_Location().m_Park == Park )
      if (peep->get_Location().mPathway != 0)
         pop++;
   }
   return pop;
}
