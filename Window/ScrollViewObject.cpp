#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Graphics/SimpleMesh.h"
#include "../Scene/Scene.h"
#include "../Delegates/GUIDelegate.h"
#include "ScrollViewObject.h"
#include "../Storage/SerializerBase.h"

using namespace Gfx;

namespace Gfx
{
   const float kTextLights[4] =
   {
       0.95f, 0.95f, 0.95f, 0.95f
   };
   const float kTextUVs[4][2] =
   {
      { 0, 0 },
      { 0, 0.25 },
      { 1, 0.25 },
      { 1, 0 }
   };
   const float kTextTextUVs[8] =
   {
      0.0f, 0.0f,  0.0f, 0.125f,  1.0f, 0.125f,  1.0f, 0.0f
   };
   const float kScrollUVs[16][2] =
   {
      { 0.02f, 0.76f },{ 0.06f, 0.76f },{ 0.20f, 0.76f },{ 0.24f, 0.76f },
      { 0.02f, 0.80f },{ 0.06f, 0.80f },{ 0.20f, 0.80f },{ 0.24f, 0.80f },
      { 0.02f, 0.94f },{ 0.06f, 0.94f },{ 0.20f, 0.94f },{ 0.24f, 0.94f },
      { 0.02f, 0.98f },{ 0.06f, 0.98f },{ 0.20f, 0.98f },{ 0.24f, 0.98f }
   };

   const float kScrollUnlitUVs[16][2] =
   {
      { 0.76f, 0.87f },{ 0.78f, 0.87f },{ 0.85f, 0.87f },{ 0.87f, 0.87f },
      { 0.76f, 0.89f },{ 0.78f, 0.89f },{ 0.85f, 0.89f },{ 0.87f, 0.89f },
      { 0.76f, 0.97f },{ 0.78f, 0.97f },{ 0.85f, 0.97f },{ 0.87f, 0.97f },
      { 0.76f, 0.99f },{ 0.78f, 0.99f },{ 0.85f, 0.99f },{ 0.87f, 0.99f }
   };
   const float kScrollLitUVs[16][2] =
   {
      { 0.875f, 0.87f },{ 0.895f, 0.87f },{ 0.975f, 0.87f },{ 0.995f, 0.87f },
      { 0.875f, 0.89f },{ 0.895f, 0.89f },{ 0.975f, 0.89f },{ 0.995f, 0.89f },
      { 0.875f, 0.97f },{ 0.895f, 0.97f },{ 0.975f, 0.97f },{ 0.995f, 0.97f },
      { 0.875f, 0.99f },{ 0.895f, 0.99f },{ 0.975f, 0.99f },{ 0.995f, 0.99f }
   };
}

ScrollViewObject::ScrollViewObject( float x, float y, int ID, ViewObject& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
,  mEvents ("Scroll")
{
   m_ID = ID;
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mSize.x = 12;
   mSize.y = 48;

   // the slot
   mpSlotFace = new SimpleMesh (pTex);
   mpSlotFace->set_Position (x,y,0);
   mpSlotFace->SetSize (mSize.x, mSize.y, 2.0);
   mpSlotFace->SetUVs (kScrollUVs);
   mpSlotFace->SetLightingColor (kTextLights);
   // the slider
   mpSlider = new SimpleMesh (pTex);
   mpSlider->set_Position (x+2, y+2, 0);
   mpSlider->SetSize (9,9,3);
   mpSlider->SetUVs (kScrollLitUVs);
   mpSlider->SetLightingColor (kTextLights);

   mOrientation = SO_Vertical;
   mPosition = 0;
   mMaxPosition = 10;
}

ScrollViewObject::~ScrollViewObject(void)
{
}

void ScrollViewObject::set_Position (int pos)
{
   if (pos >=0 && pos <= mMaxPosition)
      mPosition = pos;

   if (mOrientation == SO_Vertical)
   {
      float fy = mSize.y / mMaxPosition;
      mpSlider->set_Position(1,1+fy, 0);
   }
}

void ScrollViewObject::set_Max (int max)
{
   mMaxPosition = max;
}

void ScrollViewObject::Hit (bool bState)
{
   if (mEnabled && bState)
      Select (true);
}

void ScrollViewObject::Hit (int code)
{
   if (mEnabled)
   {
      bool bMoved;
      float fy = mSize.y / mMaxPosition;
      mSelected = true;
      switch (code)
      {
      case sf::Key::Up:
         Select(false);
         set_Position (int(mPosition - fy));   // won't underrun since we check in the set
         bMoved = true;
         break;
      case sf::Key::Down:
         Select(false);
         set_Position (int(mPosition + fy));
         bMoved = true;
         break;
      case sf::Key::Escape:
         Select(false);
         break;
      case sf::Key::Space:
         Select(false);
         break;
      }
      if (bMoved)
      {
         EventArgs ea;
         mEvents(ViewEvent::Changed, ea);
      }
   }
}

void ScrollViewObject::Select (bool bState)
{
   if (mEnabled && bState)
   {
      mSelected = 1;
      EventArgs ea;
      mEvents(ViewEvent::Changed, ea);
   }
   else
   {
      mSelected = 0;
   }
}

void ScrollViewObject::Hightlight (bool bState)
{
   if (mEnabled && bState)
   {
      mHighlit = 1;
   }
   else
   {
      mHighlit = 0;
   }
}

void ScrollViewObject::Enable (bool bEnable)
{
   mEnabled = (bEnable) ? 1 : 0;
}

void ScrollViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void ScrollViewObject::SubscribeEvent(ViewEvent::EventTypes id, EventSubscriber* subscriber)
{
   mEvents.Subscribe (id, *subscriber);
}

void ScrollViewObject::Resize (int iWidth, int iHeight)
{
   mpSlotFace->SetSize (iWidth-8, iHeight-8, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
}

void ScrollViewObject::Move (int iX, int iY, int iZ)
{
   float fX = (float)iX;
   float fY = (float)iY;
   mpSlotFace->set_Position (fX, fY, (float)iZ);
   mPoints[0].x = fX;
   mPoints[0].y = fY;
   mPoints[1].x = fX + mSize.x;
   mPoints[1].y = fY + mSize.y;
}

int ScrollViewObject::TestHit (Vector2i& point)
{
   if ((point.x > mPoints[0].x && point.x < mPoints[1].x)
      && (point.y > mPoints[0].y && point.y < mPoints[1].y))
      return this->m_ID;
   return 0;
}

void ScrollViewObject::Update (ScrollState state)
{
   mScrollState = state;
}

void ScrollViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   Render (mpSlotFace);
   Render (mpSlider);
}

// Serialization
void ScrollViewObject::Load(SerializerBase& ser)
{
   int iW = ser.GetInt ("Width");
   int iH = ser.GetInt ("Height");
   this->mSize.x = (float)iW;
   this->mSize.y = (float)iH;
//   this->mSize.z = 0;
}

void ScrollViewObject::Save(SerializerBase& ser)
{
   ser.Add("Width", mSize.x);
   ser.Add("Height", mSize.y);
}
