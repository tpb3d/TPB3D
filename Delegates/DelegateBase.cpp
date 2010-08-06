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
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
#include "../Scene/Scene.h"
#include "DelegateBase.h"

#include "../Builders/RidePartLoader.h"

ObjectNode* DelegateBase::LoadGraphic ()
{
   const char* pszFileStall = "stall.3DS";
   const char* pszPathStall = "data/Building/";
   ObjectNode* pTempTree = new ObjectNode(0, 39);
   PartCorrection corr;
   RidePartLoader rpl(corr);
   rpl.Load3ds( pszPathStall, pszFileStall, pTempTree );
   return pTempTree;
}

