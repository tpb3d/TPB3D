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

#include <iostream>

// Then user-defined types
#include "../Scene/Scene.h"
#include "../Graphics/Camera.h"
#include "../Hub/Event.h"

#include "../Hub/GameManager.h" // xml saver
#include "SceneEvent.h"

SceneEvent::SceneEvent(Scene* pScene, GameManager& GM)
:  mGameManager(GM)
{
   mpScene = pScene;
}


SceneEvent::~SceneEvent ()
{
}

bool SceneEvent::OnToolHit (const HR_Events tool)
{
   switch (tool)
   {
   case HR_OpenScene:
      return OnOpen("data/xml/Park.xml");
   case HR_SaveScene:
      return OnSave("data/xml/Park2.xml");
//   case HR_Settings:
//      return mGameManager.Settings();
   case HR_FRCS:
      return mGameManager.FRCS();
   }

   return false;
}

bool SceneEvent::OnMouseDown (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb)
{
   Camera* pCam = Camera::GetInstance();
   int hit = pCam->DrawSelectionTarget (mpScene, pointa, 0);
   if( hit )
   {
      mpScene->HitDown( hit, pointa );
   }
   return false; // leave the message in for the pointer
}

bool SceneEvent::OnMouseUp (sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb)
{
   Camera* pCam = Camera::GetInstance();
   int hit = pCam->DrawSelectionTarget (mpScene, pointa, 0);
   if( hit )
   {
      mpScene->HitUp( hit, pointa );
   }
   return false; // leave the message in for the pointer
}

bool SceneEvent::OnMouseMove ( Vector2i pointa, Vector2i pointb)
{
   Camera* pCam = Camera::GetInstance();
   Vector2f vec((float)pointa.x, (float)pointa.y);
   int hit = pCam->DrawSelectionTarget (mpScene, pointa, 0);
   if( hit )
   {
   }
   else
   {
      mpScene->MoveGhostObject (vec);
   }
   return true;
}

// these methods belong in the game manager
bool SceneEvent::OnOpen (const char* pPath)
{
   return mGameManager.LoadGame( pPath );
}

bool SceneEvent::OnSave (const char* pPath)
{
   return mGameManager.SaveGame( pPath );
}
