#pragma once
#include "../Types/Vector2.h"
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

class SimpleMesh;

class LabelViewObject : public ViewObject
{
public:
   enum LabelState
   {
      CS_Normal = 0, // up and not highlighted
      CS_Highlighted // just lit as in a mouseover
   };
protected:
   std::string mStrContent;
   int m_ID;
   SimpleMesh* mpFace;
   AnimationSingle* mpTextTex;

   char mVisible; // Visible, Invisible
   char mHighlit; // mouse presence

   ViewObject& mParent;
   // TODO: add style!

   // GL Identities
protected:
   char mColorNormal[4];
   char mColorHighlit[4];

public:
   LabelViewObject(float x, float y, int ID, ViewObject& rParent);
   virtual ~LabelViewObject(void);
public:
   // properties
   void set_Text (const char* pszText);
   // methods
public:
   void Resize (int iWidth, int iHeight);
   void Move (int iX, int iY, int iZ);
   void InitGFX(float x, float y);
      
   void Hightlight (bool bState);
   void Visible (bool bVisible);

   virtual int  TestHit (Vector2i& point) { return 0; }
   virtual void Draw ();
};
