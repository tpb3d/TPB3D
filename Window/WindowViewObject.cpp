#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include "../Delegates/WindowDelegate.h"
#include "WindowViewObject.h"
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

WindowViewObject::WindowViewObject( float x, float y, int ID, WindowDelegate& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
{
   m_ID = ID;
   m_Geometry.mPoints[0] = Vector3f (x,y,0);
   m_Geometry.mPoints[1] = Vector3f (x+140,y,0);
   m_Geometry.mPoints[2] = Vector3f (x+140,y+24,0);
   m_Geometry.mPoints[3] = Vector3f (x,y+32,0);
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Windows.png", GL_RGBA);
   mpFace = new AnimationSingle (pTex, 140, 24);
   mpFace->SetPosition(x, y, 0);
   mpFace->SetLightingColor (kTextLights[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kTextTextUVs);

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

void WindowViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
   mPosition = (int)mStrContent.size();
}

void WindowViewObject::Resize (int iWidth, int iHeight)
{
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
}

void WindowViewObject::Move (int iX, int iY, int iZ)
{
   mOriginPoint.x = (float)iX;
   mOriginPoint.y = (float)iY;
   mOriginPoint.z = 0;  // don't use Z at this time
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
         mpEvent->Dispatch(1);
         break;
      case VK_ESCAPE:
         Select(false);
         break;
      case VK_SPACE:
         mWindowState = WS_Selected;
         mpEvent->Dispatch(1);
         break;
      case VK_SHIFT:
      case VK_CONTROL:
      case VK_MENU:
         break;
      }
   }
}

void WindowViewObject::Select (bool bState)
{
   if (mEnabled && bState)
   {
      mSelected = 1;
      if (mpEvent != NULL)
      {
         mpEvent->Dispatch (1);
      }
   }
   else
   {
      mParentPipe.Dispatch ('N');
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
   float fv = 1.0 / 16;
   if (mVisible )
   {
      // this needs to be in graphics
      glDisable (GL_TEXTURE_2D);
      glColor3ub (147,147,196);
      glBegin(GL_QUADS);
         glVertex3f (mOriginPoint.x, mOriginPoint.y, 20);
         glVertex3f (mOriginPoint.x+mSize.x, mOriginPoint.y, 20);
         glVertex3f (mOriginPoint.x+mSize.x, mOriginPoint.y+mSize.y, 20);
         glVertex3f (mOriginPoint.x, mOriginPoint.y+mSize.y, 20);
      glEnd();
      ChildIterator itc;
      for (itc = mChildren.begin(); itc != mChildren.end(); itc++)
      {
         ViewObject *pC = *(itc);
         //pC->Draw();
      }
   }
}

// Serialization
void WindowViewObject::Load(SerializerBase& ser)
{
   SerializerBase* pSer = ser.GetFirstChild ("Stalls");
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
   SerializerBase* pSer = ser.Spawn("Stalls"); // create a locale serializer of the type used for Stall
   ChildIterator itc;
   for (itc = mChildren.begin(); itc != mChildren.end(); itc++)
   {
      ViewObject *pC = *(itc);
//      pC->Save(*pSer);
   }
   delete pSer;
}
