//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Tree class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
#include "ObjectNode.h"

class ObjectBase;

struct TreeData
{
   float length;
   float y;
   int radion;
   int leafStyle;
};

class Tree : public ObjectNode
{
   float m_dHeight; // = 5;
   int   m_PartsCount;
   ObjectNode** m_pTreeParts;

public:
   Tree(void);
   virtual ~Tree(void);
//   void AddSection( CObjectNode* pGLBase );
//   void Draw();
};
