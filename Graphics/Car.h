#pragma once
#include "ObjectBase.h"

class Car : public ObjectBase
{
   int m_BaseTexture;
   int m_SeatTexture;
   int m_SideTexture;
   sf::Vector3f  m_vDim;
   sf::Vector3f  m_vPosition;
   sf::Vector3f  m_vAngle;
   int      m_PartsCount;
   int      m_PointsCount;
   ObjectBase* m_BaseParts[8];  // temp hardcode

public:
   Car(sf::Vector3f& vDim, sf::Vector3f& vPosition, sf::Vector3f& vAngle, int meshcount, int id );
   virtual ~Car(void);

   void Draw();
   void Render() { Render(0); };
   int Render( int lod ); // render returning the poly count
   int GetPathCount() { return m_PointsCount; };
//   virtual void SyncTexture( CMainFrame* pInterface );
   void Position(sf::Vector3f& vPosition, sf::Vector3f& vAngle)
   {
      m_vPosition = vPosition;
      m_vAngle = vAngle;
   };
};
