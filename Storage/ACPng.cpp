#include <png.h>
#include <pngconf.h>
#include "ACPng.h"
#define USE_MATH_DEFINES
#include <cmath>

#define GL_MAX_TEXTURE_SIZE 256

int ACDot::GetLuma()
{
   return (int)sqrt((double)(r*r + g+g + b*b));
}

ACPng::ACPng(void)
{
   mScreenGamma = 1.0f;
   mMaxTextureSize = 0;
   mPalettedTextures = 0;
   mStandardOrientation = 0;
}


ACPng::~ACPng(void)
{
}

int ACPng::pngLoadRaw(const char *filename, pngRawInfo *pinfo)
{
   int result;
   FILE *fp = fopen(filename, "rb");
   if (fp == NULL) return 0;

   result = pngLoadRawF(fp, pinfo);

   if (fclose(fp) != 0)
   {
      return 0;
   }

   return result;
}

int ACPng::pngLoadRawF(FILE *fp, pngRawInfo *pinfo)
{
   unsigned char header[8];
   png_structp png;
   png_infop   info;
   png_infop   endinfo;
   png_bytep   data;
   png_bytep  *row_p;
#ifdef USE_GAMMA
   double	fileGamma;
#endif

   png_uint_32 width = 0;
   png_uint_32 height = 0;
   int depth = 0;
   int color = 0;

   png_uint_32 i;

   if (pinfo == NULL) return 0;

   fread(header, 1, 8, fp);
   if (!png_check_sig(header, 8)) return 0;

   png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   info = png_create_info_struct(png);
   endinfo = png_create_info_struct(png);

   png_init_io(png, fp);
   png_set_sig_bytes(png, 8);
   png_read_info(png, info);
   png_get_IHDR(png, info, &width, &height, &depth, &color, NULL, NULL, NULL);

   pinfo->Width  = width;
   pinfo->Height = height;
   pinfo->Depth  = depth;

   /*--GAMMA--*/
#ifdef USE_GAMMA
   checkForGammaEnv();
   if (png_get_gAMA(png, info, &fileGamma))
      png_set_gamma(png, mScreenGamma, fileGamma);
   else
#endif
      png_set_gamma(png, mScreenGamma, 1.0/2.2);

   png_read_update_info(png, info);

   data = new png_byte[ png_get_rowbytes(png, info)*height ];
   row_p = new png_bytep[height];
   for (i = 0; i < height; i++)
      row_p[i] = &data[png_get_rowbytes(png, info)*i];

   png_read_image(png, row_p);
   delete row_p;

   if (color == PNG_COLOR_TYPE_PALETTE)
   {
      int cols;
      png_get_PLTE(png, info, (png_colorp *) &pinfo->pPalette, &cols);
   }
   else
   {
      pinfo->pPalette = NULL;
   }

   if (color&PNG_COLOR_MASK_ALPHA)
   {
      if (color&PNG_COLOR_MASK_PALETTE || color == PNG_COLOR_TYPE_GRAY_ALPHA)
         pinfo->Components = 2;
      else
         pinfo->Components = 4;
      pinfo->Alpha = 8;
   }
   else
   {
      if (color&PNG_COLOR_MASK_PALETTE || color == PNG_COLOR_TYPE_GRAY)
         pinfo->Components = 1;
      else
         pinfo->Components = 3;
      pinfo->Alpha = 0;
   }

   pinfo->pData = data;

   png_read_end(png, endinfo);
   png_destroy_read_struct(&png, &info, &endinfo);

   return 1;
}

int ACPng::SafeSize(int i)
{
	int p;

	if (i > mMaxTextureSize) return mMaxTextureSize;

	for (p = 0; p < 24; p++)
   {
		if (i <= (1<<p))
			return 1<<p;
   }
	return mMaxTextureSize;
}

/* Resize the texture since gluScaleImage doesn't work on everything */
void ACPng::Resize(int components, const png_bytep d1, int w1, int h1, png_bytep d2, int w2, int h2)
{
	const float sx = (float) w1/w2, sy = (float) h1/h2;
	int x, y, xx, yy, c;
	png_bytep d;

	for (y = 0; y < h2; y++) {
		yy = (int) (y*sy)*w1;

		for (x = 0; x < w2; x++) {
			xx = (int) (x*sx);
			d = d1 + (yy+xx)*components;

			for (c = 0; c < components; c++)
				*d2++ = *d++;
		}
	}
}

int (* pngLoadFilter) ( const char *filename, int mipmap ) = 0;

int ACPng::pngLoad(const char *filename, int mipmap, int trans, pngInfo *pinfo)
{
   int result;

   // jonm : has the app requested mipmap filtering?
   if ( pngLoadFilter )
      mipmap = pngLoadFilter(filename, mipmap);

   // stevec : Optionally redirect this to the pix loader
#if PIX_SUPPORT_ACTIVE
   if ( _pix_PngLoadHook )
      return _pix_PngLoadHook (filename,mipmap,trans,pinfo);
#endif

   FILE *fp = fopen(filename, "rb");
   if (fp == NULL) return 0;

   result = pngLoadF(fp, mipmap, trans, pinfo);

   if (fclose(fp) != 0) return 0;

   return result;
}

// Dumped the GL dependent stuff - AC
int ACPng::pngLoadF(FILE *fp, int mipmap, int trans, pngInfo *pinfo)
{
   unsigned char header[8];
   png_structp png;
   png_infop   info;
   png_infop   endinfo;
   png_bytep   data, data2;
   png_bytep  *row_p;
#ifdef USE_GAMMA
   double	fileGamma;
#endif

   png_uint_32 width, height, rw, rh;
   //int depth, color;

   png_uint_32 i;

   fread(header, 1, 8, fp);
   if (!png_check_sig(header, 8)) return 0;

   png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   info = png_create_info_struct(png);
   endinfo = png_create_info_struct(png);

   png_init_io(png, fp);
   png_set_sig_bytes(png, 8);
   png_read_info(png, info);

   int color = 0;
   int depth = 0;
   png_get_IHDR(png, info, &width, &height, &depth, &color, NULL, NULL, NULL);

   if (pinfo != NULL)
   {
      pinfo->Width  = width;
      pinfo->Height = height;
      pinfo->Depth  = depth;
   }

#ifdef SUPPORTS_PALETTE_EXT
#ifdef _WIN32
   if (mMaxTextureSize == 0)
      glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mMaxTextureSize);

   if (PalettedTextures == -1)
      PalettedTextures = ExtSupported("GL_EXT_paletted_texture") && (strstr((const char *) glGetString(GL_VERSION), "1.1.0 3Dfx Beta") == NULL);

   if (PalettedTextures)
   {
      if (glColorTableEXT == NULL)
      {
         glColorTableEXT = (PFNGLCOLORTABLEEXTPROC) wglGetProcAddress("glColorTableEXT");
         if (glColorTableEXT == NULL)
            PalettedTextures = 0;
      }
   }
#endif
#endif

   if (mPalettedTextures == -1)
      mPalettedTextures = 0;

   if (color == PNG_COLOR_TYPE_GRAY || color == PNG_COLOR_TYPE_GRAY_ALPHA)
      png_set_gray_to_rgb(png);

   if (color&PNG_COLOR_MASK_ALPHA && trans != PNG_ALPHA)
   {
      png_set_strip_alpha(png);
      color &= ~PNG_COLOR_MASK_ALPHA;
   }

   if (!(mPalettedTextures && mipmap >= 0 && trans == PNG_SOLID))
   {
      if (color == PNG_COLOR_TYPE_PALETTE)
         png_set_expand(png);
   }

   /*--GAMMA--*/
#ifdef USE_GAMMA
   checkForGammaEnv();
   if (png_get_gAMA(png, info, &fileGamma))
      png_set_gamma(png, screenGamma, fileGamma);
   else
#endif
      png_set_gamma(png, mScreenGamma, 1.0/2.2);

   png_read_update_info(png, info);

   data = new png_byte [png_get_rowbytes(png, info)*height];
   row_p = new png_bytep [height];

   for (i = 0; i < height; i++)
   {
      if (mStandardOrientation)
         row_p[height - 1 - i] = &data[png_get_rowbytes(png, info)*i];
      else
         row_p[i] = &data[png_get_rowbytes(png, info)*i];
   }

   png_read_image(png, row_p);
   delete [] row_p;

   rw = SafeSize(width);
   rh = SafeSize(height);

   if (rw != width || rh != height)
   {
      const int channels = png_get_rowbytes(png, info)/width;

      data2 = new png_byte [rw*rh*channels];

      /* Doesn't work on certain sizes */
      /* 		if (gluScaleImage(glformat, width, height, GL_UNSIGNED_BYTE, data, rw, rh, GL_UNSIGNED_BYTE, data2) != 0)
      return 0;
      */
      Resize(channels, data, width, height, data2, rw, rh);

      width = rw, height = rh;
      delete data;
      data = data2;
   }
   png_read_end(png, endinfo);
   png_destroy_read_struct(&png, &info, &endinfo);

   delete [] data;

   return 1;
}

