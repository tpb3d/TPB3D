#pragma once
#include "WindowDelegate.h"

class CMainFrame;

class KeyNavDelegate : public WindowDelegate
{
protected:
   WindowDelegate& mrMain;

public:
   KeyNavDelegate(WindowDelegate& rMain, const char* pszName, Scene* pScene);
   ~KeyNavDelegate(void);

   virtual void OnHitDown (short ID) {};
   virtual void OnHitUp (short ID) {};
   void Dispatch (int e);
};

