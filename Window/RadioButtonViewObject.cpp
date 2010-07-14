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
   float fv = 1.0 / 16;
   if (mVisible )
   {
      // this needs to be in graphics
      glDisable (GL_TEXTURE_2D);
      glColor3ub (147,147,196);
      glBegin(GL_QUADS);
         glVertex3f (-6, 1, 20);
         glVertex3f (-2, 1, 20);
         glVertex3f (-2, -1, 20);
         glVertex3f (-6, -1, 20);
      glEnd();
      char c;
      glColor3ub (221, 221, 221);
      float fxa = 2.0f - (0.65f * this->mStrContent.size()) / 2;
      glEnable (GL_TEXTURE_2D);
      mpTextTex->BindTexture ();
      for( unsigned int idx = 0; idx < this->mStrContent.size(); ++idx)
      {
         c = mStrContent[idx];
         float fx = (float)(c%16);
         float fy = (float)(c/16);
         fx = 1.0f / fx;
         fy = 1.0f / fy;
         glBegin(GL_QUADS);
            glTexCoord2f (fx, fy); // simple extension arm
            glVertex3f (-6+fxa, 0.625f, 20);
            glTexCoord2f (fx+fv, fy); // simple extension arm
            glVertex3f (-5.4f+fxa, 0.625f, 20);
            glTexCoord2f (fx+fv, fy+fv); // simple extension arm
            glVertex3f (-5.4f+fxa, -0.625f, 20);
            glTexCoord2f (fx, fy+fv); // simple extension arm
            glVertex3f (-6+fxa, -0.625f, 20);
         glEnd();
         fxa+= 0.65f;
      }
   }
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
