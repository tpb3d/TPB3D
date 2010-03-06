//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Flying Camera class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedMesh.h"
#include "Car.h"


Car::Car(sf::Vector3f& vDim, sf::Vector3f& vPosition, sf::Vector3f& vAngle, int meshCount, int id)
:  ObjectNode(8,600 )
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
   //try
   //{
   //}
   //catch( ... )
   //{
   //}
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
   ObjectNode::Draw();
   glPopMatrix();
}

// simple object management - to be replaced
void Car::AddSection( ObjectBase* pBase )
{
   m_BaseParts[m_PartsCount++] = pBase;
}

// simple wood car
void Car::Default()
{
   TexturedMesh* pMesh;
   Gfx::Texture* pTexB = Gfx::ImageManager::GetInstance()->GetTexture("basemetal.png",3);
   pMesh = new TexturedMesh( 4, 2, pTexB, 0x98b0b0b8, 600 );
   this->AddSection(pMesh);
   pMesh->AddPoint( sf::Vector3f(-2,0.5f,-3) );
   pMesh->AddPoint( sf::Vector3f(-2,0.5f, 3) );
   pMesh->AddPoint( sf::Vector3f(-2,0.8f,-3) );
   pMesh->AddPoint( sf::Vector3f(-2,0.8f, 3) );
   pMesh->AddPoint( sf::Vector3f( 2,0.8f,-3) );
   pMesh->AddPoint( sf::Vector3f( 2,0.8f, 3) );
   pMesh->AddPoint( sf::Vector3f( 2,0.5f,-3) );
   pMesh->AddPoint( sf::Vector3f( 2,0.5f, 3) );

   Gfx::Texture* pTexC = Gfx::ImageManager::GetInstance()->GetTexture("darkwood.png",3);
   pMesh = new TexturedMesh( 4, 2, pTexC, 0x7f7f7faf, 601 );
   this->AddSection(pMesh);
   pMesh->AddPoint( sf::Vector3f(-1.8f, 0.8f, 2.5f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 2.4f, 2.2f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 0.8f, 2.7f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 2.4f, 2.4f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 0.8f, 2.7f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 2.4f, 2.4f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 0.8f, 2.5f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 2.4f, 2.2f) );

   pMesh = new TexturedMesh( 4, 2, pTexC, 0x7f7f7faf, 602 );
   this->AddSection(pMesh);
   pMesh->AddPoint( sf::Vector3f(-1.8f, 0.8f, 1.3f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 2.4f, 1.0f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 0.8f, 0.2f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 2.4f, -0.1f) );
   pMesh->AddPoint( sf::Vector3f(-1.7f, 0.8f, 0.1f) );
   pMesh->AddPoint( sf::Vector3f(-1.7f, 2.4f, -0.2f) );
   pMesh->AddPoint( sf::Vector3f( 1.7f, 0.8f, 0.1f) );
   pMesh->AddPoint( sf::Vector3f( 1.7f, 2.4f, -0.2f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 0.8f, 0.2f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 2.4f, -0.1f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 0.8f, 1.3f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 2.4f, 1.0f) );

   pMesh = new TexturedMesh( 4, 2, pTexC, 0x7f7f7faf, 603 );
   this->AddSection(pMesh);
   pMesh->AddPoint( sf::Vector3f(-1.8f, 0.8f,-1.4f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 2.4f,-1.7f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 0.8f,-2.5f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 2.4f,-2.8f) );
   pMesh->AddPoint( sf::Vector3f(-1.7f, 0.8f,-2.6f) );
   pMesh->AddPoint( sf::Vector3f(-1.7f, 2.4f,-2.9f) );
   pMesh->AddPoint( sf::Vector3f( 1.7f, 0.8f,-2.6f) );
   pMesh->AddPoint( sf::Vector3f( 1.7f, 2.4f,-2.9f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 0.8f,-2.5f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 2.4f,-2.8f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 0.8f,-1.4f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 2.4f,-1.7f) );

   pMesh = new TexturedMesh( 4, 2, pTexC, 0x7f7f7faf, 604 );
   this->AddSection(pMesh);
   pMesh->AddPoint( sf::Vector3f(-1.8f, 1.5f, 1.0f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.5f, 1.0f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 1.8f, 1.0f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.8f, 1.0f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 1.8f, 0.0f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.8f, 0.0f) );

   pMesh = new TexturedMesh( 4, 2, pTexC, 0x7f7f7faf, 605 );
   this->AddSection(pMesh);
   pMesh->AddPoint( sf::Vector3f(-1.8f, 1.5f,-1.7f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.5f,-1.7f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 1.8f,-1.7f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.8f,-1.7f) );
   pMesh->AddPoint( sf::Vector3f(-1.8f, 1.8f,-2.65f) );
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.8f,-2.65f) );
}
