#pragma once
#include "ObjectBase.h"

struct STrig
{
   double m_dCosX;
   double m_dCosY;
   double m_dCosZ;
   double m_dSinX;
   double m_dSinY;
   double m_dSinZ;
   double m_dScale;
   double m_Distance;
   double m_Height;
   double m_Shift; // (Left-) ,Right+
   double m_MaxDepth;
   double m_AspectRatio;
   STrig( double x,double y,double z, double scale );
   virtual ~STrig() {};
   virtual void SetAspect( double Aspect );
   void Set (double x, double y, double z) {SetX(x); SetY(y); SetZ(z); }
   void SetX( double x );
   void SetY( double y );
   void SetZ( double z );
};

// Vertoral Point
class CVPoint
{
public:
	float x;
	float y;
   float z;
	inline CVPoint()
	{	x = 0; y = 0; z = 0; };
	CVPoint( double ix, double iy, double iz );
   CVPoint( const CVPoint& dp);
   void operator = (const CVPoint& vp);
   void operator += (const CVPoint& vp);
   void operator -= (const CVPoint& vp);
   void operator *= (const CVPoint& dp);
   void operator *= (double dd );
   void operator /= (const CVPoint& dp);
   CVPoint operator * (const CVPoint& dp);
   void Render( const STrig& trig, const CVPoint& Points );
   void Rotate( const STrig& trig );
   void Transform( const STrig& trig, const CVPoint& Point ); // simple rotate and position
   void Offset(const CVPoint& dp);
   double det( const CVPoint& v );
   double dot( const CVPoint& v );
   void Cross(const CVPoint& v1, const CVPoint& v2 );
   void Diff(const CVPoint& v1, const CVPoint& v2 );
   void Set( double dx,double dy,double dz )
   {
      x = (float)dx;
      y = (float)dy;
      z = (float)dz;
   };
   void Normal( const CVPoint& a, const CVPoint& b, const CVPoint& c );
   sf::Vector3f GetVector3f() { return sf::Vector3f (x,y,z); }
};

inline CVPoint::CVPoint( double ix, double iy, double iz )
{
   x = float(ix);
   y = float(iy);
   z = float(iz);
}

inline double CVPoint::det( const CVPoint& v ) // Matrix calc
{
   return x*v.y + y*v.z + z*v.x - x*v.z - y*v.x - z*v.y;
}

inline double CVPoint::dot( const CVPoint& v ) // Matrix calc
{
   return x*v.x + y*v.y + z*v.z;
}

inline void CVPoint::Cross( const CVPoint& v1, const CVPoint& v2)
{
   x= v1.y*v2.z - v1.z*v2.y;
   y= v1.z*v2.x - v1.x*v2.z;
   z= v1.x*v2.y - v1.y*v2.x;
}

inline void CVPoint::Diff(const CVPoint& v1, const CVPoint& v2)
{
   x= v1.x - v2.x;
   y= v1.y - v2.y;
   z= v1.z - v2.z;
}

// inlines for STrig
inline void STrig::SetX( double x )
{
   m_dCosX = cos(0.01745329 * (180.0 - x));
   m_dSinX = sin(0.01745329 * (180.0 - x));
}

inline void STrig::SetY( double y )
{
   m_dCosY = cos(0.01745329 * (180.0 - y));
   m_dSinY = sin(0.01745329 * (180.0 - y));
}

inline void STrig::SetZ( double z )
{
   m_dCosZ = cos(0.01745329 * (180.0 - z));
   m_dSinZ = sin(0.01745329 * (180.0 - z));
}
inline STrig::STrig( double x,double y,double z, double scale )
{
   SetX(x);
   SetY(y);
   SetZ(z);
   m_dScale = scale;
   m_Distance = 100;
   m_AspectRatio = 2000;
}
inline void STrig::SetAspect( double Depth )
{
   m_MaxDepth = Depth;
   m_AspectRatio = 1/Depth;
}
