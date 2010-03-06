//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once

class ObjectTree;

class RidePartLoader
{
protected:
   ObjectTree* m_pObjectTree;
public:
   RidePartLoader( ObjectTree* pTree );
   virtual ~RidePartLoader(void);
   void Load3ds( const char* Path, int id = -1 );// from the 3DS lib
   void LoadASE( const char* Path );// ASE files
   void LoadMS3D( const char* Path); // MilkShape
};
