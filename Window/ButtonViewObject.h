#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class WindowDelegate;

class ButtonViewObject : public ViewObject
{
   enum ButtonState
   {
      BS_Normal = 0, // up and not highlighted
      BS_Selected,       // lit and down
      BS_Highlighted // just lit
   };
   std::string mStrContent;
   int m_ID;
   AnimationSingle* mpFace;
   AnimationSingle* mpTextTex;
   SimpleQuad     m_Geometry;
   ButtonState    mButtonState;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   WindowDelegate* mpEvent;
   WindowDelegate& mParentPipe;
   int    mPosition;
public:
   ButtonViewObject( float x, float y, int ID, WindowDelegate& rParent);
   ~ButtonViewObject(void);

public:
   // properties
   void set_State( ButtonState cs ) { mButtonState = cs; }

   // methods
public:
   void Clear();   // return this button to normal
   int TestHit (Vector2i point); // just render geometry for selection

   void set_EventHandler (WindowDelegate* pEvent) { mpEvent = pEvent; }
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

   void Update (ButtonState state);
   void Draw ();
};
