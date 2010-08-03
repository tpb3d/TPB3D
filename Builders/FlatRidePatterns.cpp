#include "PartGuide.h"
#include "FlatRideBuilder.h"
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
   PatternData kBarnStormer[] =
   {
      { "base", "brnstrbase.3ds",{ "Height", "Count", 0 }, {0,0,0} },
      { "hub", "brnstrprimary.3ds",{ "Height", "Count", 0 }, {0,0,0} },
      { "rotationhub", "brnstrsec.3ds",{ "Height", "Count", "Speed", "Drop", 0 }, {0,0,0,0,0} },
      { "arm", "brnstrlifter.3ds",{ "Height", "Length", "Drop", "Offset", 0 }, {0,0,0,0,0} },
      { "cablehinge", "", { "Height", "Count", 0 }, {0,0,0} },
      { "car", "brnstrmcar.3ds",{ "Height", "Count", 0 }, {0,0,0} },
      { "door", "brnstrmdoor.3ds",{ "Height", "Offset", 0 }, {0,0,0} },
      { 0, 0, {0}, {0} }// EOS
   };
}

FlatRidePatterns::FlatRidePatterns( PartGuide& guide, const char* pszName )
:  mGuide( guide )
{
   mIndex = 0;
   mpSource = NULL;
   if (strcmp (pszName, "BarnStormer") == 0)
   {
      mpSource = Builders::kBarnStormer;
   }
}

FlatRidePatterns::~FlatRidePatterns()
{
}

bool FlatRidePatterns::LoadTemplate ()
{
   return true;
}

bool FlatRidePatterns::LoadNextFeature()
{
   if (mIndex >=0)
   {
      Builders::PatternData& pd = mpSource[mIndex++];
      for (int idx = 0; idx < 8; ++idx)
      {
         if (pd.pszParameters[idx][0] == 0)
            break;
         if (strcmp (pd.pszParameters[idx], "Height") == 0)
         {
            mGuide.fHeight = pd.fParameters[idx];
         }
         else if (strcmp (pd.pszParameters[idx], "Count") == 0)
         {
            mGuide.nCount = (int)pd.fParameters[idx];
         }
         else if (strcmp (pd.pszParameters[idx], "Speed") == 0)
         {
            mGuide.nSpeed = (short)pd.fParameters[idx];
         }
         else if (strcmp (pd.pszParameters[idx], "Drop") == 0)
         {
            mGuide.fDrop = pd.fParameters[idx];
         }
         else if (strcmp (pd.pszParameters[idx], "Offset") == 0)
         {
            mGuide.fOffset = pd.fParameters[idx];
         }
         else if (strcmp (pd.pszParameters[idx], "Length") == 0)
         {
            mGuide.fLength = pd.fParameters[idx];
         }
      }
      return true;
   }
   return false;
}
