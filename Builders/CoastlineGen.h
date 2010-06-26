#pragma once

#include "../types/vector2.h"
#include <stdlib.h>
#include <math.h>
//#include <STDARG.H>

// This is a set of methods for generating coastlines
// The z point is assumed to be the same throughout the coast, this only uses 2d arrays.

// header above, cpp below

#define	debugCoastalGen 1

class World
{
public:
   World(float w,float h){	width=w;	height=h;	}
   Vector2f GetRandPoint();
   float width,height;
};

class IslandCoastline
{
protected:
   ~IslandCoastline();
public:
   Vector2f*points;
   long numPoints;
   float distVariation;
   short refineRound;
   typedef enum{	OR=0,XOR=1,AND=2,NOT=3	}boolMask;
   typedef enum	{		ledge,redge,uedge,dedge		}	edge;
   //4 point constructor
   IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,Vector2f point4,float dv);
   IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,float dv);
   void Init(int np,Vector2f initpts[],float dv);
   void Init0(int np,float dv);
   bool ThereIsAnIntersection(Vector2f p1,Vector2f p2,Vector2f p3,Vector2f p4);
   //Vector2 IslandCoastline::GenRandPointNoX(i)	{}
   bool CheckForXing(int i,int stopI);
   void RefineCoastPointNoX(int i);
   void GenRandPointNoX(int i,World world){
      bool xingCheck=false;
      do{
         points[i]=world.GetRandPoint();
         xingCheck=CheckForXing(i,i);;
      }	while(xingCheck);
   }
   void RefineCoastPoint(int i);
   void RefineCoast();
   void GenIsland(int NumStartPoints,int NumCoastRefinements,bool alreadyInitialized);
   void GenIsland(int NumStartPoints,int NumCoastRefinements){
      //initial points
      GenIsland(NumStartPoints,NumCoastRefinements,false);
   }//GenIsland
   void GenIslandFromBase(int NumCoastRefinements){
      //initial points
      GenIsland(numPoints,NumCoastRefinements,true);
   }//GenIsland
#ifdef debugCoastalGen
   void RadialCoastInDegrees(int nRefinements,float angleStep,float avgRadius,float dv);
   void CoastalGenPrintout(short i,char*file);
   void FullCircle(){		points[numPoints-1]=points[0];		}
#endif// debugCoastalGen
   float GetEdge(IslandCoastline::edge e);
   bool IsPointOnIsland(Vector2f p);
   //scale island
   IslandCoastline&operator*=(float s);
   //offset island
   IslandCoastline&operator+=(float o);
   //negative island
   IslandCoastline&operator+=(Vector2f o);
   //negative island
   IslandCoastline operator-();
   //boolean combination function
   bool BooleanCombo(bool onIsle,IslandCoastline::boolMask ibmask,Vector2f pt);
};//IslandCoastline
