//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  ObjectTree factory
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////#pragma once

#include "ObjectBase.h"

class ObjectNode;

class ObjectTree : public ObjectBase
{
   int            m_AllocatedNodes;
   int            m_NodeCount;
   ObjectNode**  m_pNodes;
   float          m_Location[3];
   float          m_Rotation[3];

   virtual ObjectBase* Clone( )
   {
      throw( "Not Implemented" );
      return 0;
   }

public:
   ObjectTree( int id );
   virtual ~ObjectTree(void);

	virtual void Update(float);
	virtual void Draw();
   virtual void DrawSelectionTarget();
   void CloneNode( ObjectNode* m_pSelectedNode );

   void AddNode( ObjectNode* pNode );
   ObjectNode* FindNode( int id );
   ObjectNode* GetNode( int index );

   void SetRotation( float rotate[3] )
   {
      m_Rotation[0] = rotate[0]; // this optimizes nicely
      m_Rotation[1] = rotate[1];
      m_Rotation[2] = rotate[2];
   };
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};

