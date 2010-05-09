//CoreObjects/CoastlineGen.h

// This is a set of methods for generating coastlines
// The z point is assumed to be the same throughout the coast, this only uses 2d arrays.

#pragma once

#include "../types/vector2.h"
#include <stdlib.h>
#include <math.h>

// CoreObjects/CoastlineGen.cpp
// This is a set of methods for generating coastlines
// The z point is assumed to be the same throughout the coast, this only uses 2d arrays.

#include"CoastlineGen.h"

//4 point constructor
IslandCoastline::IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,Vector2f point4,float dv)
{
   srand((int)time(NULL));
   if(points)free(points);        points=(Vector2f*)malloc(sizeof(Vector2f)*5);
#define vp(a) points[a]=point##a
   vp(1);    vp(2);    vp(3);    vp(4);
#undef vp
   points[3]=points[0];
   numPoints=4;
   distVariation=dv;
}
//3 point constructor
IslandCoastline::IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,float dv)
{
   if(points)free(points);        points=(Vector2f*)malloc(sizeof(Vector2f)*4);
#define vp(a) points[a-1]=point##a
   vp(1);    vp(2);    vp(3);
#undef vp
   points[4]=points[0];
   numPoints=3;
   distVariation=dv;
}
bool IslandCoastline::ThereIsAnIntersection(Vector2f p1,Vector2f p2,Vector2f p3,Vector2f p4){
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
   return(true);
}//ThereIsAnIntersection
//Vector2 IslandCoastline::GenRandPointNoX(i)    {}
bool IslandCoastline::CheckForXing(int i,int stopI)
{
   bool xingCheck=false;
   for(int j=0;j<=stopI,!xingCheck;j++)
   {
      xingCheck = this->ThereIsAnIntersection(points[i],points[i+1],points[j],points[j+1])
               || this->ThereIsAnIntersection(points[i-1],points[i],points[j],points[j+1]);
   }
   return xingCheck;
}

void IslandCoastline::RefineCoastPointNoX(int i,World world)
{
   bool xingCheck=false;
   do
   {
      RefineCoastPoint(i);
      xingCheck=CheckForXing(i,i);
   } while(!xingCheck);
}

void IslandCoastline::GenRandPointNoX(int i,World world)
{
   bool xingCheck=false;
   do
   {
      points[i]=world.GetRandPoint();
      xingCheck=CheckForXing(i,i);
   } while(!xingCheck);
}

void IslandCoastline::RefineCoastPoint(int i)
{
   //bread and butter function - makes a new refinement of the coast
   float SmallestNum=0.00001f;
   float deltax=points[i+1].x-points[i-1].x;    if(deltax==0.0f)deltax=SmallestNum; //prevent division by zero
   float deltay=points[i+1].y-points[i-1].y;    if(deltay==0.0f)deltay=SmallestNum; //prevent div by zero
   float slope=deltay/deltax;        float normal=-1/slope;
   float distMax=pow(pow(deltax,2)+pow(deltay,2),1.0f/2.0f);      //^ may need to be defined as a power function for floats
   distMax*=distVariation; //distVariation should be a value in the IslandCoastline structure/class
   //distVariation basically specifies the flatness of each refinement
   float dist = World::ScaledRand(distMax); //randomizer may need to be initialized
   points[i]=PointAvg(points[i-1],points[i+1]);
   //pointOfsAbs.x=sqrt(dist^2/(1+normal^2));
   //pointOfsAbs.y=sqrt(dist^2-pointOfsAbs.x^2);
   Vector2f pointOfs(0,0);
   pointOfs.x = World::RandSign()*sqrt(pow(dist,2)/(1+pow(normal,2)));
   pointOfs.y=normal*pointOfs.x;
   points[i].x+=pointOfs.x;    points[i].y+=pointOfs.y;
   //point=this->GetRandPointNoX(i);
   //This function could alternatively be rewritten to simply find a random point in
   //the bounding box ((x1,y1),(y2,y2))
}//RefineCoastPoint

void IslandCoastline::RefineCoast()
{
   //Add more random points between the existing ones
   numPoints=2*numPoints-1;//double the points
   Vector2f*oldPoints=points;
   points=(Vector2f*)malloc(sizeof(Vector2f)*numPoints);
   for(int i=0;i<=numPoints;i+=2)
   {    //even points - copy point from last array
      points[i]=oldPoints[i/2];
   }/*for i*/

   for(int i=0;i<=numPoints;i+=2)
   {    //odd points - get random point
      this->RefineCoastPoint(i);
   }/*for i*/
   free(oldPoints);
}//RefineCoast

void IslandCoastline::GenIsland(int NumStartPoints,int NumCoastRefinements)
{
   //initial points
   const float ws=10.0f;
   World world(ws,ws);
   int nLoops=NumCoastRefinements;
   numPoints=NumStartPoints;
   for(int i=0;i<=numPoints;i++)
   {
      GenRandPointNoX(i,world);
   }/*for*/

   //subsequent points
   for(int j=1;j<=nLoops;j++)
   {
      //Add more random points between the existing ones
      this->RefineCoast();
   }
}//GenIsland
//IslandCoastline
