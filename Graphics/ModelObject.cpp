/*   This file is part of Theme Park Builder 3D The Game.
 *
 *   Theme Park Builder 3D The Game is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Theme Park Builder 3D The Game is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "Animation.h"
#include "FireAnimation.h"
#include "Tiler.h"
#include "Texture.h"
#include "ModelObject.h"

using namespace Gfx;

ModelObject::ModelObject ()
{
}

void
ModelObject::Render(AnimationBase* pBase, bool bLight)
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = -pBase->GetPositionY();//-ms.y;
   float z = pBase->GetPositionZ();
   float x2 = x + pBase->GetWidth();
   float y2 = y - pBase->GetHeight();
   //glBindTexture( GL_TEXTURE_2D, pBase->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   pBase->BindTexture();
   if (bLight)
   {
      glColor4fv (pBase->GetLightingColor());
   }
   glBegin(GL_QUADS);
   {
      glTexCoord2f( 0.0, 1.0 );
      glVertex3f( x, y2, z );
      glTexCoord2f( 0.0, 0.0 );
      glVertex3f( x, y, z );
      glTexCoord2f( 1.0, 0.0 );
      glVertex3f( x2, y, z );
      glTexCoord2f( 1.0, 1.0 );
      glVertex3f( x2, y2, z );
   }
   glColor4ub (250,250,250,255);
   glEnd();
}

void
ModelObject::Render(AnimationBase* pBase, float x, float x2 )
{
   float y = -pBase->GetPositionY();//-ms.y;
   float z = 0; //pBase->GetPositionZ();
   float y2 = y - pBase->GetHeight();

   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      glTexCoord2f( 0.0, 1.0 );
      glVertex3f( x, y2, z );
      glTexCoord2f( 0.0, 0.0 );
      glVertex3f( x, y, z );
      glTexCoord2f( 1.0, 0.0 );
      glVertex3f( x2, y, z );
      glTexCoord2f( 1.0, 1.0 );
      glVertex3f( x2, y2, z );
   }
   glEnd();
}

void ModelObject::RenderRectangle (AnimationBase* pBase )
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = -pBase->GetPositionY();//-ms.y;
   float z = 1;//pBase->GetPositionZ();
   float x2 = x + pBase->GetWidth();
   float y2 = y - pBase->GetHeight();
   const float* pColors = pBase->GetLightingColor();
   glColor4fv (pColors);
   glDisable (GL_TEXTURE_2D);
   glBegin(GL_QUADS);
   {
      glVertex3f( x, y2, z );
      glVertex3f( x, y, z );
      glVertex3f( x2, y, z );
      glVertex3f( x2, y2, z );
   }
   glEnd();
   glColor4ub (255,255,255,255);
   glEnable (GL_TEXTURE_2D);
}

void ModelObject::Render(Tiler* pTiler)
{
   float x = pTiler->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = -pTiler->GetPositionY();//-ms.y;
   float z = 0;//pTiler->GetPositionZ();
   float x2 = x + pTiler->GetWidth();
   float y2 = y - pTiler->GetHeight();
   float xT = pTiler->GetTesselX();
   float yT = pTiler->GetTesselY();
   pTiler->BindTexture();//to_draw.GetTexture() ); // get the current texture
   glBegin(GL_QUADS);
   {
      glTexCoord2f( 0.0, yT );
      glVertex3f( x, y2, z );
      glTexCoord2f( 0.0, 0.0 );
      glVertex3f( x, y, z );
      glTexCoord2f( xT, 0.0 );
      glVertex3f( x2, y, z );
      glTexCoord2f( xT, yT );
      glVertex3f( x2, y2, z );
   }
   glEnd();
}

void ModelObject::RenderParallax (FireAnimation* pBase, float xOffset )  // overload with specified X and X2 for parallax animation
{
   float x = pBase->GetPositionX() + xOffset;
   float y = pBase->GetPositionY();
   float z = pBase->GetPositionZ();

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
      pBase->BindTexture();
      //glEnable (GL_BLEND);
      glEnable (GL_COLOR_MATERIAL);
      glTranslatef (x, y, z);
      const unsigned char* pColors = pBase->GetFlameColor(0);
      const float* pUVs = pBase->GetUVs(0,0);
      const float* pVerts = pBase->GetVertecies(0,0);
      glColor4ubv (pColors);
      glBegin(GL_QUADS);
      {
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
      }
      glEnd();

      glTranslatef (2, 0, 0);
      pColors = pBase->GetFlameColor(1);
      pUVs = pBase->GetUVs(1,0);
      pVerts = pBase->GetVertecies(1,0);
      glColor4ubv (pColors);
      glBegin(GL_QUADS);
      {
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
      }
      glEnd();
      pColors = pBase->GetFlameColor(2);
      pUVs = pBase->GetUVs(2,0);
      pVerts = pBase->GetVertecies(2,0);
      glTranslatef (-3, 0, 0);
      glColor4ubv (pColors);
      glBegin(GL_QUADS);
      {
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
      }
      glEnd();
      glTranslatef (4, 0, 0);
      pColors = pBase->GetFlameColor(3);
      pUVs = pBase->GetUVs(3,0);
      pVerts = pBase->GetVertecies(3,0);
      glColor4ubv (pColors);
      glBegin(GL_QUADS);
      {
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
         pUVs+= 2; // pointer math
         pVerts+= 3;
         glTexCoord2fv( pUVs );
         glVertex3fv( pVerts );
      }
      glEnd();
      glColor4ub (255,255,255,255);
      glDisable (GL_COLOR_MATERIAL);
      //glDisable (GL_BLEND);
   glPopMatrix();
}

void
ModelObject::DrawSelectionTarget (AnimationBase* pBase, int id ) // milk and cookies run just for the basics to test for a hit
{
   float fx = pBase->GetPositionX();
   float fy = -pBase->GetPositionY();//-ms.y;
   float fz = 0; //pBase->GetPositionZ();
   float fx2 = fx + pBase->GetWidth();
   float fy2 = fy - pBase->GetHeight();

   //glPassThrough((GLfloat)id );
   glLoadName( id );
   glBegin(GL_QUADS);
   glVertex3f( fx, fy2, fz );  // needs to be a cube
   glVertex3f( fx, fy, fz );
   glVertex3f( fx2, fy, fz );
   glVertex3f( fx2, fy2, fz );
   glEnd();
#ifdef _TESTGLSELECT
   int ix = glGetError();
   if( ix )
      cout << "Glerror 3:" << ix << std::endl;
#endif
}

void
ModelObject::DrawSelectionTarget (AnimationBase* pBase, float x, float x2, int id )  // overload with specified X and X2 and id
{
   float fx = x;
   float fy = -pBase->GetPositionY();//-ms.y;
   float fz = 0; //pBase->GetPositionZ();
   float fx2 = x2;
   float fy2 = fy - pBase->GetHeight();

   //glPassThrough((GLfloat)id );
   glLoadName( id );
   glBegin(GL_QUADS);
   glVertex3f( fx, fy2, fz );  // needs to be a cube
   glVertex3f( fx, fy, fz );
   glVertex3f( fx2, fy, fz );
   glVertex3f( fx2, fy2, fz );
   glEnd();
}
