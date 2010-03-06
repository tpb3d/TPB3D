//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Rideforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
class CVPoint;

class Arm;
class Hub;
class TexturedStrip;
class Park;
struct RideGuide;

class RideFormer
{
   Gfx::Texture* mpTexture;
   Park& mPark;
public:
   RideFormer( Gfx::Texture* pTex, Park& park);
   ~RideFormer(void);
   static Ride* CreateRide();

   void MakeSection( RideGuide& guide, Ride& Ride );
   TexturedStrip* CrossTie( CVPoint& RidePoint, RideGuide& guide );
   ObjectBase* Support( CVPoint pt, RideGuide& guide, float MountAngle, float Load, float fBaseHeight );
};
