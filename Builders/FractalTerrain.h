#pragma once

//Builders/FractalTerrain.h
#include "../Types/MathStuff.h"
#include "../Graphics/pngFile.h"
#include <iostream>

class FractalTerrainMap{
	public:
	float*heights;
	union{short width;short w;};
	union{short depth;short d;};
	#define randExponential 1
	#define randFlat 2
	#define doRand randExponential
	//#if doRand==randFlat
	//low and high of the height range
	float lo; float hi;
	//#else //if doRand==randExponential
	//natural logarithms for low and high of height range
	float lnlo;		float lnhi;
	//#endif
	float spikiness;  // how "spikey" the terrain is, 1=normal
	bool varspike;	//use spikiness as a random range rather than a static scale in height calculation
	typedef enum{	diag=0,axis=1	}direction;
	float pctexpseeds;
	float gaussianSmoothRadius;
	short curRound;	short nrounds;
	FractalTerrainMap(char*pngfile,short swidth,short sdepth,float base,float shi,float sspikiness
					,bool svarspike,float spctexpseeds,float sgaussianSmoothRadius){
		nrounds=1;
		gaussianSmoothRadius=sgaussianSmoothRadius;
		pctexpseeds=spctexpseeds;
		hi=shi-base;		lo=base;
		lnhi=ln(hi);		lnlo=-lnhi;
		PngImage png;
		bool pngLoaded=(*pngfile)?png.Load(pngfile):false;
		if(pngLoaded)	{		w=png.pd.Width;		d=png.pd.Height;		}
		else	{		w=swidth;	d=sdepth;		}
		spikiness=sspikiness;	varspike=svarspike;
		heights=(float*)malloc(sizeof(float)*w*d);
		if(pngLoaded)	GetStartHeightsFromPng(png);
		else			GetStartHeights(base);
		}//FractalTerrain() constructor
	void GetStartHeightsFromPng(PngImage&png){
		for(int y=0;y<d;y++){	for(int x=0;x<w;x++){
			short luma=png.dot(x,y).GetLuma();
			float lumaf=(float)luma/255;
			float h,l,span;
			l=lo;	h=hi;
			span=l-h;
			float height=l+(h-l)*lumaf;
			ht(x,y)=height;
			}	}
		}
	void GetStartHeights(float base){
		srand(time(NULL));
		float totalHeight=0.f;	short npoints=w*d;	float avgVal=0.f;
		for(int iy=0;iy<d;iy++){
			for(int ix=0;ix<w;ix++){
				float rv=frand();
				enum	{	balanced=1,exponential=2	}	seedmode;
				if(rv<pctexpseeds)		seedmode=exponential;
				else					seedmode=balanced;
				if(seedmode==balanced)		{
					float randVal=frand()*(hi-lo)+lo;
					ht(ix,iy)=base+randVal;			}
				else /*if(seedmode==this->exponential)*/	{
					float randPwr=frand()*(lnhi-lnlo)+lnlo;
					ht(ix,iy)=base+exp(randPwr);			}
				totalHeight+=ht(ix,iy);
				}//for x
			}//for y
		avgVal=totalHeight/npoints;
		std::cout<<"GetStartHeights():\tAverage="<<avgVal<<"\r\n";
		}
	//Fractalize(): double the vertices and fractalize
	void Fractalize(){
		#define dumpFractMap 1
		#if dumpFractMap
		for(int iy=0;iy<d;iy++){
			std::cout<<"line y="<<iy<<": ";
			for(int ix=0;ix<w;ix++){
				std::cout<<round(ht(ix,iy)*10)/10<<"\t";
				}
			std::cout<<"\r\n";
			}
		#endif
		short ow=w;	short od=d;
		w=w*2-1;	d=d*2-1;
		float*ohts=heights;
		heights=(float*)malloc(sizeof(float)*w*d);
		for(int pass=0;pass<3;pass++){
			for(int iy=0;iy<d;iy++){
				for(int ix=0;ix<w;ix++){
					if((ix&1)==0&&(iy&1)==0)	{	//even
						if(pass==0){
							ht(ix,iy)=ohts[iy/2*ow+ix/2];
							if(isnan(ht(ix,iy))){
								std::cout<<"GenFractalHeight(): The height at ("<<ix<<","<<iy<<")\tis not a number\r\n";
								std::cout<<"\t\twidth: "<<w<<"\r\n";
								}
							}
						}
					else  /*odd*/
					if((ix&1)==1&&(iy&1)==1)	{	//do x pass (diagonal)
						if(pass==1)
							GenFractalHeight(ix,iy,diag);
							}
					else if((ix&1)==1||(iy&1)==1)	{	//do + pass (udlr or nsew)
						if(pass==2)
							GenFractalHeight(ix,iy,axis);
						}
					else
						std::cout<<"Fractalize(): point("<<ix<<","<<iy<<") not handled\tdim="<<w<<"x"<<d<<"\tpass="<<pass<<"\r\n";
					}//for ix
				}//for iy
			}//for pass
		free(ohts);
		//fill in the pits
		PitKiller();
		++curRound;
		if(curRound==nrounds)	{
			AltSmooth();
			//GaussianSmooth();
			}
		}
	void Fractalize(short ntimes){
		nrounds=ntimes;curRound=0;
		for(int i=0;i<ntimes;i++){
			std::cout<<"==== Fractalization round "<<i<<" ====\r\n";
			Fractalize();
			}
		}
	//GenFractalHeight():	generate a fractal height between pre-
	//						established heights
	void GenFractalHeight(long x,long y,FractalTerrainMap::direction dir){
		short ny=y-1,sy=y+1,ex=x+1,wx=x-1;
		float nh,ah[2],htbase,s[2],span;
		float h[4];
		switch(dir){
			case diag:	//0=ne 1=nw 2=sw 3=se
				//all diagonal points should be in bounds
				h[0]=ht(ex,ny);/*ne or 45*/		h[1]=ht(wx,ny);/*nw or 135*/
				h[2]=ht(wx,sy);/*sw or 225*/	h[3]=ht(ex,sy);/*se or 315*/
				break;
			case axis:	//0=e 1=n 2=w 3=s
				//test for border tiles and set out of border dimensions to the dimension opposite
				//...the current point (for averaging)
				if(x==0)	wx=ex;	if(x==w-1)	ex=wx;
				if(y==0)	ny=sy;	if(y==d-1)	sy=ny;
				h[0]=ht(ex,y);/*e or 0*/		h[1]=ht(x,ny);/*n or 90*/
				h[2]=ht(wx,y);/*w or 180*/		h[3]=ht(x,sy);/*s or 270*/
				break;
			}//switch d
		switch(dir){
			case diag:	case axis:
				float minv=Min(h);	float maxv=Max(h);
				for(int i=0;i<2;i++){	ah[i]=Avg(h[i],h[i+2]);	s[i]=Abs(h[i]-h[i+2]);	}
				short hdi;	//direction index of largest average height
				#define GenFractalHtIgnoreDirection 0
				#if GenFractalHtIgnoreDirection
				htbase=Avg(minv,maxv);	span=maxv-minv;
				#else
				hdi=ah[0]>ah[1]?0:1;
				htbase=ah[hdi];	span=s[hdi];
				#endif
				float adjspan=span*spikiness*(varspike?frand():1);
				nh=frand()*adjspan-adjspan/2+htbase;
				ht(x,y)=nh;
				//find pits
				#define FractalHtGenDebug 0
				#if FractalHtGenDebug
				if(x>0&&y>0&&x<w-1&&y<d-1)	{
					if(Avg(h)-nh>adjspan/3){//much lower than the average height
						std::cout<<"GetFractalHeight()@w="<<w<<": The height at ("<<x<<","<<y<<") may be too low. (ht="
								<<RoundPlaces(nh,2)<<",avg="<<RoundPlaces(Avg(h),2)<<",adjspan="<<RoundPlaces(adjspan,2)<<")\r\n";
						}
					}
				if(isnan(nh)){
					std::cout<<"GenFractalHeight(): The height at ("<<x<<","<<y<<")\tis not a number\r\n";
					std::cout<<"\t\tspan: "<<span<<"\thtbase: "<<htbase<<"\r\n";
					}
				#endif
				break;
			}//switch d
		}
	//Pitkiller(): step through the mesh and find any anomolous 'pits' of one node (temp function until I find out what is causing them)
	void PitKiller()	{
		#define watchNeighbors 1
		#if watchNeighbors
		float nh[3][3];	//neighborhood heights
		#endif
		for(int y=1;y<d-1;y++){		for(int x=1;x<w-1;x++){
			float sumv=0;	float maxv=-(1e+10f);	float minv=+(1e+10f);	float h;
			for(int yy=y-1;yy<=y+1;yy++){	for(int xx=x-1;xx<=x+1;xx++){
				#if watchNeighbors
				nh[yy-y+1][xx-x+1]=ht(xx,yy);
				#endif
				if(!(xx==x&&yy==y))	{	h=ht(xx,yy);
					sumv+=h;
					minv=Min(h,minv);
					maxv=Max(h,maxv);
					}//if not edge
				}	}//for xx and yy
			float avgv=sumv/8;	float span=maxv-minv;
			if(ht(x,y)<minv)	{//this is not a normal drop
				ht(x,y)=avgv;
				//std::cout<<"PitKiller() found pit at ("<<x<<","<<y<<")\r\n";
				}
			}	}//for x and y
		}

	//ht(): reference the heights array as pair of coordinates
	float&ht(short x,short y){
		return(heights[y*w+x]);
	}
	long TotalEntries(){	return((long)width*depth);	}
	//AltSmooth() - work on this
	void AltSmooth(){
		float radius=gaussianSmoothRadius;
		float unitsz=hi-lo;
		typedef float*fp;	short r=round(radius);
		if(r==0)	return;
		short ww;	short dd;		ww=dd=r*2+1;
		short nentries=ww*dd;
		fp neighbors=(float*)malloc(nentries*sizeof(float));	fp&n=neighbors;
		fp gausswts=(float*)malloc(nentries*sizeof(float));	fp&gw=gausswts;
		//calc blurs;
		std::cout<<"================= FractalTerrainMap::AltSmooth() =================\r\n";
		for(int y=0;y<d;y++){	for(int x=0;x<d;x++){
			for(int pass=0;pass<2;pass++){
				float dev;
				if(pass==1)
					dev=Stdev(n,nentries);
				for(int yy=y-r;yy<=y+r;yy++){	for(int xx=x-r;xx<=x+r;xx++){
					if(pass==0)													{
						int xxx=xx;	int yyy=yy;
						if(xxx<0||xxx>=w)	xxx=x;
						if(yyy<0||yyy>=y)	yyy=y;
						//set neighbor array entry
						n[(yy-(y-r))*ww+(xx-(x-r))]=(ht(xxx,yyy)-lo)/unitsz;	}
					else if(pass==1)	{
						//set gaussian weight
						float centerWt=1.5;
						int xxx=xx-x;		int yyy=yy-y;	float curwt;
						if(xx==x&&yy==y)	curwt=centerWt;
						else	{	curwt=1/(pow(xxx,2)+pow(yyy,2));	}
						xxx+=r;		yyy+=r;
						gw[yyy*ww+xxx]=curwt;
						}
					}	}//for xx and yy
				}//for pass
			float tht=WAvg(neighbors,gausswts,nentries)*unitsz+lo;
			//std::cout<<((float)round(ht(x,y)*10)/10)<<"<--"<<((float)round(tht*10)/10)<<"\t";
			ht(x,y)=tht;
			}//for x
			//std::cout<<"\r\n";
			}//for y
		free(neighbors);
		free(gausswts);
		}
	//Gaussian Smooth - still needs work
	void GaussianSmooth(){
		float radius=gaussianSmoothRadius;
		float unitsz=hi-lo;
		typedef float*fp;	short r=round(radius);
		if(r==0)	return;
		short ww;	short dd;		ww=dd=r*2+1;
		short nentries=ww*dd;
		fp neighbors=(float*)malloc(nentries*sizeof(float));	fp&n=neighbors;
		fp gausswts=(float*)malloc(nentries*sizeof(float));	fp&gw=gausswts;
		//calc blurs;
		for(int y=0;y<d;y++){	for(int x=0;x<d;x++){
			for(int pass=0;pass<2;pass++){
				float dev;
				if(pass==1)
					dev=Stdev(n,nentries);
				for(int yy=y-r;yy<=y+r;yy++){	for(int xx=x-r;xx<=x+r;xx++){
					if(pass==0)												{
						int xxx=xx;	int yyy=yy;
						if(xxx<0||xxx>=w)	xxx=xx;
						if(yyy<0||yyy>=y)	yyy=yy;
						//set neighbor array entry
						n[(yy-(y-r))*ww+(xx-(x-r))]=(ht(xxx,yyy)-lo)/unitsz;								}
					else if(pass==1)											{
						//set gaussian weight
						gw[(yy-(y-r))*ww+(xx-(x-r))]=CalcGaussianWeight(xx-x,yy-y,radius,dev);	}
					}	}//for xx and yy
				}//for pass
			float tht=WAvg(neighbors,gausswts,nentries)*unitsz+lo;
			ht(x,y)=tht;
			}	}//for x and y
		free(neighbors);
		free(gausswts);
		}


	};//class FractalTerrainMap
//=========================================================================================
