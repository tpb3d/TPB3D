//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  RideNode class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "RideNode.h"
#include "../Graphics/ObjectFactory.h"
#include "../Storage/SerializerBase.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/Vector3.h"
#include "../Graphics/Image.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/TexturedMesh.h"

RideNode::RideNode()
{
}

RideNode::~RideNode(void)
{
   try
   {
      RideNodeIterator ir;
      for (ir = mBaseParts.begin(); ir != mBaseParts.end(); ir++)
      {
         RideNode* pB = *(ir);
         delete pB;
      }
   }
   catch( ... )
   {
   }
}

void RideNode::AddNode( RideNode* pBase )
{
   mBaseParts.push_back(pBase);
}

void RideNode::Clear()
{
   try
   {
      while (mBaseParts.size() > 0)
      {
         mBaseParts.pop_back();
         RideNode* pB = *(mBaseParts.end());
         delete pB;
      }
   }
   catch( ... )
   {
   }
}

void RideNode::Update(int dt)
{
   RideNodeIterator ir;
   for (ir = mBaseParts.begin(); ir != mBaseParts.end(); ir++)
   {
      RideNode* pB = *(ir);
      pB->Update (dt);
   }
}

void RideNode::Draw()
{
   RideNodeIterator ir;
   for (ir = mBaseParts.begin(); ir != mBaseParts.end(); ir++)
   {
      RideNode* pB = *(ir);
      pB->Draw();
   }
//   SectionIterator im = mMeshes.begin();
//   ObjectBase* pMesh = *im;
//   pMesh->Draw();
}

void RideNode::Load(SerializerBase& ser)
{
   // need to build a factory for this
   //RideNodeSection* pRideNodeSection = new RideNodeSection();
   //pRideNodeSection->Load(ser);
}

void RideNode::Save(SerializerBase& ser)
{
   ser.Add("type", "RideNode");
   RideNode::Save(ser);
   try
   {
      RideNodeIterator ir;
      for (ir = mBaseParts.begin(); ir != mBaseParts.end(); ir++)
      {
         RideNode* pB = *(ir);
         SerializerBase* pSer = ser.Spawn("RideNodeSections");
         pB->Save(*pSer);
         delete pSer;
      }
   }
   catch( ... )
   {
   }
//   delete pSer;
}