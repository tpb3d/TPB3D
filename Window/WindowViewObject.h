#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"
#include "../Hub/Event.h"

class GUIDelegate;
class SerializerBase;

class WindowViewObject : public ViewObject
{
   enum WindowState
   {
      WS_Refresh = 0,   // nothing changes in state but the graphics updated.
      WS_Normal, // up and not highlighted
      WS_Selected,       // lit and active
      WS_Highlighted // just lit
   };
   std::string mStrContent;
   std::vector<ViewObject*> mChildren;
   Vector3f mPosition;
   Vector3f mSize;         // Size vector of the client rectangle.
   int m_ID;
   SimpleMesh*    mpFace;
   AnimationSingle* mpTextTex;
   GUIDelegate*   mpWindowDelegate;
   WindowState    mWindowState;
   ViewObject*    mpParent;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   ViewEvent mEvents;

public:
   typedef std::vector<ViewObject*>::iterator ChildIterator;

public:
   WindowViewObject( float x, float y, int ID, ViewObject* rParent );
   ~WindowViewObject(void);

public:
   // properties
   void set_State( WindowState cs ) { mWindowState = cs; }
   GUIDelegate* get_Delegate () { return mpWindowDelegate; }

   // methods
public:
   void Clear();   // return this Window to normal

   void set_Text (const char* pszText);
   void SubscribeEvent(ViewEvent::Types id, EventSubscriber* subscriber);

   void AddChild (ViewObject* pChild);

   void Resize (int iWidth, int iHeight);
   void Move (int iX, int iY, int iZ);
      
   void Select (bool bState);
   void Hightlight (bool bState);
   void Enable (bool bEnable);
   void Visible (bool bVisible);

   void Hit (int c);
   void Hit (bool b);
   void DeleteChar (int BackOrDel);
   void AppendText (int c);
   void MoveCursor (int code);

   int  TestHit (Vector2i& point);
   void Update (WindowState state);
   void Draw ();

   // support for xml
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
