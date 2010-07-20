#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/Camera.h"
#include "ListViewObject.h"

using namespace Gfx;

namespace Gfx
{
   const unsigned char kListLights[3][4] =
   {
      { 195,195,195,128 },    // Mormal
      { 195,255,255,255 },    // Lit
      { 151,151,151,255 }     // Hit
   };
   const float kListUVs[4][2] =
   {
      { 0, 0 },
      { 0, 0.25 },
      { 1, 0.25 },
      { 1, 0 }
   };
   const float kList2UVs[8] =
   {
      0.0f, 0.0f,  0.0f, 0.125f,  1.0f, 0.125f,  1.0f, 0.0f
   };
}

ListViewObject::ListViewObject( float x, float y, int ID, ViewObject& rParent)
:  ViewObject(Gfx::kListUVs)
,  mParent (rParent)
,  mEvents ("List")
{
   m_ID = ID;
   
   InitGFX(x,y);
}

ListViewObject::~ListViewObject(void)
{
}

void ListViewObject::InitGFX(float x, float y)
{
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("buttons.png", GL_RGBA);
   mpFace = new AnimationSingle (pTex, 140, 24);
   mpFace->SetPosition(x, y, 0);
   mpFace->SetLightingColor (kListLights[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetUVs (kList2UVs);

}

void ListViewObject::AddText (const char* pszText)
{
   mListContent.push_back (new string(pszText));
}

void ListViewObject::SubscribeEvent(ViewEvent::Types id, EventSubscriber* subscriber)
{
   mEvents.Subscribe (id, *subscriber);
}

void ListViewObject::Resize (int iWidth, int iHeight)
{
   mpFace->SetHeight ((float)iHeight);
   mpFace->SetWidth ((float)iWidth); 
}

void ListViewObject::Hightlight (bool bState)
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

void ListViewObject::Visible (bool bVisible)
{
   mVisible = (bVisible) ? 1 : 0;
}

void ListViewObject::Draw(void)  // Use the compiled GL code to show it in the view
{
   float fv = 1.0 / 16;
   if (mVisible )
   {
      Render (mpFace);
      std::vector<string*>::iterator its;
      float fya = 0.625f;
      for (its = mListContent.begin(); its != mListContent.end(); its++)
      {
         string &strContent = *(*its);
         RenderText (mpTextTex, strContent);
         fya+=0.5f;
      }
   }
}
