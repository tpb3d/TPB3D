//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Deck class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once
#include "RideNode.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedStrip.h"

class Deck : public RideNode, public TexturedStrip
{
   float mRadii[2];
   short mSides;
   short mSections;
   std::string mTexName;

public:
   Deck (float innerRadius, float outerRadius, short sides, const char* TexName);
   ~Deck(void);

   ObjectBase* Clone( );
   void IncreseSides();
   void DecreseSides();
   virtual void Update(int dt);
   void Render();
   void Draw();
   void DrawSelectionTarget();

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
