//  --------------------------------------------------------------------
//  Copyright (C)2009  Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Ride loader class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/ObjectTree.h"
#include "../Graphics/SimpleMeshObject.h"
#include "../Graphics/ObjectNode.h"
#include "../Graphics/Material.h"
#include "../Graphics/Image.h"
#include "../Graphics/ComponentObject.h"
#include "../Graphics/ObjectFactory.h"

#include "../Storage/MS3DFile.h"
#include "../Storage/3DSHandler.h"
#include "RidePartLoader.h"

#include <lib3ds.h>
//#include "../libASE-1.0/libASE.h"
//#include "png.h"



//static void png_cexcept_error(png_structp png_ptr, png_const_charp msg)
//{
//   if(png_ptr)
//   {
//   }
//#ifndef PNG_NO_CONSOLE_IO
//   fprintf(stderr, "libpng error: %s\n", msg);
//#endif
//   {
//      throw msg;
//   }
//}
//// local pong
//bool PngLoadImage( const char* pstrFileName, png_byte **ppbImageData,
//                  png_uint_32 *piWidth, png_uint_32 *piHeight, int *piChannels, png_color *pBkgColor )
//{
//   static FILE        *pfFile;
//   png_byte            pbSig[8];
//   int                 iBitDepth;
//   int                 iColorType;
//   double              dGamma;
//   png_color_16       *pBackground;
//   png_uint_32         ulChannels;
//   png_uint_32         ulRowBytes;
//   png_byte           *pbImageData = *ppbImageData;
//   static png_byte   **ppbRowPointers = NULL;
//   //    int                 i;
//
//   // open the PNG input file
//
//   if (!pstrFileName)
//   {
//      *ppbImageData = pbImageData = NULL;
//      return false;
//   }
//
//   //if (!(pfFile = fopen(pstrFileName, "rb")))
//   //{
//   //   *ppbImageData = pbImageData = NULL;
//   //   return false;
//   //}
//
//   //// first check the eight byte PNG signature
//
//   //fread(pbSig, 1, 8, pfFile);
//   //if (!png_check_sig(pbSig, 8))
//   //{
//   //   *ppbImageData = pbImageData = NULL;
//   //   return false;
//   //}
//
//   //// create the two png(-info) structures
//
//   //png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
//   //   (png_error_ptr)png_cexcept_error, (png_error_ptr)NULL);
//   //if (!png_ptr)
//   //{
//   //   *ppbImageData = pbImageData = NULL;
//   //   return false;
//   //}
//
//   //png_infop info_ptr = png_create_info_struct(png_ptr);
//   //if (!info_ptr)
//   //{
//   //   png_destroy_read_struct(&png_ptr, NULL, NULL);
//   //   *ppbImageData = pbImageData = NULL;
//   //   return false;
//   //}
//
//   try
//   {
//
//      // initialize the png structure
//
//#if !defined(PNG_NO_STDIO)
//      png_init_io(png_ptr, pfFile);
//#else
//      png_set_read_fn(png_ptr, (png_voidp)pfFile, png_read_data);
//#endif
//
//      png_set_sig_bytes(png_ptr, 8);
//
//      // read all PNG info up to image data
//
//      png_read_info(png_ptr, info_ptr);
//
//      // get width, height, bit-depth and color-type
//
//      png_get_IHDR(png_ptr, info_ptr, piWidth, piHeight, &iBitDepth,
//         &iColorType, NULL, NULL, NULL);
//
//      // expand images of all color-type and bit-depth to 3x8 bit RGB images
//      // let the library process things like alpha, transparency, background
//
//      if (iBitDepth == 16)
//         png_set_strip_16(png_ptr);
//      if (iColorType == PNG_COLOR_TYPE_PALETTE)
//         png_set_expand(png_ptr);
//      if (iBitDepth < 8)
//         png_set_expand(png_ptr);
//      if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
//         png_set_expand(png_ptr);
//      if (iColorType == PNG_COLOR_TYPE_GRAY ||
//         iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
//         png_set_gray_to_rgb(png_ptr);
//
//      // set the background color to draw transparent and alpha images over.
//      if (png_get_bKGD(png_ptr, info_ptr, &pBackground))
//      {
//         png_set_background(png_ptr, pBackground, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
//         pBkgColor->red   = (png_byte) pBackground->red;
//         pBkgColor->green = (png_byte) pBackground->green;
//         pBkgColor->blue  = (png_byte) pBackground->blue;
//      }
//      else
//      {
//         pBkgColor = NULL;
//      }
//
//      // if required set gamma conversion
//      if (png_get_gAMA(png_ptr, info_ptr, &dGamma))
//         png_set_gamma(png_ptr, (double) 2.2, dGamma);
//
//      // after the transformations have been registered update info_ptr data
//
//      png_read_update_info(png_ptr, info_ptr);
//
//      // get again width, height and the new bit-depth and color-type
//
//      png_get_IHDR(png_ptr, info_ptr, piWidth, piHeight, &iBitDepth,
//         &iColorType, NULL, NULL, NULL);
//
//
//      // row_bytes is the width x number of channels
//
//      ulRowBytes = png_get_rowbytes(png_ptr, info_ptr);
//      ulChannels = png_get_channels(png_ptr, info_ptr);
//
//      *piChannels = ulChannels;
//
//      // now we can allocate memory to store the image
//
//      if (pbImageData)
//      {
//         delete [] pbImageData;
//         pbImageData = NULL;
//      }
//      try
//      {
//         int bytes = ulRowBytes * (*piHeight) * sizeof(png_byte);
//         pbImageData = (png_byte *) new png_byte[ bytes  ];
//      }
//      catch( ... )
//      {
//         png_error(png_ptr, "Visual PNG: out of memory");
//      }
//      *ppbImageData = pbImageData;
//
//      // and allocate memory for an array of row-pointers
//
//      try
//      {
//         int bytes = *piHeight;
//         ppbRowPointers = (png_byte **) new png_byte*[ bytes  ];
//      }
//      catch( ... )
//      {
//         png_error(png_ptr, "Visual PNG: out of memory");
//      }
//
//      // set the individual row-pointers to point at the correct offsets
//
//      for( unsigned int i = 0; i < (*piHeight); i++)
//         ppbRowPointers[i] = pbImageData + i * ulRowBytes;
//
//      // now we can go ahead and just read the whole image
//
//      png_read_image(png_ptr, ppbRowPointers);
//
//      // read the additional chunks in the PNG file (not really needed)
//
//      png_read_end(png_ptr, NULL);
//
//      // and we're done
//
//      delete [] ppbRowPointers;
//      ppbRowPointers = NULL;
//
//      // yepp, done
//   }
//
//   catch( const char* msg)
//   {
//      // handleerror( "RidePartLoader", msg );
//      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
//
//      *ppbImageData = pbImageData = NULL;
//
//      if(ppbRowPointers)
//      {
//         delete [] ppbRowPointers;
//      }
//      fclose(pfFile);
//      return false;
//   }
//
//   fclose (pfFile);
//
//   return true;
//}


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
      ObjectNode* pNode = ObjectFactory::CreateNode( pFile->nmeshes );
      float fRRLoc[4] = { -20,0.5,55,0 };
      float fSTLoc[4] = { -31,0.5,85,0 };
      float fTALoc[4] = { 24,1,40,0 };
      float fHRLoc[4] = { 10,-60,-40,0 };
      float fRot[4] = { 0,270,0,0 };
      float frx = 1.0f;
      if (_strnicmp(Name,"Tag",3) == 0)
      {
         frx = 4;
         pNode->Move(fTALoc);
      }
      else if (_strnicmp(Name,"hrt",3) == 0)
      {
         frx = 5;
         pNode->Move(fHRLoc);
      }
      else if (_strnicmp(Name,"brn",3) == 0)
      {
         frx = 1;
      }
      else if (_strnicmp(Name,"JMO",3) == 0)
      {
         frx = 0.1f;
         pNode->Move(fTALoc);
      }
      else if (_strnicmp(Name,"sta",3) == 0)
      {
         frx = 1.0f/12; // inches to feet
         pNode->Move(fSTLoc);
         pNode->SetRotation(fRot);
      }
      else
      {
         frx = 3;
         pNode->Move(fRRLoc);
      }

      pBaseNode->AddNode( pNode );
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
         SimpleMeshObject* pGLMesh = ObjectFactory::CreateMesh();
         pGLMesh->SetScale (frx);
         pNode->AddMesh( pGLMesh );

         pGLMesh->AddMatrix( pMesh->matrix );
         pGLMesh->SetMaterials (MatList);

         pGLMesh->AddMesh( pMesh->nvertices, pMesh->vertices, pNormals, pMesh->nvertices, pMesh->texcos, pMesh->nfaces, pFaces, pMatIndexes );
         delete [] pFaces;
         delete [] pNormals;
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
