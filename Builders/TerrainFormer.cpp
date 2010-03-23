//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <cstring>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../CoreObjects/Terrain.h"
#include "../Graphics/Image.h"
#include "../Graphics/QuadMeshObject.h"
#include "../Graphics/ObjectFactory.h"
#include "TerrainFormer.h"

// our own terrain gen until Doc brings his on!

TerrainFormer::TerrainFormer(void)
{
}

TerrainFormer::~TerrainFormer(void)
{
}

Terrain* TerrainFormer::DefaultMesh()
{
   // Terrain - entity
   Terrain* pTerra = new Terrain();
   // The graphics mesh for OpenGL
   QuadMeshObject* pMesh = ObjectFactory::CreateQuadMesh();
   QuadVertex* pVerts = new QuadVertex[102*102];
   QuadFace* faces = new QuadFace[100*100];

   // Meshes are parts that make up the terrain.
   // this makes it uneven
   for (int ix = 0;ix < 101; ++ix)
   {
      for (int iz = 0; iz < 101; ++iz)
      {
         float fy = float(rand()%100)/25 -2.0f;
         int index = ix*101+iz;
         pVerts[index].Vertices[0] = 10.0f*ix-505.f;
         pVerts[index].Vertices[1] = fy;
         pVerts[index].Vertices[2] = 10.0f*iz-505.f;
         const unsigned char dirt[] = { 0xaf,0xff,0x7f,0xff,0 };
         const unsigned char full[] = { 0xcf,0xef,0xc3,0xff,0 };
         if (iz >48 && iz < 52 && ix > 50 )
         {
            memcpy(pVerts[index].Color, dirt, 4);
         }
         else
         {
            memcpy(pVerts[index].Color, full, 4);
         }
      }
   }
   // procedural test code to add color to the ls
   const unsigned char yellow[] = { 0xff,0xff,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 52].Color, yellow, 4);
   memcpy(pVerts[50*101+ 53].Color, yellow, 4);
   memcpy(pVerts[50*101+ 54].Color, yellow, 4);
   memcpy(pVerts[51*101+ 53].Color, yellow, 4);
   memcpy(pVerts[51*101+ 54].Color, yellow, 4);
   memcpy(pVerts[51*101+ 55].Color, yellow, 4);

   const unsigned char sand[] = { 0x3f,0xbf,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 45].Color, sand, 4);
   memcpy(pVerts[50*101+ 46].Color, sand, 4);
   memcpy(pVerts[50*101+ 47].Color, sand, 4);
   memcpy(pVerts[51*101+ 46].Color, sand, 4);
   memcpy(pVerts[51*101+ 47].Color, sand, 4);
   memcpy(pVerts[51*101+ 48].Color, sand, 4);
   memcpy(pVerts[52*101+ 46].Color, sand, 4);
   memcpy(pVerts[52*101+ 47].Color, sand, 4);
   memcpy(pVerts[52*101+ 48].Color, sand, 4);

   // procedural test code to add color to the ls
   const unsigned char brown[] = { 0xaf,0x9f,0x7f,0xff,0 };
   const unsigned char dbrown[] = { 0x8f,0x7f,0x6f,0xff,0 };
   memcpy(pVerts[50*101+ 49].Color, brown, 4);
   memcpy(pVerts[50*101+ 50].Color, dbrown, 4);
   memcpy(pVerts[50*101+ 51].Color, brown, 4);
   memcpy(pVerts[51*101+ 49].Color, brown, 4);
   memcpy(pVerts[51*101+ 50].Color, dbrown, 4);
   memcpy(pVerts[51*101+ 51].Color, dbrown, 4);
   memcpy(pVerts[51*101+ 52].Color, brown, 4);
   memcpy(pVerts[52*101+ 49].Color, brown, 4);
   memcpy(pVerts[52*101+ 50].Color, brown, 4);
   memcpy(pVerts[52*101+ 51].Color, brown, 4);
   memcpy(pVerts[52*101+ 52].Color, brown, 4);

   for (int ix = 0;ix < 100; ++ix)
   {
      for (int iz = 0; iz < 100; ++iz)
      {
         int index = ix*100+iz;
         int idx =  ix*101+iz;
         QuadFace& face = faces[index];
         face.mPoints[0].Index = idx;
         face.mPoints[0].mUV[0] = 0;
         face.mPoints[0].mUV[1] = 0;
         face.mPoints[1].Index = idx+1;
         face.mPoints[1].mUV[0] = 1;
         face.mPoints[1].mUV[1] = 0;
         face.mPoints[2].Index = idx+102;
         face.mPoints[2].mUV[0] = 1;
         face.mPoints[2].mUV[1] = 1;
         face.mPoints[3].Index = idx+101;
         face.mPoints[3].mUV[0] = 0;
         face.mPoints[3].mUV[1] = 1;
      }
   }
   pMesh->AddMesh( 101*101, pVerts, 100*100, faces, 0);
   pTerra->AddSection(pMesh);
   Gfx::ImageManager* pImger = Gfx::ImageManager::GetInstance();
   Gfx::Texture* pTex = pImger->GetTexture ("Grass2.png",3);
   pMesh->SetTexture (pTex);
   int iChan = pTex->SupportsAlpha() ? 4 : 3;
   gluBuild2DMipmaps( GL_TEXTURE_2D, iChan, pTex->GetWidth(), pTex->GetHeight(),
                        GL_RGBA, GL_UNSIGNED_BYTE, pTex->GetPixelsPtr());
   return pTerra;
}

Terrain* TerrainFormer::DocsMesh()
{
// Call the terraformer
   return DefaultMesh();
}

