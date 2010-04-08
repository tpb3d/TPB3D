/*   This file is part of ExtremePark Developer.
 *
 *   ExtremePark Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   ExtremePark Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with ExtremePark Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _Pathway_H
#define _Pathway_H
#include <vector>
#include <list>

#include "../Types/Vector2.h"
#include "CoreBase.h"
#include "../Graphics/ObjectNode.h"

// forward decls, some of these may be removed
class CoreBase;
class Park;
class RouteBase;
class PersonQueue;
class GameManager;
class PathAgent;
class ObjectNode;

class Pathway : public CoreBase, public ObjectNode
{
   friend class GameManager;
   friend class PathAgent;

public:
   // declarations
   typedef std::vector<Vector2f>::iterator PathNodeIterator;
   typedef std::vector<Vector2f> PathNodeVector;
   typedef std::vector<Pathway*>::iterator PathwayIterator;
   typedef std::vector<Pathway*> PathwayVector;
   typedef std::vector<CoreBase*>::iterator StallIterator;
   typedef std::vector<CoreBase*> StallVector;

protected:
   // implementation
   Pathway* mParent;   // if null use one of the nConnectors as a parent, check for recursion
   PathNodeVector mNodePath; // This paths nodes for movement and alignment.
   PathwayVector mConnectors; // other pathways that connect here
   StallVector mStalls;  // queues, shops, tras, ATM, benches and other things people may interact with.
   int  mID;

protected:
   Vector3f m_Point;
   std::string mTexName;
   ObjectNode* mpGraphic;

public:
   void  DrawEmptySpace();
   void  DrawSelectionTarget (bool PathwayOnly);
   void  DrawEmptyFramework();
   // End prototype code

public:
   // CTOR
   Pathway (const Vector3f& origin, Park* parent, const char* szTex);
   // Initialize from an xml node
   virtual ~Pathway ();

   // Properties
public:
   inline Pathway* GetParent () { return mParent; }
   inline int GetID () { return mID; }
   inline float GetX () { return m_Point.x; }
   inline float GetY () { return m_Point.y; }
   inline float GetZ () { return m_Point.z; }

   // Methods
   virtual void Update (float dt, int tod);
   virtual void Draw ();
   virtual void Render ();
   virtual void Render2 ();
   virtual void Render3 ();
   Pathway* Clone() { return new Pathway (Vector3f(mLocation[0],mLocation[1],mLocation[2]), NULL, mTexName.c_str()); }

   PathwayVector GetConnections() { return mConnectors; }

   void AddConnection (Pathway* pPath);
   bool AddFloorSpace (CoreBase * floor);
   void SetFloorPositions( int x, int x2 );
   CoreBase* GetSpaceByID (int id);
   CoreBase* FindSpace (int x); // location

   virtual const char* GetName () { return "Path"; }
   bool TestForEmptySpace (int x, int x2 );

   void Save(SerializerBase& ser);
   void Load(SerializerBase& ser);
};

#endif

