//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Lamp class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  RideLamp        Stationay Structural element such as the pylon for the yoyo and carousel.

#pragma once
#include <string>

//#include "CoreBase.h"

class ObjectNode;

class Lamp : public ObjectNode
{
protected:
   float mHeight;
   float mRadii[4];
   short mSides;
   short mSections;
   std::string mTexName;
   std::string mTexGlow;
   ObjectNode* mpGraphic;

public:
   Lamp (float height, const char* TexName, const char* TexGlow);
   Lamp (float height, ObjectNode* pGfx);
   ~Lamp(void);

   //ObjectBase* Clone( );
   void IncreseSides();
   void DecreseSides();
   virtual void Update(int dt);
   void Render();
   void Draw();
   void DrawSelectionTarget();
   Lamp* Clone() { return new Lamp (mHeight, mTexName.c_str() ,mTexGlow.c_str()); }

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
