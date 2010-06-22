//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Terraforming tool class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES
#include <cstring>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../CoreObjects/Terrain.h"
#include "../Graphics/Image.h"
#include "../Graphics/QuadMeshObject.h"
#include "../Graphics/ObjectFactory.h"
#include "TerrainFormer.h"
#include <stdio.h>
#include <iostream>

//#undef doCoastline
#define checkOutIsPointOnIsland 2
// these will not build in windows
#ifndef WIN32
#if doCoastline
#include "../Builders/coastlineGen.h"
#endif
#if doFractal
#include "../Builders/FractalTerrain.h"
#endif
// our own terrain gen until Doc brings his one!
#endif

TerrainFormer::TerrainFormer(void)
{
}

TerrainFormer::~TerrainFormer(void)
{
}

#if doCoastline
Terrain*
TerrainFormer::
IslandTestMesh(){
   // Terrain - entity
   Terrain* pTerra = new Terrain();
   // The graphics mesh for OpenGL
   QuadMeshObject* pMesh = ObjectFactory::CreateQuadMesh();
   QuadVertex* pVerts = new QuadVertex[102*102];
   QuadFace* faces = new QuadFace[100*100];

   // Meshes are parts that make up the terrain.
   // this makes it uneven

#if doCoastline
   const float dfc=250.f; //distFromCenter

   //coast->GenIslandFromBase(4);
   short numIslands=2;		short numRefinements=3;		short scaleHigh=100;	short scaleLow=0;
   short ofsRange=400;		float distVariation=0.5f;
   FILE*inf;
   if(inf=fopen("CoastlineInput.txt","r+")){
      fscanf(inf,	" Tp3dCoastInput numIslands %hd numRefinements %hd scaleHigh %hd scaleLow %hd ofsRange %hd distVariation %f "
         ,&numIslands,&numRefinements,&scaleHigh,&scaleLow,&ofsRange,&distVariation);
      fclose(inf);
   }
   IslandCoastline*coast[numIslands];
   for(int i=0;i<numIslands;i++){
      coast[i]=new IslandCoastline(Vector2f(-dfc,-dfc),Vector2f(dfc,-dfc),Vector2f(dfc,dfc),Vector2f(-dfc,dfc),1.f);
      coast[i]->RadialCoastInDegrees(numRefinements,45,dfc,distVariation);
      float scale=(float)(rand()%(scaleHigh-scaleLow+1)+scaleLow)/100;

      Vector2f ofs((float)(rand()%(ofsRange+1))-ofsRange/2,(float)(rand()%(ofsRange+1))-ofsRange/2);
      *coast[i]*=scale;
      *coast[i]+=ofs;
   }
#if checkOutIsPointOnIsland==1
   FILE*f=fopen("dumpCoastalGen1.txt","a");
   if(f){
      fprintf(f,"IsPointOnIsland() Check:\r\n");
      fprintf(f,"x\ty\tOn Isle?\r\n");
      for(int i=0;i<32;++i){
         float x=float(rand()%1000)-500;
         float y=float(rand()%1000)-500;
         bool onIsle=coast->IsPointOnIsland(Vector2f(x,y));
         fprintf(f,"%0.1f\t%0.1f\t%s\r\n",x,y,onIsle?"Yes":"No");
      }//for i
      fclose(f);
   }//if f
#endif //printoutIsPointOnIsland
#endif //doCoastline

   IslandCoastline::boolMask ibmask[numIslands];
   //ibmask=malloc(sizeof(*ibmask)*numIslands);
   for(int i=0;i<numIslands;i++){
      ibmask[i]=rand()%2==0?IslandCoastline::OR:IslandCoastline::NOT;
   }

   for (int ix = 0;ix < 101; ++ix)
   {
      for (int iz = 0; iz < 101; ++iz)
      {
         float fy = float(rand()%100)/25-2.0f;
         int index = ix*101+iz;
         pVerts[index].Vertices[0] = 10.0f*ix-505.f;
         pVerts[index].Vertices[1] = fy;
         pVerts[index].Vertices[2] = 10.0f*iz-505.f;
#if checkOutIsPointOnIsland==2
         bool onIsle=false;
         //try to see which way is which
         //if(iz==50){	pVerts[index].Vertices[1]+=200.f;		}
         //it is definitely x that is causing the problem.
         for(int i=0;i<numIslands;i++){
            Vector2f pt(pVerts[index].Vertices[0],pVerts[index].Vertices[2]);
            onIsle=coast[i]->BooleanCombo(onIsle,ibmask[i],pt);
         }//for i
         const unsigned char water[]={ 0x00,0x3f,0xbf,0xff,0 };
         const unsigned char grass[] = { 0xcf,0xef,0xc3,0xff,0 };
         if(!onIsle)		{
            pVerts[index].Vertices[1]-=5.f;
            memcpy(pVerts[index].Color,water,4);
            //pVerts[index].Vertices[0]/=100.f;
            //pVerts[index].Vertices[2]/=100.f;
         }
         else
            memcpy(pVerts[index].Color,grass,4);

#endif
         //const unsigned char dirt[] = { 0xaf,0xff,0x7f,0xff,0 };
         //const unsigned char full[] = { 0xcf,0xef,0xc3,0xff,0 };
         //if (iz >48 && iz < 52 && ix > 50 )
         //{
         //memcpy(pVerts[index].Color, dirt, 4);
         //}
         //else
         //{
         //memcpy(pVerts[index].Color, full, 4);
         //}
      }
   }
   /*
   // procedural test code to add color to the ls
   const unsigned char yellow[] = { 0xff,0xff,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 52].Color, yellow, 4);
   memcpy(pVerts[50*101+ 53].Color, yellow, 4);
   memcpy(pVerts[50*101+ 54].Color, yellow, 4);
   memcpy(pVerts[51*101+ 53].Color, yellow, 4);
   memcpy(pVerts[51*101+ 54].Color, yellow, 4);
   memcpy(pVerts[51*101+ 55].Color, yellow, 4);

   const unsigned char sand[] = { 0x3f,0xbf,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 45].Color, sand, 4);
   memcpy(pVerts[50*101+ 46].Color, sand, 4);
   memcpy(pVerts[50*101+ 47].Color, sand, 4);
   memcpy(pVerts[51*101+ 46].Color, sand, 4);
   memcpy(pVerts[51*101+ 47].Color, sand, 4);
   memcpy(pVerts[51*101+ 48].Color, sand, 4);
   memcpy(pVerts[52*101+ 46].Color, sand, 4);
   memcpy(pVerts[52*101+ 47].Color, sand, 4);
   memcpy(pVerts[52*101+ 48].Color, sand, 4);

   // procedural test code to add color to the ls
   const unsigned char brown[] = { 0xaf,0x9f,0x7f,0xff,0 };
   const unsigned char dbrown[] = { 0x8f,0x7f,0x6f,0xff,0 };
   memcpy(pVerts[50*101+ 49].Color, brown, 4);
   memcpy(pVerts[50*101+ 50].Color, dbrown, 4);
   memcpy(pVerts[50*101+ 51].Color, brown, 4);
   memcpy(pVerts[51*101+ 49].Color, brown, 4);
   memcpy(pVerts[51*101+ 50].Color, dbrown, 4);
   memcpy(pVerts[51*101+ 51].Color, dbrown, 4);
   memcpy(pVerts[51*101+ 52].Color, brown, 4);
   memcpy(pVerts[52*101+ 49].Color, brown, 4);
   memcpy(pVerts[52*101+ 50].Color, brown, 4);
   memcpy(pVerts[52*101+ 51].Color, brown, 4);
   memcpy(pVerts[52*101+ 52].Color, brown, 4);
   */
   for (int ix = 0;ix < 100; ++ix)
   {
      for (int iz = 0; iz < 100; ++iz)
      {
         int index = ix*100+iz;
         int idx =  ix*101+iz;
         QuadFace& face = faces[index];
         face.mPoints[0].Index = idx;
         face.mPoints[0].mUV[0] = 0;
         face.mPoints[0].mUV[1] = 0;
         face.mPoints[1].Index = idx+1;
         face.mPoints[1].mUV[0] = 1;
         face.mPoints[1].mUV[1] = 0;
         face.mPoints[2].Index = idx+102;
         face.mPoints[2].mUV[0] = 1;
         face.mPoints[2].mUV[1] = 1;
         face.mPoints[3].Index = idx+101;
         face.mPoints[3].mUV[0] = 0;
         face.mPoints[3].mUV[1] = 1;
      }
   }
   pMesh->AddMesh( 101*101, pVerts, 100*100, faces, 0);
   pTerra->AddSection(pMesh);
   Gfx::ImageManager* pImger = Gfx::ImageManager::GetInstance();
   Gfx::Texture* pTex = pImger->GetTexture ("data/Grass2.png",3);
   pMesh->SetTexture (pTex);
   int iChan = pTex->SupportsAlpha() ? 4 : 3;
   gluBuild2DMipmaps( GL_TEXTURE_2D, iChan, pTex->GetWidth(), pTex->GetHeight(),
      GL_RGBA, GL_UNSIGNED_BYTE, pTex->GetPixelsPtr());
   return pTerra;
}//TerrainFormer::IslandTestMesh()
#endif
#if doFractal
Terrain* TerrainFormer::FractalHeightTestMesh()
{
   //initialize fractal map values
#ifndef WIN32

   char pngHtMap[128]="initialHeightMap.png";
   short startWidth=8;
   short startDepth=8;
   float baseHeight=10; float maxHeight=500;
   short startPoints=8;
   short targetSize=128;
   float spikiness=0.75f;
   short varspikeScan;
   bool&varspike=*(bool*)&varspikeScan;
   varspikeScan=false;
   float snowLevel=0.7f;
   float rockLevel=0.4f;
   float waterTableHeight=25.f;
   float pctexpseeds=100.f;
   float gaussianSmoothRadius=1.f;
   short circularflagScan=false;
   float pctarcSeeds=0.f;	//arcseeds
   // /media/B81D-8323/game projects/tpb3d/source/00-current/tpb3dtg/Builders/TerrainFormer.cpp|227|error: ‘TerrainFormer::FractalHeightTestMesh()::<anonymous union>::<anonymous enum> TerrainFormer::FractalHeightTestMesh()::<anonymous union>::balanced’ invalid; an anonymous union can only have non-static data members|

   FILE*inf;
   if(inf=fopen("data/FractalHeightInput.txt","r+")){
      fscanf(inf,	" Tp3dFractInput pngHtMap \"%[^\"\t\n]\" startWidth %hd startDepth %hd baseHeight %f maxHeight %f targetSize"
         " %hd spikiness %f varspike %hd snowLevel %f rockLevel %f waterTableHeight %f pctExponentialSeeds %f gaussianSmoothRadius"
         " %f pctarcSeeds %f"
         ,pngHtMap,&startWidth,&startDepth,&baseHeight,&maxHeight,&targetSize,&spikiness
         ,&varspikeScan,&snowLevel,&rockLevel,&waterTableHeight,&pctexpseeds,&gaussianSmoothRadius
         ,&pctarcSeeds);
      varspike=(bool)varspikeScan;
      ///media/B81D-8323/game projects/tpb3d/source/00-current/tpb3dtg/Builders/TerrainFormer.cpp|236|error: invalid conversion from ‘short int’ to ‘TerrainFormer::FractalHeightTestMesh()::<anonymous enum>’|
      fclose(inf);
   }


   //create fractal height map
   //std::cout<<"pctarcSeeds="<<pctarcSeeds<<std::endl;

   // these will not build in windows
   FractalTerrainMap fractmap(pngHtMap,startWidth,startDepth,baseHeight,maxHeight,spikiness,varspike,pctexpseeds,gaussianSmoothRadius,pctarcSeeds);

   startWidth=fractmap.w;	startDepth=fractmap.d;
   startPoints=Max(startWidth,startDepth);
   float lv;
   short numRefinements=ceil(lv=logb(2,(float)targetSize/startPoints));
   float estPoints = (float)startPoints * pow(2.0,numRefinements);

   fractmap.Fractalize(numRefinements);
   float* ha = new float[fractmap.depth * fractmap.width];
   memcpy(ha, fractmap.heights, sizeof(ha));

   // Terrain - entity
   Terrain* pTerra = new Terrain();
   // The graphics mesh for OpenGL
   QuadMeshObject* pMesh = ObjectFactory::CreateQuadMesh();
   QuadVertex* pVerts = new QuadVertex[fractmap.width*fractmap.depth];
   QuadFace* faces = new QuadFace[(fractmap.width-1)*(fractmap.depth-1)];

   // Meshes are parts that make up the terrain.
   // this makes it uneven

   //ibmask=malloc(sizeof(*ibmask)*numIslands);

   const unsigned char defclr[] = { 0x1f,0x7f,0x1f,0xff,0 };
   const unsigned char snow[] = { 0xdf,0xef,0xff,0xff,0 };
   const unsigned char rock[] = {	0x3f,0x3f,0x3f,0xff,0 };
   const unsigned char watercolor[] = {	0x0f,0x2f,0x5f,0xff,0 };

   for(int ix=0;ix<fractmap.width;++ix)
   {
      for(int iz=0;iz<fractmap.depth;++iz)
      {
         //float fy = float(rand()%100)/25-2.0f;
         float fy=fractmap.ht(ix,iz);
         float hl=(fy-baseHeight)/maxHeight;

         int index = ix*fractmap.width+iz;

         pVerts[index].Vertices[0] = 10.0f*ix-5*fractmap.width;
         pVerts[index].Vertices[1] = Max(fy,waterTableHeight);
         pVerts[index].Vertices[2] = 10.0f*iz-5*fractmap.depth;

         //memcpy(pVerts[index].Color, grass, 4);

         if(hl>=snowLevel)
            memcpy(pVerts[index].Color, snow, 4);
         else if(hl>=rockLevel)
            memcpy(pVerts[index].Color, rock, 4);
         else
            memcpy(pVerts[index].Color, defclr, 4);

         if(fy<=waterTableHeight)
            memcpy(pVerts[index].Color,watercolor,4);

         //const unsigned char dirt[] = { 0xaf,0xff,0x7f,0xff,0 };
         //const unsigned char full[] = { 0xcf,0xef,0xc3,0xff,0 };
         //if (iz >48 && iz < 52 && ix > 50 )
         //{
         //memcpy(pVerts[index].Color, dirt, 4);
         //}
         //else
         //{
         //memcpy(pVerts[index].Color, full, 4);
         //}
      }//for iz
   }//for ix
   /*
   // procedural test code to add color to the ls
   const unsigned char yellow[] = { 0xff,0xff,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 52].Color, yellow, 4);
   */

   for (int ix = 0;ix < (fractmap.width-1); ++ix)
   {
      for (int iz = 0; iz < (fractmap.width-1); ++iz)
      {
         //int index = ix*100+iz;
         //int idx =  ix*101+iz;
         int index = ix*(fractmap.width-1)+iz;
         int idx =  ix*fractmap.width+iz;
         QuadFace& face = faces[index];
         face.mPoints[0].Index = idx;
         face.mPoints[0].mUV[0] = 0;
         face.mPoints[0].mUV[1] = 0;
         face.mPoints[1].Index = idx+1;
         face.mPoints[1].mUV[0] = 1;
         face.mPoints[1].mUV[1] = 0;
         face.mPoints[2].Index = idx+fractmap.width+1;
         face.mPoints[2].mUV[0] = 1;
         face.mPoints[2].mUV[1] = 1;
         face.mPoints[3].Index = idx+fractmap.width;
         face.mPoints[3].mUV[0] = 0;
         face.mPoints[3].mUV[1] = 1;
      }
   }
   pMesh->AddMesh( fractmap.width*fractmap.depth, pVerts, (fractmap.width-1)*(fractmap.depth-1), faces, 0);
   pTerra->AddSection(pMesh);
   Gfx::ImageManager* pImger = Gfx::ImageManager::GetInstance();
   Gfx::Texture* pTex = pImger->GetTexture ("whiteground.png",3);
   pMesh->SetTexture (pTex);
   int iChan = pTex->SupportsAlpha() ? 4 : 3;
   gluBuild2DMipmaps( GL_TEXTURE_2D, iChan, pTex->GetWidth(), pTex->GetHeight(),
      GL_RGBA, GL_UNSIGNED_BYTE, pTex->GetPixelsPtr());

   delete [] ha;
   return pTerra;
#else
   return this->FractalHeightTestMesh();
#endif // WIN32
}//TerrainFormer::FractalHeightTestMesh()

#endif //0

Terrain* TerrainFormer::DefaultMesh()
{
#if doCoastline
   return IslandTestMesh();
#elif doFractal
   return this->FractalHeightTestMesh();
#else
   // Terrain - entity
   Terrain* pTerra = new Terrain();
   // The graphics mesh for OpenGL
   QuadMeshObject* pMesh = ObjectFactory::CreateQuadMesh();
   QuadVertex* pVerts = new QuadVertex[102*102];
   QuadFace* faces = new QuadFace[100*100];

   // Meshes are parts that make up the terrain.
   // this makes it uneven
   for (int ix = 0;ix < 101; ++ix)
   {
      for (int iz = 0; iz < 101; ++iz)
      {
         float fy = float(rand()%100)/25 -2.0f;
         int index = ix*101+iz;
         pVerts[index].Vertices[0] = 10.0f*ix-505.f;
         pVerts[index].Vertices[1] = fy;
         pVerts[index].Vertices[2] = 10.0f*iz-505.f;
         const unsigned char dirt[] = { 0xaf,0xff,0x7f,0xff,0 };
         const unsigned char full[] = { 0xcf,0xef,0xc3,0xff,0 };
         if (iz >48 && iz < 52 && ix > 50 )
         {
            memcpy(pVerts[index].Color, dirt, 4);
         }
         else
         {
            memcpy(pVerts[index].Color, full, 4);
         }
      }
   }
   // procedural test code to add color to the ls
   const unsigned char yellow[] = { 0xff,0xff,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 52].Color, yellow, 4);
   memcpy(pVerts[50*101+ 53].Color, yellow, 4);
   memcpy(pVerts[50*101+ 54].Color, yellow, 4);
   memcpy(pVerts[51*101+ 53].Color, yellow, 4);
   memcpy(pVerts[51*101+ 54].Color, yellow, 4);
   memcpy(pVerts[51*101+ 55].Color, yellow, 4);

   const unsigned char sand[] = { 0x3f,0xbf,0x7f,0xff,0 };
   memcpy(pVerts[50*101+ 45].Color, sand, 4);
   memcpy(pVerts[50*101+ 46].Color, sand, 4);
   memcpy(pVerts[50*101+ 47].Color, sand, 4);
   memcpy(pVerts[51*101+ 46].Color, sand, 4);
   memcpy(pVerts[51*101+ 47].Color, sand, 4);
   memcpy(pVerts[51*101+ 48].Color, sand, 4);
   memcpy(pVerts[52*101+ 46].Color, sand, 4);
   memcpy(pVerts[52*101+ 47].Color, sand, 4);
   memcpy(pVerts[52*101+ 48].Color, sand, 4);

   // procedural test code to add color to the ls
   const unsigned char brown[] = { 0xaf,0x9f,0x7f,0xff,0 };
   const unsigned char dbrown[] = { 0x8f,0x7f,0x6f,0xff,0 };
   memcpy(pVerts[50*101+ 49].Color, brown, 4);
   memcpy(pVerts[50*101+ 50].Color, dbrown, 4);
   memcpy(pVerts[50*101+ 51].Color, brown, 4);
   memcpy(pVerts[51*101+ 49].Color, brown, 4);
   memcpy(pVerts[51*101+ 50].Color, dbrown, 4);
   memcpy(pVerts[51*101+ 51].Color, dbrown, 4);
   memcpy(pVerts[51*101+ 52].Color, brown, 4);
   memcpy(pVerts[52*101+ 49].Color, brown, 4);
   memcpy(pVerts[52*101+ 50].Color, brown, 4);
   memcpy(pVerts[52*101+ 51].Color, brown, 4);
   memcpy(pVerts[52*101+ 52].Color, brown, 4);

   for (int ix = 0;ix < 100; ++ix)
   {
      for (int iz = 0; iz < 100; ++iz)
      {
         int index = ix*100+iz;
         int idx =  ix*101+iz;
         QuadFace& face = faces[index];
         face.mPoints[0].Index = idx;
         face.mPoints[0].mUV[0] = 0;
         face.mPoints[0].mUV[1] = 0;
         face.mPoints[1].Index = idx+1;
         face.mPoints[1].mUV[0] = 1;
         face.mPoints[1].mUV[1] = 0;
         face.mPoints[2].Index = idx+102;
         face.mPoints[2].mUV[0] = 1;
         face.mPoints[2].mUV[1] = 1;
         face.mPoints[3].Index = idx+101;
         face.mPoints[3].mUV[0] = 0;
         face.mPoints[3].mUV[1] = 1;
      }
   }
   pMesh->AddMesh( 101*101, pVerts, 100*100, faces, 0);
   pTerra->AddSection(pMesh);
   Gfx::ImageManager* pImger = Gfx::ImageManager::GetInstance();
   Gfx::Texture* pTex = pImger->GetTexture ("Grass2.png",3);
   pMesh->SetTexture (pTex);
   int iChan = pTex->SupportsAlpha() ? 4 : 3;
   gluBuild2DMipmaps( GL_TEXTURE_2D, iChan, pTex->GetWidth(), pTex->GetHeight(),
                        GL_RGBA, GL_UNSIGNED_BYTE, pTex->GetPixelsPtr());
   return pTerra;
#endif
}

Terrain* TerrainFormer::DocsMesh()
{
   // Call the terraformer
   return DefaultMesh();
}

