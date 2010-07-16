#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class GUIDelegate;

class TextViewObject : public ViewObject
{
   enum TextState
   {
      TS_Normal = 0, // up and not highlighted
      TS_Selected,       // lit and down
      TS_Highlighted // just lit
   };
   std::string mStrContent;
   int m_ID;
   AnimationSingle* mpFace;
   AnimationSingle* mpTextTex;
   TextState      m_TextState;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   GUIDelegate* mpEvent;
   GUIDelegate& mParentPipe;
   int    mPosition;
   // TODO: add style!

   // GL Identities
protected:
   char mColorNormal[4];
   char mColorHighlit[4];

public:
   TextViewObject(float x, float y, int ID, GUIDelegate& rParent);
   ~TextViewObject(void);
public:
   // properties
   void set_State( TextState bs ) { m_TextState = bs; }

   // methods
public:
   void Clear();   // return this button to normal
   int  TestHit (Vector2i& point); // just render geometry for selection

   void set_EventHandler (GUIDelegate* pEvent) { mpEvent = pEvent; }
   void set_Text (const char* pszText);
      
   void Select (bool bState);
   void Hightlight (bool bState);
   void Enable (bool bEnable);
   void Visible (bool bVisible);

   void Hit (int c);
   void Hit (bool b);
   void DeleteChar (int BackOrDel);
   void AppendText (int c);
   void MoveCursor (int code);

   void Update (TextState state);
   void Draw ();
};
