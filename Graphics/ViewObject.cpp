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
#include <string>
#include "Animation.h"
#include "SimpleMesh.h"
#include "Texture.h"
#include "ViewObject.h"

// all things not in 3D space. Used for interface
using namespace Gfx;

ViewObject::ViewObject ()
{
   mUVs[0][0] = 0;
   mUVs[0][1] = 1;
   mUVs[1][0] = 0;
   mUVs[1][1] = 0;
   mUVs[2][0] = 1;
   mUVs[2][1] = 0;
   mUVs[3][0] = 1;
   mUVs[3][1] = 1;
   memset (mPoints, 0, sizeof(mPoints));
   mSize.x = 8;
   mSize.y = 8;
}

ViewObject::ViewObject (const float uvs[4][2])
{
   memcpy (mUVs, uvs, sizeof(mUVs));
   memset (&mPoints, 0, sizeof(mPoints));
   mSize.x = 8;
   mSize.y = 8;
}

void ViewObject::Render(AnimationBase* pBase)
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = (pBase->GetPositionY());//-ms.y;
   float z = 0; //pBody->GetPositionZ();
   float x2 = x + pBase->GetWidth();
   float y2 = y + pBase->GetHeight();
//   glBindTexture( GL_TEXTURE_2D, pBody->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      glTexCoord2fv( mUVs[0] );
      glVertex3f( x, y2, z );
      glTexCoord2fv( mUVs[1] );
      glVertex3f( x, y, z );
      glTexCoord2fv( mUVs[2] );
      glVertex3f( x2, y, z );
      glTexCoord2fv( mUVs[3] );
      glVertex3f( x2, y2, z );
   }
   glEnd();
}

void ViewObject::Render(AnimationBase* pBase, const float uvs[4][2])
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = (pBase->GetPositionY());//-ms.y;
   float z = 100; //pBody->GetPositionZ();
   float x2 = x + pBase->GetWidth();
   float y2 = y + pBase->GetHeight();
//   glBindTexture( GL_TEXTURE_2D, pBody->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      glTexCoord2fv (uvs[0]);
      glVertex3f( x, y2, z );
      glTexCoord2fv (uvs[1]);
      glVertex3f( x, y, z );
      glTexCoord2fv (uvs[2]);
      glVertex3f( x2, y, z );
      glTexCoord2fv (uvs[3]);
      glVertex3f( x2, y2, z );
   }
   glEnd();
}

void ViewObject::RenderText(AnimationBase* pBase, float x, float y, string str)
{
   const float cu = 1.0f/32;
   float z = 0; //pBody->GetPositionZ();
   float x2 = x + 9;
   float y2 = y + 12;
   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      for( unsigned int ic = 0; ic < str.length(); ++ic)
      {
         char t = (char)str[ic]-' ';
         float u = (t%32) * cu;
         float v = 1.0f - 0.13f * int((128-t)/32);
         glTexCoord2f (u, v-0.125f);
         glVertex3f( x, y2, z );
         glTexCoord2f (u, v);
         glVertex3f( x, y, z );
         glTexCoord2f (u+cu, v);
         glVertex3f( x2, y, z );
         glTexCoord2f (u+cu, v-0.125f);
         glVertex3f( x2, y2, z );
         x+=8;
         x2+=8;
      }
   }
   glEnd();
}

void ViewObject::RenderText(AnimationBase* pBase, std::string str)
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = (pBase->GetPositionY());//-ms.y;
   const float cu = 1.0f/32;
   float z = 0; //pBody->GetPositionZ();
   float x2 = x + 9;
   float y2 = y + 12;
   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      for( unsigned int ic = 0; ic < str.length(); ++ic)
      {
         char t = (char)str[ic]-' ';
         float u = (t%32) * cu;
         float v = 1.0f - 0.13f * int((128-t)/32);
         glTexCoord2f (u, v-0.125f);
         glVertex3f( x, y2, z );
         glTexCoord2f (u, v);
         glVertex3f( x, y, z );
         glTexCoord2f (u+cu, v);
         glVertex3f( x2, y, z );
         glTexCoord2f (u+cu, v-0.125f);
         glVertex3f( x2, y2, z );
         x+=8;
         x2+=8;
      }
   }
   glEnd();
}

void ViewObject::Render(SimpleQuad* pQuad)
{
   glPushMatrix();
//      glLoadIdentity();
      glDisable (GL_TEXTURE_2D);
      glEnable (GL_COLOR_MATERIAL);
      glTranslatef (pQuad->Position.x, pQuad->Position.y, pQuad->Position.z);
      glRotatef( -pQuad->Angle, 0, 0, 1 );
      glBegin(GL_QUADS);
      {
         glColor4ubv (pQuad->Colors[0]);
         glVertex3fv ((float*)&pQuad->mPoints[0].x);
         glColor4ubv (pQuad->Colors[1]);
         glVertex3fv ((float*)&pQuad->mPoints[1].x);
         glColor4ubv (pQuad->Colors[2]);
         glVertex3fv ((float*)&pQuad->mPoints[2].x);
         glColor4ubv (pQuad->Colors[3]);
         glVertex3fv ((float*)&pQuad->mPoints[3].x);
      }
      glEnd();
      glDisable (GL_COLOR_MATERIAL);
      glEnable (GL_TEXTURE_2D);
      glColor4ub (255,255,255,255);
   glPopMatrix();
}

void ViewObject::Render(SimpleMesh* pMesh)  // Renders a quad from 4 vectors.
{
   glPushMatrix();
      Vector3f* pQuad = pMesh->get_Mesh();
      Vector2f* pUV = pMesh->get_mUVs();
      pMesh->BindTexture();
      glColor4fv (pMesh->GetLightingColor());
      glTranslatef (pMesh->get_Position().x, pMesh->get_Position().y, pMesh->get_Position().z);
      //glBegin(GL_QUADS); //_STRIP);
      //{
      //   glTexCoord2f (0, 0);
      //   glVertex3fv ((float*)&pQuad[0].x);
      //   glTexCoord2f (1, 0);
      //   glVertex3fv ((float*)&pQuad[3].x);
      //   glTexCoord2f (1, 1);
      //   glVertex3fv ((float*)&pQuad[4].x);
      //   glTexCoord2f (0, 1);
      //   glVertex3fv ((float*)&pQuad[7].x);
      //}
      //glEnd();
      glBegin(GL_QUAD_STRIP);
      {
         glTexCoord2fv (&pUV[0].x);
         glVertex3fv ((float*)&pQuad[0].x);
         glTexCoord2fv (&pUV[4].x);
         glVertex3fv ((float*)&pQuad[4].x);
         glTexCoord2fv (&pUV[1].x);
         glVertex3fv ((float*)&pQuad[1].x);
         glTexCoord2fv (&pUV[5].x);
         glVertex3fv ((float*)&pQuad[5].x);
         glTexCoord2fv (&pUV[2].x);
         glVertex3fv ((float*)&pQuad[2].x);
         glTexCoord2fv (&pUV[6].x);
         glVertex3fv ((float*)&pQuad[6].x);
         glTexCoord2fv (&pUV[3].x);
         glVertex3fv ((float*)&pQuad[3].x);
         glTexCoord2fv (&pUV[7].x);
         glVertex3fv ((float*)&pQuad[7].x);
      }
      glEnd();
      glBegin(GL_QUAD_STRIP);
      {
         glTexCoord2fv (&pUV[4].x);
         glVertex3fv ((float*)&pQuad[4].x);
         glTexCoord2fv (&pUV[8].x);
         glVertex3fv ((float*)&pQuad[8].x);
         glTexCoord2fv (&pUV[5].x);
         glVertex3fv ((float*)&pQuad[5].x);
         glTexCoord2fv (&pUV[9].x);
         glVertex3fv ((float*)&pQuad[9].x);
         glTexCoord2fv (&pUV[6].x);
         glVertex3fv ((float*)&pQuad[6].x);
         glTexCoord2fv (&pUV[10].x);
         glVertex3fv ((float*)&pQuad[10].x);
         glTexCoord2fv (&pUV[7].x);
         glVertex3fv ((float*)&pQuad[7].x);
         glTexCoord2fv (&pUV[11].x);
         glVertex3fv ((float*)&pQuad[11].x);
      }
      glEnd();
      glBegin(GL_QUAD_STRIP);
      {
         glTexCoord2fv (&pUV[8].x);
         glVertex3fv ((float*)&pQuad[8].x);
         glTexCoord2fv (&pUV[12].x);
         glVertex3fv ((float*)&pQuad[12].x);
         glTexCoord2fv (&pUV[9].x);
         glVertex3fv ((float*)&pQuad[9].x);
         glTexCoord2fv (&pUV[13].x);
         glVertex3fv ((float*)&pQuad[13].x);
         glTexCoord2fv (&pUV[10].x);
         glVertex3fv ((float*)&pQuad[10].x);
         glTexCoord2fv (&pUV[14].x);
         glVertex3fv ((float*)&pQuad[14].x);
         glTexCoord2fv (&pUV[11].x);
         glVertex3fv ((float*)&pQuad[11].x);
         glTexCoord2fv (&pUV[15].x);
         glVertex3fv ((float*)&pQuad[15].x);
      }
      glEnd();
      glColor4ub (255,255,255,255);
   glPopMatrix();
}

void ViewObject::DrawSelectionTarget(SimpleQuad* pQuad)   // just the basic geometry
{
   float x = pQuad->Position.x;
   float y = pQuad->Position.y;
   float z = pQuad->Position.z;
   glPushMatrix();
//      glLoadIdentity();
      glTranslatef (x, y, z);
      glRotatef( -pQuad->Angle, 0, 0, 1 );
      glBegin(GL_QUADS);
      {
         glVertex3fv ((float*)&pQuad->mPoints[0].x);
         glVertex3fv ((float*)&pQuad->mPoints[1].x);
         glVertex3fv ((float*)&pQuad->mPoints[2].x);
         glVertex3fv ((float*)&pQuad->mPoints[3].x);
      }
      glEnd();
   glPopMatrix();
}
