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

#pragma once
#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "Clock.h"
#include "Stats.h"
#include "../Hub/Event.h"

class ToolBar;
class EventHandler;

class Interface : public EventBase
{
private:
protected:
   Clock mClock;
   Stats mStats;
   EventHandler& mEVH; // tap the event handler for the app
   ToolBar* mpToolBar;
   float m_fHeight;

public:
   Interface (EventHandler& revh);

   Stats& GetStats() { return mStats; }
   int GetTimeOfDay() { return mClock.GetTimeOfDay();  }
   virtual bool OnMouseDown (sf::Mouse::Button Button, Vector2i point, Vector2i pointb);
   virtual bool OnMouseUp (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb);
   virtual bool OnMouseMove ( Vector2i pointa, Vector2i pointb);

   void LoadToolbar ();
   void Update (float dt);
   void Draw ();
};

#endif // _INTERFACE_H
