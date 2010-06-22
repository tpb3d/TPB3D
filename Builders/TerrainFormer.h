#pragma once
#ifndef _TerrainFormer // terra forma
#define _TerrainFormer

class Terrain;

#ifndef WIN32
#define doCoastline 0
#define doFractal 1
#endif

class TerrainFormer
{
public:
   TerrainFormer(void);
   ~TerrainFormer(void);

   Terrain* DefaultMesh();
	#if doCoastline
	Terrain* IslandTestMesh();
	#endif
	#if doFractal
	Terrain*FractalHeightTestMesh();
	#endif
   Terrain* DocsMesh();
};

#endif // _TerrainFormer
