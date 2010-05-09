//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Author Level5
//  Licensed according to the GPL v3.0
//
//  ParkBench class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

//#pragma once
#ifndef PARKBENCH_H
#define PARKBENCH_H

#include "CoreBase.h"
#include "../Graphics/ObjectNode.h"
#include "PersonQueue.h"

#include "PathItem.h"

class Bench : public PathItem
{

   protected:

      PersonQueue mQueue;
      const char *mObjName;
      ObjectNode* mpGraphic;

      std::list<Person*> mPeepList;

   private:
      unsigned short mSeats;

   public:
      Bench(ObjectNode *node, Pathway *path, float alignment, ItemHeading side, unsigned short seats);
      virtual ~Bench();

      const char *GetName() { return "Bench"; }

      void AddPerson (Person* pPeep);
      void RemovePerson (Person* pPeep);


      void SetGraphic (ObjectNode* pGfx) { mpGraphic = pGfx; }
      ObjectNode *GetGraphic() { return mpGraphic; }

      void Draw();




      void Update (float dt, int tod) {;}
      BaseType GetType () { return BasePathItem;}
      CoreBase* Clone() { return NULL;} // this might end ugly until we implement

      void DrawSelectionTarget() {;}

      void Save(SerializerBase& ser) {;}
      void Load(SerializerBase& ser) {;}
};

#endif // PARKBENCH_H
