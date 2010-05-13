#pragma once
#ifndef _TerrainFormer // terra forma
#define _TerrainFormer

class Terrain;

class TerrainFormer
{
public:
   TerrainFormer(void);
   ~TerrainFormer(void);

   Terrain* DefaultMesh();
	Terrain* IslandTestMesh();

   Terrain* DocsMesh();
};

#endif // _TerrainFormer
