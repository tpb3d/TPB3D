/*   This file is part of ExtremePark Developer.
 *
 *   ExtremePark Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   ExtremePark Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ExtremePark Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstring>
#include <string>
#include <iostream>
#include "../Physics/MotionPhysics.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../People/Person.h"
#include "../Storage/SerializerBase.h"

#include "PersonQueue.h"
#include "Routes.h"
#include "CoreBase.h"
#include "Pathway.h"

#include "../Utility/GameException.h"

#include "../Types/String.h"

using namespace Gfx;

Pathway::Pathway (Vector3f& origin, Park * ParkParent)
:  CoreBase(origin, Vector3f(0,0,0))
{
   mID = CoreBase::GetNextID();
   mSkin = new AnimationSingle (ImageManager::GetInstance()->GetTexture("foundation.png", GL_RGBA), 56, 36);
   mThePathway = new AnimationEmpty ((int)origin.x, (int)origin.z);
}

//Pathway::Pathway(TiXmlNode* pnPathway)
//{
//   TiXmlNode* pnNum = pnPathway->FirstChild("number");
//}

Pathway::~Pathway()
{
   // delete the nodes
}

void Pathway::Update (float dt, int tod)
{
}

// Function that calls the OpenGL rendering in the subclass.
void Pathway::Draw ()
{
   // add meshed then draw them here
   // mpMesh->Draw;
}

void Pathway::DrawSelectionTarget (bool PathwayOnly)
{
   if (PathwayOnly)
   {
//      DrawSelectionTarget(mThePathway, mID);
   }
   else
   {
      //DrawSelectionTarget (*mpMesh);
   }
}

void Pathway::DrawEmptyFramework ()
{
   try
   {
      //DrawSelectionTarget (*mpMesh);
   }
   catch (...)
   {
      throw new GameException ("Error rendering empty Pathway");
   }
}

void Pathway::Load(SerializerBase& ser)
{
   CoreBase::Load (ser);
   // add exception handler if something goes bump, either deal with it or throw it
}

void Pathway::Save(SerializerBase& ser)
{
   ser.Add("type", "Pathway");   // first tag
   CoreBase::Save (ser);
   // add exception handler if something goes bump, either deal with it or throw it
}
