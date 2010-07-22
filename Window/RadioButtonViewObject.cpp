#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/SimpleMesh.h"
#include "../Scene/Scene.h"
#include "../Delegates/GUIDelegate.h"
#include "RadioButtonViewObject.h"
#include "../Storage/SerializerBase.h"

namespace Gfx
{
   const float kUnpressedUVs[16][2] =
   {
      { 0.76f, 0.87f },{ 0.78f, 0.87f },{ 0.85f, 0.87f },{ 0.87f, 0.87f },
      { 0.76f, 0.89f },{ 0.78f, 0.89f },{ 0.85f, 0.89f },{ 0.87f, 0.89f },
      { 0.76f, 0.97f },{ 0.78f, 0.97f },{ 0.85f, 0.97f },{ 0.87f, 0.97f },
      { 0.76f, 0.99f },{ 0.78f, 0.99f },{ 0.85f, 0.99f },{ 0.87f, 0.99f }
   };
   const float kPressedUVs[16][2] =
   {
      { 0.875f, 0.87f },{ 0.895f, 0.87f },{ 0.975f, 0.87f },{ 0.995f, 0.87f },
      { 0.875f, 0.89f },{ 0.895f, 0.89f },{ 0.975f, 0.89f },{ 0.995f, 0.89f },
      { 0.875f, 0.97f },{ 0.895f, 0.97f },{ 0.975f, 0.97f },{ 0.995f, 0.97f },
      { 0.875f, 0.99f },{ 0.895f, 0.99f },{ 0.975f, 0.99f },{ 0.995f, 0.99f }
   };
}

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
int RadioButtonViewObject::OnClear (const EventArgs& e)
{
   Select (false);
   return true;
}

void RadioButtonViewObject::Hit (bool bState)
{
   if (mEnabled && bState)
   {
      Update (RS_Pressed);
   }
}

int  RadioButtonViewObject::Dispatch (short code, Vector2i& point)
{
   Hit (true);
   EventArgs ea;
   return mEvents(ViewEvent::Changed, ea);
}


void RadioButtonViewObject::Select (bool bState)
{
   if (mEnabled && bState)
   {
      mSelected = 1;
      mpFace->SetUVs (kPressedUVs);
   }
   else
   {
      mSelected = 0;
      mpFace->SetUVs (kUnpressedUVs);
   }
}


void RadioButtonViewObject::Update(RadioState rs)
{
   EventArgs ea;
   mGroupEvents(GroupViewEvent::RadioExclude, ea);
   Select (true);
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
