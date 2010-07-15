#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include "../Delegates/WindowDelegate.h"
#include "RadioButtonViewObject.h"
#include "../Storage/SerializerBase.h"

RadioButtonViewObject::RadioButtonViewObject( float x, float y, int ID, ViewObject& rParent, GroupViewEvent& rEvents)
:  CheckViewObject(x, y, ID, rParent)
,  mGroupEvents(rEvents)
,  mState (RS_NotPressed)
,  mEventSub (1, &RadioButtonViewObject::OnClear, this)
{
   mEvents.set_Name ("RadioButton");
   mGroupEvents.Subscribe (GroupViewEvent::RadioExclude,  mEventSub);

   InitGFX(x,y);
}

RadioButtonViewObject::~RadioButtonViewObject(void)
{
}

//used by the group event to clear this control.
bool RadioButtonViewObject::OnClear (const EventArgs& e)
{
   mState = RS_NotPressed;
   return true;
}

void RadioButtonViewObject::Hit (bool bState)
{
   if (mEnabled && bState)
   {
      Update (RS_Pressed);
   }
}

void RadioButtonViewObject::Update(RadioState rs)
{
   EventArgs ea;
   mGroupEvents(GroupViewEvent::RadioExclude, ea);
   mState = rs;
}

void RadioButtonViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   Render (mpFace);
   RenderText (mpTextTex, mStrContent);
}

// Serialization
void RadioButtonViewObject::Load(SerializerBase& ser)
{
   int iW = ser.GetInt ("Width");
   int iH = ser.GetInt ("Height");
//   this->mSize.x = (float)iW;
//   this->mSize.y = (float)iH;
//   this->mSize.z = 0;
}

void RadioButtonViewObject::Save(SerializerBase& ser)
{
   ser.Add("RadioButton", this->mStrContent.c_str());
}
