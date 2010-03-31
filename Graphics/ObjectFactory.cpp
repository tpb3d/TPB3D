//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Object class factory
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "ObjectNode.h"
#include "MeshNode.h"
#include "SimpleMeshObject.h"
#include "ComponentObject.h"
#include "StripMeshObject.h"
#include "QuadMeshObject.h"
#include "ComplexMeshObject.h"
#include "ObjectFactory.h"
#include "TexturedStrip.h"
#include "TexturedMesh.h"
#include "Image.h"

int ObjectFactory::mNextObjectID = 1;

ObjectFactory::ObjectFactory(void)
{
}

ObjectFactory::~ObjectFactory(void)
{
}

ObjectNode* ObjectFactory::CreateNode( int meshes )
{
   return new ObjectNode( meshes, TakeANumber() );
}

MeshNode* ObjectFactory::CreateMeshNode( int meshes )
{
   return new MeshNode( meshes, TakeANumber() );
}

ComponentObject* ObjectFactory::CreateComponent()
{
   return new ComponentObject( TakeANumber() );
}

SimpleMeshObject* ObjectFactory::CreateMesh() // Objec
{
   return new SimpleMeshObject( TakeANumber() );
}

QuadMeshObject* ObjectFactory::CreateQuadMesh() // Objec
{
   return new QuadMeshObject( TakeANumber() );
}

StripMeshObject* ObjectFactory::CreateStrip() // Objec
{
   return new StripMeshObject( TakeANumber() );
}

ComplexMeshObject* ObjectFactory::CreateComplex() // Objec
{
   return new ComplexMeshObject( 1, TakeANumber() );
}

TexturedStrip* ObjectFactory::CreateTexturedStrip(int length, const char* pTexName, long color)
{
   return new TexturedStrip (length, Gfx::ImageManager::GetInstance()->GetTexture(pTexName, 4), color);
}

TexturedMesh* ObjectFactory::CreateTexturedMesh(int length, int width, const char* pTexName, long color)
{
   return new TexturedMesh (length, width, Gfx::ImageManager::GetInstance()->GetTexture(pTexName, 4),
                            color, TakeANumber());
}

ObjectBase* ObjectFactory::Clone( ObjectBase* pDupee )
{
   return pDupee->Clone( );
}

