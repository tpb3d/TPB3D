
// Vertoral Point
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "VPoint.h"
/*
CVPoint::CVPoint( double ix, double iy, double iz )
{
	x = ix;
	y = iy;
   z = iz;
}
*/
CVPoint::CVPoint( const CVPoint& vp )
{
	x = vp.x;
	y = vp.y;
   z = vp.z;
}

void CVPoint::operator = (const CVPoint& vp)
{
	x = vp.x;
	y = vp.y;
   z = vp.z;
}

void CVPoint::operator += (const CVPoint& dp)
{
	x += dp.x;
	y += dp.y;
   z += dp.z;
}

void CVPoint::operator *= (const CVPoint& dp)
{
	x *= dp.x;
	y *= dp.y;
   z *= dp.z;
}

void CVPoint::operator *= (double dd )
{
	x *= (float)dd;
	y *= (float)dd;
   z *= (float)dd;
}

void CVPoint::operator /= (const CVPoint& dp)
{
	x /= dp.x;
	y /= dp.y;
   z /= dp.z;
}

void CVPoint::operator -= (const CVPoint& dp)
{
	x -= dp.x;
	y -= dp.y;
   z -= dp.z;
}

void CVPoint::Offset(const CVPoint& dp)
{
   x += dp.x;
   y += dp.y;
   z += dp.z;
}

void CVPoint::Rotate( const STrig& trig )  // Lean - Mean
{
   double TY = y*trig.m_dCosX - z*trig.m_dSinX;
   double TZ = y*trig.m_dSinX + z*trig.m_dCosX;
    /*rotate around y-axis*/
   double TX = x*trig.m_dCosY - TZ*trig.m_dSinY;

   z = (float)(x*trig.m_dSinY + TZ*trig.m_dCosY);
    /*rotate around z-axis*/
   x = (float)(TX*trig.m_dCosZ - TY*trig.m_dSinZ);//x
   y = (float)(TX*trig.m_dSinZ + TY*trig.m_dCosZ);//y
}

void CVPoint::Transform( const STrig& trig, const CVPoint& point )
{
   double TY = y*trig.m_dCosX - z*trig.m_dSinX;
   double TZ = y*trig.m_dSinX + z*trig.m_dCosX;
    /*rotate around y-axis*/
   double TX = x*trig.m_dCosY - TZ*trig.m_dSinY;

    /*rotate around z-axis*/
   z = (float)(x*trig.m_dSinY + TZ*trig.m_dCosY + point.z);
   y = (float)(TX*trig.m_dSinZ + TY*trig.m_dCosZ + point.y);//y
   x = (float)((TX*trig.m_dCosZ - TY*trig.m_dSinZ) + point.x);//x
}

void CVPoint::Render( const STrig& trig, const CVPoint& Points )
{
    /*rotate around x-axis*/
   double TY = trig.m_dScale * Points.y*trig.m_dCosX - trig.m_dScale * Points.z*trig.m_dSinX;
   double TZ = trig.m_dScale * Points.y*trig.m_dSinX + trig.m_dScale * Points.z*trig.m_dCosX;
    /*rotate around y-axis*/
   double TX = trig.m_dScale * Points.x*trig.m_dCosY - TZ*trig.m_dSinY;

   z = (float)( trig.m_dScale * Points.x*trig.m_dSinY + TZ*trig.m_dCosY );
    /*rotate around z-axis*/
   x = (float)( TX*trig.m_dCosZ - TY*trig.m_dSinZ );//x
   y = (float)( TX*trig.m_dSinZ + TY*trig.m_dCosZ );//y
}

void CVPoint::Normal( const CVPoint& a, const CVPoint& b, const CVPoint& c )
{
   CVPoint p(c);
   p -= b;
   CVPoint q(a);
   q -= b;
   *(this) = c;
   Cross(p, q );

//   lib3ds_vector_cross(n, p, q);
//   lib3ds_vector_normalize(n);
}
