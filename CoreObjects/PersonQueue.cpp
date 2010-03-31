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

// head and tail queue. People in and out while waiting for rides, trams, rail and buses.
#include <iostream>
#include "../People/Person.h"
#include "PersonQueue.h"

PersonQueue::PersonQueue()
{
}

PersonQueue::~PersonQueue()
{
}

void PersonQueue::AddPerson (Person* person)
{
   mQueue.push(person);
   if( mHeadIndex >= mCapacity )
   {
      mHeadIndex = 0;
   }
}

bool PersonQueue::RemovePerson (Person* person)
{
   // iterate and remove one
   return false;
}

Person* PersonQueue::TakeNextPerson ()
{
   Person* person = 0;
   if (!mQueue.empty())
   {
      person = mQueue.front();
      mQueue.pop();
   }
   return person;
}

size_t PersonQueue::Count()  // how many people in line
{
   return mQueue.size();
}

void PersonQueue::Update()
{
}

void PersonQueue::Draw (int vx, int vy)
{
/*   for( unsigned int x = 0; x < mpQueue.size(); ++x )
   {
      Person* peep = mpQueue[x];
      peep->Draw(vx,vy);
   }*/
}
