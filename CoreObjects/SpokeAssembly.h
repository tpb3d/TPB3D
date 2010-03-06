//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  SpokeAssembly class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//  RideSpokeAssembly        Stationay Structural element such as the pylon for the yoyo and carousel.

#pragma once
#include "RideNode.h"

class SpokeAssembly : public RideNode
{
   float mHeight;
   short mSpokes;
   //  added lifters and other parts

public:
   SpokeAssembly (float height, short sides );
   ~SpokeAssembly(void);

   void IncreseSpokes();
   void DecreseSpokes();
   void Render();

   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
