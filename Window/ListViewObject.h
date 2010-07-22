#pragma once
#include "../Types/Vector2.h"
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"
#include "../Hub/Event.h"

class SimpleMesh;

class ListViewObject : public ViewObject
{
public:
   enum ListState
   {
      CS_Normal = 0, // up and not highlighted
      CS_Highlighted // just lit as in a mouseover
   };
protected:
   ViewEvent      mEvents;
   std::vector<string*> mListContent;
   int m_ID;
   SimpleMesh* mpFace;
   AnimationSingle* mpTextTex;

   char mVisible; // Visible, Invisible
   char mHighlit; // mouse presence

   ViewObject& mParent;
   // TODO: add style!

   // GL Identities
protected:
   char mColorNormal[4];
   char mColorHighlit[4];

public:
   ListViewObject(float x, float y, int ID, ViewObject& rParent);
   virtual ~ListViewObject(void);
public:
   // properties
   void AddText (const char* pszText);
   // methods
public:
   void InitGFX(float x, float y);
   void SubscribeEvent(ViewEvent::EventTypes id, EventSubscriber* subscriber);
      
   void Hightlight (bool bState);
   void Visible (bool bVisible);
   void Resize (int x, int y);
   void Move (int iX, int iY, int iZ);

   virtual int  TestHit (Vector2i& point) { return 0; }
   virtual void Draw ();
};
