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
#define testNames 1
#if testNames
#include "../People/PeepNames.h"
#endif

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

#define WithRide

PeepsAgent::PeepsAgent (Park& Park) // use a Park agent for multiple Parks
      :  mPark (Park)
{
	#define testNames 1
	#if testNames
		#if doAmericanTest
			TestAmericanNames();
		#endif
		#if doTestNameTree
			TestNameTree();
		#endif
	#endif
}

PeepsAgent::~PeepsAgent ()
{
}

void PeepsAgent::Update (float dt, int tod)
{
   // Shouldn't Peeps be a member within each Park? Supposedly you would want this seperate.
   Peeps* Peeps = Peeps::get_Instance(); // the Peeps object that holds the people collection
//
   if( Peeps->GetPopulation() < 1)
   {
      Person* peep = Peeps->NewPerson();
      peep->SetPathFind( new PathFind(peep) );
      mPark.EnterPark (peep);

      Peeps->Update( dt );
   }

//   if ( (rand() % 4) == 3 )  // TODO: need a better spawn mechanism, raised to 100
//   {
//      //Location loc; // all zeros
//      Person* peep = Peeps->NewPerson();
//      peep->SetPathFind( new PathFind(peep) );
//
//      mPark.EnterPark (peep);
//      Peeps->Update( dt );
//   }


   std::list<Person *>::iterator i;
   std::list<Person *>& persons = Peeps->get_Persons(); // get the persons collection.

   // TODO: Need to create a better interface that provides a clear persons iteration.
   for (i = persons.begin (); i != persons.end (); i++)
   {
      Person* peep = (*i);

      // Update each peep
      peep->Update( tod );

      //Path& workPath = peep->get_WorkPath(); // for now just doing work
      //  TODO: case statement from hell, on the refactor list
      // use a state engine to replace this
      switch ( peep->GetActivity() )
      {
         case Person::AS_LookingForEntrance:
         {
            cout << "Peep is looking for the park entrance." << endl;
            Pathway *entrance = mPark.GetEntrance();
            if(entrance)
            {
               peep->SetPathway(entrance);
               //peep->SetLocation( Vector3f( entrance->GetX(), -entrance->GetY() - 6, entrance->GetZ()) );
               peep->SetActivity(Person::AS_None);
               peep->SetInPark(true);
               cout << "Peep found park entrance and has entered the park." << endl;
            }
            else
            {
               Peeps->DestroyPerson(peep);
            }
         }
         break;


         case Person::AS_LookingForFood:
//
//         cout << "Peep is looking for food" << endl;
//
//         Stall *stall;
//         stall = mPark.FindStallByType (ST_Food);
//         if(stall)
//         {
//            peep->SetLocation( Vector3f( stall->GetQueue()->GetX(), -stall->GetQueue()->GetY() - 6, stall->GetQueue()->GetZ()) );
//
//            stall->AddPerson(peep);
//            stall->Update (dt, tod);
//         } else {
//            cout << "Couldn't find a food stall " << endl;
//         }

         break;

         case Person::AS_LookingForDrink:
         break;

         case Person::AS_Wandering:
         {
            Pathway *p = NULL;

            cout << "Peep is wandering" << endl;
            Pathway::PathwayVector v = mPark.GetPaths();

            //p = v.at( 5 );
            while ( p == peep->GetPathway() || p == NULL)
            {
               int n = (rand() % (v.size()-1));
               cout << n << " " << v.size() << endl;
               p = v.at( n );

            }

            cout << "Calculating" << endl;
            if( peep->GetPathFind()->Calculate( p ) )
            {
               peep->SetActivity(Person::AS_LookingForPath);
            }
            else
            {
               peep->SetActivity(Person::AS_None);
               cout << "No Path" << endl;
            }
            cout << "Done" << endl;
         }
         break;


         case Person::AS_LookingForRide:
            cout << "Peep is looking for a ride" << endl;
#ifdef WithRide
            cout << "Peep is looking for a ride..." << endl;

            Ride* pRide;
            pRide = mPark.FindRideByName("Barn Stormers");
            if (pRide != NULL)
            {
               cout << "Looking for Path..." << endl;

               if( peep->GetPathFind()->Calculate( pRide->GetQueue() ) )
               {
                  peep->SetActivity(Person::AS_LookingForPath);
               }
               else
               {
                  peep->SetActivity(Person::AS_None);
               }

//
//               cout << "Peep found ride: " << pRide->GetName() << endl;
//               peep->SetLocation( Vector3f( pRide->GetQueue()->GetX(), -pRide->GetQueue()->GetY() - 6, pRide->GetQueue()->GetZ()) );
//
//               pRide->AddPerson (peep);
            } else {
               peep->SetActivity(Person::AS_None);
            }
#endif
         break;

         case Person::AS_LookingForPath:
         {
            PathFind *find = peep->GetPathFind();
            if(find->Update())
            {
               Pathway *dest = (Pathway*)find->GetDestination();
               peep->SetPathway(dest);
               //peep->SetActivity( peep->GetLastActivity() );
               peep->SetActivity( Person::AS_None );

               cout << "Arrived at Destination" << endl;
            }
         }
         break;

         case Person::AS_LookingForATM:
         break;

         case Person::AS_GoingHome:
         {
            Pathway *entrance = mPark.GetEntrance();

            if(peep->GetPathway() != entrance) {
               if( peep->GetPathFind()->Calculate( entrance ) )
                  peep->SetActivity( Person::AS_LookingForPath );
               else
                  Peeps->DestroyPerson(peep);
            } else {
               Peeps->DestroyPerson(peep);
            }
         }
         break;


         default:
         // do something
         break;   // microsoft requires this break
      }
   }
}
