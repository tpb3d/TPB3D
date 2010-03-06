// TexturedStrip.h: interface for the CTexturedStrip class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
namespace GFX
{
   class Texture;
}

class TexturedStrip : public ObjectBase
{
protected:
   Gfx::Texture* mpTexture;

   virtual ObjectBase* Clone( )
   {
      throw( "No cloning TexturedStrip" );
      return 0;
   }

public:
   TexturedStrip( int Count, Gfx::Texture* pTex, int Color );
	virtual ~TexturedStrip();

   void Draw();
   void DrawSelectionTarget();
   void Render();
   void AddPointPair( CVPoint& pt1, CVPoint& pt2 );

};

