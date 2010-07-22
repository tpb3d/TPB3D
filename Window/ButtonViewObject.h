#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"
#include "../Hub/Event.h"

class SerializerBase;

class ButtonViewObject : public ViewObject
{
   enum ButtonState
   {
      BS_Normal = 0, // up and not highlighted
      BS_Selected,       // lit and down
      BS_Highlighted // just lit
   };
   ViewEvent      mEvents;
   std::string    mStrContent;
   int m_ID;
   SimpleMesh*    mpFace;
   AnimationSingle* mpTextTex;
   ButtonState    mButtonState;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   ViewObject& mParentPipe;

public:
   ButtonViewObject( float x, float y, int ID, ViewObject& rParent);
   ~ButtonViewObject(void);

public:
   // properties
   void set_State( ButtonState cs ) { mButtonState = cs; }

   // methods
public:
   GUIDelegate* subscribeEvent(const char* name, EventSubscriber* subscriber);

   void Clear();   // return this button to normal
   void set_Text (const char* pszText);
   void SubscribeEvent(ViewEvent::EventTypes id, EventSubscriber* subscriber);
      
   void Select (bool bState);
   void Hightlight (bool bState);
   void Enable (bool bEnable);
   void Visible (bool bVisible);

   int  Hit (int c);
   int  Hit (bool b);
   void DeleteChar (int BackOrDel);
   void AppendText (int c);
   void MoveCursor (int code);
   void Resize (int iWidth, int iHeight);
   void Move (int iX, int iY, int iZ);
   virtual int  TestHit (Vector2i& point);
   virtual int  Dispatch (short code, Vector2i& point);
   void Update (ButtonState state);
   void Draw ();

   // support for xml
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
