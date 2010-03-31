//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Derived from Libs3ds stock code.
//  Licensed according to the GPL v3.0
//
//  Libs3ds class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
//enum Lib3dsIoSeek;
//enum Lib3dsLogLevel;
struct Lib3dsViewport;
struct Lib3dsTextureMap;
struct Lib3dsMaterial;
struct Lib3dsCamera;
struct Lib3dsLight;
struct Lib3dsMesh;
struct Lib3dsNode;
struct Lib3dsFile;

typedef enum Flags {
    LIB3DSDUMP_MATERIALS  = 0x0004,
    LIB3DSDUMP_TRIMESHES  = 0x0008,
    LIB3DSDUMP_INSTANCES  = 0x0010,
    LIB3DSDUMP_CAMERAS    = 0x0020,
    LIB3DSDUMP_LIGHTS     = 0x0040,
    LIB3DSDUMP_NODES      = 0x0080
} Flags;


class C3DSHandler
{
protected:
   //FILE* m_pFile;
   Lib3dsFile* m_p3DSFile;
   const char* filename;
   const char* output;
   unsigned flags;
   int  log_level;

public:
   C3DSHandler(void);
   ~C3DSHandler(void);

   Lib3dsFile* GetFile()
   {
      return m_p3DSFile;
   }

   void GetMatrix(float matrix[4][4]);
   void GetViewport( Lib3dsViewport *vp );
   void GetTexture( const char *maptype, Lib3dsTextureMap *texture);
   void GetMaterial( Lib3dsMaterial *material );
   void GetCamera( Lib3dsCamera *camera);
   void GetLight( Lib3dsLight *light);
   void GetMesh( Lib3dsMesh *mesh );
   void GetInstances( Lib3dsNode *node, const char* parent );
   void GetNode(Lib3dsNode *node, int level);
   bool Load( const char* szPath );

};
