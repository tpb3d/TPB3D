#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Graphics/SimpleMesh.h"
#include "../Scene/Scene.h"
#include "../Delegates/KeyNavDelegate.h"
#include "WindowViewObject.h"
#include "../Storage/SerializerBase.h"

using namespace Gfx;

namespace Gfx
{
   const float kTextLights[3][4] =
   {
       0.85f, 0.85f, 0.85f, 0.88f,
       0.75f, 0.75f, 0.75f, 0.58f,
       0.75f, 0.75f, 0.75f, 0.38f
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
   const float kWindowRightUVs[16][2] = // Right Titlebar
   {
      { 0.52f, 0.76f },{ 0.56f, 0.76f },{ 0.70f, 0.76f },{ 0.74f, 0.76f },
      { 0.52f, 0.80f },{ 0.56f, 0.80f },{ 0.70f, 0.80f },{ 0.74f, 0.80f },
      { 0.52f, 0.94f },{ 0.56f, 0.94f },{ 0.70f, 0.94f },{ 0.74f, 0.94f },
      { 0.52f, 0.98f },{ 0.56f, 0.98f },{ 0.70f, 0.98f },{ 0.74f, 0.98f }
   };
   const float kCloseUVs[8] = // the red X
   {
      0.76f, 0.76f, 0.76f, 0.87f, 0.87f, 0.76f, 0.87f, 0.87f
   };
}

WindowViewObject::WindowViewObject( float x, float y, int ID, ViewObject* pParent)
:  ViewObject (Gfx::kTextUVs)
,  mpParent (pParent)
,  mEvents ("Window")
{
   m_ID = ID;
   Update (WS_Refresh);
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mpFace = new SimpleMesh (pTex);
   mpFace->SetSize(120, 200, 4);
   mpFace->SetLightingColor (kTextLights[0]);
   mpFace->SetUVs (kWindowRightUVs);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kTextTextUVs);
   mSize.x = 120.0f;
   mSize.y = 200.0f;
   mpWindowDelegate = new KeyNavDelegate(*mpWindowDelegate, "Window", this);
}

WindowViewObject::~WindowViewObject(void)
{
   ChildIterator itc;
   for (itc = mChildren.begin(); itc != mChildren.end(); itc++)
   {
      ViewObject *pC = *(itc);
      delete pC;
   }
   mChildren.clear();
}

void WindowViewObject::AddChild (ViewObject* pChild)
{
   if (pChild != NULL)
   {
      mChildren.push_back (pChild);
   }
}

void WindowViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
}

void WindowViewObject::Resize (int iWidth, int iHeight)
{
   mpFace->SetSize (iWidth, iHeight, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
}

void WindowViewObject::Move (int iX, int iY, int iZ)
{
   float fX = (float)iX;
   float fY = (float)iY;
   mPosition.x = fX;
   mPosition.y = fY;
   mPosition.z = (float)iZ;
   mpFace->set_Position (fX, fY, (float)iZ);
   mpTextTex->MoveTo (fX, fY, (float)iZ, 0);
   mPoints[0].x = fX;
   mPoints[0].y = fY;
   mPoints[1].x = fX + mSize.x;
   mPoints[1].y = fY + mSize.y;
}

void WindowViewObject::Update (WindowState state)
{
   mWindowState = state;
}

void WindowViewObject::Hit (bool bState)
{
   if (mEnabled && bState) mSelected = true;
}

void WindowViewObject::Hit (int code)
{
   if (mEnabled)
   {
      mSelected = true;
      switch (code)
      {
      case VK_RETURN:
         Select(false);
         mWindowState = WS_Selected;
         break;
      case VK_ESCAPE:
         Select(false);
         break;
      case VK_SPACE:
         mWindowState = WS_Selected;
         break;
      case VK_SHIFT:
      case VK_CONTROL:
      case VK_MENU:
         break;
      }
   }
}

int WindowViewObject::TestHit (Vector2i& point)
{
   int hit = 0;
   ChildIterator itc;
   for (itc = mChildren.begin(); itc != mChildren.end(); itc++)
   {
      ViewObject *pC = *(itc);
      hit = pC->TestHit (point);
   }
   return hit;
}


void WindowViewObject::Select (bool bState)
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

void WindowViewObject::Hightlight (bool bState)
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

void WindowViewObject::Enable (bool bEnable)
{
   mEnabled = (bEnable) ? 1 : 0;
}

void WindowViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void WindowViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   if (mVisible )
   {
   	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
      glTranslatef (mPosition.x, mPosition.y, mPosition.z);
      Render (mpFace);
      ChildIterator itc;
      for (itc = mChildren.begin(); itc != mChildren.end(); itc++)
      {
	      glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
         ViewObject *pC = *(itc);
         pC->Draw();
       	glPopMatrix();															// Pop Back
      }
    	glPopMatrix();															// Pop Back
   }
}

// Serialization
void WindowViewObject::Load(SerializerBase& ser)
{
   SerializerBase* pSer = ser.GetFirstChild ("WindowChildren");
   while (pSer != NULL)
   {
      int iW = pSer->GetInt ("Width");
      int iH = pSer->GetInt ("Height");
      this->mSize.x = (float)iW;
      this->mSize.y = (float)iH;
      this->mSize.z = 0;
   }
}

void WindowViewObject::Save(SerializerBase& ser)
{
   ser.Add("Window", this->mStrContent.c_str());
   SerializerBase* pSer = ser.Spawn("WindowChildren"); // create a locale serializer of the type used for Stall
   ChildIterator itc;
   for (itc = mChildren.begin(); itc != mChildren.end(); itc++)
   {
      ViewObject *pC = *(itc);
//      pC->Save(*pSer);
   }
   delete pSer;
}
