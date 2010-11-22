#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/SimpleMesh.h"
#include "../Scene/Scene.h"
#include "../Delegates/GUIDelegate.h"
#include "CheckViewObject.h"

using namespace Gfx;

namespace Gfx
{
   const float kButtonLight[4] =
   {
       0.95f, 0.95f, 0.95f, 0.95f
   };
   const unsigned char kTextLights[3][4] =
   {
      { 195,195,195,128 },    // Mormal
      { 195,255,255,255 },    // Lit
      { 151,151,151,255 }     // Hit
   };
   const float kTextUVs[4][2] =
   {
      { 0, 0.25 },
      { 0, 0 },
      { 1, 0 },
      { 1, 0.25 }
   };
   const float kTextTextUVs[8] =
   {
      0.0f, 0.125f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 0.125f
   };
   const float kUncheckedUVs[16][2] =
   {
      { 0.75f, 0.99f },{ 0.77f, 0.99f },{ 0.85f, 0.99f },{ 0.87f, 0.99f },
      { 0.75f, 0.97f },{ 0.77f, 0.97f },{ 0.85f, 0.97f },{ 0.87f, 0.97f },
      { 0.75f, 0.89f },{ 0.77f, 0.89f },{ 0.85f, 0.89f },{ 0.87f, 0.89f },
      { 0.75f, 0.87f },{ 0.77f, 0.87f },{ 0.85f, 0.87f },{ 0.87f, 0.87f }
   };
   const float kCheckedUVs[16][2] =
   {
      { 0.875f, 0.76f },{ 0.895f, 0.76f },{ 0.975f, 0.76f },{ 0.995f, 0.76f }, // inverted for OpenGL
      { 0.875f, 0.78f },{ 0.895f, 0.78f },{ 0.975f, 0.78f },{ 0.995f, 0.78f },
      { 0.875f, 0.85f },{ 0.895f, 0.85f },{ 0.975f, 0.85f },{ 0.995f, 0.85f },
      { 0.875f, 0.87f },{ 0.895f, 0.87f },{ 0.975f, 0.87f },{ 0.995f, 0.87f }
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
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mpFace = new SimpleMesh (pTex);
   mpFace->set_Position(x, y, 0);
   mpFace->SetSize (12,12,3);
   mpFace->SetUVs (kUncheckedUVs);
   mpFace->SetLightingColor (kButtonLight);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kTextTextUVs);
   mpTextTex->SetPosition (x+32, y, 0);
   mpTextTex->SetLightingColor (kTextLights[0]);
   Move (int(x), int(y), 0);
}

void CheckViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
   mPosition = (int)mStrContent.size();
}

void CheckViewObject::SubscribeEvent(ViewEvent::EventTypes id, EventSubscriber* subscriber)
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
   case sf::Mouse::Left:
      Select((mSelected == 1) ? false : true);
      break;
   case sf::Key::Return:
      Select(false);
      break;
   case sf::Key::Escape:
      Select(false);
      break;
   case sf::Key::Space:
      Select(false);
      mCheckState = CS_Checked;
      break;
   case sf::Key::RShift:
   case sf::Key::LShift:
   case sf::Key::LControl:
   case sf::Key::RControl:
   case sf::Key::Menu:
      break;
   }
}

void CheckViewObject::Select (bool bState)
{
   if (mEnabled && bState)
   {
      mSelected = 1;
      mpFace->SetUVs (kCheckedUVs);
   }
   else
   {
      mSelected = 0;
      mpFace->SetUVs (kUncheckedUVs);
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

void CheckViewObject::Resize (int iWidth, int iHeight)
{
   mpFace->SetSize (iWidth-8, iHeight-8, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
   mPoints[1].x = mPoints[0].x + mSize.x;
   mPoints[1].y = mPoints[0].y + mSize.y;
}

void CheckViewObject::Move (int iX, int iY, int iZ)
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

int CheckViewObject::TestHit (Vector2i& point)
{
   if ((point.x >= mPoints[0].x && point.x <= mPoints[1].x)
      && (point.y >= mPoints[0].y && point.y <= mPoints[1].y))
      return this->m_ID;
   return 0;
}

void CheckViewObject::Update(CheckState cs)
{
   mCheckState = cs;
}

int  CheckViewObject::Dispatch (short code, Vector2i& point)
{
   Hit (code);
   EventArgs ea;
   return mEvents(ViewEvent::Changed, ea);
}


void CheckViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   if (mVisible )
   {
      Render (mpFace);
      RenderText (mpTextTex, mStrContent);
   }
}
