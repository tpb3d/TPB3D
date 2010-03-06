//   This file is part of Theme Park Builder 3D The Game.
//   seel copyright in header


// When a new Ride space object is added, it needs to be built, detailed and rented or sold.
// This code will also have to release spaces when tenants move out.

#include <vector>
#include <list>
#include <algorithm>

#include "../CoreObjects/Ride.h"
#include "../CoreObjects/RidePart.h"
#include "RideAgent.h"

RideAgent::RideAgent ()
{

}

RideAgent::~RideAgent ()
{

}

bool RideAgent::AddRide (Ride* pRide)
{
   return true;
}

bool RideAgent::AddRidePart (RidePart* pRidePart)
{
   return true;
}

