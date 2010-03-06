//#include "stdafx.h"
//#include "CamPath.h"
#include "Track.h"
#include "ObjectBase.h"
//#include "MainFrame.h"
#include "ObjectFactory.h"


CTrack::CTrack(void)
:  ObjectNode( 5, 5/*gObjectFactory.TakeANumber()*/ )
{
   m_dHeight = 5;
   m_PartsCount = 0;
}

CTrack::~CTrack(void)
{
   try
   {
      for( int ix = 0; ix < m_PartsCount; ++ix )
      {
         delete m_BaseParts[ix];
      }
   }
   catch( ... )
   {
   }
}

void CTrack::AddSection( ObjectBase* pBase )
{
   m_BaseParts[m_PartsCount++] = pBase;
}

void CTrack::Draw()
{
   for( int ix = 0; ix < m_PartsCount; ++ix )
   {
      m_BaseParts[ix]->Draw();
   }
}
