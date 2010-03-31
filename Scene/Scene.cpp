//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Scene class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////


#include <iostream>
#include <list>
#include "../Physics/MotionPhysics.h"
#include "../CoreObjects/Routes.h"
#include "../Graphics/Camera.h"
#include "../Graphics/SkyBowl.h"
#include "../Hub/Event.h"
#include "../CoreObjects/CoreBase.h"
#include "../CoreObjects/Pathway.h"
#include "../CoreObjects/Park.h"
#include "../CoreObjects/BuildStrategies.h"
#include "../CoreObjects/Terrain.h"
#include "Scene.h"

//using namespace Gfx;
Scene::Scene ()
{
   mpTerrain = NULL;
   mpBuildStrategy = NULL;
   mpSky = new SkyBowl();
   mpSky->Init( 800 );
}

Scene::~Scene ()
{
   delete mpSky;
}

void Scene::AddPark (Park* pPark)
{
   mParks.push_back (pPark);   // Multiple parks are possible with piping
}

void Scene::SetTerrain (Terrain* pTerrain)
{
   if (mpTerrain != NULL)
   {
      delete mpTerrain;
   }
   mpTerrain = pTerrain;
}


bool Scene::SelectTool (int toolID)
{
   bool bResult = false;
   BuildStrategyBase* pOldStrategy = mpBuildStrategy;
   switch (toolID)
   {
   case HR_PlaceBuilding:
      mpBuildStrategy = new BuildBuildingStrategy();
      mpBuildStrategy->ShowGhostBuild (mParks[0]);
      bResult = true;
      break;
   }
   if (bResult && !(pOldStrategy==NULL))
   {
      try
      {
         delete pOldStrategy;
      }
      catch (...)
      {
         std::cout << "Error deleting old BuildStrategy in Scene";
      }
   }
   return bResult;
}

void Scene::Update (float dt, int timeOfDay)
{
}

void Scene::Draw ()
{
   std::vector<Park *>::iterator iPark;
//glEnable(GL_FOG);
   // Acutal
   glEnable(GL_CULL_FACE);
   glDisable(GL_LIGHTING);
   glEnable (GL_COLOR_MATERIAL);
   mpSky->Draw();
   glEnable(GL_LIGHTING);
   glDisable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   //glDisable (GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
   mpTerrain->Draw();
   //glDisable(GL_LIGHT1);
	glDisable(GL_CULL_FACE);

   for (iPark = mParks.begin (); iPark != mParks.end (); iPark++)
   {
      Park* pPark = (*iPark);
      pPark->Draw( );
   }
	glDisable(GL_NORMALIZE);
}

void Scene::DrawSelectionTarget (int PathwayNo)
{
   bool bPathwaysOnly = (this->mpBuildStrategy==NULL) ? false : true;
   std::vector<Park *>::iterator iPark;
   for (iPark = mParks.begin (); iPark != mParks.end (); iPark++)
   {
      if (PathwayNo==0)
      {
         (*iPark)->DrawSelectionTarget (bPathwaysOnly);
      }
      else
      {
      }
   }
}

void Scene::MoveGhostObject (Vector2f& point)
{
   Camera* pCam = Camera::GetInstance();
   Vector3f vec = pCam->GetOGLPos (point);
   Park* pPark = mParks[0];
   pPark->GetGhostObject().Move (vec);// asp
}

void Scene::HitDown( int hit, Vector2i& Scene )  // taking a mouse hit, send it through geometry to see what we hit
{
   if( mpBuildStrategy && mpBuildStrategy->PlacingRoom() )
   {
      //std::vector<Park *>::iterator iPark;
      //for (iPark = mParks.begin (); iPark != mParks.end (); iPark++)
      //{
      //   Park* pPark = (*iPark);
      //   Pathway* pPathway = pPark->FindPathway (hit);
      //   if( pPathway )
      //   {
      //      int x = (int)(pPark->GetGhostObject().GetX() / 9);
      //      std::cout << "Mouse on Pathway: " << pPathway->GetPathway() << " Pathway ID: " << hit << std::endl;
      //      mpBuildStrategy->BuildHere(pPark, x, pPathway->GetPathway());
      //      break;
      //   }
      //   else
      //   {
      //      std::cout << "Mouse on unknown Pathway, Pathway ID: " << hit << std::endl;
      //   }
      //}
   }
   else
   {
      //CoreBase* pFS = FindFloorSpace(hit);
      //std::vector<Park *>::iterator iPark;
      //for (iPark = mParks.begin (); iPark != mParks.end (); iPark++)
      //{
      //   Park* pPark = (*iPark);
      //   Pathway* pPathway = pPark->FindPathway (hit);
      //   if( pPathway )
      //   {
      //      int x = (int)(pPark->GetGhostObject().GetX() / 9);
      //      std::cout << "Mouse on Pathway: " << pPathway->GetPathway() << " Pathway ID: " << hit << std::endl;
      //      mpBuildStrategy->BuildHere(pPark, x, pPathway->GetPathway());
      //      break;
      //   }
      //   else
      //   {
      //      std::cout << "Mouse landed on an unresgister object (BUG)" << " Pathway ID: " << hit  << std::endl;
      //   }
      //}
   }
}

void Scene::HitUp( int hit, Vector2i& Scene )  // taking a mouse hit, send it through geometry to see what we hit
{
   if( mpBuildStrategy && mpBuildStrategy->PlacingRoom() )
   {
      //std::vector<Park *>::iterator iPark;
      //for (iPark = mParks.begin (); iPark != mParks.end (); iPark++)
      //{
      //   Park* pPark = (*iPark);
      //   Pathway* pPathway = pPark->FindPathway (hit);
      //   if( pPathway )
      //   {
      //      int x = (int)(pPark->GetGhostObject().GetX() / 9);
      //      std::cout << "Mouse on Pathway: " << pPathway->GetPathway() << " Pathway ID: " << hit << std::endl;
      //      mpBuildStrategy->BuildHere(pPark, x, pPathway->GetPathway());
      //      break;
      //   }
      //   else
      //   {
      //      std::cout << "Mouse on unknown Pathway, Pathway ID: " << hit << std::endl;
      //   }
      //}
   }
   else
   {
      //CoreBase* pFS = FindFloorSpace(hit);
      //std::vector<Park *>::iterator iPark;
      //for (iPark = mParks.begin (); iPark != mParks.end (); iPark++)
      //{
      //   Park* pPark = (*iPark);
      //   Pathway* pPathway = pPark->FindPathway (hit);
      //   if( pPathway )
      //   {
      //      int x = (int)(pPark->GetGhostObject().GetX() / 9);
      //      std::cout << "Mouse on Pathway: " << pPathway->GetPathway() << " Pathway ID: " << hit << std::endl;
      //      mpBuildStrategy->BuildHere(pPark, x, pPathway->GetPathway());
      //      break;
      //   }
      //   else
      //   {
      //      std::cout << "Mouse landed on an unresgister object (BUG)" << " Pathway ID: " << hit  << std::endl;
      //   }
      //}
   }
}

void Scene::RegisterFloorSpace (int id, CoreBase* pFS)
{
   mFloorSpaces.insert (mFloorSpaces.end(),TypeFloorSpaceMap(id, pFS));
}

void Scene::UnregisterFloorSpace (int id, CoreBase* pFS)
{
   mFloorSpaces.erase (id);
}

CoreBase* Scene::FindFloorSpace (int id)
{
   CoreBase* pFS = NULL;
   try
   {
      TypeFloorSpaceIterator it = mFloorSpaces.find(id);
      if( !(it == mFloorSpaces.end()))
      {
         TypeFloorSpaceMap& FSM = (TypeFloorSpaceMap&)(*it);
         pFS = FSM.second;
      }
   }
   catch(...)
   {
      // find failed
   }

   return pFS;
}
