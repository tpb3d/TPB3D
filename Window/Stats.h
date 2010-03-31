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
// Tick Tock!

#pragma once
#ifndef _STATS_H
#define _STATS_H

#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class AnimationSingle;

class Stats : public Gfx::ViewObject
{
protected:
   AnimationSingle* mOtherFace;   // Day of week
   AnimationSingle* mStatsFace;
   int mNet;
   int mPopulation;
   int mStars;
   string mstrNet;
   string mstrPopulation;
   string mstrDayOfWeek;
   string mstrDate;

public:
   // properties
   void SetDayOfWeek (const char* szDay) { mstrDayOfWeek = szDay; }
   void SetDate (const char* szDate) { mstrDate = szDate; }
   void SetNet (int amt) { mNet = amt; }
   void SetPopulation (int pop) { mPopulation = pop; }
   void SetStars (int stars) { mStars = stars; }
public:
   Stats ();
   ~Stats ();
   void PosCalc ();
   void Update ();
   void Draw ();

};

#endif // _STATS_H
