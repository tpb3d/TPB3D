#pragma once
#include "car.h"
#include "../Physics/LinearPhysics.h"

class RailCar : public Car
{
protected:
   T_Spline& mSpline;
   T_Spline::iterator mCurrentSpline;

public:
   RailCar(const sf::Vector3f& vDim, int meshcount, int id);
   virtual ~RailCar(void);

   virtual void Start();
   virtual void Draw();
};
