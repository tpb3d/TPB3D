// Builders/WaterTable.cpp - Implementation of water table classes
#include "../Builders/WaterTable.h"


//WaterTable methods
bool
WaterTable::
	PushPointInMapBounds(short px,short py,WaterTableStack&stack)	{
		if(PointOnTable(px,py))	{
			if(!water(px,py).IsSet())	{
				stack.Push(px,py);
				return true;
				}
			else	{
				return false;	}
			}
		else	{
			return false;
			}
		}	//PushinBounds()
bool
WaterTable::
	FloodTileNeighborPusher(short px,short py,WaterTableStack&stack)	{
		enum	{u=0,r,d,l} dirs;
		bool sides[4];
		short xo[4]	=	{	0,1,0,-1	};
		short yo[4]	=	{	-1,0,1,0	};
		int tpx;	int tpy;
		for(int i=0;i<4;i++)	{	sides[i]=false;	}
		for(int i=0;i<4;i++)	{
			tpx=px+xo[i];	tpy=py+yo[i];
			sides[i]=PointOnTable(tpx,tpy)
				?((!water(tpx,tpy).IsSet())
					?IsLandPointUnderWater(tpx,tpy)
					:false)
				:false;
			if(sides[i])	{
				bool pushrv;
				pushrv=PushPointInMapBounds(tpx,tpy,stack);
				#define setaftpush 1
				#if setaftpush
				water(tpx,tpy).SetOn();
				#endif
				}
			}
		//push border tiles according to these rules
			//if any single land corner is under water, push the diagonal tile in the corner's direction
			//if two adjacent land corners are under water, push the edge tile in the edge's direction
		/*
		enum	{u=0,r,d,l} edges;
		enum	{ul=0,ur,dl,dr} diags;
		bool corners[4];	bool sides[4];
		short ttx;	short tty;
		//step through corners
		for(int i=0;i<4;i++)	{	int txo=i%2;	int tyo=i/2;
			corners[i]=IsLandPointUnderWater(ttx=tx+txo,tty=ty+tyo);
			if(corners[i])
				PushTileInMapBounds(ttx=tx-1+txo*2,tty=ty-1+tyo*2,stack);
			++i;
			}	//for i
		//int sum=0;
		//for(int i=0;i<4;i++)	{	sum+=i%2+1;	sides[i]=corners[i]&&corners[(sum%4)];	}
		sides[u]=corners[ul]&&corners[ur];
		sides[d]=corners[dl]&&corners[dr];
		sides[l]=corners[ul]&&corners[dl];
		sides[r]=corners[ur]&&corners[dr];
		if(sides[u])	PushPointInMapBounds(ttx=tx,tty=ty-1,stack);
		if(sides[d])	PushTileInMapBounds(ttx=tx,tty=ty+1,stack);
		if(sides[l])	PushTileInMapBounds(ttx=tx-1,tty=ty,stack);
		if(sides[r])	PushTileInMapBounds(ttx=tx+1,tty=ty,stack);
		*/
		/*
		//alternate push neighbors code
		struct NeighborTile	{
			short x;	short y;	bool setf; WaterTable*parent;
			void Inc(short xo,short yo)	{
				x+=xo;	y+=yo;	setf=parent->IsTileInMapBounds(x,y)?parent->water(x,y).IsSet():false;
				}
			};
		struct NeigborCorner	{
			NeigborTiley
			};
		NeighborTile neighborTiles[3][3]=
			{
				{	{	-1,-1,false,this	},	{	0,-1,false,this	},	{	+1,-1,false,this	}	},
				{	{	-1,0,false,this	},	{	0,0,false,this	},	{	+1,0,false,this	}	},
				{	{	-1,+1,false,this	},	{	0,+1,false,this	},	{	+1,+1,false,this	}	}
			};
		for(int iy=0;iy<3;iy++)	{	for(int ix=0;ix<3;ix++)	{
			neighborTiles[iy][ix].Inc(tx,ty);
			}	}
		*/

		//sides[0]=corners[0]&&corners[1];	//n
		//sides[1]=corners[1]&&corners[3];	//e
		//sides[2]=corners[2]&&corners[0];	//s
		//sides[3]=corners[3]&&corners[2];	//w
		return true;
		}
// ! WaterTable methods
