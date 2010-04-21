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
#include "../Utility/GameException.h"

PathFind::PathFind(Person *peep)
{
   mPeep = peep;
   mStack = new stack<Pathway* >;
}

bool PathFind::Calculate(Pathway *dest)
{
   iter = 0;
   mDest = dest;
   mFound = false;
   start = mPeep->GetPathway();

   path.clear();
   Interpolation.clear();

   for(unsigned int i = 0; i < start->GetConnections().size(); i++)
   {
      Pathway *p = start->GetConnections().at(i);

      //cout << "Finding Connections" << endl;
      if( Find(p, start) )
      {
         //cout << "Found" << endl;
         if(!mStack->empty())
         {
            while (true)
            {
               //cout << "Adding" << endl;
               path.insert ( path.begin(), mStack->top() );
               mStack->pop();

               if(mStack->empty()) break;
            }
         }

         path.insert ( path.begin(), p );
         mFound = true;
         break;
      }
   }

   if(mFound)
   {

      path.insert ( path.begin(), start );
      path.push_back(mDest);

      // Build interpolation path
      for(unsigned int i = 0; i < path.size(); i++)
      {
         Vector3f d;
         Vector3f v1;

         if(i+1 > path.size()-1 ) break;

         Pathway *p1 = path.at(i);
         Pathway *p2 = path.at(i+1);

         d.x = p1->GetX()-p2->GetX();
         d.y = p1->GetY()-p2->GetY();
         d.z = p1->GetZ()-p2->GetZ();

         v1.x = p1->GetX();
         v1.y = p1->GetY();
         v1.z = p1->GetZ();

         for(unsigned int j = 0; j < 15; j++)
         {
            if(d.x != 0)
            {
               v1.x -= (d.x / 15);
            }

            if(d.z != 0)
            {
               v1.z -= (d.z / 15);
            }
            Interpolation.push_back(v1);
            if ( Interpolation.size() > 100000)
            {
               throw new GameException ("Interpolation Exceeded 100k limit in PeepAgent.PathFind");
            }
         }
      }
      return true;
   }
   return false;
}


bool PathFind::Find(Pathway *p, Pathway *root)
{
   //cout << "Step Up" << endl;

   for(unsigned int i = 0; i < p->GetConnections().size(); i++)
   {
      if(p->GetConnections().at(i) == mDest)
      {
         return true;
      }
   }

   // Look up a layer for paths
   for(unsigned int i = 0; i < p->GetConnections().size(); i++)
   {
      if(p->GetConnections().at(i) != root) {

         mStack->push( p->GetConnections().at(i) );
         if(Find(p->GetConnections().at(i), p))
         {
            //cout << "Found connection" << endl;
            return true;
         }
         else {
            //cout << "No Route" << endl;
            if(!mStack->empty())
               mStack->pop();
         }

      }

   }
   return false;
}

bool PathFind::Update()
{
   if(mFound)
   {
      if(iter < Interpolation.size())
      {
         Vector3f v = Interpolation.at(iter);
         mPeep->SetLocation( Vector3f( v.x, -v.y - 6, v.z) );
         iter++;
         return false;
      }
      else
      {
         return true;
      }
   }
   return false;
}
