//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  ObjectTree class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ObjectTree.h"
#include "ObjectBase.h"
#include "ObjectNode.h"
#include "ObjectFactory.h"
#include "../Storage/SerializerBase.h"
// PNG image handler functions
// cexcept interface

const float verts[6][3] =
{
   { -5.0, 0, 10 },
   { -5.0, 10, 10 },
   {  0, 0, 10 },
   {  0, 10, 10 },
   {  0, 0, 15 },
   {  0, 10, 15 }
};

const int faces[8][3] =
{
   { 0,1,2 },
   { 2,1,3 },
   { 2,3,4 },
   { 4,3,5 },
   { 4,5,0 },
   { 0,5,1 }
};

const float test[16][2] =
{
   {0.5f, 1.0f}, // base BL
   {0.0f, 0.62f}, // side TR
   {0.5f, 0.62f}, // side BR
   {1.0f, 1.0f}, // base BR
   {0.5f, 0.62f}, //base TL
   {1.0f, 0.62f}, // rear base TR
   {0.5f, 0.62f}, // lid BL
   {1.0f, 0.62f}, // lid BR
   {0.5f, 0.0f}, //8 lid TL
   {1.0f, 0.0f}  //  lid TR
};


ObjectTree::ObjectTree( int id )
:  ObjectBase( 1, id ) // just the mount point
{
   m_NodeCount = 0;
   m_pNodes = 0;
   m_AllocatedNodes = 0;
   m_Location[0] = 0;
   m_Location[1] = 1;
   m_Location[2] = 0;
   m_Rotation[0] = 0;
   m_Rotation[1] = 0;
   m_Rotation[2] = 0;

}

ObjectTree::~ObjectTree(void)
{
   if( m_pNodes )
   {
      for( int idx = 0; idx < m_NodeCount; ++idx )
      {
         ObjectNode* pObj = m_pNodes[idx];
         delete pObj;
      }
      delete [] m_pNodes;
   }
}

void ObjectTree::Update(float dt)
{
   for( int idx = 0; idx < m_NodeCount; ++idx )
   {
      ObjectNode* pObj = m_pNodes[idx];
      pObj->Update((int)dt);
   }
}


void ObjectTree::Draw()
{
   glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
	glTranslatef( m_Location[0],m_Location[1],m_Location[2] );

	glRotatef(m_Rotation[0],1.0f,0.0f,0.0f);
	glRotatef(m_Rotation[1],0.0f,1.0f,0.0f);
	glRotatef(m_Rotation[2],0.0f,0.0f,1.0f);
//   m_Rotation[1]+= 0.2; //animation

   for( int idx = 0; idx < m_NodeCount; ++idx )
   {
      ObjectNode* pObj = m_pNodes[idx];
      pObj->Draw();
   }
   glPopMatrix();
}

void ObjectTree::DrawSelectionTarget()
{
   for( int idx = 0; idx < m_NodeCount; ++idx )
   {
      ObjectNode* pObj = m_pNodes[idx];
      if( pObj->GetID() )
      {
         pObj->DrawSelectionTarget();
      }
   }
}

void ObjectTree::AddNode( ObjectNode* pNode )
{
   if( m_NodeCount+1 > m_AllocatedNodes )
   {
      m_AllocatedNodes += 4;
      ObjectNode** pNodes = new ObjectNode*[m_AllocatedNodes];
      if( m_AllocatedNodes > 0 )
      {
         for( int idx = 0; idx < m_NodeCount; ++idx )
         {
            pNodes[idx] = m_pNodes[idx];
         }
         delete [] m_pNodes;
      }
      m_pNodes = pNodes;
   }
   m_pNodes[m_NodeCount++] = pNode;
}

ObjectNode* ObjectTree::GetNode( int index )
{
   ObjectNode* pNode = 0;
   if( index < m_NodeCount )
   {
      pNode = m_pNodes[index];
   }
   return pNode;
}

ObjectNode* ObjectTree::FindNode( int id )
{
   ObjectNode* pNodeFound = 0;
   for( int idx = 0; idx < m_NodeCount; ++idx )
   {
      ObjectNode* pNode = m_pNodes[idx];
      if( pNode->GetID() == id )
      {
         pNodeFound = pNode;
         break;
      }
   }
   return pNodeFound;
}

void ObjectTree::CloneNode( ObjectNode* pSelectedNode )
{
   ObjectNode* pClonedNode = reinterpret_cast<ObjectNode*>(ObjectFactory::Clone( pSelectedNode ));
   float newLoc[] = { 0,0,0 };
   for( float idx = -20; idx < 20; idx+=4 )
   {
      for( float idy = -20; idy < 20; idy+=4 )
      {
         ObjectNode* pClonedNode = reinterpret_cast<ObjectNode*>(ObjectFactory::Clone( pSelectedNode ));
         newLoc[0] = idx;
         newLoc[2] = idy;
         pClonedNode->Move( newLoc );
         AddNode( pClonedNode );
      }
   }
}

void ObjectTree::Load(SerializerBase& ser)
{
//   TrackSection* pTrackSection = new TrackSection();
//   pTrackSection->Load(ser);
}

void ObjectTree::Save(SerializerBase& ser)
{
   ser.Add("type", "Trunk");
   ser.Add("ID", mID);
   SerializerBase* pSer = ser.Spawn("Branches");
   for( int ix = 0; ix < m_NodeCount; ++ix )
   {
      ObjectNode* pNode = m_pNodes[ix];
      pNode->Save(*pSer);
   }
   delete pSer;
}