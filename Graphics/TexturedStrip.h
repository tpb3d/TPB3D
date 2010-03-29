// TexturedStrip.h: interface for the CTexturedStrip class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
namespace Gfx
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
   void AddPointPair( Vector3f& pt1, Vector3f& pt2 );

};

