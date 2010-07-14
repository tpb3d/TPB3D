#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"
#include "../Hub/Event.h"

class WindowDelegate;

class CheckViewObject : public ViewObject
{
public:
   enum CheckState
   {
      CS_Normal = 0, // up and not highlighted
      CS_Selected,       // lit and down
      CS_Highlighted, // just lit
      CS_Checked
   };
protected:
   ViewEvent mEvents;
   std::string mStrContent;
   int m_ID;
   AnimationSingle* mpFace;
   AnimationSingle* mpTextTex;
   SimpleQuad     m_Geometry;
   CheckState      mCheckState;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   char mChecked;

//   WindowDelegate* mpEvent;
   ViewObject& mParent;
   int    mPosition;
   // TODO: add style!

   // GL Identities
protected:
   char mColorNormal[4];
   char mColorHighlit[4];

public:
   CheckViewObject(float x, float y, int ID, ViewObject& rParent);
   virtual ~CheckViewObject(void);
public:
   // properties
   void set_State( CheckState cs ) { mCheckState = cs; }
   bool isChecked() { return (mChecked != 0); }
   // methods
public:
   void InitGFX(float x, float y);
   void Clear();   // return this button to normal
   int TestHit (Vector2i point); // just render geometry for selection

//   void set_EventHandler (WindowDelegate* pEvent) { mpEvent = pEvent; }
   void set_Text (const char* pszText);
   void SubscribeEvent(ViewEvent::Types id, EventSubscriber* subscriber);
      
   void Select (bool bState);
   void Hightlight (bool bState);
   void Enable (bool bEnable);
   void Visible (bool bVisible);

   void Hit (int c);
   virtual void Hit (bool b);
   void DeleteChar (int BackOrDel);
   void AppendText (int c);
   void MoveCursor (int code);

   virtual void Update (CheckState state);
   virtual void Draw ();
};

typedef CheckViewObject CheckBox;