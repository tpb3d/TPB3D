//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TexturedMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#include <cstring>
#include <math.h>
#include "Texture.h"
#include "ObjectBase.h"
#include "TexturedMesh.h"

using namespace Gfx;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TexturedMesh::TexturedMesh( int Width, int Depth, Gfx::Texture* pTex, int Color, int id )
:  ObjectBase( Width * Depth, id )
,  mWidth( Width )
,  mDepth( Depth )
,  mpTexture( pTex )
{
   memcpy( mRGBA, &Color, 4 );
}

TexturedMesh::~TexturedMesh()
{

}

void TexturedMesh::Draw()
{
   float Flip = 0;

   glColor3ubv( mRGBA );
//   glBindTexture( GL_TEXTURE_2D, mTexture ); // iTex
   mpTexture->Bind();
   Vector3f* pQ;
   Vector3f* pR;
   for( int iz = 0; iz < mWidth -1; ++iz )
   {
      glBegin(GL_QUAD_STRIP);
      pQ = &mpPoints[iz*mDepth];
      pR = &mpPoints[(iz+1)*mDepth];
      for( int ix =0; ix < mDepth; ++ix )
      {
         glTexCoord2f( Flip,0);
         glVertex3fv( (float*)(pQ++) ); // simple extension arm
//         Flip+=1;
         glTexCoord2f( Flip,1);
         glVertex3fv( (float*)(pR++) );
         Flip = (Flip) ? 0 : 1.0f;
      }
      glEnd();
   }
}

void TexturedMesh::DrawSelectionTarget()   // just the basic geometry
{
   Vector3f* pQ;
   Vector3f* pR;
   for( int iz = 0; iz < mWidth -1; ++iz )
   {
      glBegin(GL_QUAD_STRIP);
      pQ = &mpPoints[iz*mDepth];
      pR = &mpPoints[(iz+1)*mDepth];
      for( int ix =0; ix < mDepth; ++ix )
      {
         glVertex3fv( (float*)(pQ++) ); // simple extension arm
         glVertex3fv( (float*)(pR++) );
      }
      glEnd();
   }
}
