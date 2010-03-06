//#include "stdafx.h"
#include "Rail.h"

CRail::CRail( double dDiameter, CVPoint Position ) // position in the track or structure and diameter
:  m_Position( Position )
{
   m_dRadius = dDiameter / 24; // = /12" /2
}

CRail::~CRail(void)
{
}
