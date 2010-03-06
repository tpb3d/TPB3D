#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix16.h"
#include "../Types/MathStuff.h"

CMatrix16::CMatrix16(void)
{
}

CMatrix16::CMatrix16( const Matrix4x4& m4x4 )
{
   memcpy( m_Matrix, m4x4, 4*4*sizeof(float));
}

CMatrix16::~CMatrix16(void)
{
}

CMatrix16::CMatrix16( const float x, const float y, const float z) // Scaled Matrix
{
	m_Matrix[ 0] = x;
	m_Matrix[ 1] = 0.0;
	m_Matrix[ 2] = 0.0;
	m_Matrix[ 3] = 0.0;

	m_Matrix[ 4] = 0.0;
	m_Matrix[ 5] = y;
	m_Matrix[ 6] = 0.0;
	m_Matrix[ 7] = 0.0;

	m_Matrix[ 8] = 0.0;
	m_Matrix[ 9] = 0.0;
	m_Matrix[10] = z;
	m_Matrix[11] = 0.0;

	m_Matrix[12] = 0.0;
	m_Matrix[13] = 0.0;
	m_Matrix[14] = 0.0;
	m_Matrix[15] = 1.0;
}

void CMatrix16::operator = (CMatrix16& m16 )
{
   memcpy( m_Matrix, m16.m_Matrix, 4*4*sizeof(float));
}

void CMatrix16::operator = ( const Matrix4x4& m4x4 )
{
   memcpy( m_Matrix, m4x4, 4*4*sizeof(float));
}

void CMatrix16::Look( const Vector3f& pos, const Vector3f& dir, const Vector3f& up)
{
   Vector3f lftN = Vector3f::Cross( dir, up );
	lftN.Normalize( );

   Vector3f upN = Vector3f::Cross( lftN, dir );
	upN.Normalize( );

   Vector3f dirN( dir );
	dirN.Normalize( );

	m_Matrix[ 0] = lftN.x;
	m_Matrix[ 1] = upN.x;
	m_Matrix[ 2] = -dirN.x;
	m_Matrix[ 3] = 0.0;

	m_Matrix[ 4] = lftN.y;
	m_Matrix[ 5] = upN.y;
	m_Matrix[ 6] = -dirN.y;
	m_Matrix[ 7] = 0.0;

	m_Matrix[ 8] = lftN.z;
	m_Matrix[ 9] = upN.z;
	m_Matrix[10] = -dirN.z;
	m_Matrix[11] = 0.0;

	m_Matrix[12] = -(lftN.Dot( pos ));
	m_Matrix[13] = -(upN.Dot( pos ));
	m_Matrix[14] = dirN.Dot( pos );
	m_Matrix[15] = 1.0;
}

void CMatrix16::ScaleTranslateToFit( const Vector3f& vMin, const Vector3f& vMax)
{
	m_Matrix[ 0] = 2/(vMax.x-vMin.x);
	m_Matrix[ 4] = 0;
	m_Matrix[ 8] = 0;
	m_Matrix[12] = -(vMax.x+vMin.x)/(vMax.x-vMin.x);

	m_Matrix[ 1] = 0;
	m_Matrix[ 5] = 2/(vMax.y-vMin.y);
	m_Matrix[ 9] = 0;
	m_Matrix[13] = -(vMax.y+vMin.y)/(vMax.y-vMin.y);

	m_Matrix[ 2] = 0;
	m_Matrix[ 6] = 0;
	m_Matrix[10] = 2/(vMax.z-vMin.z);
	m_Matrix[14] = -(vMax.z+vMin.z)/(vMax.z-vMin.z);

	m_Matrix[ 3] = 0;
	m_Matrix[ 7] = 0;
	m_Matrix[11] = 0;
	m_Matrix[15] = 1;
}

void CMatrix16::PerspectiveRad( const float vFovy, const float vAspect,
						              const float vNearDis, const float vFarDis)
{
	const float f = (float)coTan(vFovy/2);
	const float dif = (float)(1.0/(vNearDis-vFarDis));

	m_Matrix[ 0] = f/vAspect;
	m_Matrix[ 4] = 0;
	m_Matrix[ 8] = 0;
	m_Matrix[12] = 0;

	m_Matrix[ 1] = 0;
	m_Matrix[ 5] = f;
	m_Matrix[ 9] = 0;
	m_Matrix[13] = 0;

	m_Matrix[ 2] = 0;
	m_Matrix[ 6] = 0;
	m_Matrix[10] = (vFarDis+vNearDis)*dif;
	m_Matrix[14] = 2*vFarDis*vNearDis*dif;

	m_Matrix[ 3] = 0;
	m_Matrix[ 7] = 0;
	m_Matrix[11] = -1;
	m_Matrix[15] = 0;
}

void CMatrix16::PerspectiveDeg( const float vFovy, const float vAspect,
                                const float vNearDis, const float vFarDis)
{
	PerspectiveRad( vFovy*(float)PI_180,vAspect,vNearDis,vFarDis);
}


void CMatrix16::Invert( const Matrix4x4 i)
{
	float a11 = (float) det3x3(i[5],i[6],i[7],i[9],i[10],i[11],i[13],i[14],i[15]);
	float a21 = (float)-det3x3(i[1],i[2],i[3],i[9],i[10],i[11],i[13],i[14],i[15]);
	float a31 = (float) det3x3(i[1],i[2],i[3],i[5],i[6],i[7],i[13],i[14],i[15]);
	float a41 = (float)-det3x3(i[1],i[2],i[3],i[5],i[6],i[7],i[9],i[10],i[11]);

	float a12 = (float)-det3x3(i[4],i[6],i[7],i[8],i[10],i[11],i[12],i[14],i[15]);
	float a22 = (float) det3x3(i[0],i[2],i[3],i[8],i[10],i[11],i[12],i[14],i[15]);
	float a32 = (float)-det3x3(i[0],i[2],i[3],i[4],i[6],i[7],i[12],i[14],i[15]);
	float a42 = (float) det3x3(i[0],i[2],i[3],i[4],i[6],i[7],i[8],i[10],i[11]);

	float a13 = (float) det3x3(i[4],i[5],i[7],i[8],i[9],i[11],i[12],i[13],i[15]);
	float a23 = (float)-det3x3(i[0],i[1],i[3],i[8],i[9],i[11],i[12],i[13],i[15]);
	float a33 = (float) det3x3(i[0],i[1],i[3],i[4],i[5],i[7],i[12],i[13],i[15]);
	float a43 = (float)-det3x3(i[0],i[1],i[3],i[4],i[5],i[7],i[8],i[9],i[11]);

	float a14 = (float)-det3x3(i[4],i[5],i[6],i[8],i[9],i[10],i[12],i[13],i[14]);
	float a24 = (float) det3x3(i[0],i[1],i[2],i[8],i[9],i[10],i[12],i[13],i[14]);
	float a34 = (float)-det3x3(i[0],i[1],i[2],i[4],i[5],i[6],i[12],i[13],i[14]);
	float a44 = (float) det3x3(i[0],i[1],i[2],i[4],i[5],i[6],i[8],i[9],i[10]);

	float det = (float)((i[0]*a11) + (i[4]*a21) + (i[8]*a31) + (i[12]*a41));
	float oodet = 1/det;

	m_Matrix[ 0] = a11*oodet;
	m_Matrix[ 1] = a21*oodet;
	m_Matrix[ 2] = a31*oodet;
	m_Matrix[ 3] = a41*oodet;

	m_Matrix[ 4] = a12*oodet;
	m_Matrix[ 5] = a22*oodet;
	m_Matrix[ 6] = a32*oodet;
	m_Matrix[ 7] = a42*oodet;

	m_Matrix[ 8] = a13*oodet;
	m_Matrix[ 9] = a23*oodet;
	m_Matrix[10] = a33*oodet;
	m_Matrix[11] = a43*oodet;

	m_Matrix[12] = a14*oodet;
	m_Matrix[13] = a24*oodet;
	m_Matrix[14] = a34*oodet;
	m_Matrix[15] = a44*oodet;
}

CMatrix16 CMatrix16::Copy( )
{
	CMatrix16 result;
	memcpy(result.m_Matrix, m_Matrix, 4*4*sizeof(float));
   return result;
}

void CMatrix16::MultUnSave( const CMatrix16& a, const CMatrix16& b)
{
	const int SIZE = 4;
	int iCol;
	for(iCol = 0; iCol < SIZE; iCol++)
   {
		const int cID = iCol*SIZE;
		int iRow;
		for(iRow = 0; iRow < SIZE; iRow++)
      {
			const int id = iRow+cID;
			int k;
			m_Matrix[id] = a.m_Matrix[iRow] * b.m_Matrix[cID];
			for(k = 1; k < SIZE; k++)
         {
				m_Matrix[id] += a.m_Matrix[iRow+k*SIZE] * b.m_Matrix[k+cID];
			}
		}
	}
}

void CMatrix16::Mult( const CMatrix16& a, const CMatrix16& b)
{
	if( &a == this )
   {
		CMatrix16 tmpA = a;
		if( &b == this )
      {
			MultUnSave( tmpA, tmpA );
		}
		else 
      {
			MultUnSave( tmpA, b );
		}
	}
	else
   {
		if( &b == this )
      {
			CMatrix16 tmpB = b;
			MultUnSave( a, tmpB );
		}
		else
      {
			MultUnSave( a, b );
		}
	}
}
