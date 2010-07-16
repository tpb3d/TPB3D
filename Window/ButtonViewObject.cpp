#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Graphics/SimpleMesh.h"
#include "../Scene/Scene.h"
#include "../Delegates/GUIDelegate.h"
#include "ButtonViewObject.h"
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
   const float kButtonUVs[16][2] =
   {
      { 0.02f, 0.76f },{ 0.06f, 0.76f },{ 0.20f, 0.76f },{ 0.24f, 0.76f },
      { 0.02f, 0.80f },{ 0.06f, 0.80f },{ 0.20f, 0.80f },{ 0.24f, 0.80f },
      { 0.02f, 0.94f },{ 0.06f, 0.94f },{ 0.20f, 0.94f },{ 0.24f, 0.94f },
      { 0.02f, 0.98f },{ 0.06f, 0.98f },{ 0.20f, 0.98f },{ 0.24f, 0.98f }
   };
}

ButtonViewObject::ButtonViewObject( float x, float y, int ID, ViewObject& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
,  mEvents ("Button")
{
   m_ID = ID;
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mpFace = new SimpleMesh (pTex);
   mpFace->set_Position (x,y,0);
   mpFace->SetSize (24,24,4);
   mpFace->SetUVs (kButtonUVs);
   mpFace->SetLightingColor (kTextLights);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetPosition (x+4, y+2, 0);
   mpTextTex->SetUVs (kTextTextUVs);
   mpTextTex->SetLightingColor (kTextLights);
}

ButtonViewObject::~ButtonViewObject(void)
{
}

void ButtonViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
}

void ButtonViewObject::Hit (bool bState)
{
   if (mEnabled && bState)
      Select (true);
}

void ButtonViewObject::Hit (int code)
{
   if (mEnabled)
   {
      EventArgs ea;
      mSelected = true;
      switch (code)
      {
      case sf::Key::Return:
         Select(false);
         mButtonState = BS_Selected;
         mEvents(ViewEvent::Changed, ea);
         break;
      case sf::Key::Escape:
         Select(false);
         break;
      case sf::Key::Space:
         mButtonState = BS_Selected;
         mEvents(ViewEvent::Changed, ea);
         break;
//      case sf::Key::Shift:
//      case sf::Key::Control:
//      case sf::Key::Menu:
//         break;
      }
   }
}

void ButtonViewObject::Select (bool bState)
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

void ButtonViewObject::Hightlight (bool bState)
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

void ButtonViewObject::Enable (bool bEnable)
{
   mEnabled = (bEnable) ? 1 : 0;
}

void ButtonViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void ButtonViewObject::SubscribeEvent(ViewEvent::Types id, EventSubscriber* subscriber)
{
   mEvents.Subscribe (id, *subscriber);
}

void ButtonViewObject::Resize (int iWidth, int iHeight)
{
   mpFace->SetSize (iWidth-8, iHeight-8, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
}

void ButtonViewObject::Move (int iX, int iY, int iZ)
{
   float fX = (float)iX;
   float fY = (float)iY;
   mpFace->set_Position (fX, fY, (float)iZ);
   mpTextTex->MoveTo (fX, fY, (float)iZ, 0);
   mPoints[0].x = fX;
   mPoints[0].y = fY;
   mPoints[1].x = fX + mSize.x;
   mPoints[1].y = fY + mSize.y;
}

int ButtonViewObject::TestHit (Vector2i& point)
{
   if ((point.x > mPoints[0].x && point.x < mPoints[1].x)
      && (point.y > mPoints[0].y && point.y < mPoints[1].y))
      return this->m_ID;
   return 0;
}

void ButtonViewObject::Update (ButtonState state)
{
   mButtonState = state;
}

void ButtonViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   Render (mpFace);
   RenderText (mpTextTex, mStrContent);
}

// Serialization
void ButtonViewObject::Load(SerializerBase& ser)
{
   int iW = ser.GetInt ("Width");
   int iH = ser.GetInt ("Height");
//   this->mSize.x = (float)iW;
//   this->mSize.y = (float)iH;
//   this->mSize.z = 0;
}

void ButtonViewObject::Save(SerializerBase& ser)
{
   ser.Add("Button", this->mStrContent.c_str());
}
