#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ObjectBase.h"
#include "Car.h"

Car::Car(sf::Vector3f& vDim, sf::Vector3f& vPosition, sf::Vector3f& vAngle, int meshCount, int id)
:  ObjectBase( meshCount, id )
{
   m_BaseTexture = 2;
   m_SeatTexture = 3;
   m_SideTexture = 5;
   m_vDim = vDim;
   m_vPosition = vPosition;
   m_vAngle = vAngle;
   m_PartsCount = 0;
}

Car::~Car(void)
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

int Car::Render( int lod ) // render returning the poly count
{
//   CGLTexturedMesh* pMesh;
   return 0;
}

void Car::Draw()
{
	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( m_vPosition.x, m_vPosition.y+1.5f, m_vPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(m_vAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-m_vAngle.y,0.0f,1.0f,0.0f);
	glRotatef(m_vAngle.z,0.0f,0.0f,1.0f);

   for( int ix = 0; ix < m_PartsCount; ++ix )
   {
      m_BaseParts[ix]->Draw();
   }
   glPopMatrix();
}

