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

#ifndef _MEDICALCLINIC_H
#define _MEDICALCLINIC_H

#include <map>

#include "../Graphics/ModelObject.h"
#include "CoreBase.h"

class Animation;
class SerializerBase;

enum MedicalState
{
   MS_NightUnoccupied = 0, 
   MS_NightOccupied,
   MS_DayUnoccupied,
   MS_DayOccupied
};

class MedicalClinic : public CoreBase, public Gfx::ModelObject
{
   std::map<MedicalState, AnimationBase*> manimations;
   MedicalState mCurrentState;// vacant /occupied / day / night
   int mCurrentAnimation;
   int mPatients;
   int mEmployees;
   int mMaxPositions;
   int mMedicalClinicStyle; // MedicalClinics, boardrooms, data Clinics, phone banks, etc
   int mMedicalClinicNumner;

public:
   MedicalClinic (int x, int level, Park * TowerParent);

   void Update (float dt, int tod);
   void Draw ();
   void DrawFramework ();
   virtual BaseType GetType () { return BaseClinic; }

   void RemoveImages();
   void SetImages (int set);
   void Save(SerializerBase& ser);

   void PeopleInOut( int count );
   bool PeopleApply( );    // get a job
   void SetMedicalClinicNumber(int no) { mMedicalClinicNumner = no; }
   int  GetMedicalClinicNumber() { return mMedicalClinicNumner; }

private:
   void MedicalClinicState(int tod);
};

#endif //_MEDICALCLINIC_H
