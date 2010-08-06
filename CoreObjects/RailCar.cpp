#include "RailCar.h"


RailCar::RailCar (const sf::Vector3f& vDim, int meshcount, int id )
:  Car (vDim, meshcount, id)
,  mSpline (Test::GetSpline())
{
   Start();
}

RailCar::~RailCar(void)
{
}

void RailCar::Start()
{
   mCurrentSpline = mSpline.begin();
}

void RailCar::Draw()
{
   mCurrentSpline++;
   if (mCurrentSpline == mSpline.end())
   {
      if (mCurrentSpline == mSpline.begin()) return;
      mCurrentSpline = mSpline.begin();
   }
   Spline* pSp = *mCurrentSpline;
	glPushMatrix();	// Push Matrix Onto Stack (Copy The Current Matrix)

      glTranslatef( pSp->mVPoint.x, pSp->mVPoint.y, pSp->mVPoint.z );				// Move Left 1.5 Units And Into The Screen 6.0
	   glRotatef(-pSp->mVAngle.y,0.0f,1.0f,0.0f);
	   glRotatef(-pSp->mVAngle.x,1.0f,0.0f,0.0f);
	   glRotatef(-pSp->mVAngle.z,0.0f,0.0f,1.0f);
      m_BaseParts->Draw();
   glPopMatrix();
}
