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

ButtonViewObject::ButtonViewObject( float x, float y, int ID, WindowDelegate& rParent)
:  ViewObject(Gfx::kTextUVs)
,  mParentPipe (rParent)
,  mEvents ("Button")
{
   m_ID = ID;
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
      mSelected = true;
      switch (code)
      {
      case sf::Key::Return:
         Select(false);
         mButtonState = BS_Selected;
         mpEvent->Dispatch(1);
         break;
      case sf::Key::Escape:
         Select(false);
         break;
      case sf::Key::Space:
         mButtonState = BS_Selected;
         mpEvent->Dispatch(1);
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

void ButtonViewObject::Draw(void)  // Use the compiled GL code to show it in the view
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
