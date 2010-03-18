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
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/vector3.h"
#include "../Graphics/VPoint.h"
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
   double dRad = 0.0;
   double dDeg = 360.0/ (iSides-1);
   double dBaseTop = mHeight * 0.2;
   double dPoleTop = mHeight * 0.8;
   float  fOff = 0.35f;
   Material mat(0,0,0,0,0,0,0);
   mat.SetTexture( Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   StripMeshObject* pBase = ObjectFactory::CreateStrip ();
   Material *mats[1];
   mats[0] = &mat;
   pBase->AddMaterials(1, mats);
   mpGraphic->AddMesh (pBase);
   CVPoint pt1 (-fOff,0, -fOff);
   CVPoint pt2 (-fOff,dBaseTop, -fOff);

   sf::Vector3f vecs[10];   
   vecs[0] = pt1.GetVector3f();
   vecs[1] = pt2.GetVector3f();
   pt1.x = fOff;
   pt2.x = fOff;
   vecs[2] = pt1.GetVector3f();
   vecs[3] = pt2.GetVector3f();
   pt1.z = fOff;
   pt2.z = fOff;
   vecs[4] = pt1.GetVector3f();
   vecs[5] = pt2.GetVector3f();
   pt1.x = -fOff;
   pt2.x = -fOff;
   vecs[6] = pt1.GetVector3f();
   vecs[7] = pt2.GetVector3f();
   pt1.z = -fOff;
   pt2.z = -fOff;
   vecs[8] = pt1.GetVector3f();
   vecs[9] = pt2.GetVector3f();
   pBase->AddMesh (10, vecs, 1);
   StripGroup* pGroup = pBase->AddStripGroup(0, 4, 0, Gfx::ImageManager::GetInstance()->GetTexture (mTexName, 4));
   StripPair pair;
   memset (&pair, 0, sizeof(pair));
   pair.mPoints[0].mUV[0] = 0.1f;
   pair.mPoints[0].mUV[1] = 0.4f;
   pair.mPoints[1].mUV[0] = 0.1f;
   pair.mPoints[1].mUV[1] = 0.25f;
   pair.mPoints[0].Index = 0;
   pair.mPoints[1].Index = 1;
   pGroup->AddStripPair(0,&pair);
   pair.mPoints[0].Index = 2;
   pair.mPoints[1].Index = 3;
   pair.mPoints[0].mUV[0] = 0.3f;
   pair.mPoints[1].mUV[0] = 0.3f;
   pGroup->AddStripPair(1,&pair);
   pair.mPoints[0].Index = 4;
   pair.mPoints[1].Index = 5;
   pair.mPoints[0].mUV[0] = 0.1f;
   pair.mPoints[1].mUV[0] = 0.1f;
   pGroup->AddStripPair(2,&pair);
   pair.mPoints[0].Index = 6;
   pair.mPoints[1].Index = 7;
   pair.mPoints[0].mUV[0] = 0.3f;
   pair.mPoints[1].mUV[0] = 0.3f;
   pGroup->AddStripPair(3,&pair);
   pair.mPoints[0].Index = 8;
   pair.mPoints[1].Index = 9;
   pair.mPoints[0].mUV[0] = 0.1f;
   pair.mPoints[1].mUV[0] = 0.1f;
   pGroup->AddStripPair(4,&pair);
/*
   TexturedStrip* pPole = ObjectFactory::CreateStrip ();
   mpGraphic->AddMesh (pPole);
   for( int idx = 0; idx < iSides; ++idx )
   {
      double dTheta = M_PI/180 * dRad;
      CVPoint pt (cos(dTheta) * this->mRadii[0], dBaseTop, sin(dTheta)* this->mRadii[0]);
      sf::Vector3f temp = pt.GetVector3f();
      pPole->AddPoint (temp);
      dRad += dDeg;
      pt = CVPoint (cos(dTheta) * this->mRadii[1], dPoleTop, sin(dTheta)* this->mRadii[1]);
      temp = sf::Vector3f (pt.GetVector3f());
      pPole->AddPoint (temp);
   }
   TexturedStrip* pHead = ObjectFactory::CreateTexturedStrip (4, mTexName.c_str(), 0xf0f0f0f0);
   mpGraphic->AddMesh (pHead);
   pt1 = CVPoint (-fOff,dPoleTop, -fOff);
   pt2 = CVPoint (-fOff,mHeight, -fOff);
   pHead->AddPoint (pt1.GetVector3f());
   pHead->AddPoint (pt2.GetVector3f());
   pt1.x = fOff;
   pt2.x = fOff;
   pHead->AddPoint (pt1.GetVector3f());
   pHead->AddPoint (pt2.GetVector3f());
   pt1.z = fOff;
   pt2.z = fOff;
   pHead->AddPoint (pt1.GetVector3f());
   pHead->AddPoint (pt2.GetVector3f());
   pt1.x = -fOff;
   pt2.x = -fOff;
   pHead->AddPoint (pt1.GetVector3f());
   pHead->AddPoint (pt2.GetVector3f());
   pt1.z = -fOff;
   pt2.z = -fOff;
   pHead->AddPoint (pt1.GetVector3f());
   pHead->AddPoint (pt2.GetVector3f());
*/
   TexturedStrip* pGlow = ObjectFactory::CreateTexturedStrip (2, mTexGlow.c_str(), 0xf0f0f0f0);
   pGlow->AddPoint (sf::Vector3f(-1.5f, mHeight-1.75f, 0.4));
   pGlow->AddPoint (sf::Vector3f(-1.5f, mHeight+1.25f, 0.4));
   pGlow->AddPoint (sf::Vector3f(1.5f, mHeight-1.75f, 0.4));
   pGlow->AddPoint (sf::Vector3f(1.5f, mHeight+1.25f, 0.4));
   mpGraphic->AddMesh (pGlow);
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