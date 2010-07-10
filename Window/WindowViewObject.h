#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class WindowDelegate;
class SerializerBase;

class WindowViewObject : public ViewObject
{
   enum WindowState
   {
      WS_Normal = 0, // up and not highlighted
      WS_Selected,       // lit and active
      WS_Highlighted // just lit
   };
   std::string mStrContent;
   std::vector<ViewObject*> mChildren;
   Vector3f mOriginPoint;  // Window anchor point in the world scene
   Vector3f mSize;         // Size vector of the client rectangle.
   int m_ID;
   AnimationSingle* mpFace;
   AnimationSingle* mpTextTex;
   SimpleQuad     m_Geometry;
   WindowState    mWindowState;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   WindowDelegate* mpEvent;
   WindowDelegate& mParentPipe;
   int    mPosition;
public:
   typedef std::vector<ViewObject*>::iterator ChildIterator;

public:
   WindowViewObject( float x, float y, int ID, WindowDelegate& rParent);
   ~WindowViewObject(void);

public:
   // properties
   void set_State( WindowState cs ) { mWindowState = cs; }

   // methods
public:
   void Clear();   // return this Window to normal
   int TestHit (Vector2i point); // just render geometry for selection

   void set_EventHandler (WindowDelegate* pEvent) { mpEvent = pEvent; }
   void set_Text (const char* pszText);

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

   void Update (WindowState state);
   void Draw ();

   // support for xml
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};
