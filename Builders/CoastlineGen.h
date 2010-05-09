#pragma once

class CoastlineGen
{
public:
   CoastlineGen(void);
   virtual ~CoastlineGen(void);

};

class IslandCoastline
{
   Vector2f* points;
   long numPoints;
   float distVariation;

   struct World
   {
      World(float w,float h) {    width=w;    height=h;    }
      static short RandSign(void)
      {
         return((rand()%2==0)?1:-1);
      }

      static float frand()
      {
         return((float)rand()/0x8000);
      }
      static float SignedFloatRand(){    return(RandSign()*frand());    }
      static float ScaledRand(float scale){            return(frand()*scale);        }
      float SignedScaledRand(float span){            return(frand()*span-(span/2));        }
      Vector2f GetRandPoint()
      {
         Vector2f point(SignedScaledRand(width),SignedScaledRand(height));
         return point;
      }
      float width,height;
   };


public:
   //4 point constructor
   IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,Vector2f point4,float dv);
   Vector2f PointAvg(Vector2f point1,Vector2f point2)
   {
      Vector2f pavg = point1 + point2;
      pavg.x /= 2;
      pavg.y /= 2;
      return(pavg);
   }
   //3 point constructor
   IslandCoastline(Vector2f point1,Vector2f point2,Vector2f point3,float dv);
   bool ThereIsAnIntersection(Vector2f p1,Vector2f p2,Vector2f p3,Vector2f p4);
   //Vector2 IslandCoastline::GenRandPointNoX(i)    {}
   bool CheckForXing(int i,int stopI);
   void RefineCoastPointNoX(int i,World world);
   void GenRandPointNoX(int i,World world);
   void RefineCoastPoint(int i);
   void RefineCoast();
   void GenIsland(int NumStartPoints,int NumCoastRefinements);
   //IslandCoastline
};
