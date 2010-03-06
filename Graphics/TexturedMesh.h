//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  TexturedMeshObject class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#pragma once

class TexturedMesh : public ObjectBase
{
protected:
   Gfx::Texture* mpTexture;
   int mWidth;
   int mDepth;

   virtual ObjectBase* Clone( )
   {
      throw( "No cloning GLTexturedMesh" );
      return 0;
   }

public:
   TexturedMesh( int Width, int Depth, Gfx::Texture* pText, int Color, int id );
	virtual ~TexturedMesh();

   void Draw();
   void DrawSelectionTarget();

};

