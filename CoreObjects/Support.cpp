//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Track Support class
//
//  You should have received a copy of the GNU General Public License
//  along with Extreme Park Developer.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/VPoint.h"
#include "CamPath.h"
#include "Support.h"
#include "../Graphics/ObjectFactory.h"


Support::Support( CVPoint ptMount, float fMountAngle, float fLoad, float fHeight, float fBaseHeight )
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
{
   mMountPoint = ptMount;
   mfMountAngle = fMountAngle;
   mfLoad = fLoad;
   mfHeight = fHeight;
   mfBaseHeight = fBaseHeight;
   mPartsCount = 0;
}

Support::~Support(void)
{
   try
   {
      for( int ix = 0; ix < mPartsCount; ++ix )
      {
         delete m_BaseParts[ix];
      }
   }
   catch( ... )
   {
   }
}

void Support::Render()
{

}

void Support::AddSection( ObjectBase* pBase )
{
   m_BaseParts[mPartsCount++] = pBase;
}

void Support::Draw()
{
   for( int ix = 0; ix < mPartsCount; ++ix )
   {
      m_BaseParts[ix]->Draw();
   }
}
