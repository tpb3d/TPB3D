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

#include "Graphics/Camera.h"

#include "AI/PeepAgent.h"
//#include "AI/PathAgent.h"
//#include "AI/RiderAgent.h"

#include "CoreObjects/Routes.h"
#include "CoreObjects/Park.h"
#include "Scene/Scene.h"


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
//////////////////////////////////////////
//
// Set up and display Splash Screen
//

  sf::Image SplashScreenImage;      // "Image" is a pixel array in memory
  sf::Sprite SplashScreenSprite;    // "Sprite" is a displayable interface to "Image"
  int SplashScreenLeft;            // left side of splash screen on desktop
  int SplashScreenTop;             // top of splash screen on desktop
  int SplashScreenWidth;           // width of splash screen (to be determined by inspecting the image after loading
  int SplashScreenHeight;          // height of splash screen (to be determined by inspecting the image after loading
  sf::Clock SplashScreenClock;      // timer to keep the splash screen displayed for a minumum amount of time

  if (!SplashScreenImage.LoadFromFile("data/splashscreen.png")) // attempt to load the splashscreen (not that the user can change this file
  {
    std::cout << "Unable to load Splash Screen - file not found\n"; // Error...
  }

  SplashScreenWidth = SplashScreenImage.GetWidth();
  SplashScreenHeight = SplashScreenImage.GetHeight();

  // set up a desktop window with render context, etc.
  sf::RenderWindow SplashScreen(sf::VideoMode(SplashScreenWidth,SplashScreenHeight, 32), "", sf::Style::None);

  SplashScreenLeft = (sf::VideoMode::GetDesktopMode().Width - SplashScreenWidth)/2;     // determine left edge based on desktop and image sizes
  SplashScreenTop  = (sf::VideoMode::GetDesktopMode().Height - SplashScreenHeight)/2;   // determine top edge based on desktop and image sizes
  if (SplashScreenLeft < 0) SplashScreenLeft = 0;  // clamp value in case of big image on small desktop
  if (SplashScreenTop  < 0) SplashScreenTop  = 0;  // clamp value in case of big image on small desktop

  SplashScreen.SetPosition(SplashScreenLeft, SplashScreenTop);  // set the window position to be the center of the desktop
  SplashScreenSprite.SetImage(SplashScreenImage);               // associate pixel array ("Image") with rendering class ("Sprite")
  SplashScreen.Draw(SplashScreenSprite);                        // render the image to the splash screen window
  SplashScreen.Display();                                       // we can finally draw it to the desktop!!

  SplashScreenClock.Reset();      // begin timing from this point.

//
//  Splash Screen now displayed
//
//////////////////////////////////////////////

   atexit(debugprint);
   Camera * cam = Camera::GetInstance ();

   cam->SetSceneSize (Vector2f(1280, 720));
   cam->SetMaxFramerate (120);
   cam->SetActive();
   cam->InitGL();

   Scene theScene;
   Park thePark (1, 10, theScene);
   theScene.AddPark (&thePark);
   GameManager gm(theScene, thePark);
   gm.InitialSetup();
   PeepsAgent People( thePark ); // known Park, later this will be a Park list for mutiple Parks
   sf::String Title( string("Alpha"));

   try
   {

      SceneEvent SceneEV(&theScene, gm);

      EventHandler Events;
      Interface* pInterface = new Interface(Events, gm);
      MainEvent mev;

      Events.Add (cam);
      Events.Add(&SceneEV);
      Events.Add (&mev);
      Events.Add (pInterface);

      // Load the test Park
      SceneEV.OnOpen("data/xml/Park.xml");
      //

      //////////////////////////////////////////////////////////////
      //
      //  Minimum time to display Splash Screen
      //
      while (SplashScreenClock.GetElapsedTime() < 2.5)
      {
        // display the splash screen for a minumum amount of time (eg 2.5 seconds)
        // as game initialization time increases due to development, this will likely become redundant.
      }
      SplashScreen.Close(); // Done with the splash screen - close it up and forget it
      //
      //////////////////////////////////////////////////////////////



      std::cout << "Starting event loop...\n";
      int cycle = 0;
      sf::Window* pWindow = cam->GetWindow();
      while (mev.IsRunning())
      {
         // This should be here so we can create custom events later,
         // and also so we can create fake events for debugging.
         sf::Event Event;
         while (pWindow->GetEvent(Event))
         {
            Events.HandleEvents (Event);
         }
         // drawing scope
         cam->Clear ();
         cam->SetActive();
         cam->Integrate (60);
         cam->DrawModel(&theScene); // the background and Park(s).
         cam->DrawInterface( pInterface );
         cam->Display ();

         // end drawing scope

         // update scope, thread candidates
         switch( cycle++ )
         {
         case 0:
            theScene.Update (0, pInterface->GetTimeOfDay());
            break;
         case 4:
            pInterface->GetStats().SetPopulation( thePark.GetPopulation() );
            pInterface->Update(10);
            break;
         case 8:
            thePark.Update (5, pInterface->GetTimeOfDay());
            break;
         case 1:
         case 2:
         case 3:
         case 5:
         case 6:
         case 7:
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
