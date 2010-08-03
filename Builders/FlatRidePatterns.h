#pragma once

namespace Builders
{
   struct PatternData
   {
      const char* pszType;
      const char* pszName;
      const char* pszParameters[8];
      const float fParameters[8];
   };
}

struct PartGuide;

class FlatRidePatterns
{
protected:
   int mIndex;
   PartGuide& mGuide;
   Builders::PatternData* mpSource;

public:
   FlatRidePatterns( PartGuide& guide, const char* pszName );
   ~FlatRidePatterns(void);

   bool LoadTemplate ();
   bool LoadNextFeature();
};
