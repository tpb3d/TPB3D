/*   This file is part of Theme Park Developer 3D The Game.
 *
 *   Theme Park Developer 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Developer 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

// People that make the Park thrive.

#include <iostream>
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "Person.h"

Person::Person (Location& loc)
{
   mHealth = HS_Well;
   mMood = MS_Content;
   mActivity = AS_JobHunting; // noob, starts out looking for home, job etc.
   mOccupation = 0;
   mHome = 0;
   mCurrentState = CS_Idle;
   mLocation = loc;    // copy
   ImageManager * pImageMam = ImageManager::GetInstance ();
   Texture* ptexHappy =pImageMam->GetTexture ("person_h.png", GL_RGBA);
   Texture* ptexAnnoied =pImageMam->GetTexture ("person_a.png", GL_RGBA);
   Texture* ptexMad =pImageMam->GetTexture ("person_m.png", GL_RGBA);

   manimations[MS_Furious] = new AnimationSingle (ptexMad, 8, 16);
   manimations[MS_Mad] = new AnimationSingle (ptexMad, 8, 16);
   manimations[MS_Annoyed] = new AnimationSingle (ptexAnnoied, 8, 16);
   manimations[MS_Annoyed]->SetPosition(590,0);
   manimations[MS_Content] = new AnimationSingle (ptexHappy, 8, 16);
   manimations[MS_Content]->SetPosition(590,0);
   manimations[MS_Happy] = new AnimationSingle (ptexHappy, 8, 16);
   manimations[MS_Happy]->SetPosition(590,0);
   manimations[MS_Excited] = new AnimationSingle (ptexHappy, 8, 16);
   manimations[MS_Excited]->SetPosition(590,0);

}
Person::~Person (void)
{
}

void Person::Update (int tod)   //actual time
{
   // check time of day, what activity should we be doing.
   if (tod > 20*60 && !(mActivity == AS_Sleeping) )
   {
      SetActivity (AS_Sleeping);
   }

   if (mOccupation < 1) // && age > 16 )
   {
      SetActivity (AS_JobHunting);
      return;
   }
   else if (mHome < 1 && mActivity == AS_GoingHome )
   {
      SetActivity (AS_ApartmentHunting);
      return;
      //mActivity = AS_CondoHunting; // if income < $n AS_ApartmentHunting.
   }

   switch (mActivity)
   {
   case AS_GoingToWork:
      if (mWorkPath.index < mWorkPath.size)
      {
         Location& cur = mWorkPath.mPathList[mWorkPath.index];
         // TODO: check building first but for now we only have 1
         if (cur.mPathway == mLocation.mPathway)
         {
            mLocation.mX = cur.mX; // TODO: Move peep in animator
            mWorkPath.index++;
         }
         else
         {
            // waiting 
         }
      }
      if (mWorkPath.index >= mWorkPath.size) // this can be handled better and also need to check times
      {
         mLocation.mPathway = mWorkPath.mPathList[mWorkPath.index-1].mPathway; // this will bring the car to the Building Pathway at days end
         SetActivity( AS_Working ); // Buildings and businesses show employees at work.
      }
      break;
   case AS_Working:
      if (tod > 17*60)
      {
         SetActivity( AS_ClockingOut );
         SetCurrentState( Person::CS_Walking );
         mWorkPath.index--;  // this is the return trip home
      }
      else if( tod > 11*60+45 && tod < 13*60+15) // do lunch
      {
         SetActivity( AS_LunchBreak );
         SetCurrentState( Person::CS_Walking );
         mWorkPath.index--;  // this is the return trip home
      }
      break;
   case AS_LunchBreak:
      if( tod > 13*60) // do lunch
      {
         SetActivity( AS_GoingToWork );
         SetCurrentState( Person::CS_Walking );
      }
      break;
   case AS_GoingHome:
      if (mWorkPath.index > 0)
      {
         Location& cur = mWorkPath.mPathList[mWorkPath.index];
         // TODO: check building first but for now we only have 1
         if (cur.mPathway == mLocation.mPathway)
         {
            mLocation.mX = cur.mX; // TODO: Move peep in animator
            mWorkPath.index--;
         }
         else
         {
            // waiting
         }
      }
      else
      {
         SetActivity( AS_Relaxing ); // Buildings and businesses show employees at work.
         mLocation.mPathway = mWorkPath.mPathList[mWorkPath.index].mPathway; // this will bring the car to the Building Pathway at days end
      }
      break;
   case AS_Sleeping:
      if (tod > 6*60 && tod < 14*60)
      {
         SetActivity( AS_GoingToWork );
         SetCurrentState( CS_Busy );
      }
      break;
   }
}

void Person::Draw ()
{
   
   Render (manimations[mMood] );
}

void Person::Draw (int vx, int vy)
{
   
   Render (manimations[mMood], vx, vx+8 );
}

void Person::SetResidence (int Pathway)
{
   SetActivity (AS_GoingHome);
   mWorkPath.mPathList[0].mPathway = Pathway;
   mWorkPath.mPathList[0].mX = 400; // need this
   mHome = 1; // pResidence
}

void Person::SetCurrent( int Pathway )
{
   mLocation.mPathway = Pathway;
}