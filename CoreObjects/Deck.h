//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Deck class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once
#include "RideNode.h"

class ObjectBase;

class Deck : public RideNode
{
   float mRadii[2];
   short mSides;
   short mSections;
   std::string mTexName;
   ObjectBase* mpGraphic;

public:
   Deck (float innerRadius, float outerRadius, short sides, const char* TexName);
   Deck (float innerRadius, float outerRadius, short sides, ObjectBase* pGfx);
   ~Deck(void);

   //ObjectBase* Clone( );
   void IncreseSides();
   void DecreseSides();
   virtual void Update(int dt);
   void Render();
   void Draw();
   void DrawSelectionTarget(int mode);

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
