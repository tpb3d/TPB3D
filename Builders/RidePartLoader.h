//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once

class ObjectNode;

class RidePartLoader
{
public:
   RidePartLoader( );
   virtual ~RidePartLoader(void);
   void Load3ds( const char* Path, const char* Name, ObjectNode* pBase);// from the 3DS lib
   void LoadASE( const char* Path );// ASE files NOT SUPPORTED YET
   void LoadMS3D( const char* Path, const char* Name, ObjectNode* pBase); // MilkShape
};
