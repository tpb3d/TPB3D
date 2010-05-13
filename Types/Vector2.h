#pragma once

#include <SFML/Graphics.hpp>

//typedef std::pair<float, float> vector2;
template <class T = float>
class Vector2
{
    public:
    Vector2()
    {
        x = 0; y = 0;
    }
    Vector2(T xv, T yv)
    {
        x = xv; y = yv;
    }
    template <class U>
    Vector2(const sf::Vector2<U>& Other)
    {
        x = Other.x; y = Other.y;
    }
    template <class U>
    Vector2(const Vector2<U>& Other)
    {
        x = (T)Other.x;
        y = (T)Other.y;
    }
    template <class U>
    Vector2& operator+(const Vector2<U>& Other)
    {
        Vector2* temp = new Vector2(x+Other.x, y+Other.y);
        return *temp;
    }
    template <class U>
    Vector2& operator+(const sf::Vector2<U>& Other)
    {
        Vector2* temp = new Vector2(x+Other.x, y+Other.y);
        return *temp;
    }
    template <class U>
    Vector2& operator=(const Vector2<U>& Other)
    {
        x = (float)Other.x;
        y = (float)Other.y;
        return *this;
    }
    template <class U>
    Vector2<T>& operator=(const sf::Vector2<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        return *this;
    }
    template <class U>
    Vector2<T>& operator-(const Vector2<U>& Other)
    {
       return *(new Vector2(-Other.x, -Other.y));
    }
    Vector2<T>& operator-()
    {
       return *(new Vector2(-x,-y));
    }
    //* scalar multiplication
    template<class U>
    Vector2<T> operator*(U a)	{
		Vector2<T> av(x*a,y*a);
		return av;
    	}
    // %: get average of two vectors
	template<class U>
    Vector2<T> operator%(const Vector2<U>& v2)	{
		Vector2<T> av((x+v2.x)/2,(y+v2.y)/2);
		return av;
    	}
	// || : magnitude
	template<class U>
    T operator||(const Vector2<U>& v2)	{
		return (T)sqrt(pow(x-v2.x,2)+pow(y-v2.y,2));
    	}
    T x;
    T y;
};

typedef Vector2 <float> Vector2f; // russ
typedef Vector2 <int> Vector2i;   // likes this
