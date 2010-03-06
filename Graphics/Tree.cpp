//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Tree class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Tree.h"
#include "ObjectFactory.h"

Tree::Tree(  )
:  ObjectNode( 5, ObjectFactory::TakeANumber() )
{
   m_PartsCount = 0;
   m_dHeight = 5;
   m_pTreeParts = new ObjectNode*[8];
}

Tree::~Tree(void)
{
   for( int idx =0;idx < m_PartsCount; ++idx )
   {
      ObjectNode* pNode = m_pTreeParts[idx];
      delete pNode;
   }
   delete [] m_pTreeParts;
}

//void CTree::AddSection( CObjectNode* pBase )
//{
//   m_pTreeParts[m_PartsCount++] = pBase;
//}

//void CTree::Draw()
//{
//   for( int ix = 0; ix < m_PartsCount; ++ix )
//   {
//      m_pTreeParts[ix]->Draw();
//   }
//}
