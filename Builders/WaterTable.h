// Builders/WaterTable.cpp - Declaration of water table classes
#pragma once
#include <stdlib.h>
#include "../Types/MathStuff.h"

struct LandPoint	{
	float x;	//point along width axis
	float y;	//point along length axis
	float z;	//point along height axis
	void Init(float sx,float sy,float sz)	{
		x=sx;	y=sy;	z=sz;
		}
	LandPoint()	{	Init(0,0,0);	}
	LandPoint(float sx,float sy,float sz)	{	Init(sx,sy,sz);	}
	};//LandPoint;

struct WaterTablePoint	{
	float x;	//point along width axis
	float y;	//point along length axis
	float z;	//point along height axis
	union {	bool setflag;	bool f;	};
	void Init(float sx,float sy,float sz,bool sf)	{
		x=sx;	y=sy;	z=sz;	f=sf;
		}
	WaterTablePoint()	{	Init(0,0,0,false);	}
	WaterTablePoint(float sx,float sy,float sz,bool sf)	{	Init(sx,sy,sz,sf);	}
	WaterTablePoint(float sx,float sy,float sz)	{	Init(sx,sy,sz,false);	}
	void SetOn()	{	f=true;	}
	void SetOff()	{	f=false;	}
	bool Toggle()	{	return(this->f=!(this->f));	}
	bool IsSet()	{	return(this->f);	}
	};//WaterTablePoint

struct WaterTableStackEntry	{
	short x;	short y;
	bool usedflag;
	WaterTableStackEntry()	{	x=0;	y=0;	}
	WaterTableStackEntry(short sx,short sy)	{	x=sx;	y=sy;	}
	bool operator==(WaterTableStackEntry e)	{
		bool rv=x==e.x&&y==e.y&&usedflag==e.usedflag;
		return rv;
		}
	};//WaterTableStackEntry

//#define maxWaterTableStackEntries 10000

class WaterTableStack	{
	public:
	WaterTableStackEntry*entries;
	short stacki;
	long ntiles;
	bool testForOnStack;
	WaterTableStack(bool stestForOnStack,long sntiles){
		ntiles=sntiles;
		entries=new WaterTableStackEntry[ntiles];
		stacki=-1;		testForOnStack=stestForOnStack;
		for(int i=0;i<ntiles;i++)	{
			entries[i]=WaterTableStackEntry(0,0);
			}
		}
	~WaterTableStack()	{	delete[]entries;	}
	bool AlreadyOnStack(WaterTableStackEntry&e)	{
		if(testForOnStack)	{
			for(int i=0;i<stacki;i++)	{
				if(e==entries[i])	{
					return true;
					}
				}
			}
		return false;
		}
	bool Push(short xo,short yo)	{	return(Push(WaterTableStackEntry(xo,yo)));	}
	bool Push(WaterTableStackEntry e)	{
		if(stacki+1<ntiles-1&&!AlreadyOnStack(e))	{
			entries[++stacki]=e;	return(true);	}
		else
			return(false);
		}
	bool Pop(WaterTableStackEntry&e)	{
		if(stacki>-1)	{
			e=entries[stacki--];	return(true);	}
		else						return(false);
		}
	bool Pop(WaterTablePoint&rwaterPoint,WaterTablePoint*waterPoints,short pw)	{
		WaterTableStackEntry e;		bool rv=Pop(e);
		if(rv)	rwaterPoint=waterPoints[e.y*pw+e.x];
		return(rv);
		}
	};

struct WaterTableBoundBox	{
	union	{	float l;	float left;	};	//2 aliases for the same value
	union	{	float t;	float top;	};
	union	{	float r;	float right;	};
	union	{	float b;	float bottom;	};
	WaterTableBoundBox(float sl,float st,float sr,float sb)	{
		l=sl;	t=st;	r=sr;	b=sb;
		}
	WaterTableBoundBox(float sw,float sh)	{
		l=-sw/2;	t=-sh/2;	r=sw/2;	b=sh/2;
		}
	WaterTableBoundBox()	{
		l=0;	t=0;	r=0;	b=0;
		}
	inline float width(){	return(Abs(r-l));	}
	inline float depth(){	return(Abs(t-b));	}
	bool OverlapsWith(WaterTableBoundBox bb2)	{
		bool rv=false;
		rv=rv||InBox(bb2.l,bb2.t)||InBox(bb2.l,bb2.b)||InBox(bb2.r,bb2.t)||InBox(bb2.r,bb2.b);
		return(rv);
		}
	bool InBox(float x,float y)	{
		bool rv=false;
		rv=x>=l&&x<=r&&y>=t&&y<=b;
		return(rv);
		}
	};

class WaterTable	{
	public:
	//data
	union{	short tw;	short tileWidth;	short nwidthTiles;	};	//aliases
	union{	short tl;	short tileLength;	short nlengthTiles;	};
	union{	float tuw;	float tileUnitWidth;	};	//aliases
	union{	float tul;	float tileUnitLengh;	};
	union{	float sharedheight;	float z;	};
	WaterTablePoint*waterPoints;
	LandPoint*landPoints;
	WaterTableBoundBox bounds;
	inline short PointWidth()	{	return(tileWidth+1);	}
	inline short pw()	{	return(tileWidth+1);	}
	inline short PointLength()	{	return(tileLength+1);	}
	inline short pl()	{	return(tileLength+1);	}
	//constructors
	void Init(short stw,short stl,float stuw,float stul,bool flood,float floodHt,float*landHtTbl)	{
		tw=stw;	tl=stl;	tuw=stuw;	tul=stul;
		waterPoints=new WaterTablePoint[pw()*pl()];
		landPoints=new LandPoint[pw()*pl()];
		for(int py=0;py<pw();py++)	{	for(int px=0;px<pw();px++)	{
			ConvertTile2World(water(px,py).x,water(px,py).y,px,py);
			ConvertTile2World(land(px,py).x,land(px,py).y,px,py);
			land(px,py).z=landHtTbl[py*pw()+px];
			}	}	//for px and py
		if(flood)	FloodIgnoreLand(floodHt);
		else		WaterDrain();
		z=floodHt;	SetWaterLevel(z);
		}
	WaterTable(short stw,short stl,float stuw,float stul,bool flood,float floodHt,float*landHtTbl)	{
		Init(stw,stl,stuw,stul,flood,floodHt,landHtTbl);
		}
	WaterTable()	{
		}
	void Destroy()	{
		delete [] landPoints;
		delete [] waterPoints;
		}
	~WaterTable()	{	Destroy();	}
	//methods
	inline bool PointOnTable(short x,short y)	{	return(x>=0&&x<pw()&&y>=0&&y<pl());	}
	inline bool TileOnTable(short x,short y)	{	return(x>=0&&x<tw&&y>=0&&y<tl);	}
	WaterTablePoint&water(short x,short y)	{	return(waterPoints[pw()*y+x]);	}
	LandPoint&land(short x,short y)	{	return(landPoints[pw()*y+x]);	}
	void WaterDrain()	{
		for(int ipy=0;ipy<pl();ipy++)	{	for(int ipx=0;ipx<pw();ipx++)	{
			water(ipx,ipy).SetOff();
			}	}	//for itx and ity
		}
	bool FloodFillRandom(float szlo,float szhi)	{
		float seedx=frandRange(-tw/2*tuw,tw/2*tuw);
		float seedy=frandRange(-tl/2*tul,tw/2*tul);
		float seedz=frandRange(szlo,szhi);
		return FloodFill(seedx,seedy,seedz);
		}
	bool FloodFillRandom(float sxlo,float sxhi,float sylo,float syhi,float szlo,float szhi)	{
		float seedx=frandRange(sxlo,sxhi);
		float seedy=frandRange(sylo,syhi);
		float seedz=frandRange(szlo,szhi);
		return FloodFill(seedx,seedy,seedz);
		}
	bool FloodFill(float seedx,float seedy,float seedz)	{
		return(FloodFill(WaterTablePoint(seedx,seedy,seedz,false)));
		}	//FloodFill() with coords
	public:
	//bool IsPointInMapBounds(short px,short py)	{	return(px>=0&&px<pw()&&py>=0&&py<pl());	}
	private:
	bool 	PushPointInMapBounds(short px,short py,WaterTableStack&stack)	;
   bool FloodTileNeighborPusher(short tx,short ty,WaterTableStack&stack)	{ return false; }
	public:
	bool FloodFill(WaterTablePoint seed)	{
		WaterDrain();
		WaterTableStack stack(false,pw()*pl());
		short px;short py;
		ConvertWorld2Point(px,py,seed.x,seed.y);
		//SetWaterLevel(seed.z);
		//test if seed tile is on table
		if(!TileOnTable(px,py))	{
			//no: return
			return(false);	}
		//test if seed water point is above land
		if(IsLandPointUnderWater(px,py))	{
			//yes: push seed tile and start flood fill
			stack.Push(px,py);	}
		else	{
			//no: return false
			return(false);	}
		//for each point
			//pop tile from stack
		WaterTableStackEntry e;
		while(stack.Pop(e))	{
			//set water tile to true
			px=e.x;	py=e.y;
			water(px,py).SetOn();
			//push border tiles according to these rules
				//if any single land corner is under water, push the diagonal tile in the corner's direction
				//if two adjacent land corners are under water, push the edge tile in the edge's direction
			FloodTileNeighborPusher(px,py,stack);
			}	//while stack is not empty
		//return
		return(true);
		}	//	FloodFill()
	void ConvertTile2World(float&x,float&y,short tx,short ty)	{
		//this assumes the center of the world coords is (x=0,y=0)
		//this assumes the tile coords start at (tx=0,ty=0) ("northwest" corner of table if tilea were aligned to a geographic map)
		short tx0o;	short ty0o;		//"0o"	= zero origin
		tx0o=tx-tw/2;	ty0o=ty-tl/2;
		x=static_cast<float>(tx0o*tuw);		y=static_cast<float>(ty0o*tul);
		}
	void ConvertWorld2Tile(short&tx,short&ty,float x,float y)	{
		//this assumes the center of the world coords is (x=0,y=0)
		//this assumes the tile coords start at (tx=0,ty=0) ("northwest" corner of table if tilea were aligned to a geographic map)
		short tx0o;	short ty0o;		//"0o"	= zero origin
		tx0o=static_cast<short>(x/tuw);		ty0o=static_cast<short>(y/tul);
		tx=tx0o+tw/2;	ty=ty0o+tl/2;
		}
	void ConvertWorld2Point(short&px,short&py,float x,float y)	{
		//this assumes the center of the world coords is (x=0,y=0)
		//this assumes the tile coords start at (tx=0,ty=0) ("northwest" corner of table if tilea were aligned to a geographic map)
		short tx0o;	short ty0o;		//"0o"	= zero origin
		tx0o=static_cast<short>(x/tuw);		ty0o=static_cast<short>(y/tul);
		px=tx0o+pw()/2;	py=ty0o+pl()/2;
		}
	float WaterHeightAtPoint(short px,short py){
		return(water(px,py).z);
		}
	bool IsLandPointUnderWater(short px,short py){
		bool rv=PointOnTable(px,py);		if(!rv)	return(rv);
		rv=land(px,py).z<water(px,py).z;
		return(rv);
		}
	bool IsLandTileUnderWater(short tx,short ty)	{
		bool rv=	IsLandPointUnderWater(tx,ty)
					||	IsLandPointUnderWater(tx+1,ty)
					||	IsLandPointUnderWater(tx+1,ty+1)
					||	IsLandPointUnderWater(tx,ty+1)
					;
		return(rv);
		}
	void FloodIgnoreLand(float waterHt)	{
		for(int ipx=0;ipx<pw();ipx++)	{	for(int ipy=0;ipy<pl();ipy++)	{
			water(ipx,ipy).SetOn();	water(ipx,ipy).z=waterHt;
			}	}	//for itx and ity
		}
	//	WaterTable::GetBounds()
	// 	parameters:		none
	// 	returns:	 	were any tiles set to filled?
	bool GetTableBounds()	{
		float verylargeNumber=1.0e+12;
		float&vln=verylargeNumber;
		bounds=WaterTableBoundBox(+vln,+vln,-vln,-vln);
		long setcount=0;
		//go through array and find bounds
		for(int py=0;py<PointLength();py++)	{	for(int px=0;px<PointWidth();px++)	{
			WaterTablePoint&wp=water(px,py);
			if(wp.IsSet())	{
				bounds.left=Max(wp.x,bounds.left);		bounds.right=Min(wp.x,bounds.right);
				bounds.top=Max(wp.y,bounds.top);		bounds.bottom=Min(wp.y,bounds.top);
				++setcount;
				}	//if water point set
			}	}	//for px and py
		return(setcount>0);
		}
	bool operator&&(WaterTable&wt2)	{
		return(OverlapsWithSameDim(wt2));
		}
	bool OverlapsWithSameDim(WaterTable&wt2)	{
		bool overlap=false;
		//for simplicity and speed, only process tables with the same dimensions (no need for a nested for xy loop
		//	this guarantees that the xs and ys will be in the same place for both tables' points
		bool samedims=this->HasSameDimsAs(wt2);
		if(!samedims)	return(overlap=false);
		//find the boundaries
		//wt2.GetBounds();	GetBounds();
		//if bounding boxes overlap, a water body overlap is possible
		//if(bounds&&wt2.bounds)	{
			int py=0;	int px=0;
			for(py=0;py<PointLength()&&!overlap;py++)	{	for(px=0;px<PointWidth()&&!overlap;px++)	{
				bool bothset=water(px,py).IsSet()&&wt2.water(px,py).IsSet();
				overlap=overlap||bothset;
				}	}	//for px and py
		//	}	// ! if bound boxes overlap
		return(overlap);
		}
	bool HasSameDimsAs(WaterTable&wt2)	{
		bool samedims=wt2.tw==tw&&wt2.tl==tl&&wt2.tuw==tuw&&wt2.tul==tul;
		return(samedims);
		}
	bool IsOnSetWaterTile(short tx,short ty)	{
		short xo=tx==0?0:-1;		short yo=ty==0?0:-1;
		bool rv=water(tx,ty).IsSet()||water(tx+xo,ty).IsSet()||water(tx,ty+yo).IsSet()||water(tx+xo,ty+yo).IsSet();
		return(rv);
		}
	void SetWaterLevel(float sz)	{
		z=sz;
		for(int py=0;py<pl();py++)	{	for(int px=0;px<pw();px++)	{
			water(px,py).z=z;
			}	}	//for px and py
		}
	};//WaterTable
