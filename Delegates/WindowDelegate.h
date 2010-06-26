#pragma once
#include "DelegateBase.h"

class Scene;

class WindowDelegate : public DelegateBase
{
public:
   WindowDelegate(const char* pszName, Scene* pScene);
   virtual ~WindowDelegate(void);
   virtual void Dispatch (int e) = 0;
};

