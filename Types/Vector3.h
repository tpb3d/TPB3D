#pragma once

#include <SFML/Graphics.hpp>

//typedef std::pair<float, float> Vector3;
template <class T = float> class Vector3
{
public:
   T x;
   T y;
   T z;

   // AC: Internal public structure matching the Vector3 class.
   // Provides fast rotation of the vector by presetting the sines and cosines.
   // This saves cycles by reducing time needed to redo that step reach rotation.
   template <class T> struct VectorAngle3
   {
      T dCosX;
      T dSinX;
      T dCosY;
      T dSinY;
      T dCosZ;
      T dSinZ;

      VectorAngle3 (double x,double y,double z)
      {
         Set ((T)x, (T)y, (T)z);
      }
      VectorAngle3 (float x, float y, float z)
      {
         Set ((T)x, (T)y, (T)z);
      }
      inline void Set (T x, T y, T z)
      {
         // pre-calc all these sines and cosines so the rotates are much faster
         dCosX = (T)cos(0.01745329 * (180.0 - x));
         dSinX = (T)sin(0.01745329 * (180.0 - x));
         dCosY = (T)cos(0.01745329 * (180.0 - y));
         dSinY = (T)sin(0.01745329 * (180.0 - y));
         dCosZ = (T)cos(0.01745329 * (180.0 - z));
         dSinZ = (T)sin(0.01745329 * (180.0 - z));
      }
      typedef VectorAngle3<T> VectorAngle3T;
   };

   Vector3()
   {
      x = 0;
      y = 0;
      z = 0;
   }
   Vector3(T xv, T yv, T zv)
   {
      x = xv;
      y = yv;
      z = zv;
   }
   template <class U> Vector3(const sf::Vector3<U>& Other)
   {
      x = Other.x;
      y = Other.y;
      z = Other.z;
   }

   template <class U> Vector3(const Vector3<U>& Other)
   {
      x = Other.x;
      y = Other.y;
      z = Other.z;
   }

   void Set (float fX, float fY, float fZ)
   {
      x = fX;
      y = fY;
      z = fZ;
   }

   template <class U> Vector3& operator+(const Vector3<U>& Other)
   {
      Vector3* temp = new Vector3(x+Other.x, y+Other.y, z+Other.z);
      return *temp;
   }
   template <class U> void operator+=(const Vector3<U>& Other)
   {
      x += Other.x;
      y += Other.y;
      z += Other.z;
   }
   template <class U> void operator-=(const Vector3<U>& Other)
   {
      x -= (T)Other.x;
      y -= (T)Other.y;
      z -= (T)Other.z;
   }
   template <class U> void operator*=(const U UVal)  // generaly this is used for scaling a vector
   {
      x *= (T)UVal;
      y *= (T)UVal;
      z *= (T)UVal;
   }

   template <class U> Vector3& operator+(const sf::Vector3<U>& Other)
   {
      Vector3* temp = new Vector3(x+Other.x, y+Other.y);
      return *temp;
   }
   template <class U> Vector3& operator=(const Vector3<U>& Other)
   {
      x = Other.x;
      y = Other.y;
      z = Other.z;
      return *this;
   }
   template <class U>
   Vector3<T>& operator=(const sf::Vector3<U>& Other)
   {
      x = Other.x;
      y = Other.y;
      z = Other.z;
      return *this;
   }
   template <class U>
   Vector3<T>& operator-(const Vector3<U>& Other)
   {
      return *(new Vector3(-Other.x, -Other.y));
   }

	T GetSquaredLength() const
	{
      return (x*x)+(y*y)+(z*z);
   }

   void Normalize()
   {
      const T len = (T)(1.0/sqrt(GetSquaredLength() ));
      x *= len;
      y *= len;
      z *= len;
   }
   void Rotate (const VectorAngle3<T>& angle)
   {
      double TY = y*angle.dCosX - z*angle.dSinX;
      double TZ = y*angle.dSinX + z*angle.dCosX;
      double TX = x*angle.dCosY - TZ*angle.dSinY;

      z = (float)( x*angle.dSinY + TZ*angle.dCosY);
      x = (float)(TX*angle.dCosZ - TY*angle.dSinZ);//x
      y = (float)(TX*angle.dSinZ + TY*angle.dCosZ);//y
   }

   void Transform (const VectorAngle3<T>& angle, const Vector3<T>& distance)  // rotate and move
   {
      double TY = y*angle.dCosX - z*angle.dSinX;
      double TZ = y*angle.dSinX + z*angle.dCosX;
      double TX = x*angle.dCosY - TZ*angle.dSinY;

      z = (float)( x*angle.dSinY + TZ*angle.dCosY) + distance.z;
      x = (float)(TX*angle.dCosZ - TY*angle.dSinZ) + distance.x;
      y = (float)(TX*angle.dSinZ + TY*angle.dCosZ) + distance.y;
   }

   static Vector3<T>& Cross( const Vector3<T>& a, const Vector3<T>& b)
   {
      static Vector3<T> result;
      result.x =  Det2x2(a.y, b.y, a.z, b.z);
      result.y = -Det2x2(a.x, b.x, a.z, b.z);
      result.z =  Det2x2(a.x, b.x, a.y, b.y);
      return result;
   }
   static T Det2x2( const T a1, const T a2,const T b1, const T b2)
   {
      return a1*b2 - b1*a2;
   }

   T Dot( const Vector3<T>& vb)
   {
      return vb.x * vb.x + vb.y * vb.y + vb.z * vb.z;
   }

};

typedef Vector3 <float> Vector3f;
typedef Vector3 <int> Vector3i;
