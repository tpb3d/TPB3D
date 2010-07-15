#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include "../Delegates/WindowDelegate.h"
#include "ButtonViewObject.h"
#include "../Storage/SerializerBase.h"

using namespace Gfx;

namespace Gfx
{
   const unsigned char kTextLights[3][4] =
   {
      { 195,195,195,128 },    // Mormal
      { 195,255,255,255 },    // Lit
      { 151,151,151,255 }     // Hit
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
}

ButtonViewObject::ButtonViewObject( float x, float y, int ID, ViewObject& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
,  mEvents ("Button")
{
   m_ID = ID;
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("buttons.png", GL_RGBA);
   mpFace = new AnimationSingle (pTex, 140, 24);
   mpFace->SetPosition(x, y, 0);
   mpFace->SetLightingColor (kTextLights[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetPosition (x+4, y+2, 0);
   mpTextTex->SetUVs (kTextTextUVs);
   mpTextTex->SetLightingColor (kTextLights[0]);
}

ButtonViewObject::~ButtonViewObject(void)
{
}

void ButtonViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
   mPosition = (int)mStrContent.size();
}

void ButtonViewObject::Hit (bool bState)
{
   if (mEnabled && bState) mSelected = true;
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
   mpFace->SetWidth ((float)iWidth);
   mpFace->SetHeight ((float)iHeight);
}

void ButtonViewObject::Move (int iX, int iY, int iZ)
{
   mpFace->MoveTo (iX, iY, iZ, 0);
   mpTextTex->MoveTo (iX, iY, iZ, 0);
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
