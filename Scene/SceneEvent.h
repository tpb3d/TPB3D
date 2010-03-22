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

#pragma once

#include "../Resources.h"

// Include libraries first
#include <utility>
#include <string>

#include "../Hub/Event.h"  // event base

class Scene;

class SceneEvent : public EventBase
{
protected:
   Scene* mpScene;
   GameManager& mGameManager;
public:
   SceneEvent (Scene* pScene, GameManager& GM);
   ~SceneEvent ();

   bool OnToolHit (const HR_Events tool);
   bool OnOpen (const char* pPath);
   bool OnSave (const char* pPath);
   virtual bool OnMouseDown (sf::Mouse::Button Button, Vector2i point, Vector2i pointb);
   virtual bool OnMouseUp (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb);
   virtual bool OnMouseMove ( Vector2i pointa, Vector2i pointb);
};
