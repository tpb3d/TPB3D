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

// #DEFINES moved to resource.h until we get a platform ind resouce file.

#include "Resources.h"

// Include libraries first
#include <utility>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// Then user-defined types
#include "Window/Interface.h"
#include "Hub/Event.h"

#include "Utility/GameException.h"


class MainEvent : public EventBase
{
   bool mbRunning;
public:
   MainEvent()
   {
      mbRunning = true;
   }
   bool IsRunning()
   {
      return mbRunning;
   }
   bool OnClose()
   {
      mbRunning = false;
      return true;
   }
};

class ToolEvent : public EventBase
{
public:
   ToolEvent() {}


};