#pragma once
#include "Texture.h"

class Material
{
protected:
   Gfx::Texture* mpTexture;
   long  mTag;
   float mAmbiance[3];
   float mDiffused[3];
   float mSpecular[3];
   int   mShading; // int
   int   mTwoSided; // int
   int   mColorMode;
   float mBlur; // float
   float mEmittion; // float
   float mShineStrength; // float
   float mShininess; // float
   float mTransparency; // float

public:

   Material() {};
   Material( int shade, int sides, float blur, float emit, float shine, float glossy, float trans );
   ~Material(void);

   void GLSetMaterial();
   void GLSetBlendMode();
   void GLSetDiffuse();
   //void SetLight( float ambi[3], float diff[3], float spec[3] );
   void SetLight( float* ambi, float* diff, float* spec );
   void SetTexture( Gfx::Texture* pTex ) { mpTexture = pTex; };
   Gfx::Texture* GetTexture( ) { return mpTexture; };
};

namespace Gfx
{
   class ImageManager;

   class MaterialsList
   {
      friend class ImageManager;
      int mCount;
      Material** mpMaterials;
   public:
      Material** GetMats() const { return mpMaterials; }
      MaterialsList (int count)
      {
         try
         {
            mpMaterials = new Material*[count];
            mCount = count;
         }
         catch (...)
         {
            // todo
         }
      }
      ~MaterialsList ()
      {
         try
         {
            delete [] mpMaterials;
         }
         catch (...)
         {
            // todo
         }
      }
   };
}
