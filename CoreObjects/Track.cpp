//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utility/CamPath.h"
#include "Track.h"
#include "TrackSection.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"

Track::Track(void)
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
{
   m_dHeight = 5;
   m_PartsCount = 0;
}

Track::~Track(void)
{
   try
   {
      for( int ix = 0; ix < m_PartsCount; ++ix )
      {
         delete m_BaseParts[ix];
      }
   }
   catch( ... )
   {
   }
}

void Track::AddSection( ObjectBase* pBase )
{
   m_BaseParts[m_PartsCount++] = pBase;
}

void Track::Draw()
{
   for( int ix = 0; ix < m_PartsCount; ++ix )
   {
      m_BaseParts[ix]->Draw();
   }
}

void Track::Load(SerializerBase& ser)
{
   TrackSection* pTrackSection = new TrackSection();
   pTrackSection->Load(ser);
}

void Track::Save(SerializerBase& ser)
{
   ser.Add("type", "Track");
   ser.Add("height", m_dHeight);
   ser.Add("angle",mAngle);
   ser.Add("ID", mID);
   for( int ix = 0; ix < m_PartsCount; ++ix )
   {
      SerializerBase* pSer = ser.Spawn("TrackSections");
      m_BaseParts[ix]->Save(*pSer);
      delete pSer;
   }
//   delete pSer;
}
