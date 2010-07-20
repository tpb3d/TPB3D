#include "SimpleMesh.h"

SimpleMesh::SimpleMesh(Gfx::Texture* pTex)
{
   mpTexture = pTex;
   mPosition.Set(0,0,0);
   SetSize(24,24, 4);   // works out to 32x32
}

SimpleMesh::~SimpleMesh(void)
{
}

void SimpleMesh::SetSize (float fX, float fY, float fB) // width, height, border thickness
{
   mMesh[0] = Vector3f(0, 0, 0);
   mMesh[1] = Vector3f(fB, 0, 0);
   mMesh[2] = Vector3f(fB+fX, 0, 0);
   mMesh[3] = Vector3f(fB+fX+fB, 0, 0);

   mMesh[4] = Vector3f(0, fB, 0);
   mMesh[5] = Vector3f(fB, fB, 0);
   mMesh[6] = Vector3f(fB+fX, fB, 0);
   mMesh[7] = Vector3f(fB+fX+fB, fB, 0);

   mMesh[8] = Vector3f(0, fB+fY, 0);
   mMesh[9] = Vector3f(fB, fB+fY, 0);
   mMesh[10] = Vector3f(fB+fX, fB+fY, 0);
   mMesh[11] = Vector3f(fB+fX+fB, fB+fY, 0);

   mMesh[12] = Vector3f(0, fB+fY+fB, 0);
   mMesh[13] = Vector3f(fB, fB+fY+fB, 0);
   mMesh[14] = Vector3f(fB+fX, fB+fY+fB, 0);
   mMesh[15] = Vector3f(fB+fX+fB, fB+fY+fB, 0);
}

void SimpleMesh::SetUVs( const float uv[16][2])
{
   mUVs[0].x = uv[0][0];
   mUVs[0].y = uv[0][1];
   mUVs[1].x = uv[1][0];
   mUVs[1].y = uv[1][1];
   mUVs[2].x = uv[2][0];
   mUVs[2].y = uv[2][1];
   mUVs[3].x = uv[3][0];
   mUVs[3].y = uv[3][1];
   mUVs[4].x = uv[4][0];
   mUVs[4].y = uv[4][1];
   mUVs[5].x = uv[5][0];
   mUVs[5].y = uv[5][1];
   mUVs[6].x = uv[6][0];
   mUVs[6].y = uv[6][1];
   mUVs[7].x = uv[7][0];
   mUVs[7].y = uv[7][1];
   mUVs[8].x = uv[8][0];
   mUVs[8].y = uv[8][1];
   mUVs[9].x = uv[9][0];
   mUVs[9].y = uv[9][1];
   mUVs[10].x = uv[10][0];
   mUVs[10].y = uv[10][1];
   mUVs[11].x = uv[11][0];
   mUVs[11].y = uv[11][1];
   mUVs[12].x = uv[12][0];
   mUVs[12].y = uv[12][1];
   mUVs[13].x = uv[13][0];
   mUVs[13].y = uv[13][1];
   mUVs[14].x = uv[14][0];
   mUVs[14].y = uv[14][1];
   mUVs[15].x = uv[15][0];
   mUVs[15].y = uv[15][1];
}

void SimpleMesh::BindTexture()
{
   mpTexture->Bind();
}
