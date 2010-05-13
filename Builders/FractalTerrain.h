#pragma once

//Builders/FractalTerrain.h
#include "../Types/MathStuff.h"

class FractalTerrainMap{
	public:
	float*heights;
	union{short width;short w;};
	union{short height;short h;};
	float lnlo;		float lnhi;
	typedef enum{	diag=0,axis=1	}direction;
	FractalTerrainMap(short swidth,short sheight,float base,float shi){
		lnhi=ln(shi);		lnlo=-lnhi;	w=swidth;	h=sheight;
		heights=(float*)malloc(sizeof(float)*w*h);
		GetStartHeights();
		}//FractalTerrain() constructor
	void GetStartHeights(){
		for(int ix=0;ix<w;ix++){
			for(int iy=0;iy<h;iy++){
				float randPwr=frand()*2*lnhi-lnhi;
				ht(ix,iy)=exp(randPwr);
				}
			}
		}
	//DoubleTheVertices(): double the vertices
	void DoubleTheVertices(){
		short ow=w;	short oh=h;
		w=w*2-1;	h=h*2-1;
		float*ohts=heights;
		heights=(float*)malloc(sizeof(float)*w*h);
		for(int pass=0;pass<2;pass++){
			for(int ix=0;ix<w;ix++){
				for(int iy=0;iy<h;iy++){
					if((ix&1)==0&&(iy&1)==0)	{	//even
						if(pass==0)	ht(ix,iy)=ohts[iy/2*ow+ix/2];	}
					else  /*odd*/
					if(pass==1&&((ix&1)==1&&(iy&1)==1))	{	//do x pass (diagonal)
						GenFractalHeight(ix,iy,diag);	}
					else if(pass==2&&((ix&1)==0||(iy&1)==0))	{	//do + pass (udlr or nsew)
						GenFractalHeight(ix,iy,axis);	}
					}//for iy
				}//for ix
			}//for pass
		free(ohts);
		}
	//GenFractalHeight():	generate a fractal height between pre-
	//						established heights
	void GenFractalHeight(long x,long y,FractalTerrainMap::direction d){
		float nh,ah[2],htbase,s[2],span;
		float h[4];
		switch(d){
			case diag:	//0=ne 1=nw 2=sw 3=se
				h[0]=ht(x+1,y+1);/*ne or 45*/	h[1]=ht(x-1,y+1);/*nw or 135*/
				h[2]=ht(x-1,y-1);/*sw or 225*/	h[3]=ht(x+1,y-1);/*se or 315*/
				break;
			case axis:	//0=e 1=n 2=w 3=s
				h[0]=ht(x+1,y);/*e or 0*/		h[1]=ht(x,y+1);/*n or 90*/
				h[2]=ht(x-1,y);/*w or 180*/		h[3]=ht(x,y-1);/*s or 270*/
				break;
			}//switch d
		switch(d){
			case diag:	case axis:
				for(int i=0;i<2;i++){	ah[i]=Avg(h[i],h[i+2]);	s[i]=abs(h[i]-h[i+2]);	}
				htbase=max(ah[0],ah[1]);		span=max(s[0],s[1]);
				nh=frand()*span+htbase-span/2;	ht(x,y)=nh;
				break;
			}//switch d
		}
	//ht(): reference the heights array as pair of coordinates
	float&ht(short x,short y){
		return(heights[y*w+x]);
	}
	long TotalEntries(){	return((long)width*height);	}
	};//class FractalTerrainMap
//=========================================================================================

