#pragma once

#include "../Types/Vector3.h"
#include "../Types/Vector2.h"
#include "Texture.h"

class SimpleMesh
{
   Vector3f mMesh[16];
   Vector2f mUVs[16];
   Vector3f mPosition;
   float    mLightingColor[4];
   Gfx::Texture* mpTexture;

public:

   SimpleMesh (Gfx::Texture* pTex);
   virtual ~SimpleMesh(void);

   Vector3f* get_Mesh() { return mMesh; }
   Vector2f* get_mUVs() { return mUVs; }
   inline void SetLightingColor( const float lc[4] )
   {
      mLightingColor[0] = lc[0];
      mLightingColor[1] = lc[1];
      mLightingColor[2] = lc[2];
      mLightingColor[3] = lc[3];
   }
   void SetUVs( const float uv[16][2]);
   inline float* GetLightingColor() { return mLightingColor; }
   inline void set_Position(float x, float y, float z) { mPosition.Set(x,y,z); }
   inline Vector3f& get_Position() { return mPosition; }

   void SetSize (int x, int y, int border);
   void BindTexture();
};
