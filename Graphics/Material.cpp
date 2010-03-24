#include <cstring>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ObjectBase.h"
#include "Material.h"

Material::Material( int shade, int sides, float blur, float emit, float shine, float glossy, float trans )
{
   mTag = 0x89ABCDEF;
   mShading = shade;
   mTwoSided = sides;
   mBlur = blur;
   mEmittion = emit;
   mShineStrength = shine;
   mShininess = glossy;
   mTransparency = trans;
   mColorMode = GL_AMBIENT;
   mpTexture = NULL;
   if( mEmittion != 0 )
   {
      mColorMode = GL_EMISSION;
   }
   else
   {
      mColorMode = GL_AMBIENT_AND_DIFFUSE;
   }
}

Material::~Material(void)
{
#ifdef _DEBUG
   mColorMode = sizeof(Material);
#endif
}

void Material::SetLight( float ambi[3], float diff[3], float spec[3] )
{
   memcpy( mAmbiance, ambi, sizeof(mAmbiance));
   memcpy( mDiffused, diff, sizeof(mDiffused));
   memcpy( mSpecular, spec, sizeof(mSpecular));
   if( mAmbiance[0] || mAmbiance[1] || mAmbiance[2] )
   {
      if( mDiffused[0] || mDiffused[1] || mDiffused[2] )
      {
         mColorMode = GL_AMBIENT_AND_DIFFUSE;
      }
      else
      {
         mColorMode = GL_AMBIENT;
      }
   }
   else if( mDiffused[0] || mDiffused[1] || mDiffused[2] )
   {
      mColorMode = GL_DIFFUSE;
   }
   else if( mSpecular[0] || mSpecular[1] || mSpecular[2] )
   {
      mColorMode = GL_SPECULAR;
   }
};

void Material::GLSetMaterial()
{
//   glEnable( GL_COLOR_MATERIAL );
//   glShadeModel( mShading );
//   glMaterialf( GL_FRONT, GL_SHININESS, mShininess );
//   glMaterialf( GL_FRONT, GL_TRANSPARANCY, mTransparency );
//   glMaterialf( GL_FRONT, GL_EMISSION, mEmittion );
   GLSetBlendMode();
   glColor4f( mDiffused[0], mDiffused[1], mDiffused[2], 1.0 );
}

void Material::GLSetBlendMode()
{
   if( this->mShading == 64 )
   {
      glEnable( GL_BLEND );
//      glBlendFunc( GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
   }
}
