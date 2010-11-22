#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Graphics/SimpleMesh.h"
#include "../Scene/Scene.h"
#include "../Delegates/GUIDelegate.h"
#include "TextViewObject.h"

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
      0.0f, 0.125f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 0.125f
   };
}

TextViewObject::TextViewObject( float x, float y, int ID, GUIDelegate& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
{
   m_ID = ID;
   m_TextState = TS_Normal;
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mpFace = new SimpleMesh (pTex);
   mpFace->set_Position(x, y, 0);
   mpFace->SetLightingColor (kTextLights);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kTextTextUVs);
   Move (int(x), int(y), 0);
   Resize (int(x), int(y));
}

TextViewObject::~TextViewObject(void)
{
}

void TextViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
   mPosition = (int)mStrContent.size();
}

void TextViewObject::Resize (int iWidth, int iHeight)
{
   mpFace->SetSize (iWidth-8, iHeight-8, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
   mPoints[1].x = mPoints[0].x + mSize.x;
   mPoints[1].y = mPoints[0].y + mSize.y;
}

void TextViewObject::Move (int iX, int iY, int iZ)
{
   float fX = (float)iX;
   float fY = (float)iY;
   mpFace->set_Position (fX, fY, (float)iZ);
   mpTextTex->MoveTo (fX+4, fY+4, (float)iZ, 0);
   mPoints[0].x = fX;
   mPoints[0].y = fY;
   mPoints[1].x = fX + mSize.x;
   mPoints[1].y = fY + mSize.y;
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
   case sf::Key::Back:
      DeleteChar(1);
      break;
   case sf::Key::Left:
      MoveCursor(1);
      break;
   case sf::Key::Right:
      MoveCursor(2);
      break;
   case sf::Key::End:
      MoveCursor(3);
      break;
   case sf::Key::Home:
      MoveCursor(0);
      break;
   case sf::Key::Return:
      Select(false);
      break;
   case sf::Key::Escape:
      Select(false);
      break;

   case sf::Key::Numpad5: // numpad 5 without numlock is Linux for "VK_CLEAR"
   #ifdef  VK_CLEAR
   case VK_CLEAR:
   #endif
      set_Text ("");
      break;
   case sf::Key::LShift:
   case sf::Key::RShift:
   case sf::Key::LControl:
   case sf::Key::RControl:
   case sf::Key::Menu:
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

int TextViewObject::TestHit (Vector2i& point)
{
   if ((point.x > mPoints[0].x && point.x < mPoints[1].x)
      && (point.y > mPoints[0].y && point.y < mPoints[1].y))
      return this->m_ID;
   return 0;
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
