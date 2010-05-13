// CoreObjects/CoastlineGen.cpp
// This is a set of methods for generating coastlines
// Since the z point is assumed to be the same throughout the coast (or at least inconsequent), this only uses 2d arrays.

#include "../Builders/CoastlineGen.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "../Types/MathStuff.h"
//#include <algorithm>
//using namespace std;

// the following has been moved to ../types/mathstuff.h
/*

short ShortRand(void){
	short r;		static short ncalls=0;		short callThreshold=10;
	if(ncalls>=callThreshold)	{	srand(time(NULL));ncalls=0;	}
	else						++ncalls;
	r=rand()%0x8000;
	//std::cout<<r<<" "<<inited<<"\r\n";
	return(r);
	}

short RandSign(v1oid)	{	return((ShortRand()%2==0)?1:-1);	}
template<class InRangeType>
	bool InRange(InRangeType a,InRangeType l,InRangeType h){	return(l>h?InRange(a,h,l):a>=l&&a<=h);	}

float frand(){
	float fr=(float)(ShortRand())/0x8000l;
	//std::cout<<fr<<"\r\n";
	return(fr);
	}
float frandCenter(float c,float distFrom)	{
	distFrom=abs(distFrom);
	return(frand()*distFrom*2+c-distFrom);
	}
float SignedFloatRand(){	return(RandSign()*frand());	}
float ScaledRand(float scale){			return(frand()*scale);		}
float SignedScaledRand(float span){			return(frand()*span-(span/2));		}
float nzsign(float n){	return(n>=0?1:-1);	}
*/

bool operator == (Vector2f a,Vector2f b){		return(a.x==b.x&&a.y==b.y);		}

Vector2f PointAvg(Vector2f point1,Vector2f point2){
	Vector2f pavg=point1%point2;
    return(pavg);
    }

Vector2f
World::
	GetRandPoint(){
		Vector2f point(SignedScaledRand(width),SignedScaledRand(height));
		return(point);
		}
void
IslandCoastline::
	RefineCoastPointNoX(int i){
		int maxTries=10;
		bool xingCheck=false;int tries=0;
		do{
			RefineCoastPoint(i);
			xingCheck=CheckForXing(i,i);
			;
			}	while(xingCheck&&(++tries)<maxTries);
		}
void
IslandCoastline::
	RefineCoast(){
		//Add more random points between the existing ones
		numPoints=2*numPoints-1;//double the points
		Vector2f*oldPoints=points;
		points=(Vector2f*)calloc(numPoints,sizeof(Vector2f));
		for(int i=0;i<numPoints;i+=2){	//even points - copy point from last array
			points[i]=oldPoints[i/2];
			}/*for i*/
		for(int i=1;i<numPoints;i+=2){	//odd points - get random point
			this->RefineCoastPointNoX(i);
			}/*for i*/
		free(oldPoints);
		}//RefineCoast
void
IslandCoastline::
	RefineCoastPoint(int i){
		//bread and butter function - makes a new refinement of the coast
		float SmallestNum=0.00001f;
		float deltax=points[i+1].x-points[i-1].x;    if(abs(deltax)<SmallestNum)deltax=nzsign(deltax)*SmallestNum; //prevent division by zero
		float deltay=points[i+1].y-points[i-1].y;    if(abs(deltay)<SmallestNum)deltay=nzsign(deltay)*SmallestNum; //prevent div by zero
		float slope=deltay/deltax;        float normal=-1/slope;
		float distMax=pow(pow(deltax,2)+pow(deltay,2),1.0f/2.0f);      //^ may need to be defined as a power function for floats
		//halfDist
		distMax/=2.f;
		distMax*=distVariation; //distVariation should be a value in the IslandCoastline structure/class
			//distVariation basically specifies the flatness of each refinement
		float dist=ScaledRand(distMax); //randomizer may need to be initialized
		points[i]=PointAvg(points[i-1],points[i+1]);
		//pointOfsAbs.x=sqrt(dist^2/(1+normal^2));
		//pointOfsAbs.y=sqrt(dist^2-pointOfsAbs.x^2);
		Vector2f pointOfs(0,0);
		//point offsets in absolute values
		//=SQRT(Y90^2/(1+U90^2))
		pointOfs.x=RandSign()*sqrt(pow(dist,2)/(1+pow(normal,2)));
		//SQRT(Y90^2-Z90^2)
		//pointOfs.y=sqrt(pow(dist,2)-pow(pointOfs.x,2));
		//signed point offsets
		pointOfs.x*=RandSign();
		pointOfs.y=normal*pointOfs.x;
		points[i].x+=pointOfs.x;    points[i].y+=pointOfs.y;
		//point=this->GetRandPointNoX(i);
		//This function could alternatively be rewritten to simply find a random point in
				//the bounding box ((x1,y1),(y2,y2))
		}//RefineCoastPoint
IslandCoastline::
	IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,Vector2f point4,float dv){
		//if(points)free(points);
		Vector2f pa[]={point1,point2,point3,point4};
		Init(5,pa,dv);
		}
	//3 point constructor
IslandCoastline::
	IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,float dv){
		//if(points)free(points);
		Vector2f pa[]={point1,point2,point3};
		Init(4,pa,dv);
		}
//the following function should only be called by constructors.
void
IslandCoastline::
	Init(int np,Vector2f initpts[],float dv){
		numPoints=np;	distVariation=dv;	points=NULL;
		points=(Vector2f*)calloc(numPoints,sizeof(Vector2f));
		for(int i=0;i<numPoints-1;i++)	{	points[i]=initpts[i];	}
		FullCircle();
		}
void
IslandCoastline::
	Init0(int np,float dv){
		numPoints=np;	distVariation=dv;
		points=(Vector2f*)realloc(points,numPoints*sizeof(Vector2f));
		for(int i=0;i<numPoints;i++)	{	points[i]=Vector2f(0.f,0.f);	}
		}
bool
IslandCoastline::
	ThereIsAnIntersection(Vector2f p1,Vector2f p2,Vector2f p3,Vector2f p4){
		//if any two points are the same, return false
		if(		p1==p2||p1==p3||p1==p4||p2==p3||p2==p4||p3==p4		)	{
			return(false);
			}
		//step through the points in the coastline, and see if any line intersects the new
		//prospective one
		float numeA=(p4.x-p3.x)*(p1.y-p3.y)-(p1.x-p3.x)*(p4.y-p3.y);
		float numeB=(p2.x-p1.x)*(p1.y-p3.y)-(p1.x-p3.x)*(p2.y-p1.y);
		float denom=(p2.x-p1.x)*(p4.y-p3.y)-(p4.x-p3.x)*(p2.y-p1.y);
		//check for parallel and coincident lines
		if(denom==0.0f){
			if(numeA==0.0f&&numeB==0.0f)
				return(false); //COINCIDENT
			return(false);//PARALLEL;
			}//if denom
		float ua=numeA/denom;		float ub=numeB/denom;
		if(ua>=0.0f&&ua<=1.0f&&ub>=0.0f&&ub<=1.0f)	{
			// Get the intersection point.
			Vector2f intersection;
			intersection.x=p1.x+ua*(p2.x-p1.x);
			intersection.y=p1.y+ua*(p2.y-p1.y);
			std::cout<<"There was an intersection between \r\n"
					<<"\t("<<p1.x<<","<<p1.y<<")<->("<<p2.x<<","<<p2.y<<")\r\n"
					<<"\t\t and\r\n"
					<<"(\t"<<p3.x<<","<<p3.y<<")<->("<<p4.x<<","<<p4.y<<")\r\n"
					;
			return(true);
			}
		return(false);
		}//ThereIsAnIntersection
bool
IslandCoastline::
	CheckForXing(int i,int stopI){
		bool xingCheck=false;int j;
		for(j=0;j<stopI&&!xingCheck;j++){
			if(j<stopI){
				if(i<numPoints-1)
					xingCheck=xingCheck||this->ThereIsAnIntersection(points[i],points[i+1],points[j],points[j+1]);
				xingCheck=xingCheck||this->ThereIsAnIntersection(points[i-1],points[i],points[j],points[j+1]);
				}
			}
		return xingCheck;
		}
#define debugCoastGenAppendFlag 1
void
IslandCoastline::
GenIsland(int NumStartPoints,int NumCoastRefinements,bool alreadyInitialized){
	//initial points
	float dv=this->distVariation;
	int nLoops=NumCoastRefinements;
	refineRound=0;
	if(!alreadyInitialized)		{
		const float ws=10.0f;
		World world(ws,ws);
		numPoints=NumStartPoints;
		for(int i=0;i<=numPoints;i++){
			GenRandPointNoX(i,world);
			}/*for*/
		}
	//subsequent points
	float base=1.25f;
	CoastalGenPrintout(0,"dumpCoastalGen1.txt");
	for(int j=1;j<=nLoops;j++){
		//Add more random points between the existing ones
		distVariation=dv/pow(base,j);
		refineRound=j;
		this->RefineCoast();
		char file[]="dumpCoastalGen0.txt    ";
		sprintf(file,"dumpCoastalGen%01i.txt",
				#if debugCoastGenAppendFlag
					1
				#else
					refineRound
				#endif
				);
		CoastalGenPrintout(refineRound,file);
		}
	#if debugCoastalGen
	#endif// debugCoastalGen
	distVariation=dv;
	}//GenIsland
#if debugCoastalGen
#if(debugCoastalGen==1)
void
IslandCoastline::
	CoastalGenPrintout(short i,char*file)	{
		FILE*f;char mode[3];
		if(this->refineRound!=0&&debugCoastGenAppendFlag)	{	strcpy(mode,"a");		}
		else strcpy(mode,"w+");
		f=fopen(file,mode);
		if(!f)			return;
		fprintf(f,"Vector printout for island refinement %d\r\n",i);
		fprintf(f,"point#\tx\ty\t\r\n");
		for(int i=0;i<numPoints;i++){
			fprintf(f,"%i:\t%0.3f\t%0.3f\t\r\n",i,points[i].x,points[i].y);
			}//for
		fclose(f);
		}//CoastalGenPrintout
#elif(debugCoastalGen==2)
void
IslandCoastline::
	CoastalGenPrintout(short i)	{
		char s[64];

		sprintf(s,"Vector printout for island %d\r\n",i);	std::cout<<s;
		sprintf(s,"point#\tx\ty\t\r\n");				std::cout<<s;
		for(int i=0;i<numPoints;i++){
			sprintf(s,"%i:\t%0.3f\t%0.3f\t\r\n",i,points[i].x,points[i].y);	std::cout<<s;
			}//for
		}//CoastalGenPrintout
#endif// if==
#endif// debugCoastalGen

void
IslandCoastline::
RadialCoastInDegrees(int nRefinements,float angleStep,float avgRadius,float dv){
	float pi=3.14159f; //3.1415927c
	bool useDegrees=true;// to use later for a function that takes both radians and degrees
	float angleStepRadians;	float a;	float r;
	int npts=0;	int i;
	if(useDegrees)angleStepRadians=angleStep/180*pi;
	else angleStepRadians=angleStep;
	npts=trunc(2*pi/angleStepRadians)+1;
	Init0(npts,dv);
	//std::cout<<"Radial Island Maker: ("<<angleStepRadians<<")\r\n";

	for(i=0,a=0;i<npts-1;i++,a+=angleStepRadians){
		r=frandCenter(avgRadius,avgRadius*dv/2);
		points[i].x=r*cos(a);
		points[i].y=r*sin(a);
		//std::cout<<"Radius: "<<r<<"\tAngle: "<<a<<"\r\n";
		}
	FullCircle();
	GenIsland(npts,nRefinements,true);
	}
float
IslandCoastline::
	GetEdge(IslandCoastline::edge e){
		float ge=0.f;
		float largeVal=1.0E+07f;
		switch(e){
			case(IslandCoastline::redge):	case(IslandCoastline::dedge):	ge=largeVal;	break;
			case(IslandCoastline::ledge):	case(IslandCoastline::uedge):	ge=-largeVal;	break;
			default:			return(ge);
			}//switch
		for(int i=0;i<numPoints;i++){
			switch(e){
				case(IslandCoastline::redge):	ge=Max(ge,points[i].x);	break;
				case(IslandCoastline::ledge):	ge=Min(ge,points[i].x);	break;
				case(IslandCoastline::dedge):	ge=Max(ge,points[i].y);	break;
				case(IslandCoastline::uedge):	ge=Min(ge,points[i].y);	break;
				default:														break;
				}//switch
			}//for
		return(ge);
		}//GetEdge
Vector2f operator*(Vector2f v,float s){
	Vector2f mv(v.x*s,v.y*s);
	return(mv);
	}
bool
IslandCoastline::
	IsPointOnIsland(Vector2f p){
		const float step=0.5f;
		bool oic;
		float x=0.f; float l=this->GetEdge(IslandCoastline::ledge);	float y=0.f;
		Vector2f ip(0.f,0.f);	//intersection point
		Vector2f dp;
		float s;	float denom;	float nume;
		long leftCount=0;	//polygon crossing count left of the test point
		short iinc=1;
		for(int i=0;i<numPoints-1;i+=iinc){
			if(p.y==points[i].y){	//equals start point -
				iinc=1;
				float xmin=points[i].x;
				//while loop: counts an entire horizontal line as one crossing
				while(i+iinc<numPoints&&p.y==points[i+iinc].y){
					xmin=Min(xmin,points[i+iinc].x);
					iinc++;
					}//while
				if(p.x>=xmin){
					++leftCount;
					if(i==numPoints-1)
						--leftCount;
					}
				}//if p.y==points[i].y
			else if(p.y==points[i+1].y)//don't add to leftCount, It will come up next in the loop
				iinc=1;
			else if(InRange<float>(p.y,points[i].y,points[i+1].y))	{	/*within ys*/
				dp=points[i+1]+(-points[i]);
				nume=p.y-points[i].y;	denom=dp.y;	s=nume/denom;
				ip=points[i]+dp*s;
				if(ip.x<p.x)	{	++leftCount;	}
				iinc=1;
				}//else if inrange()
			else
				iinc=1;
			//vCheck=vCheck&&points[i].y!=points[i+1].y;	//
			}//for i
		//if there are an odd amount of crossings, the point is on the island; even crossing counts fall outside the bounds of the island
		oic=(leftCount&1)==1;
		return(oic);
		}//IsPointOnIsland
//scale island
IslandCoastline&
IslandCoastline::
	operator*=(float s){
		for(int i=0;i<numPoints;i++){
			points[i].x*=s;
			points[i].y*=s;
			}//for i
		return(*this);
		}//operator *=
//offset island
IslandCoastline&
IslandCoastline::
	operator+=(Vector2f o){
		for(int i=0;i<numPoints;i++){
			points[i].x+=o.x;
			points[i].y+=o.y;
			}//for i
		return(*this);
		}
IslandCoastline&
IslandCoastline::
	operator+=(float o){
		for(int i=0;i<numPoints;i++){
			points[i].x+=o;
			points[i].y+=o;
			}//for i
		return(*this);
		}
//negative island
IslandCoastline
IslandCoastline::
	operator-(){
		IslandCoastline ic=*this;
		for(int i=0;i<numPoints;i++){
			ic.points[i].x=-ic.points[i].x;
			ic.points[i].y=-ic.points[i].y;
			}//for i
		return(ic);
		}
bool
IslandCoastline::
	BooleanCombo(bool onIsle,IslandCoastline::boolMask ibmask,Vector2f pt){
		bool r=onIsle;
		switch(ibmask){
			case (IslandCoastline::OR):
				r=r||IsPointOnIsland(pt);			break;
			case (IslandCoastline::XOR):
				r=(r&1)^(IsPointOnIsland(pt)&1);	break;
			case (IslandCoastline::AND):
				r=r&&this->IsPointOnIsland(pt);			break;
			case (IslandCoastline::NOT):
				r=r&&!IsPointOnIsland(pt);	break;
			default:
				r=r||IsPointOnIsland(pt);			break;
			}//switch ibmask
		return(r);
		// error: prototype for ‘bool IslandCoastline::BooleanCombo(bool, IslandCoastline::boolMask, Vector2f)’ does not match any in class ‘IslandCoastline’|
		}//BooleanCombo()




