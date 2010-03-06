//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Flying Camera class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once

#include "RideNode.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/SimpleMeshObject.h"

class Carriage : public RideNode, public SimpleMeshObject
{

public:
   Carriage();
   virtual ~Carriage(void);

   virtual void Render();
   virtual void Draw();
   virtual void DrawSelectionTarget(); // base can't draw
   virtual ObjectBase* Clone( );
   void Default();
};
