// The following source is a derivative works with respect to Ben Wyatt and Dave McClurg
// Converted from the following authors by AlabamaCajun to C++ generic source.
/*
 * NOTICE: This is an altered version of LibPNG
 * It has been altered to work with TinyLIB
 * June-2000 : Ported to TinyLIB by Dave McClurg <dpm@efn.org>
 */

/*
 * PNG loader library for OpenGL v1.42
 * by Ben Wyatt ben@wyatt100.freeserve.co.uk
 * Using LibPNG 1.0.2 and ZLib 1.1.3
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the author be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is hereby granted to use, copy, modify, and distribute this
 * source code, or portions hereof, for any purpose, without fee, subject to
 * the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented. You must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered versions must be plainly marked as such and must not be
 *    misrepresented as being the original source.
 * 3. This notice must not be removed or altered from any source distribution.
 */

#pragma once

/* Transparency parameters */
enum PNG_Trasparency
{
   PNG_CALLBACK = -3, /* Call the callback function to generate alpha   */
   PNG_ALPHA,    //  -2 /* Use alpha channel in PNG file, if there is one */
   PNG_SOLID,    //  -1 /* No transparency                                */
   PNG_STENCIL,  //   0 /* Sets alpha to 0 for r=g=b=0, 1 otherwise       */
   PNG_BLEND1,   //   1 /* a = r+g+b                                      */
   PNG_BLEND2,   //   2 /* a = (r+g+b)/2                                  */
   PNG_BLEND3,   //   3 /* a = (r+g+b)/3                                  */
   PNG_BLEND4,   //   4 /* a = r*r+g*g+b*b                                */
   PNG_BLEND5,   //   5 /* a = (r*r+g*g+b*b)/2                            */
   PNG_BLEND6,   //   6 /* a = (r*r+g*g+b*b)/3                            */
   PNG_BLEND7,   //   7 /* a = (r*r+g*g+b*b)/4                            */
   PNG_BLEND8    //   8 /* a = sqrt(r*r+g*g+b*b)                          */
};

struct pngInfo
{
   int Width;
   int Height;
   int Depth;
   int Alpha;

   pngInfo()
   {
      Width = 0;
      Height = 0;
      Depth = 0;
      Alpha = 0;
   }
   bool IsValid () { return (Depth > 0); }
};

struct ACDot
{
   short r;
   short g;
   short b;
   short a;
   int  GetLuma();
};

struct pngRawInfo
{
   unsigned char* pData;
   png_colorp* pPalette;
   int Components;
   int Width;
   int Height;
   int Depth;
   int Alpha;

   pngRawInfo()
   {
      pData = NULL;
      pPalette = NULL;
      Width = 0;
      Height = 0;
      Depth = 0;
      Components = 0;
      Alpha = 0;
   }
   ~pngRawInfo()
   {
      delete [] pData;
      delete [] pPalette;
   }
   bool IsValid () { return ((pData != NULL) && (Depth > 0)); }
   ACDot dot (int x, int y);
};

inline ACDot pngRawInfo::dot (int x, int y)
{
   ACDot pixel;
   memset (&pixel, 0, sizeof(pixel));
   if (IsValid())
   {
      int vec = (y * Width + x) * Components;
      if(Components >= 3)
      {
         pixel.r = pData[vec+0];
         pixel.g = pData[vec+1];
         pixel.b = pData[vec+2];
         if(Components == 4)
         {
            pixel.a = pData[vec+3];
         }
      }
      if(Components >= 2)
      {
         // lame 15 or 16 bit color fail
      }
      else
      {
         // dig it out of the palette fail
      }
   }
   return pixel;
}

class ACPng
{
   float mScreenGamma;
   int   mMaxTextureSize;
   int   mPalettedTextures;
   bool  mStandardOrientation;
public:
   ACPng(void);
   ~ACPng(void);

   int pngLoadRaw(const char *filename, pngRawInfo *pinfo);
   int pngLoadRawF(FILE *fp, pngRawInfo *pinfo);
   int pngLoad(const char *filename, int mipmap, int trans, pngInfo *pinfo);
   int pngLoadF(FILE *fp, int mipmap, int trans, pngInfo *pinfo);
   int SafeSize(int i);
   void Resize(int components, const png_bytep d1, int w1, int h1, png_bytep d2, int w2, int h2);
};

