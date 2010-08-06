#include "FlatRidePatterns.h"

/* Must Have List
Monorail - Large Retro
Monorail ( People Mover with Roof )

Coasters

Steel Twister
Woodie Twister

Flat Rides

Carousel Small
Crazy Bus
Eli Ferris Wheel
Eyerly Loop-O-Plane
Eyerly Octopus
Flying Scooters
Scrambler
*/
namespace Builders
{
   PatternData kBarnSormer[] =
   {
      { "base", "brnstrbase.3ds",{ "Height", "Count", 0 }},
      { "hub", "brnstrprimary.3ds",{ "Height", "Count", 0 }},
      { "rotationhub", "brnstrsec.3ds",{ "Height", "Count", "Speed", "Drop", 0 }},
      { "arm", "brnstrlifter.3ds",{ "Height", "Length", "Drop", "Offset", 0 }},
      { "cablehinge", "", { "Height", "Count", 0 }},
      { "car", "brnstrmcar.3ds",{ "Height", "Count", 0 }}
   };
}

FlatRidePatterns::FlatRidePatterns()
{
}

FlatRidePatterns::~FlatRidePatterns()
{
}