//pngfile.h
//A class for loading pngs, as readable data, mostly used for terrain height maps.

#pragma once

//#include "/usr/include/GL/glpng.h"
#ifdef WIN32
#include "png.h"
#else
#include <GL/glpng.h>
#endif
//#include "/usr/include/libpng12/png.h"
//#include "/usr/include/libpng12/pngconf.h"

//extern int APIENTRY pngLoadRaw(const char *filename, pngRawInfo *rawinfo);

struct PngImageDot{
	unsigned char r,g,b,a;
	PngImageDot(int sr,int sg,int sb,int sa){	r=sr;	g=sg;	b=sb;	a=sa;	return;	};
	PngImageDot(){	r=g=b=a=0;	}
	short GetLuma();
	};

class PngImage{
	public:
	union{	pngRawInfo pngData;	pngRawInfo pd;	};
	PngImageDot dot4;
	void Init()
   {
      pd.Data=NULL; 	pd.Palette=NULL;
   }
	PngImage()
   {
      Init();
   }
	PngImage(char*file)
   {
      Init();
      Load(file);
   }
	bool Load(char*file)
   {
      return (pngLoadRaw(file,&pd)!=0);
   }
	int ImgIndex(int x,int y)
   {
      int ii=y*pd.Width+x;	int i=pd.Components*ii;	return(i);
   }
	void*imgptr(int x,int y)
   {
      return((void*)&pd.Data[ImgIndex(x,y)]);
   }
	//color: reference palette entry as address
	PngImageDot&
	color(int entry)
   {
      PngImageDot*p=(PngImageDot*)pd.Palette;
      return(p[entry]);
   }
	//dot:	address of pixel only if there are 4 color Components, otherwise it just
	//		returns the address of the dot4 field, where it can't be used as an l-value to set the pixel
	PngImageDot& dot(int x,int y);
   ~PngImage() {}//{	if(pd.Data)free(pd.Data);	if(pd.Palette)free(pd.Palette);		}
};
