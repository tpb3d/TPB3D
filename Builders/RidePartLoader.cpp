//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/ObjectTree.h"
#include "../Graphics/SimpleMeshObject.h"
#include "../Graphics/SimpleMatMeshObject.h"
#include "../Graphics/ObjectNode.h"
#include "../Graphics/Material.h"
#include "../Graphics/Image.h"
#include "../Graphics/ComponentObject.h"
#include "../Graphics/ObjectFactory.h"

#include "../Storage/MS3DFile.h"
#include "../Storage/3DSHandler.h"
#include "RidePartLoader.h"

#include <lib3ds.h>

#ifdef LINUX
#define _strnicmp strncasecmp
#endif


RidePartLoader::RidePartLoader()
{
}

RidePartLoader::~RidePartLoader(void)
{
}

void RidePartLoader::Load3ds( const char* Path, const char* Name, ObjectNode* pBaseNode )
{
   C3DSHandler cds;
   Gfx::Texture* texs[16];
   memset( texs, 0, sizeof(texs) );
   char buf[256];
   // removed the _s, so it might have a buffer overrun now!
   strcpy (buf, Path);
   strcat (buf, Name);
   //char* pdest = strrchr( buf, '/' );
   //*(pdest++) = 0;
   Gfx::ImageManager& IMan = *(Gfx::ImageManager::GetInstance());
   IMan.set_path(Path);

   if( cds.Load( buf ) )
   {
      Lib3dsFile* pFile = cds.GetFile();
      Gfx::MaterialsList* MatList = NULL; //Mats[8];
      int iTMax = 0;
      if( pFile->nmaterials > 0 )
      {
         iTMax = pFile->nmaterials; // <= 32) ? pFile->nmaterials : 32;
         MatList = new Gfx::MaterialsList(pFile->nmaterials);
         Material** Mats = MatList->GetMats();
         //glGenTextures( iTMax * 2, tex );
         for( int idx = 0; idx < iTMax; ++idx )
         {
            Lib3dsMaterial *pMat = pFile->materials[idx];
            Material* pGLMat = new Material( pMat->shading, pMat->two_sided, pMat->blur,
                                             pMat->self_illum, pMat->shininess, pMat->shin_strength, pMat->transparency );
            pGLMat->SetLight( pMat->ambient, pMat->diffuse, pMat->specular );
            //assert(pMat)
            if( pMat->texture1_map.name && strlen(pMat->texture1_map.name) > 0)
            {
               char szName[256];
               // removed the _s, should check lengths.
               //strcpy( szName, buf );
               //strcat( szName, "/" );
               //strcat( szName, pMat->texture1_map.name );//mat.diffuseMaterialMap.bitmap_filter );
               strcpy( szName, pMat->texture1_map.name );
               if( strlen(szName) > 11 && !(szName[8] == '.'))
               {
                  size_t iNameLen = strlen(szName);
                  for( size_t ixc = 9; ixc < iNameLen; ++ixc)
                  {
                     if(szName[ixc] == '.')
                     {
                        szName[ixc] = 0;
                        break;
                     }
                  }
                  strcat (szName, ".png");
               }
               int iChannels = GL_RGBA;
               Gfx::Texture* pTex = IMan.GetTexture(szName, iChannels);
               texs[idx] = pTex;
               pGLMat->SetTexture(pTex);


               //png_color pngColor;
               //png_uint_32 iWide = 0;
               //png_uint_32 iHeight = 0;
               //int iChannels = 4;
               //png_byte* pImage = new png_byte[iWide * iHeight * 4 + 64];

               //PngLoadImage( szName, &pImage, &iWide, &iHeight, &iChannels, &pngColor );

               //glBindTexture(GL_TEXTURE_2D, tex[idx]);
               //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
               //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
               //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

               //png_byte* pMirImage = new png_byte[iWide * iHeight * 4 + 64]; // Ping Pong
               //int iBytesW = iWide * iChannels;
               //for( unsigned int idx = 0, irx = iHeight-1; idx < iHeight; ++idx )
               //{
               //   memcpy( pMirImage+(idx * iBytesW), pImage+(irx * iBytesW), iBytesW );
               //   irx--;
               //}

               // Finally we define the 2d texture
               //if( iChannels == 3)
               //{
               //   glTexImage2D(GL_TEXTURE_2D, 0, iChannels, iWide, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pMirImage);
               //   gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGB, GL_UNSIGNED_BYTE, pMirImage);
               //}
               //else
               //{
               //   glTexImage2D(GL_TEXTURE_2D, 0, iChannels, iWide, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pMirImage);
               //   gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, pMirImage);
               //}
               //glTexEnvi (GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
               //glEnable (GL_BLEND);
               //delete [] pMirImage;
               //delete [] pImage;
            }
            Mats[idx] = pGLMat;
         }
      }
      //if( !tex[0] )
      //{
      //   tex[0] = 1;
      //}

      float pn[3];
      //ObjectNode* pNode = ObjectFactory::CreateNode( pFile->nmeshes );
      float fRRLoc[4] = { 1,0.5,2,0 };
      float fSTLoc[4] = { -31,0.5,85,0 };
      float fTALoc[4] = { 24,1,40,0 };
      float fHRLoc[4] = { 10,-60,-40,0 };
      float fRot[4] = { 0,270,0,0 };
      float fRot2[4] = { 270,0,0,0 }; // polyp
      float fRot3[4] = { 270,-22,0,0 }; // octo
      float frx = 1.0f;
      if (_strnicmp(Name,"Tag",3) == 0)
      {
         frx = 4;
         //pNode->Move(fTALoc);
         pBaseNode->Move(fTALoc);
      }
      else if (_strnicmp(Name,"hrt",3) == 0)
      {
         frx = 5;
         //pNode->Move(fHRLoc);
         pBaseNode->Move(fHRLoc);
      }
      else if (_strnicmp(Name,"brn",3) == 0)
      {
         frx = 1;
      }
      else if (_strnicmp(Name,"JMO",3) == 0)
      {
         frx = 0.1f;
         //pNode->Move(fTALoc);
         pBaseNode->Move(fTALoc);
      }
      else if (_strnicmp(Name,"oct",3) == 0)
      {
         frx = 1;
         pBaseNode->Move(fRRLoc);
         pBaseNode->SetRotation(fRot3);
      }
      else if (_strnicmp(Name,"sta",3) == 0)
      {
         frx = 1.0f/18; // inches to feet
         //pNode->Move(fSTLoc);
         //pNode->SetRotation(fRot);
         pBaseNode->Move(fSTLoc);
         pBaseNode->SetRotation(fRot);
      }
      else
      {
         frx = 1;
         //pNode->Move(fRRLoc);
         pBaseNode->Move(fRRLoc);
         pBaseNode->SetRotation(fRot2);
      }

      //pBaseNode->AddNode( pNode );
      int MatIndexes[32];
      memset (MatIndexes, 0, sizeof(MatIndexes));
      for( int idx = 0; idx < pFile->nmeshes; idx++ )
      {
         Lib3dsMesh* pMesh = pFile->meshes[idx];
         float(* pNormals)[3] = new float[pMesh->nfaces+1][3];
         unsigned short(* pFaces)[3] = new unsigned short[pMesh->nfaces+1][3];
         unsigned int(* pMatIndexes) = new unsigned int[pMesh->nfaces+1];
         for( int ifx = 0; ifx < pMesh->nfaces; ++ifx )
         {
            int ia = pFaces[ifx][0] = pMesh->faces[ifx].index[0];
            int ib = pFaces[ifx][1] = pMesh->faces[ifx].index[1];
            int ic = pFaces[ifx][2] = pMesh->faces[ifx].index[2];
            lib3ds_vector_normal( pn, pMesh->vertices[ia], pMesh->vertices[ib], pMesh->vertices[ic] );
            pNormals[ifx][0] = pn[0];
            pNormals[ifx][1] = pn[1];
            pNormals[ifx][2] = pn[2];
            pMatIndexes[ifx] = pMesh->faces[ifx].material;
         }
         if(pMesh->texcos)
         {
            SimpleMeshObject* pGLMesh = ObjectFactory::CreateMesh();
            pGLMesh->SetScale (frx);
            //pNode->AddMesh( pGLMesh );
            pBaseNode->AddMesh( pGLMesh );

            pGLMesh->AddMatrix( pMesh->matrix );
            pGLMesh->SetMaterials (MatList);

            pGLMesh->AddMesh( pMesh->nvertices, pMesh->vertices, pNormals, pMesh->nvertices, pMesh->texcos, pMesh->nfaces, pFaces, pMatIndexes );
            delete [] pFaces;
            delete [] pNormals;
         }
         else
         {
            SimpleMatMeshObject* pGLMesh = ObjectFactory::CreateMatMesh();
            pGLMesh->SetScale (frx);
            //pNode->AddMesh( pGLMesh );
            pBaseNode->AddMesh( pGLMesh );

            pGLMesh->AddMatrix( pMesh->matrix );
            pGLMesh->SetMaterials (MatList);

            pGLMesh->AddMesh( pMesh->nvertices, pMesh->vertices, pNormals, pMesh->nfaces, pFaces, pMatIndexes );
            delete [] pFaces;
            delete [] pNormals;
         }
      }
   }
   IMan.set_path("data/");
}

void RidePartLoader::LoadASE( const char* Path )
{
//   ASE_Scene* pSE = ASE_loadFilename( (char*)Path );
//   char buf[256];
//   strcpy_s( buf, 256, Path );
//   char* pdest = strrchr( buf, '\\' );
//   *(pdest++) = 0;
//
//   GLuint tex[16];
//   memset( tex, 0, 16 );
//   if( pSE )
//   {
//      CMaterial* Mats[4];
//      Mats[0] = 0;
//      if( pSE->objectCount > 0 )
//      {
//         int iTMax = (pSE->materialCount <= 8) ? pSE->materialCount : 8;
//         glGenTextures( iTMax * 2, tex );
//         for( int idx = 0; idx < iTMax; ++idx )
//         {
//            ASE_Material& mat = pSE->materials[idx];
//            CMaterial* pGLMat = new CMaterial( GL_SMOOTH, 0, 0, mat.selfIllum, mat.shine, mat.shinestrength, mat.transparency );
//            pGLMat->SetLight( (float*)&mat.ambient, (float*)&mat.diffuse, (float*)&mat.specular );
//            Mats[idx] = pGLMat;
//
//            png_color pngColor;
//            png_uint_32 iWide = 0;
//            png_uint_32 iHeight = 0;
//            int iChannels = 0;
//            png_byte* pImage = new png_byte[iWide * iHeight * 4 + 64];
//
//            char buf2[256];
//            strcpy_s( buf2, 256, buf );
//            strcat_s( buf2, 256, "\\testtrash.png" );//mat.diffuseMaterialMap.bitmap_filter );
//            PngLoadImage( buf2, &pImage, &iWide, &iHeight, &iChannels, &pngColor );
//
//            glBindTexture(GL_TEXTURE_2D, tex[idx]);
//		      //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // Low power video
//		      //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//
//      gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
//      glTexEnvi (GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//      glEnable (GL_BLEND);
////      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//            //glTexImage2D( GL_TEXTURE_2D, iChannels, 3, 128, 128,0, GL_RGBA, GL_UNSIGNED_BYTE, pImage );
//            //glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//            //glTexSubImage2D( GL_TEXTURE_2D, 0, 3, 128, 128,0, GL_ALPHA, GL_UNSIGNED_BYTE, pImage );
//            delete [] pImage;
//         }
//      }
//      if( !tex[0] )
//      {
//         tex[0] = 1;
//      }
//      if( pSE->objectCount > 0 )
//      {
//         CObjectNode* pNode = new CObjectNode( pSE->objectCount, 460 );
//         this->m_pObjectTree->AddNode( pNode );
//
//         for( int idx = 0; idx <  pSE->objectCount; idx++ )
//         {
//            ASE_GeomObject& pObj = pSE->objs[idx];
//            ASE_Mesh& pMesh = pObj.mesh;
//
//            CSimpleMeshObject* pGLMesh = gObjectFactory.CreateMesh();
//            pGLMesh->AddMaterials( 1, Mats[0] ); // this id is borked pMesh.faces[0].mtlid] );
//
//            pNode->AddMesh( pGLMesh );
//            unsigned short(* pFaces)[3] = new unsigned short[pMesh.faceCount+1][3];
//            float(* pUVs)[2] = new float[pMesh.faceCount*3+4][2];
//            int iUV = 0;
//            for( int ifx = 0; ifx < pMesh.faceCount; ++ifx )
//            {
//               int mid = pMesh.faces[ifx].mtlid;
//
//               pFaces[ifx][0] = (unsigned short)pMesh.faces[ifx].vertex[0];
//               pFaces[ifx][1] = (unsigned short)pMesh.faces[ifx].vertex[1];
//               pFaces[ifx][2] = (unsigned short)pMesh.faces[ifx].vertex[2];
//               int iA = pMesh.faces[ifx].texture_coordinates[0];
//               int iB = pMesh.faces[ifx].texture_coordinates[1];
//               int iC = pMesh.faces[ifx].texture_coordinates[2];
//               pUVs[iUV][0] = pMesh.texture_coordinates[iA].x;
//               pUVs[iUV++][1] = pMesh.texture_coordinates[iA].y;
//               pUVs[iUV][0] = pMesh.texture_coordinates[iB].x;
//               pUVs[iUV++][1] = pMesh.texture_coordinates[iB].y;
//               pUVs[iUV][0] = pMesh.texture_coordinates[iC].x;
//               pUVs[iUV++][1] = pMesh.texture_coordinates[iC].y;
//            }
//   //         pGLMesh.AddMatrix( pMesh.matrix );
//            pGLMesh->AddMesh( pMesh.vertexCount, (float(*)[3])pMesh.vertices, (float(*)[3])pMesh.vertex_normals,
//                              iUV, (float(*)[2])pUVs, //pMesg.textcoordinatecount, pMesh.texture_coordinates,
//                              pMesh.faceCount, pFaces );
//            delete [] pFaces;
//            delete [] pUVs;
//         }
//      }
//   }
}

void RidePartLoader::LoadMS3D (const char *Path, const char* Name, ObjectNode* pBaseNode)
{
   CMS3DFile cds;
   Gfx::Texture* texs[16];

   memset( texs, 0, sizeof(texs) );
   char buf[256];
   // removed _s should do a length check
   strcpy( buf, Path );
   char* pdest = strrchr( buf, '/' );
   *(pdest++) = 0;
   Gfx::ImageManager& IMan = *(Gfx::ImageManager::GetInstance());

   if( cds.LoadFromFile( Path ) )
   {
      Material* Mats[8];
      Mats[0] = 0;
      int iMatCount = 0;
      if( cds.GetNumMaterials() > 0 )
      {
       	glDisable(GL_DEPTH_TEST);												// Stop Depth Testing

         int iTMax = (cds.GetNumMaterials() <= 8) ? cds.GetNumMaterials() : 8;
         int iTexMax = 0;
         iMatCount = iTMax;
         ms3d_material_t* pMat;
         for( int idx = 0; idx < iTMax; ++idx )
         {
            cds.GetMaterialAt( idx, &pMat );
            //assert(pMat)
            if( strlen(pMat->texture) )
            {
               iTexMax++;
            }
         }

         //glGenTextures( iTexMax, tex );
         int iTexNo = 0;

         for( int idx = 0; idx < iTMax; ++idx )
         {
            cds.GetMaterialAt( idx, &pMat );
            //assert(pMat)
            if( strlen(pMat->texture) )
            {
//               png_color pngColor;
//               png_uint_32 iWide = 0;
//               png_uint_32 iHeight = 0;
//               int iChannels = 4;
//               png_byte* pImage = new png_byte[iWide * iHeight * 4 + 64];
//
//               char buf2[256];
//               strcpy_s( buf2, 256, buf );
//               strcat_s( buf2, 256, "\\" );
//               strcat_s( buf2, 256, pMat->texture );//mat.diffuseMaterialMap.bitmap_filter );
//
//               PngLoadImage( buf2, &pImage, &iWide, &iHeight, &iChannels, &pngColor );
//
//               glBindTexture(GL_TEXTURE_2D, tex[iTexNo]);
//               glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//               glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//               glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//               glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//
//               //png_byte* pMirImage = new png_byte[iWide * iHeight * 4 + 64]; // Ping Pong
//               int iBytesW = iWide * iChannels;
//               //for( unsigned int ipx = 0, irx = iHeight-1; ipx < iHeight; ++ipx )
//               //{
//               //   memcpy( pMirImage+(ipx * iBytesW), pImage+(irx * iBytesW), iBytesW );
//               //   irx--;
//               //}
//
//               // Finally we define the 2d texture
//               if( iChannels == 3)
//               {
////                  gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGB, GL_UNSIGNED_BYTE, pImage);
////                  glTexEnvi (GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//                  glTexImage2D(GL_TEXTURE_2D, 0, iChannels, iWide, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage);
//                  gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGB, GL_UNSIGNED_BYTE, pImage);
//               }
//               else
//               {
//                  gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
//                  glTexEnvi (GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
////                  glTexImage2D(GL_TEXTURE_2D, 0, iChannels, iWide, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pMirImage);
////                  gluBuild2DMipmaps( GL_TEXTURE_2D, iChannels, iWide, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, pMirImage);
//               }
//               glTexEnvi (GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//               //glEnable (GL_BLEND);
//               //delete pMirImage;
//               delete [] pImage;
               char szName[256];
               // removed _s, should do a length check
               strcpy( szName, buf );
               strcat( szName, "/" );
               strcat( szName, pMat->texture );//mat.diffuseMaterialMap.bitmap_filter );
               int iChannels = 4;
               Gfx::Texture* pTex = IMan.GetTexture(szName,4);
               texs[iTexNo] = pTex;
               iTexNo++;
            }
            else
            {

            }
            Material* pGLMat = new Material( pMat->mode, 0, 0.0, pMat->emissive[0], pMat->shininess, pMat->specular[0], pMat->transparency );
            pGLMat->SetLight( pMat->ambient, pMat->diffuse, pMat->specular );
            Mats[idx] = pGLMat;
         }
      }
      //if( !tex[0] )
      //{
      //   tex[0] = 1;
      //}

      ComponentObject* pNode = ObjectFactory::CreateComponent();// new CComponentObject( 461 );
      pBaseNode->AddNode( pNode );

      int iVerts = cds.GetNumVertices();
      int iFaces = cds.GetNumTriangles();
      int iMax = iFaces*3 +1;
      float(* pVertexes)[3] = new float[iMax][3];
      for( int ifx = 0; ifx < iVerts; ++ifx )
      {
         ms3d_vertex_t* pVert;
         cds.GetVertexAt( ifx, &pVert );
         pVertexes[ifx][0] = pVert->vertex[0];
         pVertexes[ifx][1] = pVert->vertex[1];
         pVertexes[ifx][2] = pVert->vertex[2];
      }
      pNode->AddMaterials( iMatCount, Mats );

      pNode->AddMesh( iVerts, pVertexes, cds.GetNumGroups() );

      for( int idx = 0; idx < cds.GetNumGroups(); ++idx )
      {
         ms3d_group_t* pMesh;
         cds.GetGroupAt(idx, &pMesh );
         int iTexNo = (pMesh->materialIndex >= 0) ? pMesh->materialIndex : 0;
         MeshGroup* pGroup = pNode->AddMeshGroup( idx, pMesh->numtriangles, pMesh->materialIndex, texs[iTexNo] );
         for( int ifx = 0; ifx < pMesh->numtriangles; ++ifx )
         {
            int index = pMesh->triangleIndices[ifx];
            ms3d_triangle_t* pTrig;
            cds.GetTriangleAt( index, &pTrig );
            pGroup->AddMeshFace( ifx, pTrig->vertexIndices[0], pTrig->vertexNormals[0], pTrig->s[0], pTrig->t[0],
                                      pTrig->vertexIndices[1], pTrig->vertexNormals[1], pTrig->s[1], pTrig->t[1],
                                      pTrig->vertexIndices[2], pTrig->vertexNormals[2], pTrig->s[2], pTrig->t[2] );
         }
      }

      delete [] pVertexes;
      cds.Clear();
      for( int idx = 0; idx < iMatCount; ++idx )
      {
         delete Mats[idx];
      }
   }

}
