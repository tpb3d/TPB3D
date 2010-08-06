#pragma once

namespace Builders
{
   struct PatternData
   {
      const char* pszType;
      const char* pszName;
      const char* parameters[8];
   };
}

class FlatRidePatterns
{
public:
   FlatRidePatterns(void);
   ~FlatRidePatterns(void);
};
