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
   Terrain* doOld(); // have to have a default or this shit won't compile or run
};

#endif // _TerrainFormer
