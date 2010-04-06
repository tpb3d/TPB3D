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

// People that make the Park thrive, treat them well and you prosper.
// Annoy them and they will fight back
// Make them made and they take their money elsewhere.
#pragma once
#ifndef _PERSON_H
#define _PERSON_H

#include <map>
#include <list>

#include "../Graphics/ModelObject.h"
#include "../CoreObjects/Park.h"
#include "../Types/Vector3.h"

class AnimationSingle;

// temporary home for some structures
// If Location is a destination and mBuilding <=0 then this person is leaving.
// If Location is a currentLocation and mBuilding = 0 then this person is outside
// Above subject to change.




// Temporary Base class for item
class Item
{
    public:
        enum ItemType{
            IT_Food = 0,
            IT_Drink,
            IT_Souvenir,
            IT_Information
        };

    private:
        ItemType mType;
        unsigned int mCost; // Cost in cents, 100 = 1 US Dollar

    public:
        Item(const ItemType &type, const unsigned int &cost)
        {
            mType = type;
            mCost = cost;
        }
        ~Item() {}

        ItemType GetType() const { return mType; }
        void SetItemType(const ItemType &type) { mType = type; }

        unsigned int GetCost() const { return mCost; }
        void SetCost(const unsigned int &cost) { mCost = cost; }
};

class FoodItem : public Item
{
    private:
        unsigned int mSubstance; // The amount of hunger the food should shave off.
        short mConsumed;
    public:

        FoodItem(const unsigned int &substance, const unsigned int &cost) : Item(Item::IT_Food, cost)
        {
            mSubstance = substance;
        }
        ~FoodItem() {}

        unsigned int GetSubstance() const {return mSubstance;}

        void SetSubstance(const unsigned int &substance) { mSubstance = substance; }

        void SetConsumed(const float &consumed) { mConsumed = (short)consumed; }
        float GetConsumed() const { return mConsumed; }
};


struct Location
{
   short mRoute;   // changed from state to route meaning any path, elevator, stairs or other mode of traversal.
   short mBuilding;
   short mPathway;   // 0 = lobby
   short mX;       // 0 = outide the building
   Location ()
   {
      clear ();   // any time this structure is instantiated, clear the inner data
   }
   void clear()
   {
      mRoute = -1;
      mBuilding = 0;
      mPathway = 0;
      mX = 490;
   }
};

struct Path // this could have been a list<T> but it would slow this high traffic structure
{
   short size;   // elements in play at this time
   short index;  // the current position of the person in the array.
   Location mPathList[8]; // the max is 4 or so transistions a person cares to make.
   Path()
   {
      clear();
   }
   void clear()
   {
      for (int idx = 0; idx < 8; ++idx )
      {
         mPathList[idx].clear();
      }
   }
};

class Person : public Gfx::ModelObject
{
public:
   enum Gender {
      Male = 0,
      Female
   };

   // enumerations
   enum Health_State
   {
      HS_Dead,          // remove from Park
      HS_Dire,          // outside services are needed
      HS_NeedMedical,   // a medical center will help
      HS_Ill,           // caught a cold, may miss work is not happy.
      HS_Weak,          // The peep is weak from hunger.
      HS_Well           // I think I'll go jogging today
   };

   enum Mood_State
   {
      MS_Furious,    // this soul is about to leave
      MS_Mad,        // not good, do something
      MS_Annoyed,    // why are the elevators soo slow?
      MS_Content,    // today was ok, no major bummers and the elevators where on time
      MS_Happy,      // it's great living/working here :)
      MS_Excited     // somebody got a raise.
   };

    // An activity state is set when the peep needs to do something.
   enum Activity_State
   {
      AS_None = 0, // When this is set we need to start looking for something the peep can be doing

      AS_LookingForFood,
      AS_LookingForDrink,
      AS_LookingForTrash, // Looking for a trash can
      AS_LookingForRest, // Looking for a place to rest, such as a bench
      AS_LookingForRide,
      AS_LookingForGift,
      AS_LookingForMap,
      AS_LookingForATM, // Peep needs money from an ATM
      AS_LookingForGroup,
      AS_LookingForRestroom,


      // These should probably be current states
      AS_UsingRestroom,

      AS_Riding,
      AS_Eating,  // The peep has food, we should probably look for a place to sit.
      AS_Drinking, // The peep has drink, we should probably look for a place to sit.
      AS_GoingHome, // Peep wants to go home, we need to head for the park gate.


      // Some of these should be removed
      AS_Sleeping,   // first four are done at home (mostly).
      AS_Relaxing,
      AS_Playing,
      AS_Reading,
      AS_GoingToWork,
      AS_Working,
      AS_ClockingOut,
      AS_Shopping,
      AS_BreakFast,
      AS_LunchBreak, // be sure the service personell take one
      AS_Dining,     // if you order take out, go home and eat it, was that dine in or eat out?
      AS_RestRoom,
      AS_OnVacation,  // we'll post pics in the lobby when we return
      AS_Evacuating,
      AS_WatchingMovie,
      AS_Socializing,
      AS_JobHunting,
      AS_ApartmentHunting,
      AS_CondoHunting,   // Income dependant.
      AS_HotelHunting
   };


    // Currently unsued
   enum Current_State   // had to add this to describe what a person is doing while heading to work, home or play.
   {
      // may also cover other activities. A Person.heading to work may also be stuck in an elevator queue.
      CS_Idle = 0,      // Idle is defined as doing nothing, or standing still.
      CS_Busy,          // Waiting for a timed event to trigger their next move. At work, sleeping etc.
      CS_Walking,       // Ok good, going somewhere
      CS_Riding,        // In a vehicle, elevator, train, car etc.
      CS_Disembarking,  // Car just dropped a person off;
      CS_Boarding,      // Car picking up person
      CS_Waiting,       // In queue
      CS_Sitting        // Sitting on a bench, either resting or eating.
   };

private:
   Location       mLocation;
   Path           mWorkPath;    // To and from work, stays permanant as long as working.
   // Changes if they change jobs or the business goes bust.
   Path           mOtherPath;   // To and from other activities when they go shopping etc.

protected:
   std::list <Item*> mItems;

   //unsigned char  NeedToRide;

   // Changes almost daily
   // these four are level triggered and increase over time
   short mHunger; // 0-200
   short mThirst; // 0-200
   short mRestroom;// 0-200

   unsigned short mWeight;   // Peep's weight in pounds
   unsigned short mAge;      // Peep's age in years
   unsigned short mHeight;   // Peep's height in inches.

   unsigned int mTime;
   unsigned int mInParkTime; // Time the peep has spent in the park

   float mCurTod;

   Gender         mGender;
   RideIntensity  mRidePreference;
   Health_State   mHealth;
   Mood_State     mMood;
   Activity_State mActivity;
   Current_State  mCurrentState;// Covers busy, waiting, walking, riding.
   int            mOccupation;  // school and retired are valid occupations
   std::map<Mood_State, AnimationSingle *> manimations;
   // not set on if this will be a class or enum

   unsigned int mHome;     // Where's the Crib
   unsigned int mWorkID;   // number of the Building or buisinee we work in
public:
    // CTOR/DTOR
   Person (Location& loc);    // x is their starting point, usually in the lobby.
   Person( const Vector3f &loc );
   virtual ~Person (void);


   void SetLocation( const Vector3f &loc);

   bool AddItem(Item* item);
   void RemoveItem(Item* item);

   Item* GetItemByType(Item::ItemType type);

   std::list<Item*> GetItemList() const;

   // Properties
   Mood_State GetMood() const;
   Health_State GetHealth() const;
   RideIntensity GetRidePreference() const;
   Gender GetGender() const;

   unsigned short GetWeight() const { return mWeight; }
   unsigned short GetHeight() const;
   unsigned short GetAge() const;
   short GetHunger() const;
   short GetThirst() const;

   unsigned int GetID() const;
   unsigned int GetInParkTime() const;


   void SetMood(const Mood_State &mood);
   void SetHealth(const Health_State &health);
   void SetHunger(const unsigned int &hunger);
   void SetThirst(const unsigned int &thirst);
   void SetID(const unsigned int &id);
   void SetInParkTime(const unsigned int &t);


   Path& get_WorkPath()    // this gets called to fill and route to and from work.
   {
      return mWorkPath;
   }
   Path& get_OtherPath()   // this gets called to fill, move the person and alternate checking paths.
   {
      return mOtherPath;
   }

   Activity_State GetActivity () // inline for faster access, same isolation, just quicker code.
   {
      return mActivity;
   }
   void SetActivity (Activity_State state )
   {
      mActivity = state;
   }
   Current_State GetCurrentState () // inline for faster access, same isolation, just quicker code.
   {
      return mCurrentState;
   }
   void SetCurrentState (Current_State state )
   {
      mCurrentState = state;
   }
   void SetOccupation( int occ )
   {
      mOccupation = occ;
   }
   int GetOccupation()
   {
      return mOccupation;
   }
   Location& get_Location()
   {
      return mLocation;
   }
   unsigned int GetWorkID()   // number of the Building or buisinee we work in
   {
      return mWorkID;
   }
   void SetWorkID (unsigned int id)
   {
      mWorkID = id;   // number of the Building or buisinee we work in
   }
   // Implementation methods
   virtual void Update (int tod);
   virtual void Draw ();
   virtual void Draw (float vx, float vy);
   virtual int  DrawSelectionTarget (int id) { return 0; }
   void    SetResidence (int Pathway);
   void    SetCurrent( int Pathway );


};

#endif //_PERSON_H
