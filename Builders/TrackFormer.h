//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Trackforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
class CVPoint;
struct TrackGuide;

class Track;
class TexturedStrip;
class Park;
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
   TexturedStrip* CrossTie( CVPoint& TrackPoint, TrackGuide& guide );
   ObjectBase* Support( CVPoint pt, TrackGuide& guide, float MountAngle, float Load, float fBaseHeight );
};
