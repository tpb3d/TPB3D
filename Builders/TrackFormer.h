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
   ObjectBase* WoodSupports( Vector3f pt, TrackGuide& guide, float MountAngle, float Load, float fBaseHeight );

   void WoodPost(MeshNode* pSupp, float x, float y, float z, float w, float height);
   void WoodBeam(MeshNode* pSupp, float x, float y, float z, float w, float l, float d);
   void WoodBrace(MeshNode* pSupp, float x, float y, float z, float w, float l, float d, float h);
   void WoodBent(MeshNode* pSupp, float x, float y, float z, float w, float l, float d, float angle);
};
