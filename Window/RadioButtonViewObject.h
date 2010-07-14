#pragma once
#include "CheckViewObject.h"

class WindowDelegate;
class SerializerBase;

class RadioButtonViewObject : public CheckViewObject
{
public:
   enum RadioState
   {
      RS_NotPressed,
      RS_Pressed
   };
protected:
   RadioState mState;
   GroupViewEvent& mGroupEvents;
   EventSubscriber mEventSub;
public:
   RadioButtonViewObject( float x, float y, int ID, ViewObject& rParent, GroupViewEvent& rEvents);
   ~RadioButtonViewObject(void);

   bool OnClear (const EventArgs& e);

   virtual void RadioButtonViewObject::Hit (bool bState);
   virtual void Update (RadioState state);
   virtual void Draw ();

   // support for xml
   virtual void Load(SerializerBase& ser);
   virtual void Save(SerializerBase& ser);
};
