//implementation of PngImage class

#include "../Graphics/pngFile.h"

#include <stdlib.h>
#include <memory.h>


short
PngImageDot::
	GetLuma(){
		short luma=((short)r*30+(short)g*59+(short)b*11)/100;
		return luma;
		}

/*
PngImage::
	~PngImage(){	if(pd.Data)free(pd.Data);	if(pd.Palette)free(pd.Palette);		}
*/
PngImageDot&
PngImage::
	dot(int x,int y){
		if(pd.Components==4)	return(*(PngImageDot*)imgptr(x,y));
		else	{
			if(pd.Components==1)//palette
				dot4=color(pd.Data[ImgIndex(x,y)]);
			else if(pd.Components==3)	{	//rgb+shared alpha
				memcpy(&dot4,&pd.Data[ImgIndex(x,y)],3);
				dot4.a=pd.Alpha;
				}
			else //what?
				memset(&dot4,0,4);
			return(dot4);
			}
		}


