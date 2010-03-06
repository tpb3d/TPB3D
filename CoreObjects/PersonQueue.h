/*   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once
#ifndef _PERSONQUEUE_H
#define _PERSONQUEUE_H
#include <queue>

class Person;
class CitizenAgent; // to move people
class RouteBase;

class PersonQueue // Abstract, does not even have a CPP file at this point.
{
protected:
   short mHeadIndex;
   short mTailIndex;
   short mCapacity;
   short mSweepIndex; // moves through the queue filling gaps
   //Person** mpQueue;
   std::queue<Person*> mpQueue;

public:
   PersonQueue();
   void AddPerson (Person* person);
   Person* TakeNextPerson ();
   void Update();
   void Draw (int vx, int vy);
};

#endif //_PERSONQUEUE_H
