#pragma once
#include "../Graphics/ViewObject.h"
#include "GUIDelegate.h"

class CMainFrame;

class KeyNavDelegate : public GUIDelegate
{
protected:
   GUIDelegate& mrMain;

public:
   KeyNavDelegate(GUIDelegate& rMain, const char* pszName, Gfx::ViewObject* pParent);
   ~KeyNavDelegate(void);

   virtual void OnKeyDown (short ID) {};
   virtual void OnKeyUp (short ID) {};
   virtual void OnMouseDown(short ID) {}
   virtual void OnMouseUp(short ID) {}
   void Dispatch (int e);
};

