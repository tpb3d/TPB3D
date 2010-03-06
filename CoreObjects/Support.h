//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track Support class
//
//  You should have received a copy of the GNU General Public License
//  along with Extreme Park Developer.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

// this unit consists of round or square metal tubing.
// several configurations are built with one or more concrete anchors.
// later details for he connection bolts and anchor bolts will be added.
// for now it is just the tubing and concrete anchor.

#pragma once
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
class CVPoint;

// this is just the tracks not the supports, devices or station
class ObjectBase;
class CVPoint;

class Support : public ObjectNode
{
   CVPoint mMountPoint;
   float mfMountAngle;
   float mfLoad;
   float mfHeight;
   float mfBaseHeight;
   int   mPartsCount;
   ObjectBase* m_BaseParts[8]; // temp hardcode

public:
   Support(CVPoint ptMount, float MountAngle, float Load, float fHeight, float fBaseHeight);
   ~Support(void);

   void Render();
   void AddSection( ObjectBase* pGLBase );
   void Draw();
};
