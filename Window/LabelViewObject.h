#pragma once
#include "../Graphics/ViewObject.h"
#include "../Graphics/Animation.h"

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
   AnimationSingle* mpFace;
   AnimationSingle* mpTextTex;
   SimpleQuad     m_Geometry;

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
   void InitGFX(float x, float y);
      
   void Hightlight (bool bState);
   void Visible (bool bVisible);

   virtual void Draw ();
};
