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


Person::Person (Location& loc) {;}
Person::Person ( const Vector3f &loc )
{
   float GrowthV = 0.0;
   float GrowthDrop = 0.0;
   mHeight = 0;

   // Random age generator
   mAge = (rand() % 75) + 5; // random age in the range 5-80.
   if(mAge > 70)
   {
      mAge = (rand() % 75) + 5;
   }

   // Random gender generator
   mGender = Gender(rand() % 2);

   // Random height generator
   if(mGender == Female) {
     GrowthV = (rand() % 3) + 28;
   }
   else
   {
      GrowthV = (rand() % 4) + 30;
   }


   for(unsigned short i = 1; i < mAge; i++)
   {
      if(i < 4)
         GrowthDrop = GrowthV - float(10 / float(i) );
      if(i < 16 && i > 3)
         GrowthDrop = 8.5;
      if(i > 16)
         GrowthDrop = GrowthV - float(GrowthV / 2);

      mHeight += (GrowthV) * 0.39;
      GrowthV = GrowthDrop;

      if(i > 19)
         break;
   }

   // Random weight generator
   if(mAge > 17)
   {
      if(mGender == Female)
      {
         short ran = mWeight = rand() % 4;
         if(ran < 3)
         {
            mWeight = (rand() % 20) + (mHeight + 50);
         }
         else if(ran == 3)
         {
            mWeight = (rand() % 100) + (mHeight + 70);
         }
      }

      if(mGender == Male)
      {
         short ran = mWeight = rand() % 4;
         if(ran < 3)
         {
            mWeight = (rand() % 30) + (mHeight + 80);
         }
         else if(ran == 3)
         {
            mWeight = (rand() % 100) + (mHeight + 100);
         }
      }
   }
   else // People under 17, This needs work
   {
      if(mGender == Female)
      {
         mWeight = (rand() % 50) + (mHeight) + 40;
      }

      if(mGender == Male)
      {
         mWeight = (rand() % 50) + (mHeight) + 50;
      }
   }

   // Ride intensity perference
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

   AddItem( new FoodItem(50, 500) );


   mHealth = HS_Well;
   mMood = MS_Content;
   mActivity = AS_None; // Peep starts out doing nothing.
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
   manimations[MS_Mad] = new AnimationSingle (ptexMad, size.x, size.y);
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

   // Peep is doing nothing
   if( mActivity == AS_None)
   {
      mActivity = AS_LookingForRide; // Just ride for now
   }

    // Peep has food
   if( mActivity == AS_Eating )
   {
      short bite = 2;

      FoodItem *item = (FoodItem*)GetItemByType(Item::IT_Food);
      if(!item)
      {
         mActivity = AS_None;
         return;
      }

      cout << "Peep is eating, hunger: " << mHunger << endl;

      item->SetConsumed( item->GetConsumed()+bite );
      mHunger = (mHunger-bite);

      if(mHunger <= 0 || item->GetConsumed() >= item->GetSubstance() )
      {
         cout << "Peep is full" << endl;

         mActivity = AS_None;
         if(mHunger < 0)
         {
            mHunger = 0;
         }

         // Only remove food item if it's depleted.
         if(item->GetConsumed() >= item->GetSubstance())
         {
            RemoveItem(item); // Remove food item
            cout << "Peep finished his food" << endl;
         }
         else
         {
            cout << "Peep didn't finish his food" << endl;
         }
      }
   }

   if( mActivity == AS_Riding)
   {
     // TODO: Need to keep track of how long a peep has been in a riding state.
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

bool Person::AddItem(Item* item)
{
   unsigned int nItems = 0;

   std::list<Item *>::iterator i;
   for (i = mItems.begin (); i != mItems.end (); i++)
   {
      Item* itm = (*i);

      // Peep can only have one food item at a time.
      if(item->GetType() == Item::IT_Food)
      {
         if( item->GetType() == itm->GetType())
         {
            return false;
         }
      }

      // Peep can only have one dirnk item at a time.
      if(item->GetType() == Item::IT_Drink)
      {
         if( item->GetType() == itm->GetType())
         {
            return false;
         }
      }

      // Peep can only have 3 souvenir items at a time.
      if(item->GetType() == Item::IT_Souvenir)
      {
         if( item->GetType() == itm->GetType())
         {
            nItems++;
            if(nItems == 3) {
               return false;
            }
         }
      }

      // Peep can only have 2 information items at a time.
      if(item->GetType() == Item::IT_Information)
      {
         if( item->GetType() == itm->GetType())
         {
            nItems++;
            if(nItems == 2) {
               return false;
            }
         }
      }
   }

   mItems.push_back(item);
}
void Person::RemoveItem(Item* item)
{
   mItems.remove(item);
}

Item* Person::GetItemByType(Item::ItemType type)
{
   std::list<Item *>::iterator i;
   for (i = mItems.begin (); i != mItems.end (); i++)
   {
      Item* item = (*i);

      if(type == item->GetType()) {
         return item;
      }
   }

   return NULL;
}

std::list<Item*> Person::GetItemList() const
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
