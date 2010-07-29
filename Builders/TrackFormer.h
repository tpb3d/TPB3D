//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Trackforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../Types/Vector3.h"

struct TrackGuide;

class Track;
class TexturedStrip;
class Park;
class MeshNode;
struct TrackGuide;

class TrackFormer
{
   Gfx::Texture* mpTexture;
   Park& mPark;
public:
   TrackFormer( Gfx::Texture* pTex, Park& park);
   ~TrackFormer(void);
   static Track* CreateTrack();

   void MakeSection( TrackGuide& guide, Track& track );
   TexturedStrip* CrossTie( Vector3f& TrackPoint, TrackGuide& guide );
   ObjectBase* Support( Vector3f pt, TrackGuide& guide, float MountAngle, float Load, float fBaseHeight );
   ObjectBase* WoodSupports( Vector3f pt, float fCurAngleY, float fCurRailAngle );
   ObjectBase* AddCorkSupport( Vector3f ptMount, float fCurAngleY, float fCorkLength );

   
   // wood forming methods moved to WoodTrestle
};
