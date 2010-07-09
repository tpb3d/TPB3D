#include "KeyNavDelegate.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/Virtkeys.h"

KeyNavDelegate::KeyNavDelegate(WindowDelegate& rMain, const char* pszName, Scene* pScene)
   :  WindowDelegate (pszName, pScene)
   ,  mrMain (rMain)
{
}


KeyNavDelegate::~KeyNavDelegate(void)
{
}

void KeyNavDelegate::Dispatch (int nChar)
{
	switch ( nChar ) {
   case sf::Key::Escape:
//      mrMain.PostMessage ( WM_CLOSE );
		break;
   case 'M':
   case 'N':
   case 'n':
      mrMain.Dispatch(nChar);
      break;
   case 'C':
      mrMain.Dispatch(nChar);
      break;

      // pass throughs for the arrow keys
   case VK_DOWN:
   case 'S':
      break;
   case VK_UP:
   case 'W':
      break;
   case VK_RIGHT:
   case 'D':
      break;
   case VK_LEFT:
   case 'A':
      break;
	} // end switch
}
