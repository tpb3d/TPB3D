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

#ifndef _EVENT_H
#define _EVENT_H

#include "../Types/Vector2.h"
class DelegateBase;

enum HR_Events
{
   HR_MouseInScene = 0,       // Generic
   HR_ClickInScene,           // Left Click
   HR_MenuInScene,            // Right Click
   HR_SelectBuildCursor,      // From tools if BuildOption returns true, set cursor and/or status bar to show active tool.
   HR_SelectBuildOption,      // From tools, include Building, Elevater, Condo etc as option param
   HR_Settings,
   HR_MainMenu,
   HR_Tools,
   HR_FRCS,
   HR_TRCS,
   HR_OTRCS,
   HR_PlaceBuilding,
   HR_PlaceTrackRide,
   HR_PlaceFlatRide,
   HR_PlacePath,
   HR_PlaceTerrain,
   HR_PlaceRetail,
   HR_PlaceSecurity,
   HR_PlaceClinic,
   HR_PlaceWasteManagement,
   HR_PlaceElevator,
   HR_PlaceStairs,
   HR_PlacePathItem,
   HR_PlaceNone,
   HR_NewScene,
   HR_OpenScene,
   HR_SaveScene,
   HR_CloseScene,
   HR_Close
};

class Camera;

class EventBase
{
public:
   // HELP! The Resize() event can not actually be captured by some classes, since they
   // already define a Resize() member funtion. Maybe we should call prefix theese with
   // "On"? (So OnResize(), OnMouseDown(), etc).
   virtual bool OnResize (Vector2i viewSize) { return false; }
   virtual bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnKeyDown (sf::Key::Code Key) { return false; }
   virtual bool OnKeyUp (sf::Key::Code Key) { return false; }
   virtual bool OnMouseMove (Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnMouseWheel (int Delta) { return false; }
   virtual bool OnClose () { return false; }
   virtual bool OnToolHit (const HR_Events Event) {return false; }
   virtual bool OnOpen (const char* pPath) { return false; }
   virtual bool OnSave (const char* pPath) { return false; }
};

class EventArgs
{
public:
   bool bHandled;
public:
   // ctor
   EventArgs(void)
   {
      bHandled = false;
   }
   virtual ~EventArgs(void) {}
};


class FunctorBase
{
public:
   virtual ~FunctorBase() {};
   virtual int operator()(const EventArgs& args) = 0;
};

template <class T> class EventFunctor : public FunctorBase
{
   typedef int (T::*F)(const EventArgs&);
   T* mpParent;
   F mF;
public:
   EventFunctor(F f, T* obj)
   :  mF(f)
   {
      mpParent = obj;
   }
   virtual int operator()(const EventArgs& args)
   {
      return (mpParent->*mF)(args);
   }
};

class EventSubscriber
{
   FunctorBase* mpF;

public:
   EventSubscriber();
   ~EventSubscriber()
   {
      cleanup(); 
   }

   int operator()(const EventArgs& args) const
   {
      return (*mpF)(args);
   }

   void cleanup();

   template<typename T>
   EventSubscriber(int id, int (T::*function)(const EventArgs&), T* obj) :
   mpF(new EventFunctor<T>(function, obj))
   {}
};

class ViewEvent
{
public:
   enum EventTypes
   {
      None = 0,
      Click,
      Changed,
      RadioExclude,
      ParentClose
   };
protected:
   std::string mName;

   // Events container
   typedef std::multimap<int, EventSubscriber> EventMap;
   EventMap mEventSubs;

protected:
   // Copy constructor and assignment are not allowed for events
   ViewEvent(const ViewEvent& event) {}
   ViewEvent& operator=(const ViewEvent& other)  {return *this;}

public:
   ViewEvent(const char* name)
   {
      mName = name;
   }
   virtual ~ViewEvent() {};

   const std::string& get_Name(void) const
   {
      return mName;
   }
   void set_Name(const char* szName)
   {
      mName = szName;
   }

   void Subscribe(EventTypes type, const EventSubscriber& ev);
   virtual int operator()(EventTypes t, EventArgs& args)
   {
      size_t iT = mEventSubs.count (t);
      if( iT > 0 )
      {
         EventMap::iterator ies = mEventSubs.find(t);
         EventSubscriber& es = ies->second;
         return es(args);
      }
      return 0;
   };

private:
   void unsubscribe(const EventBase& ev);
};

// Mutual Exclusive group like radio buttons
class GroupViewEvent : public ViewEvent
{
public:
   GroupViewEvent(const char* name)
   :  ViewEvent(name)
   {
   }
   virtual int operator()(EventTypes t, EventArgs& args)
   {
      int iResult = 0;
      for (EventMap::iterator ies = mEventSubs.begin(); ies != mEventSubs.end(); ies++)
      {
         EventSubscriber& es = ies->second;
         iResult = es(args);
      }
      return iResult;
   };
};

class EventHandler
{
private:
   typedef std::vector<EventBase*> ConType;
   ConType mHandlers;
   Camera* Cam;
   const sf::Input* mpInput;

public:
   EventHandler ();
   void Add (EventBase* Handler);
   bool HandleEvents (const sf::Event& Event);
   bool HandleEvents (const HR_Events& ev );
};

#endif // _EVENT_H
