#pragma once

typedef float Matrix4x4[16];
//class Vector3f;
#include "../Types/Vector3.h"

class CMatrix16
{
public:
   Matrix4x4 m_Matrix;
public:
   CMatrix16(void);
   CMatrix16( const Matrix4x4& m4x4 );
   CMatrix16( const float x, const float y, const float z); // Scaled Matrix

   ~CMatrix16(void);

   void operator = (CMatrix16& m16 );
   void operator = ( const Matrix4x4& m4x4 );

   CMatrix16 CopyMatrix( const Matrix4x4);
   //[x,0,0,0]
   //[0,y,0,0]
   //[0,0,z,0]
   //[0,0,0,1]
   CMatrix16 MakeScaleMtx( const float x, const float y, const float z);
   CMatrix16 Copy( );

   //output = a*b (matrix product)
   void Mult( const Matrix4x4 a, const Matrix4x4 b);
   //output = i^(-1)
   void Invert( const Matrix4x4 i);
   //output = look from position:pos into direction:dir with up-vector:up
   void Look( const Vector3f& pos, const Vector3f& dir, const Vector3f& up);
   //make a scaleTranslate matrix that includes the two values vMin and vMax
   void ScaleTranslateToFit( const Vector3f& vMin, const Vector3f& vMax);

   void PerspectiveRad( const float vFovy, const float vAspect,
                        const float vNearDis, const float vFarDis);
   //output is initialized with the same result as glPerspective vFovy in degrees
   void PerspectiveDeg( const float vFovy, const float vAspect,
                        const float vNearDis, const float vFarDis);
   void MultUnSave( const CMatrix16& a, const CMatrix16& b);
   void Mult( const CMatrix16& a, const CMatrix16& b);
};
