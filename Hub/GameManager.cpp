
//  --------------------------------------------------------------------
//  Copyright (C)2009 Ralph Daigle, Russ Frank and crazy2be.   All rights reserved.
//  Licensed according to the GPL v3.0
//
//  Skybowl class
//
//  You should have received a copy of the GNU General Public License
//  along with Theme Park Builder 3D The Game.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "../Types/String.h"

#include "../xml/tinyxml/tinyxml.h"
#include "../Physics/MotionPhysics.h"
#include "../Storage/XMLSerializer.h"
#include "../Graphics/Texture.h"

#include "../CoreObjects/Routes.h"
#include "../CoreObjects/Routes.h"
#include "../CoreObjects/CoreBase.h"
#include "../CoreObjects/Park.h"
#include "../CoreObjects/Pathway.h"
#include "../CoreObjects/RouteBase.h"  // (Pathways).
#include "../Builders/TerrainFormer.h"
#include "../Scene/Scene.h"
#include "Event.h"

#include "GameManager.h"
//test
#include "../Graphics/StripMeshObject.h"
#include "../Graphics/ObjectTree.h"
#include "../Graphics/ObjectBase.h"
#include "../Graphics/ObjectNode.h"
#include "../Graphics/Tree.h"
#include "../Graphics/Image.h"
#include "../Builders/TreeFormer.h"
#include "../Builders/TrackFormer.h"
#include "../Builders/FlatRideBuilder.h"
#include "../Builders/RidePartLoader.h"
#include "../CoreObjects/TrackBase.h"
#include "../CoreObjects/Track.h"
#include "../CoreObjects/TrackGuide.h"
#include "../CoreObjects/TrackSection.h"
#include "../CoreObjects/RailCar.h"
#include "../CoreObjects/Ride.h"
#include "../CoreObjects/Lamp.h"
#include "../CoreObjects/Pathway.h"
#include "../CoreObjects/Stall.h"
#include "../CoreObjects/Bench.h"
#include "../SalesObjects/FoodItem.h"
// endtest

GameManager::GameManager (Scene& scene, Park& park)
:  mScene(scene)
,  mPark( park)
{

}

void GameManager::InitialSetup()
{
   //Park* pPark = new Park(1, 10, mScene);
   TerrainFormer TF;
   mScene.SetTerrain (TF.DefaultMesh());
}

bool GameManager::Settings()
{
   return true;
}

bool GameManager::FRCS()
{
   return true;
}

bool GameManager::LoadGame (const char *fileName)
{
   //TiXmlDocument* xml = new TiXmlDocument();
   //xml->LoadFile(fileName);
   //std::cout << "DEBUG: " << xml->Value() << " output: \n";
   //xml->Print();

   //TiXmlNode* pnGame = xml->FirstChild();
   ////std::cout << "DEBUG: Root node: " << nPark->Value() << '\n';
   //if ((!xml->Error()) || pnGame)
   //{
   //   TiXmlNode* pnName = pnGame->FirstChild("name");
   //   TiXmlNode* pnNet = pnGame->FirstChild("net");
   //   TiXmlNode* pnPop = pnGame->FirstChild("population");
   //   TiXmlNode* pnTime = pnGame->FirstChild("time");
   //   // Data needs to be push/pulled through a class attribute
   //   TiXmlNode* pnPark = pnGame->FirstChild("Park");
   //   //std::cout << "DEBUG: Root node: " << nPark->Value() << '\n';
   //   if ((!xml->Error()) || pnPark)
   //   {
   //      Scene::TypeParkIterator it;
   //      Scene::TypeParkVector& Parks = mScene.GetParks();
   //      for( it=Parks.begin(); it!=Parks.end(); it++ )
   //      {
   //         LoadPark(pnPark, (*it));
   //      }
   //   }
   //}
   //else
   //{
   //   std::cout << "WARNING: Failed to load demo Park: " << xml->ErrorDesc() << std::endl
   //             << " row: " << xml->ErrorRow() << " col: " << xml->ErrorCol()
   //             << " id: " << xml->ErrorId() << " file: " << xml->Value() << '\n'
   //             << "DEBUG: File contents (if any): \n";

   //   xml->Print();
   //}
   //delete xml;

   // Test build a tree
   Tree* myTree = new Tree();
   sf::Vector3f pt( 40, 0, 0 );
   TreeFormer tfm( pt, 25 );
   tfm.Generate( myTree,1 );
   ObjectTree& pOTree = mScene.GetPark()->GetTree();
   pOTree.AddNode( myTree);


   // Define paths
   Pathway* pPath1 = new Pathway (Vector3f(-30.0f, 1.0f, 100.0f), mScene.GetPark(), "Stone.png");
   pPath1->Rotate( Vector3f(0, 180, 0) );

   Pathway* pPath2 = new Pathway (Vector3f(-79.0f, 1.0f, 100.0f), mScene.GetPark(), "Stone.png");
   pPath2->Rotate( Vector3f(0, 90, 0) );

   Pathway* pPath3 = new Pathway (Vector3f(-79.0f, 1.0f, 51.0f), mScene.GetPark(), "Stone.png");
   pPath3->Rotate( Vector3f(0, 0, 0) );

   Pathway* pPath4 = new Pathway (Vector3f(-30.0f, 1.0f, 151.0f), mScene.GetPark(), "Stone.png");
   pPath4->Rotate( Vector3f(0, 100, 0) );

   Pathway* pPath5 = new Pathway (Vector3f(-38.5f, 1.0f, 102.0f), mScene.GetPark(), "Stone.png");
   pPath5->Rotate( Vector3f(0, 80, 0) );

   Pathway* pPath6 = new Pathway (Vector3f(-30.0f, 1.0f, 53.0f), mScene.GetPark(), "Stone.png");
   pPath6->Rotate( Vector3f(0, 90, 0) );

   Pathway* pPath7 = new Pathway (Vector3f(-30.0f, 1.0f, 4.0f), mScene.GetPark(), "Stone.png");
   pPath7->Rotate( Vector3f(0, 90, 0) );

   Pathway* pPath8 = new Pathway (Vector3f(-30.0f, 1.0f, 60.0f), mScene.GetPark(), "Stone.png");
   pPath8->Rotate( Vector3f(0, 0, 0) );

   // Connect paths
   mScene.GetPark()->GetEntrance()->AddConnection (pPath1); // connect the entrance to the paths
   pPath1->AddConnection (pPath2);
   pPath2->AddConnection (pPath1);

   pPath2->AddConnection (pPath3);
   pPath3->AddConnection (pPath2);

   pPath3->AddConnection (pPath4);
   pPath4->AddConnection (pPath3);

   pPath4->AddConnection (pPath5);
   pPath5->AddConnection (pPath4);

   pPath5->AddConnection (pPath6);
   pPath6->AddConnection (pPath5);

   pPath6->AddConnection (pPath7);
   pPath6->AddConnection (pPath8);
   pPath7->AddConnection (pPath6);

   // Add paths to the park collection
   mScene.GetPark()->AddPath(pPath1);
   mScene.GetPark()->AddPath(pPath2);
   mScene.GetPark()->AddPath(pPath3);
   mScene.GetPark()->AddPath(pPath4);
   mScene.GetPark()->AddPath(pPath5);
   mScene.GetPark()->AddPath(pPath6);
   mScene.GetPark()->AddPath(pPath7);
   mScene.GetPark()->AddPath(pPath8);

   // Render paths
   pOTree.AddNode (pPath1->GetGraphic());
   pOTree.AddNode (pPath2->GetGraphic());
   pOTree.AddNode (pPath3->GetGraphic());
   pOTree.AddNode (pPath4->GetGraphic());
   pOTree.AddNode (pPath5->GetGraphic());
   pOTree.AddNode (pPath6->GetGraphic());
   pOTree.AddNode (pPath7->GetGraphic());
   pOTree.AddNode (pPath8->GetGraphic());

   PartCorrection corr;
   RidePartLoader rpl (corr);
   ObjectNode* pTempTree = new ObjectNode(0, 33);
   const char* pszFile = "restroom01.3ds";
   const char* pszPath = "data/Restroom 01/";
   rpl.Load3ds( pszPath, pszFile, pTempTree );
   //pOTree.AddNode (pTempTree);
   // Can't add the restroon, not yet a part object, just a graphic

   float fSTLoc[4] = { -31,0.5,25,0 };
   float fRot[4] = { 0,270,0,0 };
   corr.frx = 1.0f/18; // inches to feet
   corr.SetLocation (fSTLoc);
   corr.SetRotation (fRot);
   Stall* pStall = new Stall(1,41, ST_Food);
   mScene.GetPark()->AddStall (pStall);
   const char* pszFileStall = "stall.3DS";
   const char* pszPathStall = "data/Building/";
   pTempTree = new ObjectNode(0, 33);
   rpl.Load3ds( pszPathStall, pszFileStall, pTempTree );
   pStall->SetGraphic (pTempTree);
   pStall->AddItem (FoodItem::Create ("Deluxe Pizza", 4, 1));
   pStall->AddItem (FoodItem::Create ("Cheese Pizza", 1, 1));
   pStall->AddItem (FoodItem::Create ("Burger", 3, 1));
   pStall->AddItem (FoodItem::Create ("Chicken Sandwich", 5, 1));
   pPath5->AddConnection (pStall->GetQueue());  // "Stall" is now on the path

   //float fTALoc[4] = { 24,1,40,0 };
   //float fTARot[4] = { 0,0,0,0 };
   //corr.frx = 1.0f;
   //corr.SetRotation (fTARot);
   //corr.SetLocation (fTALoc);
   //pTempTree = new ObjectNode(0, 39);
   //const char* pszFileB = "JMORendered.3ds";
   //const char* pszPathB = "data/Building/";
   //rpl.Load3ds( pszPathB, pszFileB, pTempTree );
   //pOTree.AddNode (pTempTree);

   Lamp* pLamp = new Lamp(8, "SteamPunkLamp.png", "LightParticle1.png");
   float fLoc[] = { -10, 0.1f, 15};
   pLamp->Render();
   pLamp->Move (fLoc);
   pOTree.AddNode (pLamp);


   // Park Bench
   ObjectNode* pbench = new ObjectNode(0, 36);

   const char* pszFileBench = "bench01.3ds";
   const char* pszPathBench = "data/Benches/";
   rpl.Load3ds( pszPathBench, pszFileBench, pbench );

   Bench *bench = new Bench(pbench, pPath5, 20, Bench::IH_Left,  2);
   pOTree.AddNode ( bench->GetGraphic() );

   Bench *bench2 = new Bench(pbench, pPath5, 30, Bench::IH_Right,  2);
   pOTree.AddNode ( bench2->GetGraphic() );

   Bench *bench3 = new Bench(pbench, pPath2, 30, Bench::IH_Right,  2);
   pOTree.AddNode ( bench3->GetGraphic() );

   Bench *bench4 = new Bench(pbench, pPath1, 20, Bench::IH_Left,  2);
   pOTree.AddNode ( bench4->GetGraphic() );

   Bench *bench5 = new Bench(pbench, pPath7, 25, Bench::IH_Left,  2);
   pOTree.AddNode ( bench5->GetGraphic() );

   Bench *bench6 = new Bench(pbench, pPath4, 8, Bench::IH_Left,  2);
   pOTree.AddNode ( bench6->GetGraphic() );

   Bench *bench7 = new Bench(pbench, pPath3, 40, Bench::IH_Left,  2);
   pOTree.AddNode ( bench7->GetGraphic() );


   // test build coaster track
   Texture* pTex = Gfx::ImageManager::GetInstance()->GetTexture("ref1.png",3);
   TrackFormer TF(pTex, mPark);
   Track* pTrack = TrackFormer::CreateTrack();
   TrackGuide guide;
   guide.fCurAngleY = 180;
   guide.fCurAngleZ = 0;
   guide.fTubeRadius = 0.4f;
   guide.fRailRadius = 0.2f;
   guide.fTrackGauge = 2;
   guide.SetRailShape (7);
   guide.point.Set (40,8, 80);

   guide.SetupStraight( 20, 0 ); // station
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch (-20, 6, 0);
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch ( 20, 6, 0);
   TF.MakeSection (guide, *pTrack);

   guide.SetupStraight( 10, 10 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupTurn( -45, 9, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 10, -20 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupTurn( 45, 9, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 10, 10 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch( 20, 6, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 6, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch ( -40, 8, 0);
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 6, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch ( 20, 6, -20);
   TF.MakeSection (guide, *pTrack);
   guide.SetupTurn (180, 30, 0);
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 15, 20 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch( 20, 6, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 4, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch ( -40, 8, 0);
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 4, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch ( 20, 6, 0);
   TF.MakeSection (guide, *pTrack);
   guide.SetupStraight( 89, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupTurn( 180, 23.48, 0 );
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch ( 20, 6, 0);
   TF.MakeSection (guide, *pTrack);
   guide.SetupPitch (-20, 6, 0);
   TF.MakeSection (guide, *pTrack);

   pOTree.AddNode (pTrack);
   RailCar* pCar = new RailCar( sf::Vector3f( 4, 1.8f, 6 ), 8, 599 );
   Ride* pCarRide = new Ride(Vector3f(0,0,0), mPark);
   pOTree.AddNode ( new RidePack (pCarRide));
   pCarRide->SetNode (pCar);
   pCar->Default();
   mPark.mpCar = pCar;

   FlatRideBuilder flat;

   Ride* pRide;
   float fx = 0;
   float fz = 40;
   pRide = flat.CreateRide(FlatRideBuilder::Biplanes, mPark );
   pRide->SetPosition (fx,0.1f,fz);
   mScene.GetPark()->AddRide (pRide);
   pPath4->AddConnection (pRide->GetQueue());   // join the "Barn Stormers" to the path4


   //pRide = flat.CreateRide(FlatRideBuilder::Carousel, mPark);
   //pRide->SetPosition (fx-20,1, fz+10);
   //mScene.GetPark()->AddRide (pRide);
   //
   //pRide = flat.CreateRide(FlatRideBuilder::BasketRide, mPark);
   //pRide->SetPosition (fx,1, fz+40);
   //mScene.GetPark()->AddRide (pRide);

   pRide = flat.CreateRide(FlatRideBuilder::Polyp, mPark);  // polyp
   pRide->SetPosition (fx,1, fz-50);
   mScene.GetPark()->AddRide (pRide);

   pRide = flat.CreateRide(FlatRideBuilder::Octopus, mPark);  // Cephalopod octo
   pRide->SetPosition (fx,1, fz-70);
   mScene.GetPark()->AddRide (pRide);

   pRide = flat.CreateRide(FlatRideBuilder::Scrambler, mPark);
   pRide->SetPosition (fx,1, fz-100);
   mScene.GetPark()->AddRide (pRide);

//   float fHRLoc[4] = { 10,-60,-40,0 };
//   float fTARot[4] = { 0,0,0,0 };
//   corr.frx = 5.0f;
//   corr.SetLocation (fHRLoc);
//   corr.SetRotation (fTARot);
//   const char* pHT = "hrtwr.3ds";
//   const char* pHT2 = "data/HighRide/";
//   rpl.Load3ds( pHT2, pHT );

   //const char* pFC5A = "gondola.3ds";
   //const char* pFC5B = "data/Flyncircusride/5-Gondola/";
   //rpl.Load3ds( pFC5B, pFC5A, );

   SaveGame("data/xml/Park.xml");

   return true;
}

void GameManager::Add( TiXmlNode* pnElement, const char* szTag, const char* szText)
{
   TiXmlElement* pnXPos = new TiXmlElement(szTag);
   pnXPos->LinkEndChild (new TiXmlText( szText ));
   pnElement->LinkEndChild(pnXPos);
}

bool GameManager::SaveGame(const char *fileName)
{
   TiXmlDocument* pDoc = new TiXmlDocument( fileName );
   TiXmlNode* pnRoot = new TiXmlElement("ExtremePark");
//   mPark->Save(pRoot);
   TiXmlElement* pnPark = new TiXmlElement("Park");

   pDoc->LinkEndChild (pnRoot);

   int net = 100000;
   int pop = 1;
   int time = (int)(12.5*60);  // 12:30

   Add( pnRoot, "name","Park One");
   Add( pnRoot, "net",ToString (net).c_str());
   Add( pnRoot, "population", ToString (time).c_str());

   pnRoot->LinkEndChild (pnPark);

   Scene::TypeParkIterator it;
   Scene::TypeParkVector& Parks = mScene.GetParks();
   for( it=Parks.begin(); it!=Parks.end(); it++ )
   {
      SavePark( pnPark, (*it) );
   }

   std::cout << "DEBUG: Output of save attempt: \n";
   pDoc->Print();
   pDoc->SaveFile();
   return true;
}

bool GameManager::LoadPark(TiXmlNode* pnPark, Park* pPark)
{

   // Iterate through the Park

   std::cout << "DEBUG: Loading Park...\n" << pnPark->Value() << "  " << pnPark << '\n';
   //TiXmlDocument* nDoc = nPark->Parent()->ToDocument();
   //std::cout << "DEBUG: xml output:\n";
   //nPark->P->Print();
   TiXmlNode* pnPathway = pnPark->FirstChild("Pathway");
   std::cout << "DEBUG: Pathway node is " << pnPathway << std::endl;
   if (!pnPathway) return false;

   //for (; pnPathway; pnPathway = pnPathway->NextSibling("Pathway"))
   //{
   //   std::cout << "DEBUG: Loading Pathway... (" << pnPathway << ")\n";
   //   TiXmlNode* pnPathwayType = pnPathway->FirstChild("type");
   //   TiXmlNode* pnStart = pnPathway->FirstChild("xstart");
   //   TiXmlNode* pnEnd = pnPathway->FirstChild("xend");
   //   TiXmlNode* pnPathwayNo = pnPathway->FirstChild("Pathway");
   //   std::cout << "DEBUG: Loaded basic nodes..." << std::endl;
   //   int Pathwayno;
   //   if (pnStart && pnEnd && pnPathwayNo && pnPathwayType)
   //   {
   //      std::string PathwayType = pnPathwayType->FirstChild()->Value();
   //      int XStart = FromString<int>(pnStart->FirstChild()->Value());
   //      int XEnd = FromString<int>(pnEnd->FirstChild()->Value());
   //      Pathwayno = FromString<int>(pnPathwayNo->FirstChild()->Value());
   //      Pathway* pPathway = NULL;
   //      if( Pathwayno < 1 )
   //      {
   //         pPathway = pPark->GetPathway(Pathwayno);
   //      }
   //      else
   //      {
   //         // use Pathwaytype here to pick up sky Pathways etc
   //         pPathway = pPark->NewPathway(XStart, Pathwayno, XEnd);
   //      }

   //      for (TiXmlNode* pnRoom = pnPathway->FirstChild("room"); pnRoom != 0; pnRoom = pnRoom->NextSibling("room"))
   //      {
   //         TiXmlNode* pnType = pnRoom->FirstChild("type");
   //         TiXmlNode* pnXPos = pnRoom->FirstChild("xpos");
   //         TiXmlNode* pnXEnd = pnRoom->FirstChild("xend");
   //         TiXmlNode* pnState = pnRoom->FirstChild("state");

   //         if (pnType && pnXPos && pnState)
   //         {
   //            int State = (pnState) ? FromString<int>(pnState->FirstChild()->Value()) : 0;
   //            std::string Type = pnType->FirstChild()->Value();
   //            int XPos = FromString<int>(pnXPos->FirstChild()->Value());
   //            int XEnd = 0;
   //            std::cout << "Loading room. " << Type << " " << XPos << " " << State << std::endl;
   //            if( pnXEnd!= NULL)
   //            {
   //               XEnd = FromString<int>(pnXEnd->FirstChild()->Value());
   //            }
               // Need a better way to do this...
               //ObjectBase* pRoom = NULL;
               //if (Type == "Building")
               //{
               //   pRoom = new Building(XPos, Pathwayno, pPark);
               //   pPark->GetPathway(Pathwayno)->AddFloorSpace(pRoom);
               //}
               //else if (Type == "apartment")
               //{
               //   pRoom = new Apartment(XPos, Pathwayno, pPark);
               //   pPark->GetPathway(Pathwayno)->AddFloorSpace(pRoom);
               //}
               //else if (Type == "skylobby")
               //{
               //   pRoom = new SkyLobby(XPos, XEnd, Pathwayno, pPark);
               //   pPark->GetPathway(Pathwayno)->AddFloorSpace(pRoom);
               //}
               //else
               //{
               //   std::cout << "WARNING: " << Type << " is an invalid room type!\n";
               //}
      //         std::cout << "DEBUG: New " << Type << " on floor " << Pathwayno << " (position " << XPos << ")\n";
      //      }
      //   }
      //}
      //else
      //{
      //   std::cout << "WARNING: Failed to load Pathway " << Pathwayno << ", could not find xstart or xend node.\n";
      //}
      //std::cout << "DEBUG: finished loading Pathway " << Pathwayno << '\n';
   //}
   std::cout << "DEBUG: finished loading Park...\n";
   return true;
}

bool GameManager::SavePark(TiXmlElement* pnPark, Park* pPark)
{
   //Park::PathwayIterator it;
   ObjectTree& theTree = pPark->GetTree();     // Lobby is at mNo_SubPathways not zero

   TiXmlElement* pnTree = new TiXmlElement("Park");
   XMLSerializer xmlPathway( pnTree );
   theTree.Save( xmlPathway );
   pnPark->LinkEndChild(pnTree);

   //Pathway::FloorMap& fps = pPathway->GetFloorSpaces();
   //for (unsigned int i = 0; i < fps.size(); i++)
   //{
   //   TiXmlElement* pnSpace = new TiXmlElement("room");
   //   XMLSerializer xmlRoom(pnSpace);
   //   fps[i]->Save( xmlRoom );
   //   pnPathway->LinkEndChild(pnSpace);
   //}
   //Routes::RoutesVector& routes = pPark->GetRouteList();
   //Routes::RouteIterator iR;
   //for (iR=routes.begin(); iR!=routes.end(); iR++)
   //{
   //   TiXmlElement* pnEle = new TiXmlElement("elevator");
   //   RouteBase* pR = *(iR);
   //   XMLSerializer xmlEle( pnEle );
   //   pR->Save( xmlEle );
   //   pnPark->LinkEndChild(pnEle);
   //}
   return true;
}

/*
void GameManager::LoadRide()
{
   static char BASED_CODE szFilter[] = "3D Studio Files (*.3DS)|*.3DS|ASE Files (*.ase)|*.ase|Milk Shape (*.ms3d)|*.ms3d|Model Files|*.ASE,*.3DS,*.MS3D||";

   CFileDialog dlgOpen( true, "3DS","*.3DS", OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilter, 0 );
   if( dlgOpen.DoModal() == IDOK )
   {
      if( !m_pTree )
      {
         m_pTree = new CObjectTree( 40 );//90 );
      }
      CRidePartLoader rpl( m_pTree );
      size_t slen = strlen( dlgOpen.m_pOFN->lpstrFile );
      if( slen > 3 )
      {
         if( _strnicmp( &dlgOpen.m_pOFN->lpstrFile[slen-3], "ASE", 3 ) == 0 )
         {
            rpl.LoadASE( dlgOpen.m_pOFN->lpstrFile );
         }
         else if( _strnicmp( &dlgOpen.m_pOFN->lpstrFile[slen-4], "MS3D", 4 ) == 0 )
         {
            rpl.LoadMS3D( dlgOpen.m_pOFN->lpstrFile );
         }
         else
         {
            rpl.Load3ds( dlgOpen.m_pOFN->lpstrFile );
         }
      }

      CObjectNode* pNodeSel = m_pTree->GetNode(0);
      //CObjectPlacementDlg opDlg;
      //INT_PTR dr = opDlg.DoModal();
      //if( dr == IDOK )
      //{
      //   float fRotate[3] = { 0,0,0 };
      //   fRotate[1] = (float)opDlg.GetYRotation();
      //   pNodeSel->SetRotation( fRotate );
      //}
      bool bChildren = true;
      while( bChildren )
      {
         if( dlgOpen.DoModal() == IDOK )
         {
            CRidePartLoader rpl1( m_pTree );
            size_t slen = strlen( dlgOpen.m_pOFN->lpstrFile );
            if( slen > 3 )
            {
               if( _strnicmp( &dlgOpen.m_pOFN->lpstrFile[slen-3], "ASE", 3 ) == 0 )
               {
                  rpl1.LoadASE( dlgOpen.m_pOFN->lpstrFile );
               }
               else
               {
                  rpl1.Load3ds( dlgOpen.m_pOFN->lpstrFile, 0 );
               }
            }
            CObjectPlacementDlg opDlg;
            INT_PTR dr = opDlg.DoModal();
            if( dr == IDOK )
            {
               float fRotate[3] = { 0,0,-10 };
               float fMove[3] = { 13.10f ,0, -0.5f };
               fRotate[1] = (float)opDlg.GetYRotation();
               CObjectNode* pNode1 = pNodeSel->GetNode(0);
               pNode1->SetRotation( fRotate );
               pNode1->Move( fMove );
            }
         }
         else
         {
            bChildren = false;
         }
      }
   }
}
*/
