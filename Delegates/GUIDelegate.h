#pragma once
#include "../Graphics/ViewObject.h"
#include "EventDelegate.h"

class GUIDelegate : public EventDelegate
{
public:
   GUIDelegate(const char* pszName, Gfx::ViewObject* pParent);
   virtual ~GUIDelegate(void);
   virtual void Dispatch (int e) = 0;
   virtual void OnMouseDown(short ID) = 0;
   virtual void OnMouseUp(short ID) = 0;
   virtual void OnKeyDown (short ID) = 0;
   virtual void OnKeyUp (short ID) = 0;
};

