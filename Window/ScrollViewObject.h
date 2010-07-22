#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"
#include "../Hub/Event.h"

class SerializerBase;

class ScrollViewObject : public ViewObject
{
   enum ScrollState
   {
      SO_Normal = 0, // up and not highlighted
      SO_Selected,       // lit and down
      SO_Highlighted // just lit
   };
   enum ScrollOrientation
   {
      SO_Vertical,
      SO_Horizontal
   };
   ViewEvent      mEvents;
   //Vector2i       mSize;
   int m_ID;
   int mPosition;
   int mMaxPosition;
   SimpleMesh*    mpSlotFace;
   SimpleMesh*    mpSlider;
   ScrollState    mScrollState;
   ScrollOrientation mOrientation;

   char mEnabled; // Enabled, Disabled
   char mVisible; // Visible, Invisible
   char mSelected; // hit
   char mHighlit; // mouse presence
   ViewObject& mParentPipe;

public:
   ScrollViewObject( float x, float y, int ID, ViewObject& rParent);
   ~ScrollViewObject(void);

public:
   // properties
   void set_State( ScrollState cs ) { mScrollState = cs; }
   void set_Text (const char* pszText);
   void set_Position (int pos);
   void set_Max (int max);
   void set_Orientation (ScrollOrientation orient) { mOrientation = orient; }

   // methods
public:
   GUIDelegate* subscribeEvent(const char* name, EventSubscriber* subscriber);

   void Clear();   // return this Scroll to normal

   void SubscribeEvent(ViewEvent::EventTypes id, EventSubscriber* subscriber);
      
   void Select (bool bState);
   void Hightlight (bool bState);
   void Enable (bool bEnable);
   void Visible (bool bVisible);

   void Hit (int c);
   void Hit (bool b);
   void MoveCursor (int code);
   void Resize (int iWidth, int iHeight);
   void Move (int iX, int iY, int iZ);
   virtual int  TestHit (Vector2i& point);
   void Update (ScrollState state);
   void Draw ();

   // support for xml
   void Load(SerializerBase& ser);
   void Save(SerializerBase& ser);
};

