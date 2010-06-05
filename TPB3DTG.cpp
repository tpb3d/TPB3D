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
// Original code from Extreme Park and Highrise Developer
// By AlabamaCajun, RFrank, crazy2be

#include <iostream>
#include <CEGUI.h>

#include "Graphics/Camera.h"

#include "AI/PeepAgent.h"
//#include "AI/PathAgent.h"
//#include "AI/RiderAgent.h"

#include "CoreObjects/Routes.h"
#include "CoreObjects/Park.h"
#include "Scene/Scene.h"


#include "Window/GUIManager.h"
#include "Scene/SceneEvent.h"
#include "Hub/GameManager.h"


#include "TPB3DTG.h"

void debugprint()
{
   std::cout << "Program exited correctly. Creating trace...\n";
}

int
main ()
{
   atexit(debugprint);
   Camera * cam = Camera::GetInstance ();

   cam->SetSceneSize (Vector2f(1280, 720));
   cam->SetMaxFramerate (60);
   cam->SetActive();
   cam->InitGL();

   Scene theScene;
   Park thePark (1, 10, theScene);
   theScene.AddPark (&thePark);
   GameManager gm(theScene, thePark);
   gm.InitialSetup();

   PeepsAgent People( thePark ); // known Park, later this will be a Park list for mutiple Parks
   sf::String Title( string("Alpha"));

   std::cout << "Basic loading finished....\n";
   try
   {

      SceneEvent SceneEV(&theScene, gm);

      EventHandler Events;
      Interface* pInterface = new Interface(Events);
      GUIManager Gui (Events, *pInterface); //, &thePark);
      Events.Add (&Gui);
      Events.Add (cam);

      MainEvent mev;
      Events.Add(&SceneEV);
      Events.Add (&mev);
      Events.Add (pInterface);

      // Load the test Park
      SceneEV.OnOpen("data/xml/Park.xml");
      //

      std::cout << "Starting event loop...\n";
      int cycle = 0;
      while (mev.IsRunning())
      {
         // This should be here so we can create custom events later,
         // and also so we can create fake events for debugging.
         sf::Event Event;
         while (cam->GetEvent(Event))
         {
            Events.HandleEvents (Event);
         }
         // drawing scope
         cam->Clear ();
         cam->SetActive();
         cam->Integrate (60);
         cam->DrawModel(&theScene); // the background and Park(s).
         cam->DrawInterface( pInterface );
         Gui.Draw ();
         cam->Display ();
         // end drawing scope

         // update scope, thread candidates
         switch( cycle++ )
         {
         case 0:
            theScene.Update (0, pInterface->GetTimeOfDay());
            break;
         case 1:
            pInterface->GetStats().SetPopulation( thePark.GetPopulation() );
            pInterface->Update(10);
            break;
         case 2:
            thePark.Update (5, pInterface->GetTimeOfDay());
            break;

         default:
            static int cc_count = 30; //only once in a while
            if( cc_count < 1 )
            {
               People.Update( 100,pInterface->GetTimeOfDay() );
               cc_count = 20;
            }
            cc_count--;
            cycle = 0;
            break;
         }
         // end update scope
      }
      std::cout << mev.IsRunning() << "\n";
   }
   catch ( GameException* ex )
   {
      std::cout << "Exception caught in main: " << ex->get_Message();
      std::cout << "Hit a key to close!";
      char t[4];
      std::cin.get(t[0]);
   }
   return 0;
}
