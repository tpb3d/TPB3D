//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TexturedStripObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "VPoint.h"
#include "Texture.h"
#include "ObjectBase.h"
#include "TexturedStrip.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TexturedStrip::TexturedStrip( int Count, Gfx::Texture* pTex, int Color )
:  ObjectBase( Count*2, 0 )
,  mpTexture( pTex )
{
   memcpy( mRGBA, &Color, 4 );
}

TexturedStrip::~TexturedStrip()
{
}

void TexturedStrip::AddPointPair( CVPoint& pt1, CVPoint& pt2 )
{
   sf::Vector3f temp1 =  pt1.GetVector3f();
   sf::Vector3f temp2 =  pt2.GetVector3f();
   AddPoint( temp1 );
   AddPoint( temp2 );
}

void TexturedStrip::Draw()
{
   if( mPointCount < 1 )
      return;

   sf::Vector3f* pQ = mpPoints;
   glColor3ubv( mRGBA );
   //glBindTexture( GL_TEXTURE_2D, mTexture ); // iTex
   mpTexture->Bind();
   glBegin(GL_QUAD_STRIP);
   float fU = 0;
   for( int ix =0; ix < mPointCount/2; ++ix )
   {
      glTexCoord2f( fU, 0.0 );
      glVertex3fv( (float*)(pQ++) ); // simple extension arm
      glTexCoord2f( fU, 1.0 );
      glVertex3fv( (float*)(pQ++) );
      fU = fU+1.0f;
   }
   glEnd();
}

void TexturedStrip::DrawSelectionTarget()
{
   if( mPointCount < 1 )
      return;

   sf::Vector3f* pQ = mpPoints;
   glBegin(GL_QUAD_STRIP);
   for( int ix =0; ix < mPointCount/2; ++ix )
   {
      glVertex3fv( (float*)(pQ++) ); // simple extension arm
      glVertex3fv( (float*)(pQ++) );
   }
   glEnd();
}
