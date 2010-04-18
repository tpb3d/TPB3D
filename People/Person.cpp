/*   This file is part of Theme Park Builder 3D The Game.
 *
 *   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

// People that make the Park thrive.

#include <iostream>
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "Person.h"


Person::Person (Location& loc) {;} // To make the super child happy for now.
Person::Person ( const Vector3f &loc )
{
   float GrowthV = 0.0;
   float GrowthDrop = 0.0;
   short WeightV = 2;
   short WeightD = 0;
   mHeight = 0;
   inPark = false;

   mPathFind = NULL;

   // Random money generator
   mMoney = float(20 + rand() % 180);
   if(mMoney > 100) {
      mMoney =  float(20 + rand() % 180);
   }

   // Random age generator
   mAge = (rand() % 75) + 5; // random age in the range 5-80.
   if(mAge > 70)
   {
      mAge = (rand() % 75) + 5;
   }

   // Random gender generator
   mGender = Gender(rand() % 2);

   // Random height generator
   if(mGender == Female)
      GrowthV = 39 + (rand() % 3);
   else
      GrowthV = 40 + (rand() % 4);

   for(unsigned short i = 1; i < mAge+1; i++)
   {
      if(i < 2)
         GrowthDrop = GrowthV;
      if(i < 4 && i > 1)
         GrowthDrop = GrowthV - 45.0 / float(i);
      if(i < 17 && i > 3)
         GrowthDrop = 7.0; // Average growth for this age range
      if(i > 16)
         GrowthDrop = GrowthV - (GrowthV / 2.0); // Drop off growth rate after 17

      mHeight += int(GrowthV * 0.39);
      GrowthV = GrowthDrop;

      if(i > 19)
         break;
   }

   // Random weight generator
   for(unsigned short i = 1; i < mAge+1; i++)
   {
      if(i > 6)
      {
         if(mGender == Female)
         {
            if(WeightV <= 5)
               WeightV += 1;
         }
         else
         {
            if(WeightV <= 8)
               WeightV += 1;
         }

         WeightD += WeightV;
         mWeight = mHeight + WeightD;
      }
      else
      {
         mWeight = (rand() % 3) + mHeight;
      }

      if(i > 19)
         break;
   }

   // Ride intensity perference
   mRidePreference = RI_Thrill; // default

   if(mAge > 10)
   {
      if(mAge > 60)
      {
         mRidePreference = RideIntensity(rand() % 5);
         // Increase the chance of a thrill ride
         if(mRidePreference < RI_Thrill)
         {
            mRidePreference = RideIntensity(rand() % 5);
         }

         // Make older people perfer extreme rides less
         if(mRidePreference == RI_Extreme)
         {
            mRidePreference = RideIntensity(rand() % 5);
         }
      }

      if(mAge < 60)
      {
         mRidePreference = RideIntensity(rand() % 5);
         if(mRidePreference < RI_Thrill) // Increase the chance of a thrill ride
         {
            mRidePreference = RideIntensity(rand() % 5);
         }
      }
   }
   else
   {
      mRidePreference = RideIntensity(rand() % 3);
   }


   //AddItem( new FoodItem(50, 1.25) );


   mHealth = HS_Well;
   mMood = MS_Content;
   mActivity = AS_None; // Peep starts out doing nothing.
   mLastActivity = AS_None;
   mCurrentState = CS_Idle;

   mCurTod = 0;
   mInParkTime = 0;
   mTime = 0;
   mHunger = 0;
   mThirst = 0;
   mOccupation = 0;
   mHome = 0;
   //mLocation = loc;    // copy


   ImageManager * pImageMam = ImageManager::GetInstance ();
   Texture* ptexHappy =pImageMam->GetTexture ("person_h.png", GL_RGBA);
   Texture* ptexAnnoied =pImageMam->GetTexture ("person_a.png", GL_RGBA);
   Texture* ptexMad =pImageMam->GetTexture ("person_m.png", GL_RGBA);

   Vector2i size = Vector2i(mHeight/24, mHeight/12);

   manimations[MS_Furious] = new AnimationSingle (ptexMad, size.x, size.y);
   manimations[MS_Furious]->SetPosition(loc.x, loc.y, loc.z);

   manimations[MS_Mad] = new AnimationSingle (ptexMad, size.x, size.y);
   manimations[MS_Mad]->SetPosition(loc.x, loc.y, loc.z);

   manimations[MS_Annoyed] = new AnimationSingle (ptexAnnoied, size.x, size.y);
   manimations[MS_Annoyed]->SetPosition(loc.x, loc.y, loc.z);

   manimations[MS_Content] = new AnimationSingle (ptexHappy, size.x, size.y);
   manimations[MS_Content]->SetPosition(loc.x, loc.y, loc.z);

   manimations[MS_Happy] = new AnimationSingle (ptexHappy, size.x, size.y);
   manimations[MS_Happy]->SetPosition(loc.x, loc.y, loc.z);

   manimations[MS_Excited] = new AnimationSingle (ptexHappy, size.x, size.y);
   manimations[MS_Excited]->SetPosition(loc.x, loc.y, loc.z);
}

Person::~Person (void)
{
}

void Person::Update (int tod)   //actual time
{
   // Time in park for each peep
   if(mTime > (tod % 60) )
   {
      mInStateTime += 60;
      mInParkTime += 60;
      mTime = tod;
   }
   else
   {
      mTime = tod;
   }


   if(mCurTod > tod) // Reset time of day
   {
      mCurTod = tod;
   }

   // Update peep's hunger, thirst and other states once every park hour.
   if((tod-mCurTod) > 60)
   {
      if( mActivity != AS_Eating)
      {
         if(mHunger < 200) // Peep is always getting hungry, except when eating.
         {
            mHunger = (mHunger+1);
            //cout << "Current Hunger: " << mHunger << endl;
         }
      }

      if( mActivity == AS_None || mActivity == AS_LookingForFood )
      {
         if(mHunger > 100 && mHunger < 199)
         {
            mActivity = Person::AS_LookingForFood;
         }

         if(mHunger >= 199)
         {
            mMood = MS_Furious;
            mActivity = Person::AS_GoingHome;
         }
      }
      mCurTod = tod;
   }


   if(mLastActivity != mActivity) {
      mInStateTime = 0;
      mLastActivity = mActivity;
   }


   if(inPark) {

      // Peep is doing nothing
      if( mActivity == AS_None)
      {
         mActivity = AS_Wandering;
//         int n = rand() % 3;
//
//         if(n == 1) mActivity = AS_Wandering;
//         if(n == 2) mActivity = AS_LookingForRide;
      }

      if(mActivity == AS_Wandering) {
         if(mInStateTime > 60*12)
         {
            mActivity = AS_None;
         }
      }

      // Peep has food, so let the peep eat it
      if( mActivity == AS_Eating )
      {
         short bite = 2;

         FoodItem *item = (FoodItem*)GetItemByType(ItemBase::IC_Food);
         if(item)
         {
            cout << "Peep is eating. Hunger: " << mHunger << endl;
            mHunger = (mHunger-bite);

            if( mHunger <= 0 )
            {
               cout << "Peep is full" << endl;

               mActivity = AS_None;
               if(mHunger < 0) mHunger = 0;

               RemoveItem(item); // Remove food item
               // Need to add a trash item here.
            }
         }
         else
         {
            mActivity = AS_None;
         }
      }

      // Peep is on a ride
      if( mActivity == AS_Riding)
      {
         if(mInStateTime > 60*24)
         {
            mMood = MS_Furious;
         }
      }
   }
   else // Not in the park yet, look for the entrance
   {
      mActivity = AS_LookingForEntrance;
   }



//   // check time of day, what activity should we be doing.
//   if (tod > 20*60 && !(mActivity == AS_Sleeping) )
//   {
//      SetActivity (AS_Sleeping);
//   }
//
//   if (mOccupation < 1) // && age > 16 )
//   {
//      SetActivity (AS_JobHunting);
//      return;
//   }
//   else if (mHome < 1 && mActivity == AS_GoingHome )
//   {
//      SetActivity (AS_ApartmentHunting);
//      return;
//      //mActivity = AS_CondoHunting; // if income < $n AS_ApartmentHunting.
//   }
//
//   switch (mActivity)
//   {
//   case AS_GoingToWork:
//      if (mWorkPath.index < mWorkPath.size)
//      {
//         Location& cur = mWorkPath.mPathList[mWorkPath.index];
//         // TODO: check building first but for now we only have 1
//         if (cur.mPathway == mLocation.mPathway)
//         {
//            mLocation.mX = cur.mX; // TODO: Move peep in animator
//            mWorkPath.index++;
//         }
//         else
//         {
//            // waiting
//         }
//      }
//      if (mWorkPath.index >= mWorkPath.size) // this can be handled better and also need to check times
//      {
//         mLocation.mPathway = mWorkPath.mPathList[mWorkPath.index-1].mPathway; // this will bring the car to the Building Pathway at days end
//         SetActivity( AS_Working ); // Buildings and businesses show employees at work.
//      }
//      break;
//   case AS_Working:
//      if (tod > 17*60)
//      {
//         SetActivity( AS_ClockingOut );
//         SetCurrentState( Person::CS_Walking );
//         mWorkPath.index--;  // this is the return trip home
//      }
//      else if( tod > 11*60+45 && tod < 13*60+15) // do lunch
//      {
//         SetActivity( AS_LunchBreak );
//         SetCurrentState( Person::CS_Walking );
//         mWorkPath.index--;  // this is the return trip home
//      }
//      break;
//   case AS_LunchBreak:
//      if( tod > 13*60) // do lunch
//      {
//         SetActivity( AS_GoingToWork );
//         SetCurrentState( Person::CS_Walking );
//      }
//      break;
//   case AS_GoingHome:
//      if (mWorkPath.index > 0)
//      {
//         Location& cur = mWorkPath.mPathList[mWorkPath.index];
//         // TODO: check building first but for now we only have 1
//         if (cur.mPathway == mLocation.mPathway)
//         {
//            mLocation.mX = cur.mX; // TODO: Move peep in animator
//            mWorkPath.index--;
//         }
//         else
//         {
//            // waiting
//         }
//      }
//      else
//      {
//         SetActivity( AS_Relaxing ); // Buildings and businesses show employees at work.
//         mLocation.mPathway = mWorkPath.mPathList[mWorkPath.index].mPathway; // this will bring the car to the Building Pathway at days end
//      }
//      break;
//   case AS_Sleeping:
//      if (tod > 6*60 && tod < 14*60)
//      {
//         SetActivity( AS_GoingToWork );
//         SetCurrentState( CS_Busy );
//      }
//      break;
//   }

}

void Person::SetLocation( const Vector3f &loc)
{
   manimations[MS_Content]->SetPosition(loc.x, loc.y, loc.z);
}

Vector3f Person::GetLocation()
{
   return Vector3f(manimations[MS_Content]->GetPositionX(),
                   manimations[MS_Content]->GetPositionY(),
                   manimations[MS_Content]->GetPositionZ());
}

void Person::Draw()
{
   Render (manimations[mMood] );
}

void Person::Draw (float vx, float vy)
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

bool Person::AddItem(ItemBase* item)
{
   unsigned int nItems = 0;

   ItemBase::ItemIterator i;
   for (i = mItems.begin (); i != mItems.end (); i++)
   {
      ItemBase* itm = (*i);

      // Peep can only have one food item at a time.
      if(item->getCategory() == ItemBase::IC_Food)
      {
         if( item->getCategory() == itm->getCategory())
         {
            return false;
         }
      }

      // Peep can only have one dirnk item at a time.
      if(item->getCategory() == ItemBase::IC_Drink)
      {
         if( item->getCategory() == itm->getCategory())
         {
            return false;
         }
      }

      // Peep can only have 3 souvenir items at a time.
//      if(item->GetType() == ItemCategory::IT_Souvenir)
//      {
//         if( item->GetType() == itm->GetType())
//         {
//            nItems++;
//            if(nItems == 3) {
//               return false;
//            }
//         }
//      }

      // Peep can only have 2 information items at a time.
      if(item->getCategory() == ItemBase::IC_Brocure)
      {
         if( item->getCategory() == itm->getCategory())
         {
            nItems++;
            if(nItems == 2) {
               return false;
            }
         }
      }
   }

   mItems.push_back(item);
   return true;
}
void Person::RemoveItem(ItemBase* item)
{
   ItemBase::ItemIterator i;
   for (i = mItems.begin (); i != mItems.end (); i++)
   {
      ItemBase* itm = (*i);
      if(itm == item)
      {
         mItems.erase(i);
      }
   }
}

ItemBase* Person::GetItemByType(ItemBase::ItemCategory type)
{
   ItemBase::ItemIterator  i;
   for (i = mItems.begin (); i != mItems.end (); i++)
   {
      ItemBase* item = (*i);

      if(type == item->getCategory()) {
         return item;
      }
   }

   return NULL;
}

ItemBase::ItemVector Person::GetItemList() const
{
   return mItems;
}

void Person::SetCurrent( int Pathway )
{
   mLocation.mPathway = Pathway;
}

Person::Mood_State Person::GetMood() const
{
   return mMood;
}

Person::Health_State Person::GetHealth() const
{
   return mHealth;
}

RideIntensity Person::GetRidePreference() const
{
   return mRidePreference;
}

unsigned short Person::GetHeight() const
{
   return mHeight;
}

unsigned short Person::GetAge() const
{
   return mAge;
}

Person::Gender Person::GetGender() const
{
   return mGender;
}

short Person::GetHunger() const
{
   return mHunger;
}

short Person::GetThirst() const
{
   return mThirst;
}

unsigned int Person::GetInParkTime() const
{
   return mInParkTime;
}

void Person::SetMood(const Mood_State &mood)
{
   mMood = mood;
}

void Person::SetHealth(const Health_State &health)
{
   mHealth = health;
}

void Person::SetHunger(const unsigned int &hunger)
{
   mHunger = hunger;
}

void Person::SetThirst(const unsigned int &thirst)
{
   mThirst = thirst;
}

void Person::SetInParkTime(const unsigned int &t)
{
   mInParkTime = t;
}

void Person::SetPathway(Pathway *path)
{
   if(path)
   {
      //this->SetLocation( Vector3f( path->GetX(), -path->GetY() - 6, path->GetZ()) );
      mPath = path;
   }
}