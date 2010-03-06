#pragma once
#include "VPoint.h"

class CRail
{
   CVPoint  m_Position; // Location of this rail in the track.
   double   m_dRadius;

public:
   CRail( double dDiameter, CVPoint Position ); // position in the track or structure and diameter
   ~CRail(void);

   void RenderSection( CVPoint& PointA, CVPoint& PointB )
   {
   }
};
