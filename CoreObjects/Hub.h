//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Hub class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  RideHub        Stationay Structural element such as the pylon for the yoyo and carousel.

#pragma once
#include <string>

#include "RideNode.h"

class ObjectBase;

class Hub : public RideNode
{
protected:
   float mHeight;
   float mRadii[4];
   short mSides;
   short mSections;
   std::string mTexName;
   ObjectBase* mpGraphic;

public:
   Hub (float height, short sides, const char* TexName);
   Hub (float height, short sides, ObjectBase* pGfx);
   ~Hub(void);

   //ObjectBase* Clone( );
   void IncreseSides();
   void DecreseSides();
   virtual void Update(int dt);
   void Render();
   void Draw();
   void DrawSelectionTarget();

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
