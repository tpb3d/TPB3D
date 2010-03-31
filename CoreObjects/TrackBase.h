//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TrackBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "../Graphics/ObjectBase.h"

class TrackBase : public ObjectBase
{
public:
   TrackBase( int PointCount, int ID );
   ~TrackBase(void);
};
