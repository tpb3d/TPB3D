//  --------------------------------------------------------------------
//  Copyright (C)2010 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Lamp class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Developer 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <string>

#include "../Storage/SerializerBase.h"
#include "../Types/Vector3.h"
#include "../Graphics/Image.h"
#include "../Graphics/Material.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ObjectNode.h"
#include "../Graphics/StripMeshObject.h"
#include "../Graphics/TexturedStrip.h"
#include "../Graphics/ObjectFactory.h"
#include "Lamp.h"

#define _USE_MATH_DEFINES
#include <math.h>

Lamp::Lamp (float height, const char* TexName, const char* TexGlow)
//:  CoreBase (Vector3f(0,0,0), Vector3f(0,0,0))
:  ObjectNode(0, ObjectFactory::TakeANumber())
{
   mTexName = TexName;
   mTexGlow = TexGlow;
   mHeight = height;
   mSections = 8; // some rides may have more
   mRadii[0] = 0.15f;
   mRadii[1] = 0.15f;
   mpGraphic = ObjectFactory::CreateNode(1);
}

Lamp::Lamp (float height, ObjectNode* pGfx)
//:  CoreBase (Vector3f(0,0,0), Vector3f(0,0,0))
:  ObjectNode(0, ObjectFactory::TakeANumber())
,  mpGraphic (pGfx)
{
   mTexName = "";
   mHeight = height;
   mSections = 2; // some rides may have more
   mRadii[0] = 0.15f;
   mRadii[1] = 0.15f;
}

Lamp::~Lamp(void)
{
   if (mpGraphic != NULL)
   {
      delete mpGraphic;
   }
}

void Lamp::Draw()
{
 	glPushMatrix();															// Push Matrix Onto Stack (Copy The Current Matrix)
   glEnable (GL_BLEND);
   glTranslatef( mLocation[0], mLocation[1], mLocation[2] );										// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef( mAngle, 0.0f, 1.0f, 0.0f);
   mpGraphic->Draw();
   glDisable (GL_BLEND);
   glPopMatrix();
}

void Lamp::Render()
{
   int iSides = 9;
   float fRad = 0.0;
   float fDeg = 360.0f/ (iSides-1);
   float fBaseTop = mHeight * 0.2f;
   float fPoleTop = mHeight * 0.8f;
   float  fOff = 0.35f;
   Material mat(0,0,0,0,0,0,0);
   mat.SetTexture( Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   StripMeshObject* pBase = ObjectFactory::CreateStrip ();
   Material *mats[1];
   mats[0] = &mat;
   pBase->AddMaterials(1, mats);
   mpGraphic->AddMesh (pBase);
   Vector3f pt1 (-fOff, 0, -fOff);
   Vector3f pt2 (-fOff, fBaseTop, -fOff);

   Vector3f vecs[20];   
   vecs[0] = pt1;
   vecs[1] = pt2;
   pt1.x = fOff;
   pt2.x = fOff;
   vecs[2] = pt1;
   vecs[3] = pt2;
   pt1.z = fOff;
   pt2.z = fOff;
   vecs[4] = pt1;
   vecs[5] = pt2;
   pt1.x = -fOff;
   pt2.x = -fOff;
   vecs[6] = pt1;
   vecs[7] = pt2;
   pt1.z = -fOff;
   pt2.z = -fOff;
   vecs[8] = pt1;
   vecs[9] = pt2;
   pBase->AddMesh (10, vecs, 1);
   StripGroup* pGroup = pBase->AddStripGroup(0, 5, 0, Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   StripPair pair[32];

   float fL = 0.09F;
   float fR = 0.44F;
   float fT = 0.32F;
   float fB = 0.46F;

   memset (&pair, 0, sizeof(pair));
   pair[0].mPoints[0].mUV[0] = fL;
   pair[0].mPoints[0].mUV[1] = fT;
   pair[0].mPoints[1].mUV[0] = fL;
   pair[0].mPoints[1].mUV[1] = fB;
   pair[0].mPoints[0].Index = 0;
   pair[0].mPoints[1].Index = 1;
   pair[1].mPoints[0].mUV[0] = fR;
   pair[1].mPoints[0].mUV[1] = fT;
   pair[1].mPoints[1].mUV[0] = fR;
   pair[1].mPoints[1].mUV[1] = fB;
   pair[1].mPoints[0].Index = 2;
   pair[1].mPoints[1].Index = 3;
   pair[2].mPoints[0].mUV[0] = fL;
   pair[2].mPoints[0].mUV[1] = fT;
   pair[2].mPoints[1].mUV[0] = fL;
   pair[2].mPoints[1].mUV[1] = fB;
   pair[2].mPoints[0].Index = 4;
   pair[2].mPoints[1].Index = 5;
   pair[3].mPoints[0].mUV[0] = fR;
   pair[3].mPoints[0].mUV[1] = fT;
   pair[3].mPoints[1].mUV[0] = fR;
   pair[3].mPoints[1].mUV[1] = fB;
   pair[3].mPoints[0].Index = 6;
   pair[3].mPoints[1].Index = 7;
   pair[4].mPoints[0].mUV[0] = fL;
   pair[4].mPoints[0].mUV[1] = fT;
   pair[4].mPoints[1].mUV[0] = fL;
   pair[4].mPoints[1].mUV[1] = fB;
   pair[4].mPoints[0].Index = 8;
   pair[4].mPoints[1].Index = 9;
   pGroup->AddStripPair(5,pair);

   StripMeshObject* pPole = ObjectFactory::CreateStrip ();
   mpGraphic->AddMesh (pPole);
   pPole->AddMaterials(1, mats);
   int iv = 0;
   float fv = 0.6f;
   for( int idx = 0; idx < iSides; ++idx )
   {
      float fTheta = (float)(M_PI/180 * fRad);
      Vector3f pt (cos(fTheta) * this->mRadii[0], fBaseTop, sin(fTheta)* this->mRadii[0]);
      pair[idx].mPoints[0].mUV[0] = fv;
      pair[idx].mPoints[0].mUV[1] = 0.0f;
      pair[idx].mPoints[1].mUV[0] = fv;
      pair[idx].mPoints[1].mUV[1] = 0.95f;
      pair[idx].mPoints[0].Index = iv;
      vecs[iv++] = pt;
      fRad += fDeg;
      pt = Vector3f (cos(fTheta) * this->mRadii[1], fPoleTop, sin(fTheta)* this->mRadii[1]);
      pair[idx].mPoints[1].Index = iv;
      vecs[iv++] = pt;
      fv += 0.025f;
   }
   pPole->AddMesh (iSides*2, vecs, 1);
   pGroup = pPole->AddStripGroup(0, iSides, 0, Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   pGroup->AddStripPair(iSides,pair);

   fOff = 0.1f;
   TexturedStrip* pMantle = ObjectFactory::CreateTexturedStrip (2, mTexName.c_str(), 0xf0f0f0f0);
   mpGraphic->AddMesh (pMantle);
   pt1 = Vector3f (-fOff, fPoleTop, 0);
   pt2 = Vector3f (-fOff, (fPoleTop + 2.1f), 0);
   pMantle->AddPoint (pt1);
   pMantle->AddPoint (pt2);
   pt1.x = fOff;
   pt2.x = fOff;
   pMantle->AddPoint (pt1);
   pMantle->AddPoint (pt2);

   pMantle = ObjectFactory::CreateTexturedStrip (2, mTexName.c_str(), 0xf0f0f0f0);
   mpGraphic->AddMesh (pMantle);
   pt1.x = 0;
   pt2.x = 0;
   pt1.z = -fOff;
   pt2.z = -fOff;
   pMantle->AddPoint (pt1);
   pMantle->AddPoint (pt2);
   pt1.z = fOff;
   pt2.z = fOff;
   pMantle->AddPoint (pt1);
   pMantle->AddPoint (pt2);

   StripMeshObject* pHead = ObjectFactory::CreateStrip ();
   mpGraphic->AddMesh (pHead);
   pHead->AddMaterials(1, mats);

   fOff = 0.4f;
   float foff2 = 0.5f;
   pt1.x = -fOff;
   pt2.x = -foff2;
   pt1.z = -fOff;
   pt2.z = -foff2;
   pt1.y = fPoleTop;
   pt2.y = mHeight;   
   vecs[0] = pt1;
   vecs[1] = pt2;
   pt1.x = fOff;
   pt2.x = foff2;
   vecs[2] = pt1;
   vecs[3] = pt2;
   pt1.z = fOff;
   pt2.z = foff2;
   vecs[4] = pt1;
   vecs[5] = pt2;
   pt1.x = -fOff;
   pt2.x = -foff2;
   vecs[6] = pt1;
   vecs[7] = pt2;
   pt1.z = -fOff;
   pt2.z = -foff2;
   vecs[8] = pt1;
   vecs[9] = pt2;
   pHead->AddMesh (10, vecs, 1);
   fL = 0.10F;
   fR = 0.44F;
   fT = 0.05F;
   fB = 0.27F;
   
   pGroup = pHead->AddStripGroup(0, 5, 0, Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   pair[0].mPoints[0].mUV[0] = fL;
   pair[0].mPoints[0].mUV[1] = fT;
   pair[0].mPoints[1].mUV[0] = fL;
   pair[0].mPoints[1].mUV[1] = fB;
   pair[0].mPoints[0].Index = 0;
   pair[0].mPoints[1].Index = 1;
   pair[1].mPoints[0].mUV[0] = fR;
   pair[1].mPoints[0].mUV[1] = fT;
   pair[1].mPoints[1].mUV[0] = fR;
   pair[1].mPoints[1].mUV[1] = fB;
   pair[1].mPoints[0].Index = 2;
   pair[1].mPoints[1].Index = 3;
   pair[2].mPoints[0].mUV[0] = fL;
   pair[2].mPoints[0].mUV[1] = fT;
   pair[2].mPoints[1].mUV[0] = fL;
   pair[2].mPoints[1].mUV[1] = fB;
   pair[2].mPoints[0].Index = 4;
   pair[2].mPoints[1].Index = 5;
   pair[3].mPoints[0].mUV[0] = fR;
   pair[3].mPoints[0].mUV[1] = fT;
   pair[3].mPoints[1].mUV[0] = fR;
   pair[3].mPoints[1].mUV[1] = fB;
   pair[3].mPoints[0].Index = 6;
   pair[3].mPoints[1].Index = 7;
   pair[4].mPoints[0].mUV[0] = fL;
   pair[4].mPoints[0].mUV[1] = fT;
   pair[4].mPoints[1].mUV[0] = fL;
   pair[4].mPoints[1].mUV[1] = fB;
   pair[4].mPoints[0].Index = 8;
   pair[4].mPoints[1].Index = 9;
   pGroup->AddStripPair(5,pair);

   TexturedStrip* pGlow = ObjectFactory::CreateTexturedStrip (2, mTexGlow.c_str(), 0xf0f0f0f0);
   pGlow->AddPoint (sf::Vector3f(-1.5f, mHeight-1.5f, 0.54f));
   pGlow->AddPoint (sf::Vector3f(-1.5f, mHeight+1.65f, 0.54f));
   pGlow->AddPoint (sf::Vector3f(1.5f, mHeight-1.5f, 0.54f));
   pGlow->AddPoint (sf::Vector3f(1.5f, mHeight+1.65f, 0.54f));
   mpGraphic->AddMesh (pGlow);

   StripMeshObject* pCap = ObjectFactory::CreateStrip ();
   mpGraphic->AddMesh (pCap);
   pCap->AddMaterials(1, mats);

   fOff = 0.53f;
   pt1.x = -fOff;
   pt1.z = -fOff;
   pt1.y = (float)mHeight;
   pt2.y = (float)mHeight;   
   vecs[0] = pt1;
   pt1.x = fOff;
   vecs[1] = pt1;
   pt1.x = -fOff;
   pt1.z = fOff;
   vecs[2] = pt1;
   pt1.x = fOff;
   vecs[3] = pt1;
   pCap->AddMesh (4, vecs, 1);
   fL = 0.10F;
   fR = 0.44F;
   fT = 0.78F;
   fB = 0.92F;
   
   pGroup = pCap->AddStripGroup(0, 2, 0, Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   pair[0].mPoints[0].mUV[0] = fL;
   pair[0].mPoints[0].mUV[1] = fT;
   pair[0].mPoints[1].mUV[0] = fL;
   pair[0].mPoints[1].mUV[1] = fB;
   pair[0].mPoints[0].Index = 0;
   pair[0].mPoints[1].Index = 1;
   pair[1].mPoints[0].mUV[0] = fR;
   pair[1].mPoints[0].mUV[1] = fT;
   pair[1].mPoints[1].mUV[0] = fR;
   pair[1].mPoints[1].mUV[1] = fB;
   pair[1].mPoints[0].Index = 2;
   pair[1].mPoints[1].Index = 3;
   pGroup->AddStripPair(2,pair);

}

void Lamp::DrawSelectionTarget()
{
}

void Lamp::Update(int dt)
{
}


//ObjectBase* Lamp::Clone( )
//{
//   Lamp* pLamp = new Lamp(mHeight, mSides, mTexName.c_str());
//   return pLamp;
//}


void Lamp::Load(SerializerBase& ser)
{
   // need to build a factory for this
   //RideNodeSection* pRideNodeSection = new RideNodeSection();
   //pRideNodeSection->Load(ser);
}

void Lamp::Save(SerializerBase& ser)
{
   ser.Add("type", "Lamp");
   mpGraphic->Save(ser);
}