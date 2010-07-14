#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include "../Delegates/WindowDelegate.h"
#include "TextViewObject.h"

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

TextViewObject::TextViewObject( float x, float y, int ID, WindowDelegate& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
{
   m_ID = ID;
   m_TextState = TS_Normal;
   m_Geometry.mPoints[0] = Vector3f (x,y,0);
   m_Geometry.mPoints[1] = Vector3f (x+140,y,0);
   m_Geometry.mPoints[2] = Vector3f (x+140,y+24,0);
   m_Geometry.mPoints[3] = Vector3f (x,y+32,0);
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("buttons.png", GL_RGBA);
   mpFace = new AnimationSingle (pTex, 140, 24);
   mpFace->SetPosition(x, y, 0);
   mpFace->SetLightingColor (kTextLights[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kTextTextUVs);

}

TextViewObject::~TextViewObject(void)
{
}

void TextViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
   mPosition = (int)mStrContent.size();
}

void TextViewObject::Hit (bool bState)
{
   if (mEnabled && bState) mSelected = true;
}

void TextViewObject::Hit (int code)
{
   switch (code)
   {
   case sf::Key::Delete:
      DeleteChar(0);   // zero because we don't move the cursor
      break;
   case VK_BACK:
      DeleteChar(1);
      break;
   case VK_LEFT:
      MoveCursor(1);
      break;
   case VK_RIGHT:
      MoveCursor(2);
      break;
   case VK_END:
      MoveCursor(3);
      break;
   case VK_HOME:
      MoveCursor(0);
      break;
   case VK_RETURN:
      Select(false);
      break;
   case VK_ESCAPE:
      Select(false);
      break;
   case VK_CLEAR:
      set_Text ("");
      break;
   case VK_LSHIFT:
   case VK_RSHIFT:
   case VK_LCONTROL:
   case VK_RCONTROL:
   #ifdef VK_MENU
   case VK_MENU:
	#endif
      break;
   default:
      AppendText(code);
   }
}

void TextViewObject::MoveCursor (int code)
{
   switch (code)
   {
   case 0:
      mPosition = 0;
      break;
   case 1:
      if (mPosition > 0)
      {
         mPosition--;
      }
      break;
   case 2:
      if (mPosition < (int)mStrContent.size())
      {
         mPosition++;
      }
      break;
   default:
      mPosition = (int)mStrContent.size();
   }
}

void TextViewObject::DeleteChar (int BackOrDel)
{
   int iOff = (BackOrDel) ? 1 : 0;    // zero for backspace because we don't move the cursor
   int ia = mPosition-iOff;
   int ib = (int)mStrContent.size() - ia - 1;
   if ((mStrContent.size() - ib) > 0)
   {
      std::string sFrag;
      if (ib > 0)
      {
         sFrag = mStrContent.substr(mStrContent.size()-ib, mStrContent.size());
      }
      if( ia == 0)
      {
         mStrContent = sFrag;
      }
      else
      {
         if( ia > 0) mStrContent = mStrContent.substr(0,ia);
         mStrContent += sFrag;
      }
      mPosition -= iOff;
   }
}

void TextViewObject::AppendText (int c)
{
   if( mPosition > (int)mStrContent.size())
   {
       mPosition = (int)mStrContent.size();
   }
   if( mPosition == (int)mStrContent.size())
   {
       mStrContent+=c;
   }
   else
   {
      std::string sT1 = mStrContent.substr (0, mPosition);
      std::string sT2 = mStrContent.substr (mPosition,mStrContent.size()-mPosition);
      mStrContent = sT1;
      mStrContent += c;
      mStrContent += sT2;
   }
   mPosition++;
}

void TextViewObject::Select (bool bState)
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

void TextViewObject::Hightlight (bool bState)
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

void TextViewObject::Enable (bool bEnable)
{
   mEnabled = (bEnable) ? 1 : 0;
}

void TextViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void TextViewObject::Draw(void)  // Use the compiled GL code to show it in the view
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
