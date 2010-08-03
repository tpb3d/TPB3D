//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Flying Camera class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once
#pragma once
#include "RideNode.h"

class ObjectBase;

class Carriage : public RideNode
{
   ObjectBase* mpGraphic;

public:
   Carriage();
   virtual ~Carriage(void);

   virtual void Render();
   virtual void Draw();
   virtual void DrawSelectionTarget(int t); // base can't draw
   //virtual ObjectBase* Clone( );
   void Default();
};
