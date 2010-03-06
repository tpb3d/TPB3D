#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2.h"

//typedef std::pair<float, float> vector2;
template <class T = float>
class Rect
{
    public:
    Rect()
    {
        //x = 0; y = 0;
    }
    Rect(T Topv, T Leftv, T Rightv, T Bottomv)
    : Top(Topv), Left(Leftv), Right(Rightv), Bottom(Bottomv)
    {
        //x = xv; y = yv;
    }
    template <class U>
    Rect(Vector2<U> TopLeft, Vector2<U> BottomRight)
    {
       Top = TopLeft.y; Left = TopLeft.x;
       Bottom = BottomRight.y; Right = BottomRight.x;
    }
    template <class U>
    Rect(const sf::Rect<U>& Other)
    {
        Top = Other.Top; Left = Other.Left; Right = Other.Right; Bottom = Other.Bottom;
    }
    template <class U>
    Rect(const Rect<U>& Other)
    {
        Top = Other.Top; Left = Other.Left; Right = Other.Right; Bottom = Other.Bottom;
    }
    template <class U>
    Rect& operator+(const sf::Rect<U>& Other)
    {
        Rect* temp = new Rect(Top+Other.Top, Left+Other.Left, Right+Other.Right, Bottom+Other.Bottom);
        return *temp;
    }
    template <class U>
    Rect& operator+(const Rect<U>& Other)
    {
        Rect* temp = new Rect(Top+Other.Top, Left+Other.Left, Right+Other.Right, Bottom+Other.Bottom);
        return *temp;
    }
    template <class U>
    Rect& operator=(const sf::Rect<U>& Other)
    {
        Top = Other.Top; Left = Other.Left; Right = Other.Right; Bottom = Other.Bottom;
        return *this;
    }
    template <class U>
    Rect& operator=(const Rect<U>& Other)
    {
        Top = Other.Top; Left = Other.Left; Right = Other.Right; Bottom = Other.Bottom;
        return *this;
    }
    template <class U>
    Rect& Move(Vector2<U> Offset)
    {
       Top += Offset.y;
       Bottom += Offset.y;
       Right += Offset.x;
       Left += Offset.x;
       return *this;
    }
    template <class U>
    operator sf::Rect<U>()
    {
       return sf::Rect<U>(Left, Top, Right, Bottom);
    }
    T Width()
    {
       return Right-Left;
    }
    T Height()
    {
       return Top-Bottom;
    }
    void DebugPrint()
    {
       std::cout << "Top: " << Top << " Left: " << Left << " Right: " << Right << " Bottom: " << Bottom << " Width: " << Width() << " Height: " << Height();
    }
    T Top;
    T Left;
    T Right;
    T Bottom;
};

typedef Rect <float> Rectf; // russ
typedef Rect <int> Recti;   // likes this
