#pragma once
#ifndef _TerrainFormer // terra forma
#define _TerrainFormer

class Terrain;

#define doCoastline 0
#define doFractal 1

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
