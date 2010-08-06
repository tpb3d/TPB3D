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
struct PartCorrection
{
   float Location[4];
   float Rotation[4];
   float frx;
   PartCorrection ()
   {
      frx = 1.0f;
      memset (Location, 0, sizeof(Location));
      memset (Rotation, 0, sizeof(Rotation));
   }
   void SetLocation (float* loc)
   {
      Location[0] = loc[0];
      Location[1] = loc[1];
      Location[2] = loc[2];
      Location[3] = loc[3];
   }
   void SetRotation (float* rot)
   {
      Rotation[0] = rot[0];
      Rotation[1] = rot[1];
      Rotation[2] = rot[2];
      Rotation[3] = rot[3];
   }};

class RidePartLoader
{
protected:
   PartCorrection& mPartCorrection;
public:
   RidePartLoader (PartCorrection& corr);
   virtual ~RidePartLoader (void);
   void Load3ds( const char* Path, const char* Name, ObjectNode* pBase);// from the 3DS lib
   void LoadASE( const char* Path );// ASE files NOT SUPPORTED YET
   void LoadMS3D( const char* Path, const char* Name, ObjectNode* pBase); // MilkShape
};
