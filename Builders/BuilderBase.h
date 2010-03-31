#pragma once
#include "BuilderBase.h"
#include "../Types/Vector3.h"

// forward decls
class Park;
class Ride;
class RideNode;
class ObjectBase;
struct PartGuide;

class BuilderBase
{
public:
   BuilderBase(void) {}

   virtual ~BuilderBase(void) {}

   virtual void OnHit (int hit) = 0;
   virtual void OnMove (const Vector3f& vec) = 0;
};