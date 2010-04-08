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
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectNode.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/ObjectFactory.h"
#include "../People/Person.h"
#include "../Storage/SerializerBase.h"

#include "PersonQueue.h"
#include "Routes.h"
#include "CoreBase.h"
#include "Pathway.h"

#include "../Utility/GameException.h"

#include "../Types/String.h"

using namespace Gfx;

Pathway::Pathway (const Vector3f& origin, Park * ParkParent, const char* szTex)
:  CoreBase(origin, Vector3f(0,45,0))
,  ObjectNode(0, ObjectFactory::TakeANumber())
{
   m_Point = origin;
   mTexName = szTex;
   mID = CoreBase::GetNextID();
   mpGraphic = ObjectFactory::CreateNode(1);
}

//Pathway::Pathway(TiXmlNode* pnPathway)
//{
//   TiXmlNode* pnNum = pnPathway->FirstChild("number");
//}

Pathway::~Pathway()
{
   if (mpGraphic != NULL)
   {
      delete mpGraphic;
   }
   // delete the nodes
}

void Pathway::Update (float dt, int tod)
{
}

void Pathway::Render()
{
   int iSides = 15;
   float  fOff = 1.75f;
   float  fStep = 3.5;
   TexturedStrip* pBase = ObjectFactory::CreateTexturedStrip (iSides, mTexName.c_str(), 0xf0f0f0f0);
   mpGraphic->AddMesh (pBase);
   Vector3f pt1 (mvPosition.x, mvPosition.y, mvPosition.z-fOff);
   Vector3f pt2 (mvPosition.x, mvPosition.y, mvPosition.z+fOff);
   pBase->AddPoint (pt1);
   pBase->AddPoint (pt2);
   for( int ix =0; ix < iSides; ++ix)
   {
      pt1.x += fStep;
      pt2.x += fStep;
      pBase->AddPoint (pt1);
      pBase->AddPoint (pt2);
   }
}
// dummy code
void Pathway::Render2()
{
   int iSides = 15;
   float  fOff = 1.75f;
   float  fStep = 3.5;
   TexturedStrip* pBase = ObjectFactory::CreateTexturedStrip (iSides, mTexName.c_str(), 0xf0f0f0f0);
   mpGraphic->AddMesh (pBase);
   Vector3f pt1 (mvPosition.x, mvPosition.y, mvPosition.z+fOff);
   Vector3f pt2 (mvPosition.x+fOff*2, mvPosition.y, mvPosition.z+fOff);
   pBase->AddPoint (pt1);
   pBase->AddPoint (pt2);
   for( int ix =0; ix < iSides; ++ix)
   {
      pt1.z += fStep;
      pt2.z += fStep;
      pBase->AddPoint (pt1);
      pBase->AddPoint (pt2);
   }
}

// dummy code
void Pathway::Render3()
{
   int iSides = 15;
   float  fOff = 1.75f;
   float  fStep = 3.5;
   TexturedStrip* pBase = ObjectFactory::CreateTexturedStrip (iSides, mTexName.c_str(), 0xf0f0f0f0);
   mpGraphic->AddMesh (pBase);
   Vector3f pt1 (mvPosition.x*2.53, mvPosition.y, mvPosition.z-fOff);
   Vector3f pt2 (mvPosition.x*2.53, mvPosition.y, mvPosition.z+fOff);
   pBase->AddPoint (pt1);
   pBase->AddPoint (pt2);
   for( int ix =0; ix < iSides; ++ix)
   {
      pt1.x += fStep;
      pt2.x += fStep;
      pBase->AddPoint (pt1);
      pBase->AddPoint (pt2);
   }
}

// Function that calls the OpenGL rendering in the subclass.
void Pathway::Draw ()
{
   // add meshed then draw them here
   mpGraphic->Draw();
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

void Pathway::AddConnection (Pathway* pPath)
{
   mConnectors.push_back (pPath);
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
