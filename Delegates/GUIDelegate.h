#pragma once
#include "../Graphics/ViewObject.h"
#include "EventDelegate.h"

enum ResultCode
{
   ResultCanel,
   ResultOK,
   ResultIdle,
   ResultDestroy  // Object is not longer needed, dispose of it
};

class GUIDelegate : public EventDelegate
{
protected:
   Gfx::ViewObject* mpParent;
public:
   GUIDelegate(const char* pszName, Gfx::ViewObject* pParent);
   virtual ~GUIDelegate(void);
   virtual void Dispatch (int e) = 0;
   virtual void OnMouseDown(short ID, Vector2i pointa) = 0;
   virtual void OnMouseUp(short ID, Vector2i pointa) = 0;
   virtual void OnKeyDown (short ID) = 0;
   virtual void OnKeyUp (short ID) = 0;
};

