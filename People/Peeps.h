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

// These are all the people or Peeps of your city some are in your Park(s) others are looking for a place
// to work, eat, shop and sleep or just hang out. The more of them you get the more profits you should see.

#ifndef _Peeps_H
#define _Peeps_H

struct Location; // from person
class Person;
class PeepsAgent;

class Peeps // : public Storage // add the serialization base
{
   friend class PeepsAgent;
private:
   std::list <Person*> mPeople;  // reverted back to a list as we will only use a forward iterator
protected:
   static Peeps* minstance;

   Peeps();
   virtual ~Peeps(void);

public:
   // instance
   static Peeps* get_Instance();
   void destroy();
   // properties
   std::list <Person*>& get_Persons()
   {
      return mPeople;
   }
   size_t GetPopulation()
   {
      return mPeople.size();
   }
   size_t GetPopulationForPark(int Park);

   // methods
   Person* NewPerson();
   void DestroyPerson( Person* person );

   void Update (float dt, float tod);
   void Draw(); // draw the people here
};

#endif //_Peeps_H
