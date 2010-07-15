#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include "../Delegates/WindowDelegate.h"
#include "CheckViewObject.h"

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

CheckViewObject::CheckViewObject( float x, float y, int ID, ViewObject& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParent (rParent)
,  mEvents ("CheckBox")
{
   m_ID = ID;
   
   mCheckState = CS_Normal;
   InitGFX(x,y);
}

CheckViewObject::~CheckViewObject(void)
{
}

void CheckViewObject::InitGFX(float x, float y)
{
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("buttons.png", GL_RGBA);
   mpFace = new AnimationSingle (pTex, 24, 24);
   mpFace->SetPosition(x, y, 0);
   mpFace->SetLightingColor (kTextLights[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kTextTextUVs);
   mpTextTex->SetPosition (x+32, y, 0);
   mpTextTex->SetLightingColor (kTextLights[0]);
}

void CheckViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
   mPosition = (int)mStrContent.size();
}

void CheckViewObject::SubscribeEvent(ViewEvent::Types id, EventSubscriber* subscriber)
{
   mEvents.Subscribe (id, *subscriber);
}

void CheckViewObject::Hit (bool bState)
{
   if (mEnabled && bState)
   {
      mSelected = true;
      EventArgs ea;
      mEvents(ViewEvent::Changed, ea);
   }
}

void CheckViewObject::Hit (int code)
{
   switch (code)
   {
   case VK_RETURN:
      Select(false);
      break;
   case VK_ESCAPE:
      Select(false);
      break;
   case VK_SPACE:
      Select(false);
      mCheckState = CS_Checked;
      break;
   case VK_SHIFT:
   case VK_CONTROL:
   case VK_MENU:
      break;
   }
}

void CheckViewObject::Select (bool bState)
{
   if (mEnabled && bState)
   {
      mSelected = 1;
   }
   else
   {
      mSelected = 0;
   }
}

void CheckViewObject::Hightlight (bool bState)
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

void CheckViewObject::Enable (bool bEnable)
{
   mEnabled = (bEnable) ? 1 : 0;
}

void CheckViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void CheckViewObject::Update(CheckState cs)
{
   mCheckState = cs;
}

void CheckViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   Render (mpFace);
   RenderText (mpTextTex, mStrContent);
}
