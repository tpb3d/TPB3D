#pragma once
#include "../Graphics/ViewObject.h"
#include "GUIDelegate.h"

class CMainFrame;

class KeyNavDelegate : public GUIDelegate
{
protected:

public:
   KeyNavDelegate(const char* pszName, Gfx::ViewObject* pParent);
   ~KeyNavDelegate(void);

   virtual void OnKeyDown (short ID) {};
   virtual void OnKeyUp (short ID) {};
   virtual void OnMouseDown(short ID, Vector2i pointa);
   virtual void OnMouseUp(short ID, Vector2i pointa);
   void Dispatch (int e);
};

