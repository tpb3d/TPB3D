//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Object class factory
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#pragma once
class ObjectBase;
class ObjectNode;
class MeshNode;
class ComponentObject;
class SimpleMeshObject; // Object;
class StripMeshObject;
class QuadMeshObject;
class ComplexMeshObject;


class ObjectFactory
{
   static int mNextObjectID;
protected:

public:
   ObjectFactory(void);
   ~ObjectFactory(void);
   static ObjectFactory& GetInstance();
   static int TakeANumber()
   {
      return mNextObjectID++;
   }
   static ObjectNode* CreateNode( int meshes );
   static MeshNode* CreateMeshNode( int meshes );
   static ComponentObject* CreateComponent();
   static SimpleMeshObject* CreateMesh();
   static QuadMeshObject* CreateQuadMesh();
   static StripMeshObject* CreateStrip();
   static ComplexMeshObject* CreateComplex();

   static ObjectBase* Clone( ObjectBase* pDupee );
};

