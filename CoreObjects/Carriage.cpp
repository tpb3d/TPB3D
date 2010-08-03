//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Flying Camera class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#define _USE_MATH_DEFINES
#include <math.h>
#include "Carriage.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/SimpleMeshObject.h"
#include "../Graphics/ObjectFactory.h"


Carriage::Carriage()
{
   mpGraphic = ObjectFactory::CreateMesh();
}

Carriage::~Carriage(void)
{
   //try
   //{
   //}
   //catch( ... )
   //{
   //}
}

void Carriage::Render()
{
}

void Carriage::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glTranslatef( mvPosition.x, mvPosition.y+1.5f, mvPosition.z );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(mvAngle.x,1.0f,0.0f,0.0f);
	glRotatef(-mvAngle.y,0.0f,1.0f,0.0f);
	glRotatef(mvAngle.z,0.0f,0.0f,1.0f);

   RideNode::Draw();
   glPopMatrix();
}

void Carriage::DrawSelectionTarget(int t)
{
}

// simple object management - to be replaced

// simple wood Carriage
void Carriage::Default()
{
/*   TexturedMesh* pMesh;
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
   pMesh->AddPoint( sf::Vector3f( 1.8f, 1.8f,-2.65f) );*/
}

//ObjectBase* Carriage::Clone( )
//{
//   Carriage* pCA = new Carriage();
//   return pCA;
//}
