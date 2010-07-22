#include "KeyNavDelegate.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Types/Virtkeys.h"
#include "../Graphics/ViewObject.h"

KeyNavDelegate::KeyNavDelegate(const char* pszName, Gfx::ViewObject* pParent)
   :  GUIDelegate (pszName, pParent)
//   ,  mrMain (rMain)
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
//      mrMain.Dispatch(nChar);
      break;
   case 'C':
//      mrMain.Dispatch(nChar);
      break;

      // pass throughs for the arrow keys
   case sf::Key::Down:
   case 'S':
      break;
   case sf::Key::Up:
   case 'W':
      break;
   case sf::Key::Right:
   case 'D':
      break;
   case sf::Key::Left:
   case 'A':
      break;
	} // end switch
}

void KeyNavDelegate::OnMouseDown(short ID, Vector2i pointa)
{
}

void KeyNavDelegate::OnMouseUp(short ID, Vector2i pointa)
{
   int iResult = mpParent->Dispatch(ID, pointa);
}
