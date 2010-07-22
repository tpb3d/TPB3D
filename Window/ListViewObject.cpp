#include <string>

#include <SFML/System.hpp>
#include "../Graphics/Image.h"
#include "../Graphics/SimpleMesh.h"
#include "../Delegates/GUIDelegate.h"
#include "ListViewObject.h"

using namespace Gfx;

namespace Gfx
{
   const float kListLights[3][4] =
   {
      { 0.95f, 0.95f, 0.95f, 0.95f },
      { 0.45f, 0.55f, 0.95f, 0.95f },
      { 0.85f, 0.85f, 0.25f, 0.95f }
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
   const float kListBackUVs[16][2] =
   {
      { 0.02f, 0.76f },{ 0.06f, 0.76f },{ 0.20f, 0.76f },{ 0.24f, 0.76f },
      { 0.02f, 0.80f },{ 0.06f, 0.80f },{ 0.20f, 0.80f },{ 0.24f, 0.80f },
      { 0.02f, 0.94f },{ 0.06f, 0.94f },{ 0.20f, 0.94f },{ 0.24f, 0.94f },
      { 0.02f, 0.98f },{ 0.06f, 0.98f },{ 0.20f, 0.98f },{ 0.24f, 0.98f }
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
   Texture* pTex = images->GetTexture ("Nav3D.png", GL_RGBA);
   mpFace = new SimpleMesh (pTex);
   mpFace->set_Position(0, 0, 0);
   mpFace->SetSize( 120, 120, 4 );
   mpFace->SetUVs (kListBackUVs);
   mpFace->SetLightingColor (kListBackUVs[0]);
   pTex = images->GetTexture ("stats.png", GL_RGBA);
   mpTextTex = new AnimationSingle (pTex, 256, 22);
   mpTextTex->SetPosition (0, 0, 0);
   mpTextTex->SetUVs (kList2UVs);
   mpTextTex->SetLightingColor (kListLights[0]);
   Move (int(x), int(y), 0);

}

void ListViewObject::AddText (const char* pszText)
{
   mListContent.push_back (new string(pszText));
}

void ListViewObject::SubscribeEvent(ViewEvent::EventTypes id, EventSubscriber* subscriber)
{
   mEvents.Subscribe (id, *subscriber);
}

void ListViewObject::Resize (int iWidth, int iHeight)
{
   mpFace->SetSize (iWidth-8, iHeight-8, 4);
   mSize.x = (float)iWidth;
   mSize.y = (float)iHeight;
   mPoints[1].x = mPoints[0].x + mSize.x;
   mPoints[1].y = mPoints[0].y + mSize.y;
}

void ListViewObject::Move (int iX, int iY, int iZ)
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
   	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
      glTranslatef (mPoints[0].x, mPoints[0].y, mPoints[0].z);
      Render (mpFace);
      std::vector<string*>::iterator its;
      float fya = 14;
      for (its = mListContent.begin(); its != mListContent.end(); its++)
      {
         string &strContent = *(*its);
         RenderText (mpTextTex, 14, fya, strContent);
         fya+=15;
      }
   	glPopMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   }
}
