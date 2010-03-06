//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TrackBase class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "TrackBase.h"

TrackBase::TrackBase( int PointCount, int ID )
:  ObjectBase( PointCount, ID)
{
}

TrackBase::~TrackBase(void)
{
}
