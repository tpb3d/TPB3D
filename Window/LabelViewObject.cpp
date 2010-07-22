#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "../Graphics/SimpleMesh.h"
#include "LabelViewObject.h"

using namespace Gfx;

namespace Gfx
{
   const float kLabelLights[4] =
   {
       0.95f, 0.95f, 0.95f, 0.95f
   };
   const float kLabelUVs[4][2] =
   {
      { 0, 0.25 },
      { 0, 0 },
      { 1, 0 },
      { 1, 0.25 }
   };
   const float kLabel2UVs[8] =
   {
      0.0f, 0.125f,  0.0f, 0.0f,  1.0f, 0.0f,  1.0f, 0.125f
   };
   const float kLabelbackUVs[16][2] =
   {
      { 0.75f, 0.99f },{ 0.77f, 0.99f },{ 0.85f, 0.99f },{ 0.87f, 0.99f },
      { 0.75f, 0.97f },{ 0.77f, 0.97f },{ 0.85f, 0.97f },{ 0.87f, 0.97f },
      { 0.75f, 0.89f },{ 0.77f, 0.89f },{ 0.85f, 0.89f },{ 0.87f, 0.89f },
      { 0.75f, 0.87f },{ 0.77f, 0.87f },{ 0.85f, 0.87f },{ 0.87f, 0.87f }
   };
}

LabelViewObject::LabelViewObject( float x, float y, int ID, ViewObject& rParent)
:  ViewObject(Gfx::kLabelUVs)
,  mParent (rParent)
{
   m_ID = ID;
   
   InitGFX(x,y);
}

LabelViewObject::~LabelViewObject(void)
{
}

void LabelViewObject::InitGFX(float x, float y)
{
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mpFace = NULL;//new SimpleMesh (pTex);
   //mpFace->set_Position(x, y, 0);
   //mpFace->SetSize (12,12,3);
   //mpFace->SetUVs (kLabelbackUVs);
   //mpFace->SetLightingColor (kLabelLights);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kLabel2UVs);
   mpTextTex->SetPosition (x+32, y, 0);
   mpTextTex->SetLightingColor (kLabelLights);
   Move (int(x), int(y), 0);
   Resize (int(x), int(y));
}

void LabelViewObject::Resize (int iWidth, int iHeight)
{
   //mpFace->SetSize (iWidth-8, iHeight-8, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
   mPoints[1].x = mPoints[0].x + mSize.x;
   mPoints[1].y = mPoints[0].y + mSize.y;
}

void LabelViewObject::Move (int iX, int iY, int iZ)
{
   float fX = (float)iX;
   float fY = (float)iY;
   //mpFace->set_Position (fX, fY, (float)iZ);
   mpTextTex->MoveTo (fX+4, fY+4, (float)iZ, 0);
   mPoints[0].x = fX;
   mPoints[0].y = fY;
   mPoints[1].x = fX + mSize.x;
   mPoints[1].y = fY + mSize.y;
}

void LabelViewObject::set_Text (const char* pszText)
{
   mStrContent = pszText;
}


void LabelViewObject::Hightlight (bool bState)
{
   if (bState)
   {
      mHighlit = 1;
   }
   else
   {
      mHighlit = 0;
   }
}

void LabelViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void LabelViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   if (mVisible )
   {
      //Render (mpFace); not needed
      RenderText (mpTextTex, mStrContent);
   }
}
